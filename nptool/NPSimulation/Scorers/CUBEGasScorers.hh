#ifndef CUBEGasScorers_h
#define CUBEGasScorers_h 1
/*****************************************************************************
 * Copyright (C) 2009-2016   this file is part of the NPTool Project         *
 *                                                                           *
 * For the licensing terms see $NPTOOL/Licence/NPTool_Licence                *
 * For the list of contributors see $NPTOOL/Licence/Contributors             *
 *****************************************************************************/

/*****************************************************************************
 * Original Author: Adrien MATTA  contact address: matta@lpccaen.in2p3.fr    *
 *                                                                           *
 * Creation Date  : February 2013                                            *
 * Last update    :                                                          *
 *---------------------------------------------------------------------------*
 * Decription:                                                               *
 *  File old the scorer specific to the Silicon Detector                     *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Comment:                                                                  *
 * This new style of scorer is aim to become the standard way of doing scorer*
 * in NPTool.                                                                *
 *The index is build using the TrackID, Detector Number and Strip Number.    *
 *The scorer Hold Energy and time together                                   *
 *Only one scorer is needed for a detector                                   *
 *****************************************************************************/
#include "G4VPrimitiveScorer.hh"
#include "NPSHitsMap.hh"
//#include "NPSecondaries.hh"

#include <map>
using namespace std;
using namespace CLHEP;

namespace CUBEGasScorers {
	// Hold One hit info
	class CUBEData{
		public:
			CUBEData(
					const int& trackID,
					const double& Energy,
					const double& Time, 
					const G4ThreeVector& Position, 
					const int &A, 
					const int &Z, 
					const double &Phi, 
					const double& Theta){ 

				m_TrackID=trackID;
				m_Energy=Energy;
				m_Time=Time;
				m_Position=Position;
				m_A=A;
				m_Z=Z;
				m_Phi=Phi;
				m_Theta=Theta;
			};

        		~CUBEData(){};

		private:
			int m_TrackID;
			double m_Energy;
			double m_Time;
			G4ThreeVector m_Position;
			int m_A;
			int m_Z;
			double m_Phi;
			double m_Theta;
		     
		public:
			inline int GetTrackID() const {return m_TrackID;};
			inline double GetEnergy() const {return m_Energy;};
			inline double GetTime() const {return m_Time;};
			inline G4ThreeVector GetPosition() const {return m_Position;};
			inline int GetA() const {return m_A;};
			inline int GetZ() const {return m_Z;};
			inline double GetPhi() const {return m_Phi;};
			inline double GetTheta() const {return m_Theta;};

		public:
			void Add(const double& Energy) {m_Energy+=Energy;};
	};
	// End CUBEData class

	//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo......
	class PS_CUBEGas : public G4VPrimitiveScorer{
	        
		public: // with description
			PS_CUBEGas(G4String name, G4int depth=0);
			~PS_CUBEGas();

        
		protected: // with description
			G4bool ProcessHits(G4Step*, G4TouchableHistory*);
        
		public:
			void Initialize(G4HCofThisEvent*);
			void EndOfEvent(G4HCofThisEvent*);
			void clear();
			void DrawAll();
			void PrintAll();
        
        
		// Sam's addition for fiber multiplicities	
		private:
			CUBEData SaveHits(G4Step*);
			// Map to hold data
			std::map<int, std::vector<CUBEData>> DetData;
			std::map<int, int> DetMult; // Stores detector number and multiplicity
			std::map<std::string, int> DetNums; // Stores detector name and detector number

		public:
			std::map<int, std::vector<CUBEData>> GetDetData(){
				return DetData;
			}
			std::map<int, int> GetDetMult(){
				return DetMult;
			}
			std::map<std::string, int> GetDetNums(){ 
				return DetNums;
			}

	};
}


#endif
