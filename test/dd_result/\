DDMIN=../../bin/o_main
SQLITE_TARGET=../../fuzzer-test-suite/build_sqlite/sqlite-2016-11-14-fsanitize_fuzzer
SQLITE_INPUT=(leak-b0276985af5aa23c98d9abf33856ce069ef600e2)
SQLITE_ANS=(sqlite3MemMalloc)

if [ ! -d dd_result ]; then
	mkdir dd_result
fi
if [ ! -d rd_result ]; then
	mkdir rd_result
fi

for (( i=0; i< ${#SQLITE_INPUT[@]} ; i++ )) do
	$DDMIN $SQLITE_TARGET ../../fuzzer-test-suite/sqlite-2016-11-14/${SQLITE_INPUT[$i]} ${SQLITE_ANS[$i]} 
	echo "ddmin: result of ${SQLITE_INPUT[$i]}"
	wc -c temp
	path="${SQLITE_INPUT[$i]}_result"
	mv temp dd_result/$path
done
