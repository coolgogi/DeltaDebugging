RANGE=../bin/r_main
THREAD=../bin/process/pcs_main
OUTPUT=output/range_output

TARGET=(../jsmn/jsondump ../fuzzer-test-suite/build_libxml2/libxml2-v2.9.2-fsanitize_fuzzer ../fuzzer-test-suite/build_libxml2/libxml2-v2.9.2-fsanitize_fuzzer ../fuzzer-test-suite/build_libxml2/libxml2-v2.9.2-fsanitize_fuzzer ../fuzzer-test-suite/build_sqlite/sqlite-2016-11-14-fsanitize_fuzzer ../fuzzer-test-suite/build_sqlite/sqlite-2016-11-14-fsanitize_fuzzer )
INPUT=(input/dd.json ../fuzzer-test-suite/libxml2-v2.9.2/crash-d8960e21ca40ea5dc60ad655000842376d4178a1 ../fuzzer-test-suite/libxml2-v2.9.2/crash-50b12d37d6968a2cd9eb3665d158d9a2fb1f6e28 ../fuzzer-test-suite/libxml2-v2.9.2/leak-bdbb2857b7a086f003db1c418e1d124181341fb1 ../fuzzer-test-suite/sqlite-2016-11-14/crash-1066e42866aad3a04e6851dc494ad54bc31b9f78 ../fuzzer-test-suite/sqlite-2016-11-14/crash-0adc497ccfcc1a4d5e031b735c599df0cae3f4eb)
ANS=(jsondump.c:44 xmlDictComputeFastQKey xmlParseXMLDecl xmlNewDocElementContent __asan_memcpy exprAnalyze)
MSG=(jsondump libxml2/crash-d8960e2 libxml2/crash-50b12d3 libxml2/leak-bdbb285 sqlite/crash-1066e42 sqlite/crash-0adc497)
for (( i=0; i < ${#TARGET[@]}; i++)) do
	echo "${MSG[$i]}" >> compare
	$RANGE ${TARGET[$i]} ${INPUT[$i]} ${ANS[$i]} >> compare
	wc -c temp >> compare
	$THREAD ${TARGET[$i]} ${INPUT[$i]} ${ANS[$i]} 1 >> compare
	wc -c temp >> compare
	$THREAD ${TARGET[$i]} ${INPUT[$i]} ${ANS[$i]} 2 >> compare
	wc -c temp >> compare
	$THREAD ${TARGET[$i]} ${INPUT[$i]} ${ANS[$i]} 3 >> compare
	wc -c temp >> compare
	$THREAD ${TARGET[$i]} ${INPUT[$i]} ${ANS[$i]} 4 >> compare
	wc -c temp >> compare
	$THREAD ${TARGET[$i]} ${INPUT[$i]} ${ANS[$i]} 5 >> compare
	wc -c temp >> compare
	$THREAD ${TARGET[$i]} ${INPUT[$i]} ${ANS[$i]} 6 >> compare
	wc -c temp >> compare
	$THREAD ${TARGET[$i]} ${INPUT[$i]} ${ANS[$i]} 7 >> compare
	wc -c temp >> compare
	$THREAD ${TARGET[$i]} ${INPUT[$i]} ${ANS[$i]} 8 >> compare
	wc -c temp >> compare
done

#INPUT=../fuzzer-test-suite/libxml2-v2.9.2/uaf-1153fbf466b9474e6e3c48c72e86a4726b449ef7
#MSG=xmlDictComputeFastKey
#echo "libxml2/uaf-1153fbf with option" >> compare
#ASAN_OPTIONS=detect_leaks=0 $RANGE $TARGET $INPUT $MSG $P &>> compare
#wc -c temp >> compare
#ASAN_OPTIONS=detect_leaks=0 $THREAD $TARGET $INPUT $MSG &>> compare
#wc -c temp >> compare
#echo "libxml2/uaf-1153fbf with no option" >> compare
#$RANGE $TARGET $INPUT $MSG $P &>> compare
#wc -c temp >> compare
#$THREAD $TARGET $INPUT $MSG &>> compare
#wc -c temp >> compare

#TARGET=../fuzzer-test-suite/build_sqlite/sqlite-2016-11-14-fsanitize_fuzzer
#INPUT=../fuzzer-test-suite/sqlite-2016-11-14/leak-b0276985af5aa23c98d9abf33856ce069ef600e2
#MSG=sqlite3MemMalloc
#echo "sqlite/leak-b027698 no option" >> compare
#$RANGE $TARGET $INPUT $MSG $P &>> compare
#wc -c temp >> compare
#$THREAD $TARGET $INPUT $MSG &>> compare
#wc -c temp >> compare
