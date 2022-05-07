

for i in {0..4197}
do
	./libxml2 ${i} > coverage
	sort coverage | uniq > cov${i}
done

