echo "ddmin algorithm test"

rm output/ddmin_output.txt
rm complement
rm substring
rm temp
touch output/ddmin_output.txt

ASAN_OPTIONS=detect_leaks=0:halt_on_error=1 ../bin/main ../jsmn/jsondump input/dd.json 1.0 1.0 12.0
mv temp output/sigma12.0/1
ASAN_OPTIONS=detect_leaks=0:halt_on_error=1 ../bin/main ../jsmn/jsondump input/dd.json 1.0 1.0 12.0
mv temp output/sigma12.0/2
ASAN_OPTIONS=detect_leaks=0:halt_on_error=1 ../bin/main ../jsmn/jsondump input/dd.json 1.0 1.0 12.0
mv temp output/sigma12.0/3
ASAN_OPTIONS=detect_leaks=0:halt_on_error=1 ../bin/main ../jsmn/jsondump input/dd.json 1.0 1.0 12.0
mv temp output/sigma12.0/4
ASAN_OPTIONS=detect_leaks=0:halt_on_error=1 ../bin/main ../jsmn/jsondump input/dd.json 1.0 1.0 12.0
mv temp output/sigma12.0/5
ASAN_OPTIONS=detect_leaks=0:halt_on_error=1 ../bin/main ../jsmn/jsondump input/dd.json 1.0 1.0 12.0
mv temp output/sigma12.0/6
ASAN_OPTIONS=detect_leaks=0:halt_on_error=1 ../bin/main ../jsmn/jsondump input/dd.json 1.0 1.0 12.0
mv temp output/sigma12.0/7
ASAN_OPTIONS=detect_leaks=0:halt_on_error=1 ../bin/main ../jsmn/jsondump input/dd.json 1.0 1.0 12.0
mv temp output/sigma12.0/8
ASAN_OPTIONS=detect_leaks=0:halt_on_error=1 ../bin/main ../jsmn/jsondump input/dd.json 1.0 1.0 12.0
mv temp output/sigma12.0/9
ASAN_OPTIONS=detect_leaks=0:halt_on_error=1 ../bin/main ../jsmn/jsondump input/dd.json 1.0 1.0 12.0
mv temp output/sigma12.0/10
ASAN_OPTIONS=detect_leaks=0:halt_on_error=1 ../bin/main ../jsmn/jsondump input/dd.json 1.0 1.0 12.0
mv temp output/sigma12.0/11
ASAN_OPTIONS=detect_leaks=0:halt_on_error=1 ../bin/main ../jsmn/jsondump input/dd.json 1.0 1.0 12.0
mv temp output/sigma12.0/12
ASAN_OPTIONS=detect_leaks=0:halt_on_error=1 ../bin/main ../jsmn/jsondump input/dd.json 1.0 1.0 12.0
mv temp output/sigma12.0/13
ASAN_OPTIONS=detect_leaks=0:halt_on_error=1 ../bin/main ../jsmn/jsondump input/dd.json 1.0 1.0 12.0
mv temp output/sigma12.0/14
ASAN_OPTIONS=detect_leaks=0:halt_on_error=1 ../bin/main ../jsmn/jsondump input/dd.json 1.0 1.0 12.0
mv temp output/sigma12.0/15
ASAN_OPTIONS=detect_leaks=0:halt_on_error=1 ../bin/main ../jsmn/jsondump input/dd.json 1.0 1.0 12.0
mv temp output/sigma12.0/16
ASAN_OPTIONS=detect_leaks=0:halt_on_error=1 ../bin/main ../jsmn/jsondump input/dd.json 1.0 1.0 12.0
mv temp output/sigma12.0/17
ASAN_OPTIONS=detect_leaks=0:halt_on_error=1 ../bin/main ../jsmn/jsondump input/dd.json 1.0 1.0 12.0
mv temp output/sigma12.0/18
ASAN_OPTIONS=detect_leaks=0:halt_on_error=1 ../bin/main ../jsmn/jsondump input/dd.json 1.0 1.0 12.0
mv temp output/sigma12.0/19
ASAN_OPTIONS=detect_leaks=0:halt_on_error=1 ../bin/main ../jsmn/jsondump input/dd.json 1.0 1.0 12.0
mv temp output/sigma12.0/20
ASAN_OPTIONS=detect_leaks=0:halt_on_error=1 ../bin/main ../jsmn/jsondump input/dd.json 1.0 1.0 12.0
mv temp output/sigma12.0/21
ASAN_OPTIONS=detect_leaks=0:halt_on_error=1 ../bin/main ../jsmn/jsondump input/dd.json 1.0 1.0 12.0
mv temp output/sigma12.0/22
ASAN_OPTIONS=detect_leaks=0:halt_on_error=1 ../bin/main ../jsmn/jsondump input/dd.json 1.0 1.0 12.0
mv temp output/sigma12.0/23
ASAN_OPTIONS=detect_leaks=0:halt_on_error=1 ../bin/main ../jsmn/jsondump input/dd.json 1.0 1.0 12.0
mv temp output/sigma12.0/24
ASAN_OPTIONS=detect_leaks=0:halt_on_error=1 ../bin/main ../jsmn/jsondump input/dd.json 1.0 1.0 12.0
mv temp output/sigma12.0/25
ASAN_OPTIONS=detect_leaks=0:halt_on_error=1 ../bin/main ../jsmn/jsondump input/dd.json 1.0 1.0 12.0
mv temp output/sigma12.0/26
ASAN_OPTIONS=detect_leaks=0:halt_on_error=1 ../bin/main ../jsmn/jsondump input/dd.json 1.0 1.0 12.0
mv temp output/sigma12.0/27
ASAN_OPTIONS=detect_leaks=0:halt_on_error=1 ../bin/main ../jsmn/jsondump input/dd.json 1.0 1.0 12.0
mv temp output/sigma12.0/28
ASAN_OPTIONS=detect_leaks=0:halt_on_error=1 ../bin/main ../jsmn/jsondump input/dd.json 1.0 1.0 12.0
mv temp output/sigma12.0/29
ASAN_OPTIONS=detect_leaks=0:halt_on_error=1 ../bin/main ../jsmn/jsondump input/dd.json 1.0 1.0 12.0
mv temp output/sigma12.0/30
