

for i in {0..58}
do
	diff cov${i} cov$(($i + 1)) > diff/diff${i}
done

