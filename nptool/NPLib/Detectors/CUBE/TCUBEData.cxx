/*****************************************************************************
 * Copyright (C) 2009-2025   this file is part of the NPTool Project       *
 *                                                                           *
 * For the licensing terms see $NPTOOL/Licence/NPTool_Licence                *
 * For the list of contributors see $NPTOOL/Licence/Contributors             *
 *****************************************************************************/

/*****************************************************************************
 * Original Author: Samuel Brown  contact address: browns@frib.msu.edu                        *
 *                                                                           *
 * Creation Date  : January 2025                                           *
 * Last update    :                                                          *
 *---------------------------------------------------------------------------*
 * Decription:                                                               *
 *  This class hold CUBE Raw data                                    *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Comment:                                                                  *
 *                                                                           *   
 *                                                                           *
 *****************************************************************************/
#include "TCUBEData.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
using namespace std; 

ClassImp(TCUBEData)


//////////////////////////////////////////////////////////////////////
TCUBEData::TCUBEData() {
}



//////////////////////////////////////////////////////////////////////
TCUBEData::~TCUBEData() {
}



//////////////////////////////////////////////////////////////////////
void TCUBEData::Clear() {
	// Event ID 
	fEventID.clear();

	// Detector multiplicities
	fCUBE_Mult_DetectorNbr.clear();
	fCUBE_Mult.clear();
	
	// Energy
	fCUBE_E_DetectorNbr.clear();
	fCUBE_Energy.clear();
	
	// Time
	fCUBE_T_DetectorNbr.clear();
	fCUBE_Time.clear();

	// Position
	fCUBE_Pos_DetectorNbr.clear();
	fCUBE_PosX.clear();
	fCUBE_PosY.clear();
	fCUBE_PosZ.clear();

	// Particle ID
	fCUBE_PID_DetectorNbr.clear();
	fCUBE_A.clear();
	fCUBE_Z.clear();
	return;
}



//////////////////////////////////////////////////////////////////////
void TCUBEData::Dump() const {
  // This method is very useful for debuging and worth the dev.
  cout << "XXXXXXXXXXXXXXXXXXXXXXXX New Event [TCUBEData::Dump()] XXXXXXXXXXXXXXXXX" << endl;

  // Energy
  size_t mysize = fCUBE_E_DetectorNbr.size();
  cout << "CUBE_E_Mult: " << mysize << endl;
 
  for (size_t i = 0 ; i < mysize ; i++){
    cout << "DetNbr: " << fCUBE_E_DetectorNbr[i]
         << " Energy: " << fCUBE_Energy[i];
  }
  
  // Time
  mysize = fCUBE_T_DetectorNbr.size();
  cout << "CUBE_T_Mult: " << mysize << endl;
 
  for (size_t i = 0 ; i < mysize ; i++){
    cout << "DetNbr: " << fCUBE_T_DetectorNbr[i]
         << " Time: " << fCUBE_Time[i];
  }
}
