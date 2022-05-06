

for i in {0..2714}
do
	diff cov${i} cov$(($i + 1)) > diff${i}
done

