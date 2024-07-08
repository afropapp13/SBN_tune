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
	const TString flat_ana_outfile = "/exp/dune/data/users/apapadop/SBN_tune/flat_analyser_samples";
	// +/- 1 sigma tweaks	
	const TString tweaked_outfile = "/exp/dune/data/users/apapadop/SBN_tune/DumpConfiguredTweaksNuSyst";

	// +/- 1 sigma tweak plots	
	const TString tweaked_plots_path = "/exp/dune/data/users/apapadop/SBN_tune/plot_tweaks";


	//----------------------------------------//



}
#endif
