RANGE=../../../../bin/r_main
TARGET=../../../../fuzzer-test-suite/build_sqlite/sqlite-2016-11-14-fsanitize_fuzzer
OUTPUT=range_output
INPUT=../record/363.part
MSG=sqlite3MemMalloc
P=1.0
echo "range test"


$RANGE $TARGET $INPUT $MSG $P
mv temp range_output
