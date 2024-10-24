#include <iostream>
#include <sstream>
#include "greedy_robot.h"
using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 6)
    {
        cout << "Malformed Input, Incorrect Number Of Parameters; Requires 5 ints" << endl;
        return 0;
    }

    int max__move_distance_ = 0;
    Point robot_pos;
    Point target_pos;

    try
    {
        max__move_distance_ = stoi(argv[1]);
        robot_pos.x_ = stoi(argv[2]);
        robot_pos.y_ = stoi(argv[3]);
        target_pos.x_ = stoi(argv[2]);
        target_pos.y_ = stoi(argv[3]);
    }
    catch (const std::exception &e)
    {
        cout << "Malformed Input, Parameters Must Be Int" << endl;
    }

    GreedyRobot(robot_pos, target_pos, max__move_distance_);
}