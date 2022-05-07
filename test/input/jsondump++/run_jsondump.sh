
for i in $(seq -w 0 376)
do
	ASAN_OPTIONS=coverage=1:detect_leaks=0 ./jsondump < $i  &> coverage
	sort coverage | uniq > cov${i}
done

