/*****************************************************************************
 * Copyright (C) 2009-2024   this file is part of the NPTool Project       *
 *                                                                           *
 * For the licensing terms see $NPTOOL/Licence/NPTool_Licence                *
 * For the list of contributors see $NPTOOL/Licence/Contributors             *
 *****************************************************************************/

/***************************************************************************** * Original Author: Sachet Jain  contact address: jainsach@msu.edu                        *
 *                                                                           *
 * Creation Date  : October 2024                                           *
 * Last update    :                                                          *
 *---------------------------------------------------------------------------*
 * Decription:                                                               *
 *  This class describe  CUBE simulation                             *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Comment:                                                                  *
 *                                                                           *
 *****************************************************************************/

// C++ headers
#include <sstream>
#include <cmath>
#include <limits>
//G4 Geometry object
#include "G4Tubs.hh"
#include "G4Box.hh"

//G4 sensitive
#include "G4SDManager.hh"
#include "G4MultiFunctionalDetector.hh"

//G4 various object
#include "G4AssemblyVolume.hh"
#include "G4Material.hh"
#include "G4Transform3D.hh"
#include "G4PVPlacement.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"
#include "G4RotationMatrix.hh"
#include "G4SystemOfUnits.hh"
#include "G4NistManager.hh"
#include "G4Box.hh"
#include "G4LogicalVolume.hh"
#include "G4ThreeVector.hh"
#include "globals.hh"

// NPTool header
#include "CUBE.hh"
//#include "CalorimeterScorers.hh"
#include "CUBEGasScorers.hh"
#include "InteractionScorers.hh"
#include "RootOutput.h"
#include "MaterialManager.hh"
#include "NPSDetectorFactory.hh"
#include "NPOptionManager.h"
#include "NPSHitsMap.hh"

// CLHEP header
#include "CLHEP/Random/RandGauss.h"

using namespace std;
using namespace CLHEP;

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
namespace CUBE_NS{
	// Energy and time Resolution
	const double EnergyThreshold 	= 0.1*MeV;
	const double ResoEnergy 	= 1.0*MeV ;

	// Timing resolution!! Very important!
	const double ResoTime 		= 1.0*ns ;

	// Position resolution
	const double ResoXPos 		= 0.5*mm;
	const double ResoYPos 		= 0.5*mm;
	const double ResoZPos 		= 0.5*mm;

	// CUBE geometry parameters
	const double halfWidth 		= 139.5 * mm;
	const double halfHeight 	= 178.5 * mm;
	const double thickness 		= 0.25 * cm;
	const double frameThickness 	= 0.5 * mm;
	const double frameDepth 	= 0.25 * mm;

	// Creating material manager
	G4NistManager* nist 	= G4NistManager::Instance();
	G4Material* gasMaterial = nist->FindOrBuildMaterial("G4_He");

	// 5/25/25 - making 10 torr isobutane
	G4Element* elH = nist->FindOrBuildElement("H");
	G4Element* elC = nist->FindOrBuildElement("C");
	// Assume room temperature conditions 
	// Ideal gas 
	// Calculate mol/L --> convert to g/cm^3

	double pressure = 10.0; // torr
	double gasConstant = 0.08206;
	double temperature = 293.15; // Kelvin - room temperature
	double molarMass = 58.12; // g/mol
	G4Material* isobutane;

}
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
// CUBE Specific Method

// Destruction of variables here isn't necessary - 
// Geant's garbage collection HAS to handle that for us or else shit breaks
CUBE::CUBE(){
	// Setting gas visualization settings
	CUBE::visualizeGasSettings = new G4VisAttributes(G4Colour(0.376, 0.796, 0.431, 0.85));

	// Consructing read out settings 
	CUBE::m_Event = new TCUBEData();
	CUBE::m_CUBEScorer = 0;

	// 5/25/25 - making 10 torr isobutane! 
	double isobutaneDensity = ((CUBE_NS::pressure/760.0)*CUBE_NS::molarMass)/(CUBE_NS::gasConstant*CUBE_NS::temperature);
	isobutaneDensity /= 1000.0; // conversion from g/L --> g/cm3
	CUBE_NS::isobutane = new G4Material("ISOBUTANE", isobutaneDensity*g/cm3, 2, kStateGas, CUBE_NS::temperature*kelvin, (CUBE_NS::pressure/760.0)*atmosphere);
	CUBE_NS::isobutane->AddElement(CUBE_NS::elC, 4);
	CUBE_NS::isobutane->AddElement(CUBE_NS::elH, 10);

}

CUBE::~CUBE(){

}



// Read stream at Configfile to pick-up parameters of detector (Position,...)
// Called in DetecorConstruction::ReadDetextorConfiguration Method
// 1/22/25 - Updates placed in by Sam
void CUBE::ReadConfiguration(NPL::InputParser parser){
	// Parsing settings from configuration, e.g., positions, origin
	std::vector<NPL::InputBlock*> blocks = parser.GetAllBlocksWithToken("CUBE");
	CUBE::detNumber = blocks.size();
	
	if (blocks.size() == 0) {
		return;
	}

	std::vector<std::string> tokens = {"Centroid"};
	
	for (long unsigned int b=0; b < blocks.size(); b++){
		if (blocks[b]->HasTokenList(tokens)){
			if (NPOptionManager::getInstance()->GetVerboseLevel()){
				G4cout << "//// CUBE detector index: " << b + 1 << '\n';
			}

			G4ThreeVector centroid = NPS::ConvertVector(blocks[b]->GetTVector3("Centroid", "mm"));

			// Calculate the normal vector from the centroid to the origin
			// Will be used to orient the detectors
			G4ThreeVector normal(-centroid.x(), -centroid.y(), -centroid.z());
			normal *= 1.0/normal.mag();

			CUBE::detCenters.push_back(centroid);
			CUBE::detNormals.push_back(normal);
		}
	}
}

// Constructing the logical volume for a single detector based on index (passed by ReadConfiguration)
G4LogicalVolume* CUBE::SetCUBELogic(unsigned int cubeIndex){
        G4String boxName = "CUBE_Det_" + std::to_string(cubeIndex);

        // Using frame depth as the z component (upon construction) for the detector
        // This can be updated in the future
        G4Box* gasBox = new G4Box(boxName, CUBE_NS::halfWidth, CUBE_NS::halfHeight, (CUBE_NS::frameDepth));

        G4String logicalName = boxName + "_LOGIC";
        G4LogicalVolume* gasLogic = new G4LogicalVolume(gasBox, CUBE_NS::gasMaterial, logicalName, 0, 0, 0);
        gasLogic->SetVisAttributes(CUBE::visualizeGasSettings);
        gasLogic->SetSensitiveDetector(m_CUBEScorer);
        return gasLogic;
}

G4LogicalVolume* CUBE::SetGasLogic(unsigned int cubeIndex, double depth){
	// 5/25/15 - adding in 10 torr isobutane between detectors
	G4String gasVolumeName 		= "gasBox_" + std::to_string(cubeIndex);
        G4String gasLogicName 		= "gasBoxLogic_" + std::to_string(cubeIndex);
	G4Box* gasBox 			= new G4Box(gasVolumeName, CUBE_NS::halfWidth, CUBE_NS::halfHeight, depth);
        G4LogicalVolume* gasLogic 	= new G4LogicalVolume(gasBox, CUBE_NS::isobutane, gasLogicName , 0, 0, 0);
	G4VisAttributes* gasVis 	= new G4VisAttributes(G4Colour(0.0, 0.5, 0.5, 1.0));
	gasLogic->SetVisAttributes(gasVis);
	return gasLogic;
}



void CUBE::AddDetector(unsigned int copyNum, unsigned int copyNum2, G4LogicalVolume* world) {
	G4String detName = "CUBE_DET_FRONT_" + std::to_string(copyNum);
	G4ThreeVector placement = CUBE::detCenters[copyNum];
	double scaling = 20.0;
	G4String detName2 = "CUBE_DET_BACK_" + std::to_string(copyNum2);

	G4ThreeVector normal = CUBE::detNormals[copyNum];
	G4ThreeVector placement2 = placement - normal*scaling;
	// Rotate the logical volume so the plane is facing the origin
	G4RotationMatrix rot;
	G4ThreeVector xAxis = normal.orthogonal().unit();
	G4ThreeVector yAxis = normal.cross(xAxis).unit();
	rot.rotateAxes(xAxis, yAxis, normal);
	
	// ARGUMENTS:
	/*
	- Rotation matrix of type G4RotationMatrix && placement of logical volume of type G4ThreeVector
	- Logical volume to be placed of type G4LogicalVolume*
	- PARENT logical volume of WHAT IS BEING PLACED ^ (this is the world)
	- Need to check this, don't remember. I think it's an overlap conditional?
	- Copy number of the logical volume. VERY important.
	- Again, need to check this. I think it has to do with overlaps again.
	*/

	new G4PVPlacement(G4Transform3D(rot, placement), CUBE::SetCUBELogic(copyNum), detName, world, false, copyNum, false);

	// 5/25/15 - adding in 10 torr isobutane between detectors
	G4ThreeVector gasPlacement 	= (placement2 + placement)/2.0;
	double gasDepth 		= scaling/2.0 - 2.0*CUBE_NS::frameDepth;
	G4LogicalVolume* gasLogic 	= CUBE::SetGasLogic(copyNum, gasDepth);
	new G4PVPlacement(G4Transform3D(rot, gasPlacement), gasLogic, gasLogic->GetName(), world, false, copyNum, false);


	// Next thing we need to do is add the back detector
	// We can do that in this loop, at the same time, given the spacing between the detectors
	// The above should be used (and not removed from this method) as a way to generate sensitive detectors
	//unsigned int copyNum2 = i+CUBE::detNumber;
	//placement2 = placement - normal*scaling;
	G4LogicalVolume* backDetLogic = CUBE::SetCUBELogic(copyNum2);
	G4VisAttributes* visBack = new G4VisAttributes(G4Colour(1.0, 0.5, 0.431, 1.0));
	backDetLogic->SetVisAttributes(visBack);
	new G4PVPlacement(G4Transform3D(rot, placement2), backDetLogic, detName2, world, false, copyNum2, false);

}


// Called After DetecorConstruction::AddDetector Method
void CUBE::ConstructDetector(G4LogicalVolume* world){
	for (int i=0; i < CUBE::detNumber; i++){
		AddDetector(i, i+CUBE::detNumber, world);
	}
}

// Add Detector branch to the EventTree.
// Called After DetecorConstruction::AddDetector Method
void CUBE::InitializeRootOutput(){
	RootOutput *pAnalysis = RootOutput::getInstance();
	TTree *pTree = pAnalysis->GetTree();
	if(!pTree->FindBranch("CUBE")){
		pTree->Branch("CUBE", "TCUBEData", &m_Event) ;
	}
	pTree->SetBranchAddress("CUBE", &m_Event) ;
}


// Read sensitive part and fill the Root tree.
// Called at in the EventAction::EndOfEventAvtion
// Updates implemented with custom scorer CUBEGasScorers on 1/22/25 by Sam
void CUBE::ReadSensitive(const G4Event* event){
	m_Event->Clear();
	m_Event->SetEventID(event->GetEventID()+1);

	///////////
	// Custom CUBE gas scorer -- written 1/22/25
	CUBEGasScorers::PS_CUBEGas* Scorer = (CUBEGasScorers::PS_CUBEGas*) m_CUBEScorer->GetPrimitive(0);

	std::map<int, std::vector<CUBEGasScorers::CUBEData>> DetData = Scorer->GetDetData();

	for (std::map<int, std::vector<CUBEGasScorers::CUBEData>>::iterator it = DetData.begin(); it != DetData.end(); it++){
		int detIndex 	= it->first;
		int detMult 	= it->second.size();

		// Multiplicity can only be 1 for these detectors
		// We should write a conditional that checks if the event is worth keeping
		// This would speed up computation times
		m_Event->SetMult(detIndex, 1);

		for (int i=0; i < detMult; i++){
			CUBEGasScorers::CUBEData data = it->second[i];

			double resolvedEnergy = fabs(RandGauss::shoot(data.GetEnergy(), CUBE_NS::ResoEnergy));
			m_Event->SetEnergy(detIndex, resolvedEnergy);

			// Setting timing data
			double resolvedTime = fabs(RandGauss::shoot(data.GetTime(), CUBE_NS::ResoTime));
			m_Event->SetTime(detIndex, resolvedTime);

			// Setting position data
			G4ThreeVector position = data.GetPosition();
			double resolvedX = RandGauss::shoot(position.x(), CUBE_NS::ResoXPos);
			double resolvedY = RandGauss::shoot(position.y(), CUBE_NS::ResoYPos);
			double resolvedZ = RandGauss::shoot(position.z(), CUBE_NS::ResoZPos);

			m_Event->SetPosX(detIndex, resolvedX);
			m_Event->SetPosY(detIndex, resolvedY); 
			m_Event->SetPosZ(detIndex, resolvedZ); 

			// Setting particle data (for referencing/benchmarking)
			m_Event->SetA(detIndex, data.GetA());
			m_Event->SetZ(detIndex, data.GetZ());
			break;
		}
	}
	// Call this outside the loop if you want to record the max multiplicity of the event
	// If not, set a conditional inside the loop for when to break and clear
	Scorer->clear(); 

	return;
}


void CUBE::InitializeScorers(){ 
	// This check is necessary in case the geometry is reloaded
	bool already_exist = false; 
	m_CUBEScorer = CheckScorer("TotalCUBEGasScorers", already_exist) ;
	
	if(already_exist){
		return;
	}
	
	// Otherwise the scorer is initialised
	std::vector<int> level; 
	level.push_back(0);
	G4VPrimitiveScorer* CUBEScorerObject = new CUBEGasScorers::PS_CUBEGas("CUBEGasScorer", 0);

	//and register it to the multifunctionnal detector
	m_CUBEScorer->RegisterPrimitive(CUBEScorerObject);

	G4SDManager::GetSDMpointer()->AddNewDetector(m_CUBEScorer) ;
}


////////////////////////////////////////////////////////////////////////////////
//            Construct Method to be pass to the DetectorFactory              //
////////////////////////////////////////////////////////////////////////////////

NPS::VDetector* CUBE::Construct(){
	return  (NPS::VDetector*) new CUBE();
}


////////////////////////////////////////////////////////////////////////////////
//            Registering the construct method to the factory                 //
////////////////////////////////////////////////////////////////////////////////
extern"C" {
	class proxy_nps_CUBE{
		public:
			proxy_nps_CUBE(){
				NPS::DetectorFactory::getInstance()->AddToken("CUBE","CUBE");
				NPS::DetectorFactory::getInstance()->AddDetector("CUBE",CUBE::Construct);
			}
	};
	
	proxy_nps_CUBE p_nps_CUBE;
}
