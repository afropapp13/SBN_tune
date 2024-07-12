#!/bin/bash

export probe="${1}" # 14,-14,12,-12
export probelabel="${2}" # numu, numub, nue, nueb
export tune="${3}" # G18_10a_02_11a, AR23_20i_00_000
export interaction="${4}" # CC, NC

export events="1000000"
export version="v3_4_0"
export target="1000060120"
export minE="0."
export maxE="10."
export fluxfile="/exp/dune/app/users/apapadop/BuildEventGenerators/jobcards/MCC9_FluxHist_volTPCActive.root"
export fluxhisto="hEnumu_cv"
export outdir="/pnfs/dune/persistent/users/apapadop/GENIE_SBN/T2K_BNB_"${version}"_"${tune}"_"${interaction}"_"${probelabel}

echo ${outdir}

# Produce the GENIE splines
gmkspl -p ${probe} -t ${target} -e ${maxE} -o ${outdir}/${probe}_${target}_${interaction}_${version}_${tune}.xml --tune ${tune} --event-generator-list ${interaction}

# Convert the xml splines to root format
gspl2root -f ${outdir}/${probe}_${target}_${interaction}_${version}_${tune}.xml --event-generator-list ${interaction} -p ${probe} -t ${target} -o ${outdir}/${probe}_${target}_${interaction}_${version}_${tune}.xml.root --tune ${tune}

# Generate GENIE events
gevgen -n $events -p ${probe} -t ${target} -e ${minE},${maxE}  --event-generator-list ${interaction} --tune ${tune} --cross-sections ${outdir}/${probe}_${target}_${interaction}_${version}_${tune}.xml -f ${fluxfile},${fluxhisto} -o ${outdir}/${probe}_${target}_${interaction}_${version}_${tune}.ghep.root 

# Convert file from ghep to gst
gntpc -f gst -i ${outdir}/${probe}_${target}_${interaction}_${version}_${tune}.ghep.root -o ${outdir} /${probe}_${target}_${interaction}_${version}_${tune}.gst.root --tune ${tune}

# Convert file from ghep to nuisance format
PrepareGENIE -i ${outdir}/${probe}_${target}_${interaction}_${version}_${tune}.ghep.root -t ${target}[1] -o ${outdir}/${probe}_${target}_${interaction}_${version}_${tune}.gprep.root -f ${fluxfile},${fluxhisto}

# Convert to nuisance flat tree format
nuisflat -i GENIE:${outdir}/${probe}_${target}_${interaction}_${version}_${tune}.gprep.root -o ${outdir}/${probe}_${target}_${interaction}_${version}_${tune}.flat.root

echo
echo ${outdir}
echo