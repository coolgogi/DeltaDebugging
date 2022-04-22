echo "ddmin algorithm test"

rm output/ddmin_output.txt
touch output/ddmin_output.txt

ASAN_OPTIONS=detect_leaks=0 ../bin/main ../jsmn/jsondump input/dd.json
