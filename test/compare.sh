RANGE=../bin/r_main
THREAD=../bin/thread/pcs_main
OUTPUT=output/range_output
TARGET=../jsmn/jsondump
INPUT=input/dd.json
MSG=jsondump.c:44

#TARGET=../fuzzer-test-suite/build_libxml2/libxml2-v2.9.2-fsanitize_fuzzer
#INPUT=../fuzzer-test-suite/libxml2-v2.9.2/crash-d8960e21ca40ea5dc60ad655000842376d4178a1
#MSG=xmlDictComputeFastQKey		

#TARGET=../fuzzer-test-suite/build_sqlite/sqlite-2016-11-14-fsanitize_fuzzer
#INPUT=../fuzzer-test-suite/sqlite-2016-11-14/crash-1066e42866aad3a04e6851dc494ad54bc31b9f78
#MSG=__asan_memcpy		


TARGET=../fuzzer-test-suite/build_libxml2/libxml2-v2.9.2-fsanitize_fuzzer
INPUT=../fuzzer-test-suite/libxml2-v2.9.2/crash-50b12d37d6968a2cd9eb3665d158d9a2fb1f6e28
MSG=xmlParseXMLDecl

#echo "fts/libxml2/crash-50b12d37d6968a2cd9eb3665d158d9a2fb1f6e28" >> compare
#$RANGE $TARGET $INPUT $MSG $P &>> compare
#wc -c temp >> compare
#$THREAD $TARGET $INPUT $MSG &>> compare
#wc -c temp >> compare

INPUT=../fuzzer-test-suite/libxml2-v2.9.2/leak-bdbb2857b7a086f003db1c418e1d124181341fb1
MSG=xmlNewDocElementContent

#echo "fts/libxml2/leak-bdbb2857b7a086f003db1c418e1d124181341fb1" >> compare
#$RANGE $TARGET $INPUT $MSG $P &>> compare
#wc -c temp >> compare
#$THREAD $TARGET $INPUT $MSG &>> compare
#wc -c temp >> compare

INPUT=../fuzzer-test-suite/libxml2-v2.9.2/uaf-1153fbf466b9474e6e3c48c72e86a4726b449ef7
MSG=xmlDictComputeFastKey

#echo "fts/libxml2/uaf-1153fbf466b9474e6e3c48c72e86a4726b449ef7" >> compare
#$RANGE $TARGET $INPUT $MSG $P &>> compare
#wc -c temp >> compare
#$THREAD $TARGET $INPUT $MSG &>> compare
#wc -c temp >> compare

TARGET=../fuzzer-test-suite/build_sqlite/sqlite-2016-11-14-fsanitize_fuzzer
INPUT=../fuzzer-test-suite/sqlite-2016-11-14/crash-0adc497ccfcc1a4d5e031b735c599df0cae3f4eb
MSG=exprAnalyze

echo "fts/sqlite/crash-0adc497ccfcc1a4d5e031b735c599df0cae3f4eb" >> compare
$RANGE $TARGET $INPUT $MSG $P &>> compare
wc -c temp >> compare
$THREAD $TARGET $INPUT $MSG &>> compare
wc -c temp >> compare

INPUT=../fuzzer-test-suite/sqlite-2016-11-14/leak-b0276985af5aa23c98d9abf33856ce069ef600e2
MSG=sqlite3MemMalloc

echo "fts/sqlite/leak-b0276985af5aa23c98d9abf33856ce069ef600e2" >> compare
$RANGE $TARGET $INPUT $MSG $P &>> compare
wc -c temp >> compare
$THREAD $TARGET $INPUT $MSG &>> compare
wc -c temp >> compare
