p1=1.00
p2=1.00
sigma=5.0
ans=sqlite3MemMalloc
home=/home/suhyun/DeltaDebugging
r_ddmin=$home/bin/main
target=$home/fuzzer-test-suite/build_sqlite/sqlite-2016-11-14-fsanitize_fuzzer
input=$home/fuzzer-test-suite/sqlite-2016-11-14/leak-b0276985af5aa23c98d9abf33856ce069ef600e2
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
for i in {19..250}; do
       	$r_ddmin $target $input $p1 $p2 $sigma $ans
        mv temp $outDIR/$i
for i in {501..750}; do
	$r_ddmin $target $input $p1 $p2 $sigma $ans
	mv temp $outDIR/$i
for i in {751..1000}; do
for i in {251..500}; do
        $r_ddmin $target $input $p1 $p2 $sigma $ans
        mv temp $outDIR/$i
done

wc -c $outDIR/* > $outDIR/result_wc

sigma=30.0
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
for i in {1..250}; do
LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib
export LD_LIBRARY_PATH
for i in {501..750}; do
for i in {751..1000}; do
for i in {251..500}; do
        $r_ddmin $target $input $p1 $p2 $sigma $ans
        mv temp $outDIR/$i
done

wc -c $outDIR/* > $outDIR/result_wc

