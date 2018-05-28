#!/bin/bash
# This should be run in the same folder as the ParaStats exectuable file with "benchmark_normal_X.csv" files in sibling
# folder called "data". (the folder housing ParaStats and this are on the same level as the "data" folder)
> results.txt
array=( $(ls ../data | grep "benchmark_normal_") )
echo	sequential >> results.txt
for i in "${array[@]}"
do
	echo $i | tr -dc '0-9' >> results.txt
	printf ",\t" >> results.txt
	for j in `seq 1 10`;
        do
		./ParaStats -s -i ../data/$i | grep took | tr -dc '0-9' >> results.txt
		printf ",\t" >> results.txt
	done
	printf "\n" >> results.txt
done
echo	parallel >> results.txt
vectorSizes=( $(ls ../data | grep -oP '[0-9]+') )
i=0
while [  $i -lt ${#array[@]} ];
do
	echo ${array[i]} | tr -dc '0-9' >> results.txt
	printf "\t" >> results.txt
	for j in `seq 1 10`;
    do
		echo $(echo "3" | ./ParaStats -i ../data/${array[i]} -z  ${vectorSizes[i]}) | grep -oP '(took: )[0-9]+' | tr -dc '0-9' >> results.txt
		printf ",\t" >> results.txt
	done
	printf "\n" >> results.txt
	let i=i+1
done
