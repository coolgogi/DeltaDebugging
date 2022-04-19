echo "ddmin algorithm test"

rm output/ddmin_output.txt
touch output/ddmin_output.txt

ASAN_OPTIONS=detect_leaks=0:halt_on_error=1 ../bin/main ../jsmn/jsondump input/dd.json
