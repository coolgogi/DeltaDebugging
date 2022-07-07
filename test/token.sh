
../bin/t_main ../jsmn/jsondump input/jsondump_input.json input/jsondump++/diff/grep_uniq jsondump.c:44:9
mv token_range_result result_of_token_range/jsondump

../bin/t_main ../fuzzer-test-suite/build_libxml2/libxml2-v2.9.2-fsanitize_fuzzer ../fuzzer-test-suite/libxml2-v2.9.2/crash-d8960e21ca40ea5dc60ad655000842376d4178a1 input/libxml2-crash-d8960e2/diff/grep2_uniq xmlDictComputeFastQKey
mv token_range_result result_of_token_range/libxml2-crash-d8960e2

../bin/t_main ../fuzzer-test-suite/build_sqlite/sqlite-2016-11-14-fsanitize_fuzzer ../fuzzer-test-suite/sqlite-2016-11-14/leak-b0276985af5aa23c98d9abf33856ce069ef600e2 input/sqlite++/diff/grep_uniq sqlite3MemMalloc
mv token_range_result result_of_token_range/sqlite-leak-b027698
