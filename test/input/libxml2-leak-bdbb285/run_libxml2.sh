

for i in {0..63}
do
	./libxml2 ${i} > coverage
	sort coverage | uniq > cov${i}
done

