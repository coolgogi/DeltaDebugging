<<<<<<< HEAD
#../bin/o_main ../fuzzer-test-suite/build_libxml2/libxml2-v2.9.2-fsanitize_fuzzer ../fuzzer-test-suite/libxml2-v2.9.2/crash-d8960e21ca40ea5dc60ad655000842376d4178a1 xmlDictComputeFastQKey
echo "result of libxml2 crash-d8"
wc -c temp
../bin/main ../fuzzer-test-suite/build_libxml2/libxml2-v2.9.2-fsanitize_fuzzer ../fuzzer-test-suite/libxml2-v2.9.2/crash-d8960e21ca40ea5dc60ad655000842376d4178a1 1.0 1.0 0.0 xmlDictComputeFastQKey
echo "result of libxml2 crash-d8"
wc -c temp
=======
#ASAN_OPTIONS=detect_leaks=0 ../bin/o_main ../jsmn/jsondump ../test/input/dd.json jsondump.c:44
#../bin/o_main ../fuzzer-test-suite/build_libxml2/libxml2-v2.9.2-fsanitize_fuzzer ../fuzzer-test-suite/libxml2-v2.9.2/crash-50b12d37d6968a2cd9eb3665d158d9a2fb1f6e28 xmlBufCreate
#echo "result of jsondump"
#wc -c temp
#../bin/o_main ../fuzzer-test-suite/build_libxml2/libxml2-v2.9.2-fsanitize_fuzzer ../fuzzer-test-suite/libxml2-v2.9.2/crash-d8960e21ca40ea5dc60ad655000842376d4178a1 xmlDictComputeFastQKey
#echo "result of libxml2 crash-d8"
#wc -c temp
#../bin/o_main ../fuzzer-test-suite/build_libxml2/libxml2-v2.9.2-fsanitize_fuzzer ../fuzzer-test-suite/libxml2-v2.9.2/crash-50b12d37d6968a2cd9eb3665d158d9a2fb1f6e28 xmlParseXMLDecl
#echo "result of libxml2 crash-50"
#wc -c temp
#../bin/o_main ../fuzzer-test-suite/build_libxml2/libxml2-v2.9.2-fsanitize_fuzzer ../fuzzer-test-suite/libxml2-v2.9.2/leak-bdbb2857b7a086f003db1c418e1d124181341fb1 xmlNewDocElementContent
<<<<<<< HEAD
#../bin/o_main ../fuzzer-test-suite/build_sqlite/sqlite-2016-11-14-fsanitize_fuzzer ../fuzzer-test-suite/sqlite-2016-11-14/leak-b0276985af5aa23c98d9abf33856ce069ef600e2 sqlite3MemMalloc
#../bin/o_main ../fuzzer-test-suite/build_sqlite/sqlite-2016-11-14-fsanitize_fuzzer ../fuzzer-test-suite/sqlite-2016-11-14/crash-0adc497ccfcc1a4d5e031b735c599df0cae3f4eb exprAnalyze
../bin/o_main ../fuzzer-test-suite/build_sqlite/sqlite-2016-11-14-fsanitize_fuzzer ../fuzzer-test-suite/sqlite-2016-11-14/crash-1066e42866aad3a04e6851dc494ad54bc31b9f78 __asan_memcpy
=======
#echo "result of libxml2 leak-bd"
#wc -c temp
#../bin/o_main ../fuzzer-test-suite/build_libxml2/libxml2-v2.9.2-fsanitize_fuzzer ../fuzzer-test-suite/libxml2-v2.9.2/uaf-1153fbf466b9474e6e3c48c72e86a4726b449ef7 xmlDictComputeFastKe
#echo "result of libxml2 uaf"
#wc -c temp

../bin/o_main ../fuzzer-test-suite/build_sqlite/sqlite-2016-11-14-fsanitize_fuzzer leak sqlite3MemMalloc
echo "result of sqlite leak-b0"
wc -c temp
#../bin/o_main ../fuzzer-test-suite/build_sqlite/sqlite-2016-11-14-fsanitize_fuzzer ../fuzzer-test-suite/sqlite-2016-11-14/crash-0adc497ccfcc1a4d5e031b735c599df0cae3f4eb heap-use-after-free
#echo "result of sqlite crash-0"
#wc -c temp
#../bin/o_main ../fuzzer-test-suite/build_sqlite/sqlite-2016-11-14-fsanitize_fuzzer ../fuzzer-test-suite/sqlite-2016-11-14/crash-1066e42866aad3a04e6851dc494ad54bc31b9f78 __asan_memcpy
#echo "result of sqlite crash-1"
#wc -c temp


#../bin/o_main ../libxml2/xmllint ../test/input/poc xmlValidBuildAContentModel 
#echo "result of libxml2 issue 243"
#wc -c temp
#../bin/o_main ../libxml2/xmllint ../test/input/test2.xml ucnv_MBCSSimpleGetNextUChar
#echo "result of libxml2 issue 350"
#wc -c temp

#../bin/o_main ../jsmn/jsondump ../test/input/dd.json jsondump.c:44
#echo "result of jsondump"
#wc -c temp
>>>>>>> 614b7f1800eebed24f04298f5cd509601e50cda7
>>>>>>> 029ba3281a5ac77c3f6681185e6bbf75c7967a52
