#ifndef CONSTANTS_H
#define CONSTANTS_H

#include "TString.h"
#include "TMath.h"

#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <map>

using namespace std;

namespace Constants {

	//----------------------------------------//

	// Exporting paths

	// Flat analyzer output files
	const TString flat_ana_outfile = "/exp/dune/data/users/apapadop/SBN_tune/flat_analyser_samples/";

	// +/- 1 sigma tweaks	
	const TString tweaked_outfile = "/exp/dune/data/users/apapadop/SBN_tune/DumpConfiguredTweaksNuSyst/";

	// +/- 1 sigma tweak plots	
	const TString tweaked_plots_path = "/exp/dune/data/users/apapadop/SBN_tune/plot_tweaks/";

	// nuiscomp output files
	const TString nuiscomp_uboone_CC1p = "/exp/dune/data/users/apapadop/SBN_tune/nuiscomp/MicroBooNE_CC1p/"; 
	const TString nuiscomp_uboone_CCNp = "/exp/dune/data/users/apapadop/SBN_tune/nuiscomp/MicroBooNE_CCNp/"; 

	const TString nuismin = "/exp/dune/data/users/apapadop/SBN_tune/nuismin/";
	const TString nuiscomp = "/exp/dune/data/users/apapadop/SBN_tune/nuiscomp/";
	const TString nuiscomp_plot_xsec = "/exp/dune/data/users/apapadop/SBN_tune/nuiscomp/plot_xsec/";

	//----------------------------------------//



}
#endif
