#ifndef __CUBEDATA__
#define __CUBEDATA__
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

// STL
#include <vector>
using namespace std;

// ROOT
#include "TObject.h"

class TCUBEData : public TObject {
	//////////////////////////////////////////////////////////////
	// data members are hold into vectors in order 
	// to allow multiplicity treatment

	private: 
		// Event ID
		vector<UShort_t>   fEventID;

		// Detector multiplicities
		vector<UShort_t>   fCUBE_Mult_DetectorNbr;
		vector<UShort_t>   fCUBE_Mult;

		// Energy
		vector<UShort_t>   fCUBE_E_DetectorNbr;
		vector<Double_t>   fCUBE_Energy;
		
		// Time
		vector<UShort_t>   fCUBE_T_DetectorNbr;
		vector<Double_t>   fCUBE_Time;

		// Position
		vector<UShort_t>   fCUBE_Pos_DetectorNbr;
		vector<Double_t>   fCUBE_PosX;
		vector<Double_t>   fCUBE_PosY;
		vector<Double_t>   fCUBE_PosZ;

		// Particle ID
		vector<UShort_t>   fCUBE_PID_DetectorNbr;
		vector<UShort_t>   fCUBE_A;
		vector<UShort_t>   fCUBE_Z;

	
	
	//////////////////////////////////////////////////////////////
	// Constructor and destructor
	public: 
		TCUBEData();
		~TCUBEData();
	
	
	//////////////////////////////////////////////////////////////
	// Inherited from TObject and overriden to avoid warnings
	public:
		void Clear();
		void Clear(const Option_t*) {};
		void Dump() const;
	
	
	//////////////////////////////////////////////////////////////
	// Getters and Setters
	// Prefer inline declaration to avoid unnecessary called of 
	// frequently used methods
	// add //! to avoid ROOT creating dictionnary for the methods

	public:
		//////////////////////    SETTERS    ////////////////////////

		// Event ID
		inline void SetEventID(const int& event){
			fEventID.push_back(event);
		}//!

		// Multiplicity
		inline void SetMult(const UShort_t& DetNbr, const UShort_t& mult){
			fCUBE_Mult_DetectorNbr.push_back(DetNbr);	
			fCUBE_Mult.push_back(mult);	
		}//!

		// Energy
		inline void SetEnergy(const UShort_t& DetNbr,const Double_t& Energy){
			fCUBE_E_DetectorNbr.push_back(DetNbr);
			fCUBE_Energy.push_back(Energy);
		};//!
		
		// Time
		inline void SetTime(const UShort_t& DetNbr,const Double_t& Time)	{
			fCUBE_T_DetectorNbr.push_back(DetNbr);     
			fCUBE_Time.push_back(Time);
		};//!

		// Position
		inline void SetPosX(const UShort_t& DetNbr, const Double_t& x){
			fCUBE_Pos_DetectorNbr.push_back(DetNbr);	
			fCUBE_PosX.push_back(x);	
		}//!
		inline void SetPosY(const UShort_t& DetNbr, const Double_t& y){
			fCUBE_Pos_DetectorNbr.push_back(DetNbr);	
			fCUBE_PosY.push_back(y);	
		}//!
		inline void SetPosZ(const UShort_t& DetNbr, const Double_t& z){
			fCUBE_Pos_DetectorNbr.push_back(DetNbr);	
			fCUBE_PosZ.push_back(z);	
		}//!

		// Particle identification
		inline void SetA(const UShort_t& DetNbr, const UShort_t& a){
			fCUBE_PID_DetectorNbr.push_back(DetNbr);	
			fCUBE_A.push_back(a);	
		}//!
		inline void SetZ(const UShort_t& DetNbr, const UShort_t& z){
			fCUBE_PID_DetectorNbr.push_back(DetNbr);	
			fCUBE_Z.push_back(z);	
		}//!

	
	
		//////////////////////    GETTERS    ////////////////////////

		// Event ID
		inline UShort_t GetEventID(const unsigned int &i) const{
			return fEventID[i];
		}//!

		inline UShort_t GetEventIDSize() const{
			return fEventID.size();
		}//!

		// Total multiplicity
		inline UShort_t GetMult() const{
			return fCUBE_Mult_DetectorNbr.size();
		}
		inline UShort_t GetDetMult(const unsigned int &i) const{
			return fCUBE_Mult[i];
		}//!

		// Energy
		inline UShort_t GetMultEnergy() const{
			return fCUBE_E_DetectorNbr.size();
		}
		inline UShort_t GetE_DetectorNbr(const unsigned int &i) const {
			return fCUBE_E_DetectorNbr[i];
		}//!

		inline Double_t Get_Energy(const unsigned int &i) const {
			return fCUBE_Energy[i];
		}//!
		
		// Time
		inline UShort_t GetMultTime() const{
			return fCUBE_T_DetectorNbr.size();
		}
		inline UShort_t GetT_DetectorNbr(const unsigned int &i) const {
			return fCUBE_T_DetectorNbr[i];
		}//!
		inline Double_t Get_Time(const unsigned int &i) const {
			return fCUBE_Time[i];
		}//!

		// Position
		inline Double_t Get_Pos_X(const unsigned int &i) const {
			return fCUBE_PosX[i];
		}//!
		inline Double_t Get_Pos_Y(const unsigned int &i) const {
			return fCUBE_PosY[i];
		}//!
		inline Double_t Get_Pos_Z(const unsigned int &i) const {
			return fCUBE_PosZ[i];
		}//!

		// Particle identification
		inline UShort_t Get_A(const unsigned int &i) const {
			return fCUBE_A[i];
		}//!
		inline UShort_t Get_Z(const unsigned int &i) const {
			return fCUBE_Z[i];
		}//!

	
	
	//////////////////////////////////////////////////////////////
	// Required for ROOT dictionnary
	ClassDef(TCUBEData,1)  // CUBEData structure
};

#endif
