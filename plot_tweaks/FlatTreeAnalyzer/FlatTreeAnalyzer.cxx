#define FlatTreeAnalyzer_cxx
#include "FlatTreeAnalyzer.h"

#include <TH1D.h>
#include <TH2D.h>
#include <TFile.h>
#include <TString.h>
#include <TMath.h>
#include <TVector3.h>
#include <TLorentzVector.h>
#include <TGraph.h>
#include <TCanvas.h>

#include <iomanip>
#include <sstream>
#include <iostream>
#include <vector>
#include <iterator>
#include <fstream>

#include "STV_Tools.h"
#include "../../Constants.h"

using namespace std;
using namespace Constants;

bool is_HeavierMeson( int pdg_code ) {

        // Ignore differences between mesons and antimesons for this test. Mesons
        // will have positive PDG codes, while antimesons will have negative ones.
        int abs_pdg = abs( pdg_code );

        int NeutralPionPdg = 111;
        if (abs_pdg == NeutralPionPdg) {return false;}

        int AbsChargedPionPdg = 211;
        if (abs_pdg == AbsChargedPionPdg) {return false;}

        // Meson PDG codes have no more than seven digits. Seven-digit
        // codes beginning with "99" are reserved for generator-specific
        // particles
        if ( abs_pdg >= 9900000 ) {return false;}

        // Mesons have a value of zero for $n_{q1}$, the thousands digit
        int thousands_digit = ( abs_pdg / 1000 ) % 10;
        if ( thousands_digit != 0 ) {return false;}

        // They also have a nonzero value for $n_{q2}$, the hundreds digit
        int hundreds_digit = ( abs_pdg / 100 ) % 10;
        if ( hundreds_digit == 0 ) {return false;}

        // Reserved codes for Standard Model parton distribution functions
        if ( abs_pdg >= 901 && abs_pdg <= 930 ) {return false;}

        // Reggeon and pomeron
        if ( abs_pdg == 110 || abs_pdg == 990 ) {return false;}

        // Reserved codes for GEANT tracking purposes
        if ( abs_pdg == 998 || abs_pdg == 999 ) {return false;}

        // Reserved code for generator-specific pseudoparticles
        if ( abs_pdg == 100 ) {return false;}

        // If we've passed all of the tests above, then the particle is a meson
        return true;

}

void FlatTreeAnalyzer::Loop() {

	// Check
	if (fChain == 0) return;
	Long64_t nentries = fChain->GetEntriesFast();

	// Variable declaration
	double Units = 1E38; // so that the extracted cross-section is in 10^{-38} cm^{2}
	double A = 40.; // so that we can have xsecs per nucleus
	int Inclusive_Events = 0;
	int Selected_uB_Events = 0;
	int Selected_T2K_Events = 0;
        ofstream outfile;
	outfile.open( flat_ana_outfile +  "/events_"+InputBeam+InputCurrent+InputFlavor+".csv");
	outfile<<"Inc"<<","<<"uBExc"<<","<<"T2KExc"<<","<<"Enu"<<","<<"Q2"<<","<<"Pmu"<<","<<"Cos_mu"<<","<<"Weight"<<","<<endl;

	// Plot declaration
	TH1D* EnuIncPlot = new TH1D("EnuInc", "", 10, 0., 2.);
	EnuIncPlot->GetXaxis()->SetTitle("E_{#nu} (GeV)");
	EnuIncPlot->GetYaxis()->SetTitle("d#sigma/dE_{#nu} (cm^{2}/GeV)");

	TH1D* Q2IncPlot = new TH1D("Q2Inc", "", 10, 0., 2.);
	Q2IncPlot->GetXaxis()->SetTitle("Q^{2} (GeV^{2})");
	Q2IncPlot->GetYaxis()->SetTitle("d#sigma/dQ^{2} (cm^{2}/GeV^{2})");

	// Loop over the events
	for (Long64_t jentry=0; jentry<nentries; jentry++) {

		// Get next event
		Long64_t ientry = LoadTree(jentry);
		if (ientry < 0) break; 
		fChain->GetEntry(jentry);
		if (jentry%100000 == 0) {std::cout << "Event "<<jentry<<" of "<<nentries<<" ("<<setprecision(2)<<double(jentry)/nentries*100.<<"%)"<<endl;} 

		// Signal definition
		bool IsInc = 0;
		bool Is_uB_Exc = 1;
		bool Is_T2K_Exc = 1;
        	double weight = fScaleFactor*Weight;
        	//double weight = fScaleFactor*Units*A*Weight;
		double Enu = -999; 
		double Q2 = -999; 
		double Pmu = -999; 
		double Cos_mu = -999;

		// Check if the event is Inc
		if (InputFlavor == "numu" and PDGnu == 14) {
			if (InputCurrent == "CC_" and PDGLep == 13) {IsInc = 1;}
			else if (InputCurrent == "NC_" and PDGLep == 14) {IsInc = 1; Is_uB_Exc = 0; Is_T2K_Exc = 0;}
		}
		else if (InputFlavor == "anumu" and PDGnu == -14) {
			if (InputCurrent == "CC_" and PDGLep == -13) {IsInc = 1; Is_uB_Exc = 0; Is_T2K_Exc = 0;}
			else if (InputCurrent == "NC_" and PDGLep == -14) {IsInc = 1; Is_uB_Exc = 0; Is_T2K_Exc = 0;}
		}
		else if (InputFlavor == "nue" and PDGnu == 12) {
			if (InputCurrent == "CC_" and PDGLep == 11) {IsInc = 1; Is_uB_Exc = 0; Is_T2K_Exc = 0;}
			else if (InputCurrent == "NC_" and PDGLep == 12) {IsInc = 1; Is_uB_Exc = 0; Is_T2K_Exc = 0;}
		}
		else if (InputFlavor == "anue" and PDGnu == -12) {
			if (InputCurrent == "CC_" and PDGLep == -11) {IsInc = 1; Is_uB_Exc = 0; Is_T2K_Exc = 0;}
			else if (InputCurrent == "NC_" and PDGLep == -12) {IsInc = 1; Is_uB_Exc = 0; Is_T2K_Exc = 0;}
		}

		if (!IsInc) {
			outfile<<IsInc<<","<<Is_uB_Exc<<","<<Is_T2K_Exc<<","<<Enu<<","<<Q2<<","<<Pmu<<","<<Cos_mu<<","<<weight<<endl;
			continue;
		}

		Inclusive_Events += 1;

		// Fill the inclusive plots 
		Enu = Enu_true;
		Q2 = Qsqrd;
		EnuIncPlot->Fill(Enu,weight);
		Q2IncPlot->Fill(Q2,weight);

		if (!Is_uB_Exc and !Is_T2K_Exc) {
			outfile<<IsInc<<","<<Is_uB_Exc<<","<<Is_T2K_Exc<<","<<Enu<<","<<Q2<<","<<Pmu<<","<<Cos_mu<<","<<weight<<endl;
			continue;
		}

		// Check signal definitions
		int nMuons_uB = 0;
		int nProtons_uB = 0;
		int nChargedPions_uB = 0;
		int nNeutralPions_uB = 0;
		int nHeavyMesons_uB = 0;
		int nLeptons_T2K = 0;
		int nMesons_T2K = 0;
		vector<int> MuonID_uB;
		vector<int> MuonID_T2K;
		
		for (int i=0; i<nfsp; i++) {
			double pf = TMath::Sqrt( px[i]*px[i] + py[i]*py[i] + pz[i]*pz[i]);
			if (abs(pdg[i]) == 11 or abs(pdg[i]) == 13 or abs(pdg[i]) == 15) {
				nLeptons_T2K += 1;
				if (pdg[i] == 13) {
					MuonID_T2K.push_back(i);
					if (pf > 0.1 && pf < 1.2) {
						nMuons_uB += 1;
						MuonID_uB.push_back(i);
					}
				}
			}
			else if (pdg[i] == 2212 && (pf > 0.3 && pf < 1.0)) {
				nProtons_uB += 1;
			}
			else if (abs(pdg[i]) >= 111 and abs(pdg[i]) <= 557) {
				nMesons_T2K += 1;
				if (pdg[i] == 111)  {
					nNeutralPions_uB += 1;
				}
				else if (abs(pdg[i]) == 211 && pf > 0.07)  {
					nChargedPions_uB += 1;
				}
			}
			else if (is_HeavierMeson(pdg[i])) {
				nHeavyMesons_uB += 1;
			}
		}

	        int genie_mode = -1.;
	        if (abs(Mode) == 1) {genie_mode = 1;} // QE
	        else if (abs(Mode) == 2) {genie_mode = 2;} // MEC
	        else if (abs(Mode) == 10 || abs(Mode) == 11 || abs(Mode) == 12 || abs(Mode) == 13
	        	|| abs(Mode) == 17 || abs(Mode) == 22 || abs(Mode) == 23) {genie_mode = 3;} // RES
	        else if (abs(Mode) == 21 || abs(Mode) == 26) {genie_mode = 4;} // DIS
	        else if (abs(Mode) == 16) {genie_mode = 5;} // COH

		// Check uB signal definition
		if (nMuons_uB == 1 && nProtons_uB == 1 && nChargedPions_uB == 0 && nNeutralPions_uB == 0 && nHeavyMesons_uB == 0 && genie_mode != -1) { 
			Selected_uB_Events += 1;
			TLorentzVector MuonLorentzVector(px[MuonID_uB[0]], py[MuonID_uB[0]], pz[MuonID_uB[0]], E[MuonID_uB[0]]);
			Pmu = MuonLorentzVector.Rho(); 
			Cos_mu = CosLep;
		}
		else {Is_uB_Exc = 0;}

		// Check T2K signal definition
		if (nLeptons_T2K == 1 and nMesons_T2K == 0) {
			Selected_T2K_Events += 1;
			TLorentzVector MuonLorentzVector(px[MuonID_T2K[0]], py[MuonID_T2K[0]], pz[MuonID_T2K[0]], E[MuonID_T2K[0]]);
			Pmu = MuonLorentzVector.Rho(); 
			Cos_mu = CosLep;
		}
		else {Is_T2K_Exc = 0;}

		if (Is_uB_Exc and Is_T2K_Exc) {
			if (MuonID_uB[0] != MuonID_T2K[0]) {
				cout<<"uB and T2K selected different muons"<<endl;
				continue;
			}
		}

		// Fill the csv
		outfile<<IsInc<<","<<Is_uB_Exc<<","<<Is_T2K_Exc<<","<<Enu<<","<<Q2<<","<<Pmu<<","<<Cos_mu<<","<<weight<<endl;

	} // End of the loop over the events

	cout<<Inclusive_Events<<" events are inclusive"<<endl;
	cout<<double(Selected_uB_Events)/double(nentries)*100.<<"% of events passed the uB selection"<<endl;
	cout<<double(Selected_T2K_Events)/double(nentries)*100.<<"% of events passed the T2K selection"<<endl;

        // Write histograms to root file
        TFile* file = new TFile( OutputFile, "recreate");
	EnuIncPlot->Write();
	Q2IncPlot->Write();
	file->Close();

        outfile.close();
        fFile->Close();
	std::cout << "File " << OutputFile +" has been created" << std::endl; 

} // End of the program
