/*****************************************************************************
 * Copyright (C) 2009-2016   this file is part of the NPTool Project         *
 *                                                                           *
 * For the licensing terms see $NPTOOL/Licence/NPTool_Licence                *
 * For the list of contributors see $NPTOOL/Licence/Contributors             *
 *****************************************************************************/

/*****************************************************************************
 * Original Author: Pierre MORFOUACE  contact address: morfouac@nscl.msu.edu       *
 *                                                                           *
 * Creation Date  : April 2016                                             *
 * Last update    :                                                          *
 *---------------------------------------------------------------------------*
 * Decription:                                                               *
 *  This event Generator is used to simulated MultipleParticle ion Source           *
 *  Very usefull to figure out Geometric Efficacity of experimental Set-Up   *
 *---------------------------------------------------------------------------*
 * Comment:                                                                  *
 *                                                                           *
 *                                                                           *
 *****************************************************************************/
// C++
#include <limits>
#include <ctime>
#include <cstdlib>

// G4 headers
#include "G4ParticleTable.hh"
#include "G4IonTable.hh"
// G4 headers including CLHEP headers
// for generating random numbers
#include "Randomize.hh"

// NPS headers
#include "EventGeneratorViola.hh"

// NPl headers
#include "RootOutput.h"
#include "NPNucleus.h"
#include "NPOptionManager.h"


#define amupernucleon 931.49402 // MeV/c^2
const double c = 3.0; // mm/s

using namespace CLHEP;


EventGeneratorViola::EventGeneratorViola(){
	// NPTool path
	string GlobalPath = getenv("NPTOOL");
	string StandardPath = GlobalPath + "/Inputs/EventGenerator/";
	m_ParticleStack = ParticleStack::getInstance();

	m_projectile	= "";
	m_target 	= "";
	m_beamEnergy	= 0.0;
	m_fitPath 	= "";

}



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
EventGeneratorViola::~EventGeneratorViola(){
	delete EventGeneratorViola::IsotopeTable;
}



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void EventGeneratorViola::ReadConfiguration(NPL::InputParser parser){
	vector<NPL::InputBlock*> blocks = parser.GetAllBlocksWithToken("ViolaFission");
	if(NPOptionManager::getInstance()->GetVerboseLevel()){
		cout << endl << "\033[1;35m//// ViolaFission token found " << endl;
	}
	    
	std::vector<std::string> tokens = {"projectile", "target", "fitPath"};
	    
	for(unsigned int i = 0 ; i < blocks.size() ; i++){
		blocks[i]->Dump(); // turn this off later
		if(blocks[i]->HasTokenList(tokens)){
			m_projectile 	= blocks[i]->GetString("projectile");
			m_target 	= blocks[i]->GetString("target");
			m_fitPath 	= blocks[i]->GetString("fitPath");
			if (gSystem->AccessPathName(m_fitPath.c_str())){ // returns 1 if file does not exist
				std::cout << "ERROR: fitPath " << m_fitPath << " does not exist." << std::endl;
				exit(1);
			}
			m_beamEnergy 	= blocks[i]->GetDouble("beamEnergy", "MeV");

		}
		else{
			cout << "ERROR: check your input file formatting \033[0m" << endl;
			exit(1);
		}
	}



	// ISOTOPE LOOK UP TABLE INSTANTIATION, THX MARSHALL :)
	std::string ame20parserpath = "/mnt/simulations/hira/Sam/nptool/NPSimulation/EventGenerator/ame20_parser/mass_1.mas20";
	EventGeneratorViola::IsotopeTable = new MassEval2020(ame20parserpath);

	// Fetch A/Z values for projectile and target
	std::pair<int, int> projectileAZ = IsotopeTable->GetIsotopeNZGeant(m_projectile);
	EventGeneratorViola::projectileZ = std::get<1>(projectileAZ);
	EventGeneratorViola::projectileA = std::get<0>(projectileAZ) + EventGeneratorViola::projectileZ;

	std::pair<int, int> targetAZ	= IsotopeTable->GetIsotopeNZGeant(m_target);
	EventGeneratorViola::targetZ 	= std::get<1>(targetAZ);
	EventGeneratorViola::targetA 	= std::get<0>(targetAZ) + EventGeneratorViola::targetZ;

	EventGeneratorViola::totalZ 	= EventGeneratorViola::targetZ + EventGeneratorViola::projectileZ;
	EventGeneratorViola::totalA 	= EventGeneratorViola::targetA + EventGeneratorViola::projectileA;

	// Calculating center of mass lorentz vector parameters for boosting later
	double beamMass 	= EventGeneratorViola::projectileA*amupernucleon; // MeV/c^2
	double targetMass 	= EventGeneratorViola::targetA*amupernucleon; // MeV/c^2
	double beamKinetic 	= EventGeneratorViola::projectileA*m_beamEnergy; // MeV
	double totalSystemEnergy= beamKinetic + beamMass + targetMass; // MeV
	double beamMomentum	= sqrt(std::pow((beamKinetic + beamMass), 2.0) - std::pow(beamMass, 2.0)); // MeV/c

	EventGeneratorViola::beta = beamMomentum/totalSystemEnergy;
	EventGeneratorViola::gamma = 1.0/sqrt(1.0 - std::pow(EventGeneratorViola::beta, 2.0));


	// Fetching fit data for event generation
	// All fits are fetched, but only fissionFit is used. Viola systematics do not apply to elastic scattering
	TFile* fitFile = TFile::Open(m_fitPath.c_str(), "READ");
	EventGeneratorViola::beamElasticFit = (TF1*)fitFile->Get("beamElasticFit");
	EventGeneratorViola::targetElasticFit = (TF1*)fitFile->Get("targetElasticFit");
	EventGeneratorViola::fissionFit = (TF1*)fitFile->Get("fissionFit");

	if ((EventGeneratorViola::beamElasticFit == nullptr) || (EventGeneratorViola::targetElasticFit == nullptr) || (EventGeneratorViola::fissionFit == nullptr)){
		std::cout << "ERROR: one or more of the fits in " << m_fitPath << " does not exist. Check your fitPath file." << std::endl;
		exit(1);
	}

	fitFile->Close();
	delete fitFile; // I don't think we need this???


	// Now we set the isobaric chain histogram
	std::map<std::pair<int, int>, long double> MassTab = EventGeneratorViola::IsotopeTable->FetchMassTab();
	EventGeneratorViola::isobaricHist = new TH2I("isobaricHist", "", 295, 0, 295, 295, 0, 118);
	for (std::map<std::pair<int, int>, long double>::iterator it = MassTab.begin(); it != MassTab.end(); it++){
		int N = std::get<0>(it->first);
		int Z = std::get<1>(it->first);
		int A = N + Z;
		EventGeneratorViola::isobaricHist->Fill(A, Z);
	}
}



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void EventGeneratorViola::GenerateEvent(G4Event*){
	int frag1A = EventGeneratorViola::totalA*EventGeneratorViola::fissionFit->GetRandom();

	// Constructing 
	int frag2A = EventGeneratorViola::totalA - frag1A;

	std::vector<int> isobarsFrag1;
	std::vector<int> isobarsFrag2;
	// Iterate through isobaricHist until all Z are collected
	for (int i=1; i < EventGeneratorViola::isobaricHist->GetNbinsX(); i++){
		int AValue = ((TAxis*)EventGeneratorViola::isobaricHist->GetXaxis())->GetBinCenter(i);
		if ((AValue == frag1A) && (isobarsFrag1.size() == 0)){
			for (int j=1; j < EventGeneratorViola::isobaricHist->GetNbinsY(); j++){
				if (EventGeneratorViola::isobaricHist->GetBinContent(i, j) != 0){
					int ZValue = ((TAxis*)EventGeneratorViola::isobaricHist->GetYaxis())->GetBinCenter(j);
					isobarsFrag1.push_back(ZValue);
				}
			}
		}
		if ((AValue == frag2A) && (isobarsFrag2.size() == 0)){
			for (int j=1; j < EventGeneratorViola::isobaricHist->GetNbinsY(); j++){
				if (EventGeneratorViola::isobaricHist->GetBinContent(i, j) != 0){
					int ZValue = ((TAxis*)EventGeneratorViola::isobaricHist->GetYaxis())->GetBinCenter(j);
					isobarsFrag2.push_back(ZValue);
				}
			}
		}
		if ((isobarsFrag1.size() != 0) && (isobarsFrag2.size() != 0)){
			break;
		}
	}

	// Randomly choose a Z value from the isobaric list, now we have fragment1 !
	std::random_device rd;

	std::shuffle(isobarsFrag1.begin(), isobarsFrag1.end(), rd);
	int frag1Z = isobarsFrag1[0]; 

	std::shuffle(isobarsFrag2.begin(), isobarsFrag2.end(), rd);
	int frag2Z = isobarsFrag2[0];



	// Need to check these for existence - easily done by checking if frag1/2-A/Z are NULL
	m_fragment1 = G4ParticleTable::GetParticleTable()->GetIonTable()->GetIon(frag1Z, frag1A, 0);
	m_fragment2 = G4ParticleTable::GetParticleTable()->GetIonTable()->GetIon(frag2Z, frag2A, 0);


	// Assuming you check for the existence of the particles, we proceed with propagation
	// Fragment1 is set to a random orientation. An angle (0, pi] is chosen. A vector for fragment 2 is calculated.
	double rand1X = RandFlat::shoot(-1.0, 1.0); 
	double rand1Y = RandFlat::shoot(-1.0, 1.0);
	double rand1Z = RandFlat::shoot(-1.0, 1.0);
	double norm1 = sqrt(std::pow(rand1X, 2.0) + std::pow(rand1Y, 2.0) + std::pow(rand1Z, 2.0));  
	G4ThreeVector frag1Dir(rand1X, rand1Y, rand1Z);
	frag1Dir *= 1.0/norm1;

	// Assuming you check for the existence of the particles, we proceed with propagation
	// Fragment1 is set to a random orientation. An angle (0, pi] is chosen. A vector for fragment 2 is calculated.
	double rand2X = RandFlat::shoot(-1.0, 1.0); 
	double rand2Y = RandFlat::shoot(-1.0, 1.0);
	double rand2Z = RandFlat::shoot(-1.0, 1.0);
	double norm2 = sqrt(std::pow(rand2X, 2.0) + std::pow(rand2Y, 2.0) + std::pow(rand2Z, 2.0));  
	G4ThreeVector frag2Dir(rand2X, rand2Y, rand2Z);
	frag2Dir *= 1.0/norm2;
	
	
	// Progress - 1/28/25
	// From https://journals.aps.org/prc/pdf/10.1103/PhysRevC.31.1550
	// Total kinetic energy release via Viola
	double slopeValue = 0.1189*RandFlat::shoot(-0.0011, 0.0011);
	double offSet 	= 7.30 + RandFlat::shoot(-1.5, 1.5);
	double totalT = slopeValue*std::pow(EventGeneratorViola::totalZ, 2.0)/std::pow(EventGeneratorViola::totalA, 1.0/3.0);
	totalT += offSet; // MeV

	// Assuming an even kinetic energy split
	double frag1T = totalT/2.0;
	double frag2T = totalT/2.0;


	// Momentum calculated in the center of mass frame
	double frag1totalE = frag1A*amupernucleon + frag1T;
	double frag1Mom = sqrt(std::pow(frag1totalE, 2.0) - std::pow(frag1A*amupernucleon, 2.0));

	double frag2totalE = frag2A*amupernucleon + frag2T;
	double frag2Mom = sqrt(std::pow(frag2totalE, 2.0) - std::pow(frag2A*amupernucleon, 2.0));

	// Updaing momentum vectors
	frag1Dir *= frag1Mom;
	frag2Dir *= frag2Mom;


	// Boosting into the lab frame
	double frag1_LabPZ = frag1totalE*EventGeneratorViola::beta*EventGeneratorViola::gamma + EventGeneratorViola::gamma*frag1Dir.getZ();
	frag1Dir.setZ(frag1_LabPZ);

	double frag2_LabPZ = frag2totalE*EventGeneratorViola::beta*EventGeneratorViola::gamma + EventGeneratorViola::gamma*frag2Dir.getZ();
	frag2Dir.setZ(frag2_LabPZ);


	// Calculating lab frame kinetic energy
	double frag1_LabT = (sqrt(std::pow(frag1Dir.mag(), 2.0) + std::pow(frag1A*amupernucleon, 2.0)) - frag1A*amupernucleon);
	double frag2_LabT = (sqrt(std::pow(frag2Dir.mag(), 2.0) + std::pow(frag2A*amupernucleon, 2.0)) - frag2A*amupernucleon);

		
	// Finalizing direction vectors / creating position vectors
	frag1Dir *= 1.0/frag1Dir.mag();
	frag2Dir *= 1.0/frag2Dir.mag();

	G4ThreeVector frag1Pos(0.0, 0.0, 0.0);
	G4ThreeVector frag2Pos(0.0, 0.0, 0.0);


		
	// Particle class constructor - direction must be a unit vector (derived from momenta)
	// *** Particle(particleDef, thetaCM, kineticEnergy, direction, position) ***
	// ThetaCM does nothing?? Also start each fragment from the origin who cares

	NPS::Particle fragment1(m_fragment1, 0.0, frag1_LabT, frag1Dir, frag1Pos);
       	m_ParticleStack->AddParticleToStack(fragment1);

	NPS::Particle fragment2(m_fragment2, 0.0, frag2_LabT, frag2Dir, frag2Pos);
       	m_ParticleStack->AddParticleToStack(fragment2);
    
}



//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
void EventGeneratorViola::InitializeRootOutput(){}



