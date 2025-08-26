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
 *  File old the scorer specific to the Sharc Detector                       *
 *                                                                           *
 *---------------------------------------------------------------------------*
 * Comment:                                                                  *
 * This new type of scorer is aim to become the standard for DSSD,SSSD and   *
 * PAD detector (any Silicon Detector)                                       *
 *****************************************************************************/

#include "CUBEGasScorers.hh"
#include "G4UnitsTable.hh"
#include <bits/stdc++.h>
#include <algorithm>

using namespace CUBEGasScorers;



PS_CUBEGas::PS_CUBEGas(G4String name, G4int depth) : G4VPrimitiveScorer(name, depth) {
}


PS_CUBEGas::~PS_CUBEGas(){}


// Just moving stuff out of ProcessHits to keep everything tidy
CUBEData PS_CUBEGas::SaveHits(G4Step* aStep){
	int trackID 		= aStep->GetTrack()->GetTrackID();
	double energy		= aStep->GetTotalEnergyDeposit();
	double time		= aStep->GetPreStepPoint()->GetGlobalTime();
	
	double x		= aStep->GetPreStepPoint()->GetPosition().getX(); //cm;
	double y		= aStep->GetPreStepPoint()->GetPosition().getY(); //cm;
	double z		= aStep->GetPreStepPoint()->GetPosition().getZ(); //cm;
	G4ThreeVector position 	= G4ThreeVector(x,y,z); 
	
	int A			= aStep->GetTrack()->GetParticleDefinition()->GetAtomicMass();
	int Z			= aStep->GetTrack()->GetParticleDefinition()->GetAtomicNumber();

	G4ThreeVector origin = G4ThreeVector(0.0, 0.0, 0.0);
	double Phi = std::atan2(y, x);
	double Theta = std::atan2(y, z);

	CUBEData savedata(trackID, energy, time, position, A, Z, Phi, Theta);
	return savedata;
}


G4bool PS_CUBEGas::ProcessHits(G4Step* aStep, G4TouchableHistory*) {

	std::string particle = aStep->GetTrack()->GetParticleDefinition()->GetParticleType();
	if (aStep->IsFirstStepInVolume()){
		int detNum = aStep->GetTrack()->GetVolume()->GetCopyNo();
		//int trackID = aStep->GetTrack()->GetTrackID();
		std::string name = aStep->GetTrack()->GetVolume()->GetName();
		CUBEData data = SaveHits(aStep);	
		if (DetData.count(detNum) == 0){
			std::vector<CUBEData> holdingVec;
			holdingVec.push_back(data);
			DetData[detNum] = holdingVec;
		}
		else{
			DetData[detNum].push_back(data);
		}

		DetNums[name] = detNum;
		DetMult[detNum] += 1;
	}

	return TRUE;
}


void PS_CUBEGas::Initialize(G4HCofThisEvent*) { clear(); }


void PS_CUBEGas::EndOfEvent(G4HCofThisEvent*) {}


void PS_CUBEGas::clear(){
	DetMult.clear();
	DetNums.clear();
	DetData.clear();
}


void PS_CUBEGas::DrawAll() {}


void PS_CUBEGas::PrintAll() {}


