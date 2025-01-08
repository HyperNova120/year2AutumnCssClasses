// program1_time_machine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include "time_span.h"
using namespace std;

int main() 
{
	int score = 1;
	TimeSpan ts1(1000);
	TimeSpan ts2(ts1);


	if (ts1 < ts2)
	{
		cout << "SCORE: 0" << endl;
		return 0;
	}
	else if (ts1 > ts2)
	{
		cout << "SCORE: 0" << endl;
		return 0;
	}
	else
	{
		cout << "SCORE: " << to_string(score) << endl;
		return score;
	}
}


