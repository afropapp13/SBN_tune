# Fit for RPA_CCQE, b4, b3, b2, b1, NormCCMEC
nuismin \
	-c cards/nuismin_6p.card \
	-o ${nuismin}/nuismin_6p.root \
	-n 100000

echo "It took $SECONDS seconds for this script to execute."
