p1=1.00
p2=1.00
sigma=5.0
ans=xmlParseXMLDecl
r_ddmin=../../../../../bin/main
input=../../../../../fuzzer-test-suite/libxml2-v2.9.2/crash-50b12d37d6968a2cd9eb3665d158d9a2fb1f6e28
target=../../../../../fuzzer-test-suite/build_libxml2/libxml2-v2.9.2-fsanitize_fuzzer
outDIR=$PWD/sigma${sigma}/

if [ ! -d $outDIR ]; then
	mkdir $outDIR
fi


LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib
export LD_LIBRARY_PATH
for i in {1..1000}; do
	ASAN_OPTIONS=detect_leaks=0 $r_ddmin $target $input $p1 $p2 $sigma $ans
	mv temp $outDIR/$i
done

wc -c $outDIR/* > $outDIR/result_wc

p1=1.00
p2=1.00
sigma=10.0
outDIR=$PWD/sigma${sigma}/

if [ ! -d $PWD/p${p1} ]; then
	mkdir $PWD/p${p1}
	mkdir $outDIR
fi

if [ ! -d $outDIR ]; then
	mkdir $outDIR
fi


LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib
export LD_LIBRARY_PATH
for i in {1..1000}; do
	ASAN_OPTIONS=detect_leaks=0 $r_ddmin $target $input $p1 $p2 $sigma $ans
	mv temp $outDIR/$i
done

wc -c $outDIR/* > $outDIR/result_wc

p1=1.00
p2=1.00
sigma=15.0
outDIR=$PWD/sigma${sigma}/

if [ ! -d $PWD/p${p1} ]; then
	mkdir $PWD/p${p1}
	mkdir $outDIR
fi

if [ ! -d $outDIR ]; then
	mkdir $outDIR
fi


LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib
export LD_LIBRARY_PATH
for i in {1..1000}; do
	ASAN_OPTIONS=detect_leaks=0 $r_ddmin $target $input $p1 $p2 $sigma $ans
	mv temp $outDIR/$i
done

wc -c $outDIR/* > $outDIR/result_wc

p1=1.00
p2=1.00
sigma=20.0
outDIR=$PWD/sigma${sigma}/

if [ ! -d $PWD/p${p1} ]; then
	mkdir $PWD/p${p1}
	mkdir $outDIR
fi

if [ ! -d $outDIR ]; then
	mkdir $outDIR
fi


LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib
export LD_LIBRARY_PATH
for i in {1..1000}; do
	ASAN_OPTIONS=detect_leaks=0 $r_ddmin $target $input $p1 $p2 $sigma $ans
	mv temp $outDIR/$i
done

wc -c $outDIR/* > $outDIR/result_wc

