# Fit for RPA_CCQE, b4, b3, b2, b1, NormCCMEC 
nuiscomp \
	-c cards/nuiscomp_6p_shape_only.card \
	-o ${nuiscomp}/MicroBooNE_CC1p/nuiscomp_6p_shape_only.root \
	-n 100000

echo "It took $SECONDS seconds for this script to execute."
