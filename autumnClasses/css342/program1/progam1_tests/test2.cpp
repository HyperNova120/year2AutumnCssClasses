// program1_time_machine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include "time_span.h"
using namespace std;

int main() 
{
	int score = 1;
	TimeSpan time(127.86);
	cout << time.hours() << " " << time.minutes() << " " << time.seconds() << endl;
	if ((time.hours() != 0) || (time.minutes() != 2) || (time.seconds() != 8))
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


