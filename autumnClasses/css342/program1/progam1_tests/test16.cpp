// program1_time_machine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include "time_span.h"
using namespace std;

int main() 
{
	int score = 1;
	TimeSpan ts1(4, 5, 6);
	TimeSpan ts2(5, 6, 7);
	TimeSpan ts3(98);
	ts1 = -ts2;

	if ((ts1.hours() != -5) || (ts1.minutes() != -6) || (ts1.seconds() != -7))
	{
		cout << "SCORE: 0" << endl;
		return 0;
	}
	else if ((ts2.hours() != 5) || (ts2.minutes() != 6) || (ts2.seconds() != 7))
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


