#include <iostream>
#include <sstream>
#include "greedy_robot.h"
using namespace std;

int main(int argc, char * argv[])
{
     if (argc != 6)
    {
        cout << "Malformed Input, Incorrect Number Of Parameters; Requires 5 ints" << endl;
        return 0;
    }

    int max__move_distance_ = 0;

    stringstream ss;
    ss << argv[1];
    ss >> max__move_distance_;

    stringstream ss2;
    stringstream ss3;
    ss2 << argv[2];
    ss3 << argv[3];
    Point robot_pos;
    ss2 >> robot_pos.x_;
    ss3 >> robot_pos.y_;

    stringstream ss4;
    stringstream ss5;
    ss4 << argv[4];
    ss5 << argv[5];
    Point target_pos;
    ss4 >> target_pos.x_;
    ss5 >> target_pos.y_;
    GreedyRobot(robot_pos, target_pos, max__move_distance_);
}