#ASAN_OPTIONS=detect_leaks=0 ../bin/o_main ../jsmn/jsondump ../test/input/dd.json jsondump.c:44
#../bin/o_main ../fuzzer-test-suite/build_libxml2/libxml2-v2.9.2-fsanitize_fuzzer ../fuzzer-test-suite/libxml2-v2.9.2/crash-50b12d37d6968a2cd9eb3665d158d9a2fb1f6e28 xmlBufCreate
#../bin/o_main ../fuzzer-test-suite/build_libxml2/libxml2-v2.9.2-fsanitize_fuzzer ../fuzzer-test-suite/libxml2-v2.9.2/leak-bdbb2857b7a086f003db1c418e1d124181341fb1 xmlNewDocElementContent
#../bin/o_main ../fuzzer-test-suite/build_sqlite/sqlite-2016-11-14-fsanitize_fuzzer ../fuzzer-test-suite/sqlite-2016-11-14/leak-b0276985af5aa23c98d9abf33856ce069ef600e2 sqlite3MemMalloc
#../bin/o_main ../fuzzer-test-suite/build_sqlite/sqlite-2016-11-14-fsanitize_fuzzer ../fuzzer-test-suite/sqlite-2016-11-14/crash-0adc497ccfcc1a4d5e031b735c599df0cae3f4eb exprAnalyze
../bin/o_main ../fuzzer-test-suite/build_sqlite/sqlite-2016-11-14-fsanitize_fuzzer ../fuzzer-test-suite/sqlite-2016-11-14/crash-1066e42866aad3a04e6851dc494ad54bc31b9f78 __asan_memcpy
