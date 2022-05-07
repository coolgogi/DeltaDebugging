

for i in {0..59}
do
	./libxml2 ${i} > coverage
	sort coverage | uniq > cov${i}
done

