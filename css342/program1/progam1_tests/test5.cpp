// program1_time_machine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include "time_span.h"
using namespace std;

int main() 
{
	int score = 1;
	TimeSpan ts1, ts2(5), ts3(7,0), ts4(4, 0, 0);
	TimeSpan time = ts1 + ts2 + ts3 + ts4;
	if ((time.hours() != 4) || (time.minutes() != 7) || (time.seconds() != 5))
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


