cd FlatTreeAnalyzer/
root -b run_FlatTreeAnalyzer.C 
cd ..

# Get the +/-1 sigma weights
cd DumpConfiguredTweaksNuSyst
./run_DumpConfiguredTweaksNuSyst.sh
./run_DumpConfiguredTweaksNuSyst_T2K.sh

# get the +/-1 sigma vars
root -b get_tweaks.cxx

#plot the vars
root -b plot_tweaks.cxx

cd ..
