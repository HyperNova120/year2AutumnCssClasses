// program1_time_machine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include "time_span.h"
using namespace std;

int main() 
{
	int score = 1;
	TimeSpan time(-3, 73, 2);
	if ((time.hours() != -1) || (time.minutes() != -46) || (time.seconds() != -58))
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


