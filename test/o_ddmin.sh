

DDMIN=../bin/o_main
R_DDMIN=../bin/main
LIBXML2_TARGET=../fuzzer-test-suite/build_libxml2/libxml2-v2.9.2-fsanitize_fuzzer
LIBXML2_INPUT=(crash-50b12d37d6968a2cd9eb3665d158d9a2fb1f6e28 crash-d8960e21ca40ea5dc60ad655000842376d4178a1 leak-bdbb2857b7a086f003db1c418e1d124181341fb1 uaf-1153fbf466b9474e6e3c48c72e86a4726b449ef7)
LIBXML2_ANS=(xmlParseXMLDecl xmlDictComputeFastQKey xmlNewDocElementContent xmlDictComputeFastKey)  

SQLITE_TARGET=../fuzzer-test-suite/build_sqlite/sqlite-2016-11-14-fsanitize_fuzzer
SQLITE_INPUT=(crash-0adc497ccfcc1a4d5e031b735c599df0cae3f4eb crash-1066e42866aad3a04e6851dc494ad54bc31b9f78 leak-b0276985af5aa23c98d9abf33856ce069ef600e2)
SQLITE_ANS=(exprAnalyze __asan_memcpy sqlite3MemMalloc)

if [ ! -d dd_result ]; then
	mkdir dd_result
fi
if [ ! -d rd_result ]; then
	mkdir rd_result
fi
for (( i=0; i< ${#LIBXML2_INPUT[@]} ; i++ )) do
	$DDMIN $LIBXML2_TARGET ../fuzzer-test-suite/libxml2-v2.9.2/${LIBXML2_INPUT[$i]} ${LIBXML2_ANS[$i]} 
	echo "ddmin: result of ${LIBXML2_INPUT[$i]}"
	wc -c temp
	path="${LIBXML2_INPUT[$i]}_result"
	mv temp dd_result/$path
	
	$R_DDMIN $LIBXML2_TARGET ../fuzzer-test-suite/libxml2-v2.9.2/${LIBXML2_INPUT[$i]} 1.0 1.0 0.0 ${LIBXML2_ANS[$i]} 
	echo "rdmin: result of ${LIBXML2_INPUT[$i]}"
	wc -c temp
	path="${LIBXML2_INPUT[$i]}_result"
	mv temp rd_result/$path
done

for (( i=0; i< ${#SQLITE_INPUT[@]} ; i++ )) do
	$DDMIN $SQLITE_TARGET ../fuzzer-test-suite/sqlite-2016-11-14/${SQLITE_INPUT[$i]} ${SQLITE_ANS[$i]} 
	echo "ddmin: result of ${SQLITE_INPUT[$i]}"
	wc -c temp
	path="${SQLITE_INPUT[$i]}_result"
	mv temp dd_result/$path
	
	$R_DDMIN $SQLITE_TARGET ../fuzzer-test-suite/sqlite-2016-11-14/${SQLITE_INPUT[$i]} 1.0 1.0 0.0 ${SQLITE_ANS[$i]} 
	echo "rdmin: result of ${SQLITE_INPUT[$i]}"
	wc -c temp
	path="${SQLITE_INPUT[$i]}_result"
	mv temp rd_result/$path
done
