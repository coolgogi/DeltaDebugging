

for i in {0..311}
do
	diff cov${i} cov$(($i + 1)) > diff/diff${i}
done

