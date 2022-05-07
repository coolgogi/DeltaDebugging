MAKEINPUT=makeinput
INPUT=
OUTPUT_PATH=
N=100
TARGET=
TARGETDIR=./target
gcc ${MAKEINPUT}.c -o ${MAKEINPUT}
./${MAKEINPUT} ${INPUT} ${OUTPUT_PATH}


for ((i=0 ; i < ${N} ; i++))
do
	./${MAKEINPUT} ${TARGETDIR}/${TARTGET} ${OUTPUT_PATH}
#	echo ${i}
done
