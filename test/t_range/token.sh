

#../../bin/t_main ../../jsmn/jsondump ../input/jsondump_input.json ../input/jsondump++/diff/grep_uniq jsondump.c:44:9
#../../bin/t_main ../../jsmn/jsondump ../input/jsondump_input.json ../input/jsondump++/diff/find2 jsondump.c:44:9
#mv token_range_result jsmn_min_result

#../../bin/t_main ../../fuzzer-test-suite/build_libxml2/libxml2-v2.9.2-fsanitize_fuzzer ../../fuzzer-test-suite/libxml2-v2.9.2/crash-d8960e21ca40ea5dc60ad655000842376d4178a1 ../input/libxml2-crash-d8960e2/diff/grep2_uniq xmlDictComputeFastQKey
#../../bin/t_main ../../fuzzer-test-suite/build_libxml2/libxml2-v2.9.2-fsanitize_fuzzer ../../fuzzer-test-suite/libxml2-v2.9.2/crash-d8960e21ca40ea5dc60ad655000842376d4178a1 ../input/libxml2-crash-d8960e2/diff/find2 xmlDictComputeFastQKey
#mv token_range_result libxml2_min_result

../../bin/t_main ../../fuzzer-test-suite/build_sqlite/sqlite-2016-11-14-fsanitize_fuzzer ../../fuzzer-test-suite/sqlite-2016-11-14/leak-b0276985af5aa23c98d9abf33856ce069ef600e2 ../input/sqlite++/diff/grep_uniq sqlite3MemMalloc 
#../../bin/t_main ../../fuzzer-test-suite/build_sqlite/sqlite-2016-11-14-fsanitize_fuzzer ../../fuzzer-test-suite/sqlite-2016-11-14/leak-b0276985af5aa23c98d9abf33856ce069ef600e2 ../input/sqlite++/diff/find2 sqlite3MemMalloc 
mv token_range_result sqlite_min_result

#../../bin/t_main ../../fuzzer-test-suite/build_sqlite/sqlite-2016-11-14-fsanitize_fuzzer ../dd_result/leak-b0276985af5aa23c98d9abf33856ce069ef600e2_result ../input/ddmin_sqlite-leak-b0/diff/find2 sqlite3MemMalloc 
