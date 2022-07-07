for i in {0..9}
do
	echo 00${i}
	ASAN_OPTIONS=detect_leaks=0 ./jsondump < 00${i} &> coverage
	sort coverage | uniq > cov00${i}
done
for i in {10..14}
do
	echo 0${i}
	ASAN_OPTIONS=detect_leaks=0 ./jsondump < 0${i} &> coverage
	sort coverage | uniq > cov0${i}
done
