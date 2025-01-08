echo :   Testing 2 0 0 5 5
./greedy_robot 2 0 0 5 5
echo :   Testing 2 0 0 -5 5
./greedy_robot 2 0 0 -5 5
echo :   Testing 2 0 0 -5 -5
./greedy_robot 2 0 0 -5 -5
echo :   Testing 2 0 0 5 -5
./greedy_robot 2 0 0 5 -5
echo :   Testing 2 0 0 5 5
./greedy_robot 2 0 0 5 5
echo :   Testing 2 0 0 5 0
./greedy_robot 2 0 0 5 0
echo :   Testing 2 0 0 0 -5
./greedy_robot 2 0 0 0 -5
echo :   Testing 2 0 0 -5 0
./greedy_robot 2 0 0 -5 0
echo :   Testing 2 0 0 0 0
./greedy_robot 2 0 0 0 0

echo :   Testing c 0 0 0 0
./greedy_robot c 0 0 0 0
echo :   Testing 2 c c c c
./greedy_robot 2 c c c c
echo :   Testing c 0 0 0 
./greedy_robot c 0 0 0  
echo :   Testing 2 c c c c C
./greedy_robot 2 c c c c C

echo more tests
./greedy_robot 2 0 0 10 10
./greedy_robot 2 0 0 -10 10
./greedy_robot 2 0 0 -10 -10
./greedy_robot 2 0 0 10 -10

./greedy_robot 2 10 10 0 0
./greedy_robot 2 10 -10 0 0
./greedy_robot 2 -10 -10 0 0
./greedy_robot 2 -10 10 0 0

./greedy_robot 2 10 0 0 0
./greedy_robot 2 0 10 0 0
./greedy_robot 2 0 0 10 0
./greedy_robot 2 0 0 0 10

./greedy_robot 4 5 0 0 0
./greedy_robot 4 0 5 0 0
./greedy_robot 4 0 0 5 0
./greedy_robot 4 0 0 0 5


./greedy_robot 5 5 0 0 0
./greedy_robot 5 0 5 0 0
./greedy_robot 5 0 0 5 0
./greedy_robot 5 0 0 0 5


./greedy_robot 5 -5 0 0 0
./greedy_robot 5 0 -5 0 0
./greedy_robot 5 0 0 -5 0
./greedy_robot 5 0 0 0 -5


./greedy_robot 5 c 0 0 0
./greedy_robot 5 0 c 0 0
./greedy_robot 5 0 0 c 0
./greedy_robot 5 0 0 0 c

./greedy_robot 5 1.5 0 0 0
./greedy_robot 5 0 1.5 0 0
./greedy_robot 5 0 0 1.5 0
./greedy_robot 5 0 0 0 1.5

./greedy_robot 0 1.5 0 0 0
./greedy_robot 500 0 1.5 0 0
./greedy_robot -5 0 0 1.5 0
./greedy_robot -500 0 0 0 1.5

./greedy_robot 2 5 0 0
