# CHARGED CURRENT 
# MUON NEUTRINO 
DumpConfiguredTweaksNuSyst \
        -c ../../myParamHeader.fcl \
        -i /pnfs/dune/persistent/users/apapadop/GENIE_SBN/v3_4_0_AR23_20i_00_000_CC_numu/14_1000180400_CC_v3_4_0_AR23_20i_00_000.gprep.root \
        -o ${tweaks_file}/tweaks_CC_numu.root 

# MUON ANTINEUTRINO 
DumpConfiguredTweaksNuSyst \
        -c ../../myParamHeader.fcl \
        -i /pnfs/dune/persistent/users/apapadop/GENIE_SBN/v3_4_0_AR23_20i_00_000_CC_anumu/-14_1000180400_CC_v3_4_0_AR23_20i_00_000.gprep.root \
        -o ${tweaks_file}/tweaks_CC_anumu.root 

# ELECTRON NEUTRINO 
DumpConfiguredTweaksNuSyst \
        -c ../../myParamHeader.fcl \
        -i /pnfs/dune/persistent/users/apapadop/GENIE_SBN/v3_4_0_AR23_20i_00_000_CC_nue/12_1000180400_CC_v3_4_0_AR23_20i_00_000.gprep.root \
        -o ${tweaks_file}/tweaks_CC_nue.root 

# ELECTRON ANTINEUTRINO 
DumpConfiguredTweaksNuSyst \
        -c ../../myParamHeader.fcl \
        -i /pnfs/dune/persistent/users/apapadop/GENIE_SBN/v3_4_0_AR23_20i_00_000_CC_anue/-12_1000180400_CC_v3_4_0_AR23_20i_00_000.gprep.root \
        -o ${tweaks_file}/tweaks_CC_anue.root 

# NEUTRAL CURRENT 
# MUON NEUTRINO 
DumpConfiguredTweaksNuSyst \
        -c ../myParamHeader.fcl \
	-i /pnfs/dune/persistent/users/apapadop/GENIE_SBN/v3_4_0_AR23_20i_00_000_NC_numu/14_1000180400_NC_v3_4_0_AR23_20i_00_000.gprep.root \
        -o ${tweaks_file}/tweaks_NC_numu.root 

# MUON ANTINEUTRINO 
DumpConfiguredTweaksNuSyst \
        -c ../../myParamHeader.fcl \
        -i /pnfs/dune/persistent/users/apapadop/GENIE_SBN/v3_4_0_AR23_20i_00_000_NC_anumu/-14_1000180400_NC_v3_4_0_AR23_20i_00_000.gprep.root \
        -o ${tweaks_file}/tweaks_NC_anumu.root 

# ELECTRON NEUTRINO 
DumpConfiguredTweaksNuSyst \
        -c ../../myParamHeader.fcl \
	-i /pnfs/dune/persistent/users/apapadop/GENIE_SBN/v3_4_0_AR23_20i_00_000_NC_nue/12_1000180400_NC_v3_4_0_AR23_20i_00_000.gprep.root \
        -o ${tweaks_file}/tweaks_NC_nue.root 

# ELECTRON ANTINEUTRINO 
DumpConfiguredTweaksNuSyst \
        -c ../../myParamHeader.fcl \
	-i /pnfs/dune/persistent/users/apapadop/GENIE_SBN/v3_4_0_AR23_20i_00_000_NC_anue/-12_1000180400_NC_v3_4_0_AR23_20i_00_000.gprep.root \
        -o ${tweaks_file}/tweaks_NC_anue.root 
