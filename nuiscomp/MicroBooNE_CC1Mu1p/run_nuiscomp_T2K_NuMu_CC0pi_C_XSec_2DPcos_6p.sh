# Fit for RPA_CCQE, b4, b3, b2, b1, NormCCMEC 
nuiscomp \
	-c cards/nuiscomp_T2K_NuMu_CC0pi_C_XSec_2DPcos_6p.card \
	-o ${nuiscomp}/MicroBooNE_CC1p/nuiscomp_T2K_NuMu_CC0pi_C_XSec_2DPcos_6p.root \
	-n 100000

echo "It took $SECONDS seconds for this script to execute."
