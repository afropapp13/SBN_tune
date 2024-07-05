#include <sys/stat.h>

void plot_tweaks() {

        vector<TString> sample_vector;
        //sample_vector.push_back("CC_anue");
        //sample_vector.push_back("CC_anumu");
        //sample_vector.push_back("CC_nue");
        sample_vector.push_back("CC_numu");
        //sample_vector.push_back("NC_anue");
        //sample_vector.push_back("NC_anumu");
        //sample_vector.push_back("NC_nue");
        //sample_vector.push_back("NC_numu");
        //sample_vector.push_back("numi_fhc_icarus_CC_anue");
        //sample_vector.push_back("numi_fhc_icarus_CC_anumu");
        //sample_vector.push_back("numi_fhc_icarus_CC_nue");
        //sample_vector.push_back("numi_fhc_icarus_CC_numu");
        //sample_vector.push_back("numi_fhc_icarus_NC_anue");
        //sample_vector.push_back("numi_fhc_icarus_NC_anumu");
        //sample_vector.push_back("numi_fhc_icarus_NC_nue");
        //sample_vector.push_back("numi_fhc_icarus_NC_numu");
        //sample_vector.push_back("numi_rhc_icarus_CC_anue");
        //sample_vector.push_back("numi_rhc_icarus_CC_anumu");
        //sample_vector.push_back("numi_rhc_icarus_CC_nue");
        //sample_vector.push_back("numi_rhc_icarus_CC_numu");
        //sample_vector.push_back("numi_rhc_icarus_NC_anue");
        //sample_vector.push_back("numi_rhc_icarus_NC_anumu");
        //sample_vector.push_back("numi_rhc_icarus_NC_nue");
        //sample_vector.push_back("numi_rhc_icarus_NC_numu");
        //sample_vector.push_back("T2K_CC_numu");
        int num_samples = sample_vector.size();

	vector<TString> var_vector = {"EnuInc", "Q2Inc"};

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

		// Data input
		TFile *file_cv = new TFile(flat_ana_outfile + "/nominal_hists_"+sample+".root", "read");
		TFile *file_1sigma = new TFile(tweaked_outfile + "/1sigma_hists_"+sample+".root", "read");

		for (TString var: var_vector) {
        	
			TString directory = tweaked_plots_path + "/"+sample+"/";
			mkdir(directory, 0777);
			TString sub_directory = directory+var+"/";
			mkdir(sub_directory, 0777);
		        TCanvas *can = new TCanvas();
			TH1D *hist_cv = (TH1D *)file_cv->Get(var);
			hist_cv->Scale(1., "width");
			hist_cv->SetLineWidth(2);
		        TString xtitle = hist_cv->GetXaxis()->GetTitle();
		        TString ytitle = hist_cv->GetYaxis()->GetTitle();

			for (TString param: param_vector) {

		        	THStack *stk = new THStack("stk", ";"+xtitle+";"+ytitle+"");
		        	TLegend *leg = new TLegend(0.6,0.75,0.95,0.95);
				leg->SetHeader("#bf{"+sample+" "+param+"}", "c");
				hist_cv->SetLineColor(kBlue);
		        	leg->AddEntry(hist_cv, "central value");
				TH1D *hist_plus1 = (TH1D *)file_1sigma->Get(var+"_"+param+"_plus1");
				hist_plus1->Scale(1., "width");
				int color = 0;
				hist_plus1->SetLineColor(kOrange+7);
				hist_plus1->SetLineWidth(2);
				color += 1;
		        	stk->Add(hist_plus1);
		        	leg->AddEntry(hist_plus1, "plus 1#sigma");
				TH1D *hist_minus1 = (TH1D *)file_1sigma->Get(var+"_"+param+"_minus1");
				hist_minus1->Scale(1., "width");
				hist_minus1->SetLineColor(kGreen-2);
				hist_minus1->SetLineWidth(2);
				color += 1;
		        	stk->Add(hist_minus1);
		        	leg->AddEntry(hist_minus1, "minus 1#sigma");
		        	stk->Add(hist_cv);
		        	stk->Draw("nostack hist");
		        	leg->Draw();
				can->Print(sub_directory+var+"_"+param+".pdf");

			}

			for (TString special_param: special_param_vector) {

		        	THStack *stk = new THStack("stk", ";"+xtitle+";"+ytitle+"");
		        	TLegend *leg = new TLegend(0.6,0.75,0.95,0.95);
				leg->SetHeader("#bf{"+sample+" "+special_param+"}", "c");
				hist_cv->SetLineColor(kBlue);
		        	leg->AddEntry(hist_cv, "dial off");
				TH1D *hist_plus1 = (TH1D *)file_1sigma->Get(var+"_"+special_param+"_error");
				hist_plus1->SetLineWidth(2);
				hist_plus1->Scale(1., "width");
                                int color = 0;
                                hist_plus1->SetLineColor(kOrange+7);
				hist_plus1->SetLineWidth(2);
                                color += 1;
		        	stk->Add(hist_plus1);
		        	leg->AddEntry(hist_plus1, "dial on");
		        	stk->Add(hist_cv);
		        	stk->Draw("nostack hist");
		        	leg->Draw();
		        	can->Print(sub_directory+var+"_"+special_param+".pdf");

			}

		}

		file_cv->Close();
		file_1sigma->Close();
		
	}
}
