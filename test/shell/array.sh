#! /bin/bash
NUMBER=(8 8 5 6)

echo ${NUMBER[0]}

for i in ${NUMBER[@]}
do
	echo ${i}
       	#key sim ${i}
done
