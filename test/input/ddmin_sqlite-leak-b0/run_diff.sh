

for i in {0..8}
do
	diff cov00${i} cov00$(($i + 1)) > diff/diff00$(($i + 1))
done
diff cov009 cov010 > diff/diff010
for i in {10..98}
do
	diff cov0${i} cov0$(($i + 1)) > diff/diff0$(($i + 1))
done
diff cov099 cov100 > diff/diff100
for i in {100..666}
do	
	diff cov${i} cov$(($i + 1)) > diff/diff$(($i + 1))
done


#for i in $(seq -w 0 375)
#do
	#echo ${i}
#	diff cov${i} cov$(($i + 1)) > diff/diff$(($i + 1))
#done

