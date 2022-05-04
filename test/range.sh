RANGE=../bin/r_main
TARGET=../jsmn/jsondump
OUTPUT=output/range_output
INPUT=input/dd.json
MSG=jsondump.c:44
P=1.0
echo "range test"


$RANGE $TARGET $INPUT $MSG $P
