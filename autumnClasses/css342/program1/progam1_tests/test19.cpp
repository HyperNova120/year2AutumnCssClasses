// program1_time_machine.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <iostream>
#include <string>
#include <sstream>
#include "time_span.h"
using namespace std;

int main() 
{
	int score = 1;
	TimeSpan time;
	string input_string = "1 2 3";
	stringstream s(input_string);
	s >> time;
	if ((time.hours() != 1) || (time.minutes() != 2) || (time.seconds() != 3))
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

