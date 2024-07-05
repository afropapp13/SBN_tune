{	
	gROOT->ProcessLine(".L FlatTreeAnalyzer.cxx+");

	vector<TString> beam_vector;
	beam_vector.push_back("");
	//beam_vector.push_back("numi_fhc_icarus_");
	//beam_vector.push_back("numi_rhc_icarus_");

	vector<TString> current_vector;
	current_vector.push_back("CC_");
	current_vector.push_back("NC_");

	vector<TString> flavor_vector;
	flavor_vector.push_back("numu");
	flavor_vector.push_back("anumu");
	flavor_vector.push_back("nue");
	flavor_vector.push_back("anue");

	for (TString beam: beam_vector) {
		for (TString current: current_vector) {
			for (TString flavor: flavor_vector) {
				TString InDir;
				if (beam != "" and flavor == "anumu") {
					InDir = "/pnfs/dune/persistent/users/apapadop/GENIE_SBN/"+beam+"v3_4_0_AR23_20i_00_000_"+current+"numubar/";
				}
				else if (beam != "" and flavor == "anue") {
					InDir = "/pnfs/dune/persistent/users/apapadop/GENIE_SBN/"+beam+"v3_4_0_AR23_20i_00_000_"+current+"nuebar/";
				}
				else {
					InDir = "/pnfs/dune/persistent/users/apapadop/GENIE_SBN/"+beam+"v3_4_0_AR23_20i_00_000_"+current+flavor+"/";
				}
				TString InFile;
				if (flavor == "numu") {InFile = InDir+"14_1000180400_"+current+"v3_4_0_AR23_20i_00_000.flat.root";}
				else if (flavor == "anumu") {InFile = InDir+"-14_1000180400_"+current+"v3_4_0_AR23_20i_00_000.flat.root";}
				else if (flavor == "nue") {InFile = InDir+"12_1000180400_"+current+"v3_4_0_AR23_20i_00_000.flat.root";}
				else {InFile = InDir+"-12_1000180400_"+current+"v3_4_0_AR23_20i_00_000.flat.root";}
				TString OutFile = flat_ana_outfile + "/nominal_hists_"+beam+current+flavor+".root";
				gROOT->ProcessLine("FlatTreeAnalyzer(\""+InFile+"\",\""+beam+"\",\""+current+"\",\""+flavor+"\",\""+OutFile+"\").Loop()");
				cout<<endl;
			}
		}
	}

	TString beam = "T2K_";
	TString current = "CC_";
	TString flavor = "numu";
	TString InDir = "/pnfs/dune/persistent/users/apapadop/GENIE_SBN/"+beam+"v3_4_0_AR23_20i_00_000_"+current+flavor+"/";
	TString InFile = InDir+"14_1000180400_"+current+"v3_4_0_AR23_20i_00_000.flat.root";
	TString OutFile = flat_ana_outfile + "/nominal_hists_"+beam+current+flavor+".root";
	gROOT->ProcessLine("FlatTreeAnalyzer(\""+InFile+"\",\""+beam+"\",\""+current+"\",\""+flavor+"\",\""+OutFile+"\").Loop()");
	cout<<endl;

};
