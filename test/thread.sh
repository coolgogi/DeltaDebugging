THREAD=../bin/thread/thd_main
TARGET=../jsmn/jsondump
INPUT=input/dd.json
MSG=jsondump.c:44
echo "thread test"


ASAN_OPTIONS=detect_leaks=0 $THREAD $TARGET $INPUT $MSG
