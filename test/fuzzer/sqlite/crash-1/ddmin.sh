p1=1.00
p2=1.00
sigma=5.00
ans=__asan_memcpy
home=/home/suhyun/DeltaDebugging
r_ddmin=$home/bin/main
input=$home/fuzzer-test-suite/sqlite-2016-11-14/crash-1066e42866aad3a04e6851dc494ad54bc31b9f78
target=$home/fuzzer-test-suite/build_sqlite/sqlite-2016-11-14-fsanitize_fuzzer
outDIR=$PWD/p${p1}/sigma${sigma}/

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

sigma=30.00
outDIR=$PWD/p${p1}/sigma${sigma}/

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

