
for i in {0..9}
do
	./sqlite 00${i} > coverage
	sort coverage | uniq > cov00${i}
done

for i in {10..99}
do
	./sqlite 0${i} > coverage
	sort coverage | uniq > cov0${i}
done



for i in {100..667}
do
	./sqlite ${i} > coverage
	sort coverage | uniq > cov${i}
done

