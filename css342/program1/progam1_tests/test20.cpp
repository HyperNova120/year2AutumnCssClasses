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
	int h = 200;
	int m = 15;
	int s = 13;
	TimeSpan time(h, m, s);
	stringstream string_out;
	string_out << time;
	string answer = string_out.str();

	if (answer.find(to_string(h)) == string::npos)
	{
		cout << "SCORE: 0" << endl;
		return 0;
	}
	else if (answer.find(to_string(m)) == string::npos)
	{
		cout << "SCORE: 0" << endl;
		return 0;
	}
	else if (answer.find(to_string(s)) == string::npos)
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

