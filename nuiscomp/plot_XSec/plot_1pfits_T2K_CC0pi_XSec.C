#include <sstream>

TString get_chi2(TH1D *hData, TH1D *hMC, TH2D *cov, TH1D *hChi2, TString analysis) { 

        int nbins = hData->GetNbinsX();
        TVectorD v_data (nbins);		// microboone unfolded cross section
        TVectorD v_mc (nbins);			// mc unfolded cross section 
        TMatrixD m_cov (nbins, nbins);		// covariance matrix

        // Import the covariance matrix 
        for (int i=0; i<nbins; i++) {
                v_data(i) = hData->GetBinContent(i+1)*pow(10,38);
                v_mc(i) = hMC->GetBinContent(i+1)*pow(10,38);
                for (int j=0; j<nbins; j++) {
                        m_cov(i, j) = cov->GetBinContent(i+1, j+1);
                }
        }

        // convert vectors to matrices for computation
        TMatrixD m_mc(1, nbins), m_data(1, nbins);
        for (int i=0; i<nbins; i++) {
              m_mc(0, i)= v_mc(i);
              m_data(0, i)= v_data(i);
        }

        // calculate chi2
        TMatrixD m = m_mc - m_data;
        TMatrixD mT = m_mc - m_data;
        mT.T();
	//m_cov.Invert(); //I am importing the inverted covariance matrix now
	TMatrixD  mret = m * m_cov;
	double chi2 = 0;
	for (int i=0; i<nbins; i++) {
		double addend = mret(0, i)*mT(i, 0);
		//cout<<"bin "<<i+1<<" addend = "<<addend<<endl;
		chi2 += addend;
		hChi2->SetBinContent(i+1, addend);
	}

        //TMatrixD  mret = m * m_cov * mT ;
        //double chi2 = mret(0, 0);

        stringstream stream;
        stream << fixed << setprecision(0) << chi2;
        string chi2_str = stream.str();
	string entry = "chi2 / nbins = "+chi2_str+" / "+to_string(nbins);
        return entry.c_str();

}

void plot_1pfits_T2K_CC0pi_XSec() {

        //TString analysis = "I";
        TString analysis = "II";

	vector<TString> parameter_vector;
	parameter_vector.push_back("RPA_CCQE");
	parameter_vector.push_back("b4");
	parameter_vector.push_back("b3");
	parameter_vector.push_back("b2");
	parameter_vector.push_back("b1");
	parameter_vector.push_back("NormCCMEC");
	int npar = parameter_vector.size();

	// Create file to which to save fit values
	ofstream outfile;
        outfile.open("/exp/dune/app/users/jwolfs/t2k_tune/outfiles/nuismin/T2K_CC0pi/analysis"+analysis+"/parval_1pfits.txt");
	outfile<<"fit_parameter"<<"\t"<<"fit_value"<<endl;

	// Set up plot
	TCanvas *can = new TCanvas();
	THStack *stk;
	THStack *chi2_stk;
	TLegend *leg = new TLegend(0.7,0.75,1.0,1.0);
	TLegend *chi2_leg = new TLegend(0.15,0.6,0.45,0.85);
	chi2_leg->SetBorderSize(0);
	int color=0;
	bool dashed_line = false;
	
	for (int par=0; par<npar; par++) {

		// Import hists
		TString infilename = "/exp/dune/app/users/jwolfs/t2k_tune/outfiles/nuismin/T2K_CC0pi/analysis"+analysis+
			"/nuismin_"+parameter_vector[par]+".root";
	        TFile *infile = new TFile(infilename, "read");
		TH1D *hData, *hMC_prefit, *hMC_postfit;
		TString mc_filename = "T2K_CC0pi_XSec_2DPcos_nu_"+analysis+"_MC";
		if (analysis == "II") {mc_filename += "_1D";}
	        if (par == 0) {
			hData = (TH1D *)infile->Get("T2K_CC0pi_XSec_2DPcos_nu_"+analysis+"_data_1D")->Clone("hData");
			TString xtitle = hData->GetXaxis()->GetTitle();
			TString ytitle = hData->GetYaxis()->GetTitle();
			stk = new THStack("stk", ";"+xtitle+";"+ytitle+"");
			chi2_stk = new THStack("chi2_stk", ";"+xtitle+";Chi-Square Addend");
	        	hMC_prefit = (TH1D *)infile->Get("nominal/"+mc_filename)->Clone("hMC_prefit");
		}
	        hMC_postfit = (TH1D *)infile->Get(mc_filename)->Clone("hMC_postfit");
		TH1D *hChi2_postfit = (TH1D *)hMC_postfit->Clone("hChi2_postfit");
		hChi2_postfit->Reset("ICESM");
		TH1D *hChi2_prefit = (TH1D *)hChi2_postfit->Clone("hChi2_prefit");
	
		// Save fit values
	        TTreeReader myReader("fit_result", infile);
	        TTreeReaderArray<double> par_vals(myReader, "parameter_values");
	        TTreeReaderArray<double> par_errs(myReader, "parameter_errors");
	        myReader.Next();
		outfile<<parameter_vector[par]<<"\t"<<par_vals[0]<<endl;
		
		// Calculate chi2
	        TH2D *cov_prefit, *cov_postfit;
		TString chi2_entry_prefit, chi2_entry_postfit;
		if (par == 0) {
			cov_prefit = (TH2D *)infile->Get("nominal/T2K_CC0pi_XSec_2DPcos_nu_"+analysis+"_INVCOV")->Clone("cov_prefit");
			chi2_entry_prefit = get_chi2(hData, hMC_prefit, cov_prefit, hChi2_prefit, analysis);

                        // Plot the t2k covariance matrix 
			//cov_prefit->SetStats(0);
			//cov_prefit->Draw("colz");
			//can->SetRightMargin(0.13);
        		//can->Print("/exp/dune/app/users/jwolfs/t2k_tune/outpngs/plot_XSec/T2K_CC0pi/analysis"+analysis
        		//        +"/nom_cov_"+parameter_vector[par]+".png");

		}
	        cov_postfit = (TH2D *)infile->Get("T2K_CC0pi_XSec_2DPcos_nu_"+analysis+"_INVCOV")->Clone("cov_postfit");
		chi2_entry_postfit = get_chi2(hData, hMC_postfit, cov_postfit, hChi2_postfit, analysis);
	
		if (par == 0) {
			// Plot T2K data
			hData->SetTitle("");
			hData->SetStats(0);
			hData->SetMarkerColor(1);
			hData->SetMarkerStyle(20);
			hData->SetMarkerSize(0.5);
			hData->SetLineColor(1);
			hData->Draw("e1p");
		        leg->AddEntry(hData, "T2K Dataset "+analysis, "lpfe");
		
			// Plot GENIE MC (prefit)
			hMC_prefit->SetLineColor(okabeIto[color]);
			if (dashed_line) {hMC_prefit->SetLineStyle(7);}
		        stk->Add(hMC_prefit);
		        leg->AddEntry(hMC_prefit, "Nominal ("+chi2_entry_prefit+")", "l");

			// Plot GENIE MC Chi2 (prefit)
			hChi2_prefit->SetLineColor(okabeIto[color]);
			if (dashed_line) {hChi2_prefit->SetLineStyle(7);}
			color += 1;
			if (color == okabeIto.size()) {
				color = 0;
				dashed_line = true;
			}
		        chi2_stk->Add(hChi2_prefit);
		        chi2_leg->AddEntry(hChi2_prefit, "Nominal ("+chi2_entry_prefit+")", "l");

		}
	
		// Plot GENIE MC (postfit)
		hMC_postfit->SetLineColor(okabeIto[color]);
		if (dashed_line) {hMC_postfit->SetLineStyle(7);}
	        stk->Add(hMC_postfit);
	        leg->AddEntry(hMC_postfit, parameter_vector[par]+" ("+chi2_entry_postfit+")", "l");

		// Plot GENIE MC Chi2 (postfit)	
		hChi2_postfit->SetLineColor(okabeIto[color]);
		if (dashed_line) {hChi2_postfit->SetLineStyle(7);}
		color += 1;
		if (color == okabeIto.size()) {
			color = 0;
			dashed_line = true;
		}
		chi2_stk->Add(hChi2_postfit);
	        chi2_leg->AddEntry(hChi2_postfit, parameter_vector[par]+" ("+chi2_entry_postfit+")", "l"); 

	}

	// Finish the hist
        stk->Draw("same nostack hist");
        leg->Draw();
        can->Print("/exp/dune/app/users/jwolfs/t2k_tune/outpngs/plot_XSec/T2K_CC0pi/analysis"+analysis
                +"/1pfits_xsec.png");

        chi2_stk->Draw("nostack hist");
        chi2_leg->Draw();
        can->Print("/exp/dune/app/users/jwolfs/t2k_tune/outpngs/plot_XSec/T2K_CC0pi/analysis"+analysis
                +"/1pfits_chi2.png");

}
