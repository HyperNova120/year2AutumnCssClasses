#include <iostream>
#include <sstream>
#include <cmath>
#include <vector>
#include "greedy_robot.h"
using namespace std;

int main(int argc, char *argv[])
{
    if (argc != 6)
    {
        cout << "Malformed Input, Incorrect Number Of Parameters:" << argc << endl;
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

    // cout << "MaxDist:" << max__move_distance_ << " robot:(" << robot_pos.x_ << "," << robot_pos.y_ << ") target:(" << target_pos.x_ << "," << target_pos.y_ << ")" << endl;

    if (target_pos == robot_pos)
    {
        cout << "Already There" << endl;
        return 0;
    }

    GreedyRobot gr;
    gr.CalculatePaths(max__move_distance_, robot_pos, target_pos);
    int smallest_path = INT32_MAX;

    vector<string> temp;
    for (string s : gr.knownPaths())
    {
        temp.push_back(s);
    }

    if (temp.size() == 0)
    {
        cout << "NP" << endl;
        cout << "Number of paths: " << temp.size() << endl;
        return 0;
    }

    for (int i = temp.size() - 1; i >= 0; i--)
    {
        cout << temp[i] << endl;
    }
    cout << "Number of paths: " << temp.size() << endl;
}

int GreedyRobot::CalculateShortestPossibleDistance(Point from, Point to)
{
    return abs(from.x_ - to.x_) + abs(from.y_ - to.y_);
}

void GreedyRobot::CalculatePaths(int max_move_distance, Point from, Point to)
{
    max_move_distance_ = max_move_distance;
    max_path_length_ = CalculateShortestPossibleDistance(from, to);
    findPaths(from, to, "", NA, max_move_distance);
}

void GreedyRobot::findPaths(Point from, Point to, string curPath, Direction lastDir, int sameStepsRemaining)
{
    if (curPath.length() > max_path_length_ || sameStepsRemaining < 0)
    {
        return;
    }
    if (from == to)
    {
        // found path
        knownPaths_.insert(curPath);
        return;
    }
    findPaths(Point(from.x_, from.y_ + 1), to, curPath + "N", N, (lastDir == N) ? sameStepsRemaining - 1 : max_move_distance_ - 1);
    findPaths(Point(from.x_, from.y_ - 1), to, curPath + "S", S, (lastDir == S) ? sameStepsRemaining - 1 : max_move_distance_ - 1);
    findPaths(Point(from.x_ + 1, from.y_), to, curPath + "E", E, (lastDir == E) ? sameStepsRemaining - 1 : max_move_distance_ - 1);
    findPaths(Point(from.x_ - 1, from.y_), to, curPath + "W", W, (lastDir == W) ? sameStepsRemaining - 1 : max_move_distance_ - 1);
}

Point::Point(int x, int y)
{
    x_ = x;
    y_ = y;
}

Point::Point()
{
    x_ = 0;
    y_ = 0;
}

bool Point::operator==(const Point &other)
{
    return x_ == other.x_ && y_ == other.y_;
}

set<string> GreedyRobot::knownPaths()
{
    return knownPaths_;
}
