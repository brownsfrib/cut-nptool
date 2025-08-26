#ifndef CUBE_h
#define CUBE_h 1
/*****************************************************************************
 * Copyright (C) 2009-2024   this file is part of the NPTool Project       *
 *                                                                           *
 * For the licensing terms see $NPTOOL/Licence/NPTool_Licence                *
 * For the list of contributors see $NPTOOL/Licence/Contributors             *
 *****************************************************************************/

/*****************************************************************************
 * Original Author: Sachet Jain  contact address: jainsach@msu.edu                        *
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

// C++ header
#include <string>
#include <vector>
using namespace std;

// G4 headers
#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"
#include "G4LogicalVolume.hh"
#include "G4MultiFunctionalDetector.hh"
#include "G4PVPlacement.hh"
#include "G4VisAttributes.hh"

// NPTool header
#include "NPSVDetector.hh"
#include "TCUBEData.h"
#include "NPInputParser.h"

class CUBE : public NPS::VDetector{
	////////////////////////////////////////////////////
	/////// Default Constructor and Destructor /////////
	////////////////////////////////////////////////////
	public:
		CUBE() ;
		virtual ~CUBE() ;

	////////////////////////////////////////////////////
	/////// Specific Function of this Class ///////////
	////////////////////////////////////////////////////
	public:
		// 1/22/25 - Sam
		// Construction of a CUBE wall
		// Methods are read in through ReadConfiguration class
		void AddDetector(unsigned int, unsigned int, G4LogicalVolume* world);

		G4LogicalVolume* SetCUBELogic(unsigned int);
		G4LogicalVolume* SetGasLogic(unsigned int, double);
		G4VisAttributes* visualizeGasSettings;

		// ReadConfiguration members
		int detNumber;
		std::vector<G4ThreeVector> detCenters; // Centroid of each detector, read in through ReadConfiguration
		std::vector<G4ThreeVector> detNormals; // Vector normal to plane tending to the origin



	////////////////////////////////////////////////////
	//////  Inherite from NPS::VDetector class /////////
	////////////////////////////////////////////////////
	public:
		// Read stream at Configfile to pick-up parameters of detector (Position,...)
		// Called in DetectorConstruction::ReadDetectorConfiguration Method
		void ReadConfiguration(NPL::InputParser) ;

		// Construct detector and initiallize sensitive part.
		// Called After DetectorConstruction::AddDetector Method
		void ConstructDetector(G4LogicalVolume* world) ;
		
		// Add Detector branch to the EventTree. 
		// Called After DetectorConstruction::AddDetector Method
		void InitializeRootOutput() ;
		
		// Read sensitive part and fill the Root tree.
		// Called at in the EventAction::EndOfEventAvtion
		void ReadSensitive(const G4Event* event) ;

	public:   // Scorer
		//   Initialize all Scorer used by the MUST2Array
		void InitializeScorers() ;
		
		//   Associated Scorer
		G4MultiFunctionalDetector* m_CUBEScorer ;
		////////////////////////////////////////////////////
		///////////Event class to store Data////////////////
		////////////////////////////////////////////////////

	private:
		TCUBEData* m_Event ;
		////////////////////////////////////////////////////
		///////////////Private intern Data//////////////////
		////////////////////////////////////////////////////
	

	// Needed for dynamic loading of the library
	public:
		static NPS::VDetector* Construct();
};

#endif
