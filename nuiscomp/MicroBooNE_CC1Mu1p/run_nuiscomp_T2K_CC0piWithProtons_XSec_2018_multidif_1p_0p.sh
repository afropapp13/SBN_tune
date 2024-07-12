# Fit for RPA_CCQE, b4, b3, b2, b1, NormCCMEC 
nuiscomp \
	-c cards/nuiscomp_T2K_CC0piWithProtons_XSec_2018_multidif_1p_0p.card \
	-o ${nuiscomp}/MicroBooNE_CC1p/nuiscomp_T2K_CC0piWithProtons_XSec_2018_multidif_1p_0p.root \
	-n 100000

echo "It took $SECONDS seconds for this script to execute."
