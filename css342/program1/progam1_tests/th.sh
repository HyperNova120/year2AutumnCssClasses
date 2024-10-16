#!/bin/bash

rm score.txt
touch score.txt

for i in {1..25}
do
	rm test$i 2> /dev/null
done

for i in {1..25}
do
	echo "TEST" $i
	echo "TEST" $i >> score.txt
	rm test$i 2> /dev/null
	g++ -o test$i test$i.cpp time_span.cpp
	./test$i >> score.txt
	rm test$i 2> /dev/null
done
echo " "
echo "FINAL SCORE::"
grep SCORE score.txt | awk '{sum+=$2;}END{print sum;}'

for i in {1..25}
do
	rm test$i 2> /dev/null
done
