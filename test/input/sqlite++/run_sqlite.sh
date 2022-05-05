

for i in {0..2715}
do
	echo ${i}
	./sqlite ${i} > coverage
	sort coverage | uniq > cov${i}
done

