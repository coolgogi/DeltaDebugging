p1=1.00
p2=1.00
sigma=5.0
home=/home/suhyun/DeltaDebugging/
r_ddmin=$home/bin/main
input=$home/test/input/test2.xml
target=$home/libxml2/xmllint
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
for i in {1001..1001}; do
#       ASAN_OPTIONS=detect_leaks=0 $r_ddmin $target $input $p1 $p2 $sigma
#       mv temp $outDIR/$i
        echo "hello world"
done

wc -c $outDIR/* > result_wc
