# Fit for NormCCMEC 
nuismin \
	-c cards/nuismin_NormCCMEC.card \
	-o ${nuismin}/nuismin_NormCCMEC.root \
	-n 100000

echo "It took $SECONDS seconds for this script to execute."
