p1=1.00
p2=1.00
sigma=5.0
ans=sqlite3MemMalloc
home=/home/suhyun/DeltaDebugging
r_ddmin=$home/bin/main
target=$home/fuzzer-test-suite/build_sqlite/sqlite-2016-11-14-fsanitize_fuzzer
input=$home/fuzzer-test-suite/sqlite-2016-11-14/leak-b0276985af5aa23c98d9abf33856ce069ef600e2

LD_LIBRARY_PATH=$LD_LIBRARY_PATH:/usr/local/lib
export LD_LIBRARY_PATH
for i in {101..200}; do
       	$r_ddmin $target $input $p1 $p2 $sigma $ans
        mv temp $i
done
