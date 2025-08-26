#ifndef EventGeneratorViola_h
#define EventGeneratorViola_h
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
 *  This event Generator is used to simulated data from transport model outputs         *
 *  Very usefull to figure out Geometric Efficacity of experimental Set-Up   *
 *---------------------------------------------------------------------------*
 * Comment:                                                                  *
 *                                                                           *
 *                                                                           *
 *****************************************************************************/
// C++ header
#include <algorithm>
#include <random>
#include <string>
using namespace std;

using namespace CLHEP;

// G4 headers
#include "G4Event.hh"

// NPS headers
#include "VEventGenerator.hh"
#include "ParticleStack.hh"
#include "NPInputParser.h"

// ROOT Headers
#include "TSystem.h"
#include "TF1.h"
#include "TH1.h"
#include "TH2.h"
#include "TChain.h"

// Mass table parser provided by Marshall Basson, thanks homie :)
#include "ame20_parser/ame20parser.h"

class EventGeneratorViola : public NPS::VEventGenerator{
	public:     // Constructor and destructor
	    EventGeneratorViola();
	    virtual ~EventGeneratorViola();
	  
	public:     // Inherit from VEventGenerator Class
	    void ReadConfiguration(NPL::InputParser);
	    void GenerateEvent(G4Event* evt);
	    void InitializeRootOutput();

	public:    // Source parameters from input file
		string                  m_projectile;
		string                  m_target;
		double			m_beamEnergy;
		string                  m_fitPath;

		G4ParticleDefinition*   m_fragment1; 
		G4ParticleDefinition*   m_fragment2; 
		ParticleStack*          m_ParticleStack;


		// Members for calculating fission fragments + kinematics (Viola)
	private:
		MassEval2020* IsotopeTable;
		int projectileZ;
		int projectileA;
		int targetZ;
		int targetA;
		int totalZ;
		int totalA;

		// Lorentz vector data for boosting
		double beta;
		double gamma;

		TF1* beamElasticFit;
		TF1* targetElasticFit;
		TF1* fissionFit;
		
		TH2I* isobaricHist;




  
};
#endif
