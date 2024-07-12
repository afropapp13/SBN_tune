#include <sstream>

TString get_chi2(TH1D *hData, TH1D *hMC, TH2D *cov) { 

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
        TMatrixD  mret = m * m_cov * mT ;
        double chi2 = mret(0, 0);

        stringstream stream;
        stream << fixed << setprecision(1) << chi2;
        string chi2_str = stream.str();
	string entry = "chi2 / nbins = "+chi2_str+" / "+to_string(nbins);
        return entry.c_str();

}

void plot_1pfits_MicroBooNE_CC1MuNp_XSec() {

        //TString analysis = "I";
        TString analysis = "II";

	// Open nominal MicroBooNE comparison file
        TFile *nomfile = new TFile("/exp/dune/app/users/jwolfs/t2k_tune/outfiles/nuiscomp/MicroBooNE_CC1MuNp/nuiscomp_0p.root", "read");

	// XSec variables
        vector<TString> var_vector;
        var_vector.push_back("Pmu");
        var_vector.push_back("cosmu");
        var_vector.push_back("Pp");
        var_vector.push_back("cosp");
        var_vector.push_back("thetamup");

	// Fit parameters
	vector<TString> parameter_vector;
	parameter_vector.push_back("RPA_CCQE");
	parameter_vector.push_back("b1");
	parameter_vector.push_back("b2");
	parameter_vector.push_back("b3");
	parameter_vector.push_back("b4");
	parameter_vector.push_back("NormCCMEC");
	int npar = parameter_vector.size();

	for (TString var: var_vector) {

		// Set up plot
	        TCanvas *can = new TCanvas();
		THStack *stk;
	        TLegend *leg = new TLegend(0.7,0.75,1.0,1.0);
		int color=0;
		bool dashed_line = false;
	
		for (int par=0; par<npar; par++) {

			// Import hists
                        TString infilename = "/exp/dune/app/users/jwolfs/t2k_tune/outfiles/nuiscomp/MicroBooNE_CC1MuNp/analysis"+analysis+
                                "/nuiscomp_"+parameter_vector[par]+".root";
	                TFile *infile = new TFile(infilename, "read");
			TH1D *hData, *hMC_prefit, *hMC_postfit;
			if (par == 0) {
		        	hData = (TH1D *)infile->Get("MicroBooNE_CC1MuNp_XSec_1D"+var+"_nu_data")->Clone("hData");
	        		TString xtitle = hData->GetXaxis()->GetTitle();
	        		TString ytitle = hData->GetYaxis()->GetTitle();
	        		stk = new THStack("stk", ";"+xtitle+";"+ytitle+"");
		        	hMC_prefit = (TH1D *)nomfile->Get("MicroBooNE_CC1MuNp_XSec_1D"+var+"_nu_MC")->Clone("hMC_prefit");
			}
	        	hMC_postfit = (TH1D *)infile->Get("MicroBooNE_CC1MuNp_XSec_1D"+var+"_nu_MC")->Clone("hMC_postfit");
	
			// Calculate chi2
			TH2D *cov_prefit, *cov_postfit;
			TString chi2_entry_prefit, chi2_entry_postfit;
			if (par == 0) {
	        		cov_prefit = (TH2D *)nomfile->Get("MicroBooNE_CC1MuNp_XSec_1D"+var+"_nu_INVCOV")->Clone("cov_prefit");
				chi2_entry_prefit = get_chi2(hData, hMC_prefit, cov_prefit);

                                // Plot the ub covariance matrix 
                                //cov_prefit->SetStats(0);
                                //can->cd();
                                //cov_prefit->Draw("colz");
                                //can->SetRightMargin(0.13);
                                //can->Print("/exp/dune/app/users/jwolfs/t2k_tune/outpngs/plot_XSec/MicroBooNE_CC1MuNp/analysis"+analysis
                                //      +"/1pfits_ub_cov.png");

			}
	        	cov_postfit = (TH2D *)infile->Get("MicroBooNE_CC1MuNp_XSec_1D"+var+"_nu_INVCOV")->Clone("cov_postfit");
			chi2_entry_postfit = get_chi2(hData, hMC_postfit, cov_postfit);
	
			if (par == 0) {

				// Plot MicroBooNE data
				hData->SetTitle("");
				hData->SetMarkerColor(1);
				hData->SetMarkerStyle(20);
				hData->SetMarkerSize(0.5);
				hData->SetLineColor(1);
				hData->SetLineWidth(1);
				hData->SetMinimum(0.);
				hData->Draw("e1p");
		        	leg->AddEntry(hData, "MicroBooNE Data", "lpfe");
		
				// Plot nominal GENIE MC
				hMC_prefit->SetLineColor(okabeIto[color]);
				if (dashed_line) {hMC_prefit->SetLineStyle(7);}
				color += 1;
				if (color == okabeIto.size()) {
					color = 0;
					dashed_line = true;
				}
				hMC_prefit->SetLineWidth(1);
		        	stk->Add(hMC_prefit);
		        	leg->AddEntry(hMC_prefit, "Nominal ("+chi2_entry_prefit+")", "l");

			}
	
			// Plot reweighted GENIE MC
			hMC_postfit->SetLineColor(okabeIto[color]);
			if (dashed_line) {hMC_postfit->SetLineStyle(7);}
			color += 1;
			if (color == okabeIto.size()) {
				color = 0;
				dashed_line = true;
			}
			hMC_postfit->SetLineWidth(1);
	        	stk->Add(hMC_postfit);
	        	leg->AddEntry(hMC_postfit, parameter_vector[par]+" Tune "+analysis+" ("+chi2_entry_postfit+")", "l");
	
		}

		// Finish the hist
	        stk->Draw("same nostack hist");
	        leg->Draw();
                can->Print("/exp/dune/app/users/jwolfs/t2k_tune/outpngs/plot_XSec/MicroBooNE_CC1MuNp/analysis"+analysis
                        +"/1pfits_MicroBooNE_CC1MuNp_XSec_1D"+var+"_nu.png");

	}

	nomfile->Close();

}
