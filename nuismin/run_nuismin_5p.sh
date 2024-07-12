# Fit for RPA_CCQE, b4, b3, b2, b1
nuismin \
	-c cards/nuismin_5p.card \
	-o ${nuismin}/nuismin_5p.root \
	-n 100000

echo "It took $SECONDS seconds for this script to execute."
