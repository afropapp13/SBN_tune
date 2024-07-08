//Things to include
#include "TFile.h"
#include "TH1F.h"
#include "TH2D.h"
#include "TTreeReader.h"
#include "TTreeReaderValue.h"
#include <math.h>
#include <iostream>
#include <fstream>

#include "../Constants.h"

using namespace Constants;

double get_mean(double *array) {

	int array_size = sizeof(array);
	double array_sum = 0.;

	for (int i=0; i<array_size; i++) {
		array_sum += array[i];
	}

	double mean = array_sum/array_size;
	return mean;

}

double get_stdev(double *array, double mean) {

	int array_size = sizeof(array);
	double array_sum = 0.;

	for (int i=0; i<array_size; i++) {
		array_sum += (array[i]-mean)*(array[i]-mean);
	}

	double stdev = sqrt(array_sum/array_size);
	return stdev;

}

void get_range(int nuniverses, TH1D *hist_array[nuniverses], TH1D *hist_hi, TH1D *hist_lo, double sigma) {

	int nbins = hist_array[0]->GetNbinsX();
	double cross_section_array[nbins][nuniverses];

	for (int universe=0; universe<nuniverses; universe++) {
		for (int bin=0; bin<nbins; bin++) {
			double cross_section = hist_array[universe]->GetBinContent(bin+1);
			cross_section_array[bin][universe] = cross_section;
		}
	}

	for (int bin=0; bin<nbins; bin++) {
		double mean = get_mean(cross_section_array[bin]);
		double stdev = get_stdev(cross_section_array[bin], mean);
		hist_hi->SetBinContent(bin+1, mean+sigma*stdev);	
		hist_lo->SetBinContent(bin+1, mean-sigma*stdev);	
	}

}

void plot_sigmas(TString var, TString sample, int nuniverses, TH1D *hist_array[nuniverses], TH1D *hist_hi, TH1D *hist_lo, vector<int> sigma_vector) {

	TCanvas *can = new TCanvas();
	TLegend *leg = new TLegend(0.85,0.65,0.95,0.95);
        THStack *stk;
	int color = 0;

	for (int universe=0; universe<nuniverses; universe++) {
		int sigma = sigma_vector[universe];
                if (universe == 0) {
                        TString xtitle = hist_array[universe]->GetXaxis()->GetTitle();
                        TString ytitle = hist_array[universe]->GetYaxis()->GetTitle();
                        stk = new THStack("stk", ";"+xtitle+";"+ytitle+"");
                }
		hist_array[universe]->SetLineWidth(2);
		hist_array[universe]->SetLineColor(okabeIto[color]);
		color += 1;
                stk->Add(hist_array[universe]);
		leg->AddEntry(hist_array[universe], (to_string(sigma)+"#sigma").c_str());
        }

        stk->Draw("nostack hist c plc");
        hist_hi->SetLineColor(1);
	hist_hi->SetLineWidth(2);
	hist_hi->Draw("same hist c");
        hist_lo->SetLineColor(1);
	hist_lo->SetLineWidth(2);
	hist_lo->Draw("same hist c");
	leg->Draw();
        can->Print("../outpngs/get_errors/"+var+"Plot_"+sample+".png");

}

void get_tweaks() { 

	vector<TString> sample_vector;
	sample_vector.push_back("CC_anue");
	sample_vector.push_back("CC_anumu");
	sample_vector.push_back("CC_nue");
	sample_vector.push_back("CC_numu");
	sample_vector.push_back("NC_anue");
	sample_vector.push_back("NC_anumu");
	sample_vector.push_back("NC_nue");
	sample_vector.push_back("NC_numu");
	sample_vector.push_back("numi_fhc_icarus_CC_anue");
	sample_vector.push_back("numi_fhc_icarus_CC_anumu");
	sample_vector.push_back("numi_fhc_icarus_CC_nue");
	sample_vector.push_back("numi_fhc_icarus_CC_numu");
	sample_vector.push_back("numi_fhc_icarus_NC_anue");
	sample_vector.push_back("numi_fhc_icarus_NC_anumu");
	sample_vector.push_back("numi_fhc_icarus_NC_nue");
	sample_vector.push_back("numi_fhc_icarus_NC_numu");
	sample_vector.push_back("numi_rhc_icarus_CC_anue");
	sample_vector.push_back("numi_rhc_icarus_CC_anumu");
	sample_vector.push_back("numi_rhc_icarus_CC_nue");
	sample_vector.push_back("numi_rhc_icarus_CC_numu");
	sample_vector.push_back("numi_rhc_icarus_NC_anue");
	sample_vector.push_back("numi_rhc_icarus_NC_anumu");
	sample_vector.push_back("numi_rhc_icarus_NC_nue");
	sample_vector.push_back("numi_rhc_icarus_NC_numu");
	sample_vector.push_back("T2K_CC_numu");
	int num_samples = sample_vector.size();

	vector<TString> param_vector;
	param_vector.push_back("ZExpA1CCQE");
	param_vector.push_back("ZExpA2CCQE");
	param_vector.push_back("ZExpA3CCQE");
	param_vector.push_back("ZExpA4CCQE");
	param_vector.push_back("RPA_CCQE");
	param_vector.push_back("CoulombCCQE");
	param_vector.push_back("NormCCMEC");
	param_vector.push_back("NormNCMEC");
	param_vector.push_back("MaNCEL");
	param_vector.push_back("EtaNCEL");
	param_vector.push_back("MaCCRES");
	param_vector.push_back("MvCCRES");
	param_vector.push_back("MaNCRES");
	param_vector.push_back("MvNCRES");
	param_vector.push_back("NonRESBGvpCC1pi");
	param_vector.push_back("NonRESBGvpCC2pi");
	param_vector.push_back("NonRESBGvpNC1pi");
	param_vector.push_back("NonRESBGvpNC2pi");
	param_vector.push_back("NonRESBGvnCC1pi");
	param_vector.push_back("NonRESBGvnCC2pi");
	param_vector.push_back("NonRESBGvnNC1pi");
	param_vector.push_back("NonRESBGvnNC2pi");
	param_vector.push_back("NonRESBGvbarpCC1pi");
	param_vector.push_back("NonRESBGvbarpCC2pi");
	param_vector.push_back("NonRESBGvbarpNC1pi");
	param_vector.push_back("NonRESBGvbarpNC2pi");
	param_vector.push_back("NonRESBGvbarnCC1pi");
	param_vector.push_back("NonRESBGvbarnCC2pi");
	param_vector.push_back("NonRESBGvbarnNC1pi");
	param_vector.push_back("NonRESBGvbarnNC2pi");
	param_vector.push_back("RDecBR1gamma");
	param_vector.push_back("RDecBR1eta");
	param_vector.push_back("NormCCCOH");
	param_vector.push_back("NormNCCOH");
	param_vector.push_back("AhtBY");
	param_vector.push_back("BhtBY");
	param_vector.push_back("CV1uBY");
	param_vector.push_back("CV2uBY");
	param_vector.push_back("MFP_pi");
	param_vector.push_back("FrCEx_pi");
	param_vector.push_back("FrInel_pi");
	param_vector.push_back("FrAbs_pi");
	param_vector.push_back("FrPiProd_pi");
	param_vector.push_back("MFP_N");
	param_vector.push_back("FrCEx_N");
	param_vector.push_back("FrInel_N");
	param_vector.push_back("FrAbs_N");
	param_vector.push_back("FrPiProd_N");
	param_vector.push_back("b1");
	param_vector.push_back("b2");
	param_vector.push_back("b3");
	param_vector.push_back("b4");
	int num_params = param_vector.size();
			
	vector<TString> special_param_vector;
	special_param_vector.push_back("VecFFCCQEshape");
	special_param_vector.push_back("DecayAngMEC");
	special_param_vector.push_back("Theta_Delta2Npi");
	special_param_vector.push_back("ThetaDelta2NRad");
	int num_special_params = special_param_vector.size();
			
	for (TString sample: sample_vector) {

		cout<<"Processing "<<sample<<" sample"<<endl;

		// Import Enu, Q2 values
		vector<int> vInc;
		vector<double> vEnu, vQ2, vWeight;
		
		fstream infile;
		infile.open(flat_ana_outfile + "/events_"+sample+".csv");
		string line, entry;
		int linen = 0, entryn = 0;
		
		while (getline(infile, line)) {
			istringstream iline(line);
			while (getline(iline, entry, ',')) {
				if (linen > 0) {
					if (entryn == 0) {vInc.push_back(stoi(entry));}
					else if (entryn == 3) {vEnu.push_back(stod(entry));}
					else if (entryn == 4) {vQ2.push_back(stod(entry));}
					else if (entryn == 7) {vWeight.push_back(stod(entry));}
				}
				entryn += 1;
				if (entryn == 8) {
					linen += 1;
					entryn = 0;
				}
			}
		}
		
		infile.close();
		int nevents = vEnu.size();
		
		// Delcare files I'll need in for-loop
		TFile *root_in = new TFile(flat_ana_outfile + "/nominal_hists_"+sample+".root", "read");
		TFile *tweak_file = TFile::Open( tweaked_outfile + "/tweaks_"+sample+".root");
		TTreeReader myReader("events", tweak_file);
		TFile *root_out = new TFile(flat_ana_outfile + "/1sigma_hists_"+sample+".root", "recreate");
		
		for (TString param: param_vector) {

			cout<<"Processing "<<param<<endl;
		
		        // Plot declarations
			int nuniverses = 7;
		        TH1D* EnuIncPlot[nuniverses];
		        TH1D* Q2IncPlot[nuniverses];
		
		        for (int universe=0; universe<nuniverses; universe++) {
		        	EnuIncPlot[universe] = (TH1D *)root_in->Get("EnuInc")->Clone(("EnuInc"+to_string(universe)).c_str());
				EnuIncPlot[universe]->Reset("ICESM");
		        	Q2IncPlot[universe] = (TH1D *)root_in->Get("Q2Inc")->Clone(("Q2Inc"+to_string(universe)).c_str());
				Q2IncPlot[universe]->Reset("ICESM");
		        }
		
			// Declare values and arrays I want to read from tweak_file tree 
			TTreeReaderValue<int> ntweak_responses(myReader, "ntweaks_"+param);
			TTreeReaderArray<double> tweak_responses(myReader, "tweak_responses_"+param);
		
			// Fill the plots
		        int event = -1; 
			while (myReader.Next()) {
				event += 1;
				if (vInc[event] != 1) {continue;}
				int ntweaks = *ntweak_responses;
				if (ntweaks != nuniverses) {
					cout<<"ntweaks = "<<ntweaks<<" is not the expected number, "<<nuniverses<<endl;
					return;
				}
				for (int universe=0; universe<ntweaks; universe++) {
					double tweak = tweak_responses[universe];
		        		EnuIncPlot[universe]->Fill(vEnu[event], tweak*vWeight[event]);
		        		Q2IncPlot[universe]->Fill(vQ2[event], tweak*vWeight[event]);
				}
			}

			myReader.Restart();	

			if (event != nevents-1) {
				cout<<"Found tweaks for "<<event+1<<" events. Expected "<<nevents<<" events"<<endl;
				return;
			}
		
			// Plot Declaration
			TH1D *EnuIncPlot_hi, *EnuIncPlot_lo;
			TH1D *Q2IncPlot_hi, *Q2IncPlot_lo;
		
			vector<int> sigma_vector = {-3, -2, -1, 0, 1, 2, 3};
			int hi_index, lo_index;
			for (int i=0; i<sigma_vector.size(); i++) {
				if (sigma_vector[i] == 1) {hi_index = i;}
				else if (sigma_vector[i] == -1) {lo_index = i;}
			}
		
			EnuIncPlot_hi = (TH1D *)EnuIncPlot[hi_index]->Clone("EnuIncPlot_hi");
			EnuIncPlot_lo = (TH1D *)EnuIncPlot[lo_index]->Clone("EnuIncPlot_lo");
			Q2IncPlot_hi = (TH1D *)Q2IncPlot[hi_index]->Clone("Q2IncPlot_hi");
			Q2IncPlot_lo = (TH1D *)Q2IncPlot[lo_index]->Clone("Q2IncPlot_lo");
		
			// Plot all curves as a sanity check!
			//plot_sigmas(param+"_EnuInc", sample, nuniverses, EnuIncPlot, EnuIncPlot_hi, EnuIncPlot_lo, sigma_vector);
			//plot_sigmas(param+"_Q2Inc", sample, nuniverses, Q2IncPlot, Q2IncPlot_hi, Q2IncPlot_lo, sigma_vector);
		
			// Write to file
			EnuIncPlot_hi->Write("EnuInc_"+param+"_plus1");
			Q2IncPlot_hi->Write("Q2Inc_"+param+"_plus1");
			EnuIncPlot_lo->Write("EnuInc_"+param+"_minus1");
			Q2IncPlot_lo->Write("Q2Inc_"+param+"_minus1");

		}	
		
		cout<<"Processing the extra genie parameters"<<endl;

		for (TString special_param: special_param_vector) {
		
			cout<<"Processing "<<special_param<<endl;

		        // Plot declarations
			int nuniverses = 1;
		        TH1D* EnuIncPlot[nuniverses];
		        TH1D* Q2IncPlot[nuniverses];
		
		        for (int universe=0; universe<nuniverses; universe++) {
		        	EnuIncPlot[universe] = (TH1D *)root_in->Get("EnuInc")->Clone(("EnuInc"+to_string(universe)).c_str());
				EnuIncPlot[universe]->Reset("ICESM");
		        	Q2IncPlot[universe] = (TH1D *)root_in->Get("Q2Inc")->Clone(("Q2Inc"+to_string(universe)).c_str());
				Q2IncPlot[universe]->Reset("ICESM");
		        }
		
			// Declare values and arrays I want to read from tweak_file tree 
			TTreeReaderValue<int> ntweak_responses(myReader, "ntweaks_"+special_param);
			TTreeReaderArray<double> tweak_responses(myReader, "tweak_responses_"+special_param);
		
			// Fill the plots
		        int event = -1; 
			while (myReader.Next()) {
				event += 1;
				if (vInc[event] != 1) {continue;}
				int ntweaks = *ntweak_responses;
				if (ntweaks != nuniverses) {
					cout<<"ntweaks = "<<ntweaks<<" is not the expected number, "<<nuniverses<<endl;
					return;
				}
				for (int universe=0; universe<ntweaks; universe++) {
					double tweak = tweak_responses[universe];
		        		EnuIncPlot[universe]->Fill(vEnu[event], tweak*vWeight[event]);
		        		Q2IncPlot[universe]->Fill(vQ2[event], tweak*vWeight[event]);
				}
			}
		
			myReader.Restart();

			if (event != nevents-1) {
				cout<<"Found tweaks for "<<event+1<<" events. Expected "<<nevents<<" events"<<endl;
				return;
			}
		
			// Plot Declaration
			TH1D *EnuIncPlot_hi, *Q2IncPlot_hi;
		
			int hi_index = 0;
			EnuIncPlot_hi = (TH1D *)EnuIncPlot[hi_index]->Clone("EnuIncPlot_hi");
			Q2IncPlot_hi = (TH1D *)Q2IncPlot[hi_index]->Clone("Q2IncPlot_hi");
		
			// Write to file
			EnuIncPlot_hi->Write("EnuInc_"+special_param+"_error");
			Q2IncPlot_hi->Write("Q2Inc_"+special_param+"_error");
		
		}	
	}
}
