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
	const TString flat_ana_outfile = "/pnfs/dune/persistent/users/apapadop/SBN_tune/flat_analyser_samples";
	// +/- 1 sigma tweaks	
	const TString tweaked_outfile = "/pnfs/dune/persistent/users/apapadop/SBN_tune/DumpConfiguredTweaksNuSyst";

	// +/- 1 sigma tweak plots	
	const TString tweaked_plots_path = "/pnfs/dune/persistent/users/apapadop/SBN_tune/plot_tweaks";


	//----------------------------------------//



}
#endif
