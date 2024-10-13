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

    int max_distance_ = 0;

    stringstream ss;
    ss << argv[1];
    ss >> max_distance_;

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

    cout << "MaxDist:" << max_distance_ << " robot:(" << robot_pos.x_ << "," << robot_pos.y_ << ") target:(" << target_pos.x_ << "," << target_pos.y_ << ")" << endl;

    GreedyRobot gr;
    gr.CalculatePaths(max_distance_, robot_pos, target_pos);
}

int GreedyRobot::CalculateDist(Point from, Point to)
{
    return abs(from.x_ - to.x_) + abs(from.y_ - to.y_);
}

Direction GreedyRobot::CalculateMostLikely(Point from, Point to)
{
    int xDist = to.x_ - from.x_;
    int yDist = to.y_ - from.y_;
    if (abs(xDist) < abs(yDist))
    {
        // x smaller dist
        return (xDist > 0) ? E : W;
    }
    return (yDist > 0) ? N : S;
}

void GreedyRobot::CalculatePaths(int max_distance, Point from, Point to)
{
    max_distance_ = max_distance;
    findPaths(from, to, "");
}

string GreedyRobot::findPaths(Point from, Point to, string curPath)
{
    Direction mostLikely = CalculateMostLikely(from, to);
    if (smallestPath < curPath.length())
    {
        return curPath.substr(0, curPath.length()-1);
    }
    
    string path = "";
    if (mostLikely == E)
    {
        Point point(from.x_ + 1, from.y_);
        curPath += "E";
        path = findPaths(point, to, curPath);
    }
    if (mostLikely == W)
    {
        Point point(from.x_ - 1, from.y_);
        curPath += "W";
        path = findPaths(point, to, curPath);
    }
    if (mostLikely == N)
    {
        Point point(from.x_, from.y_ + 1);
        curPath += "N";
        path = findPaths(point, to, curPath);
    }
    if (mostLikely == S)
    {
        Point point(from.x_, from.y_ - 1);
        curPath += "S";
        path = findPaths(point, to, curPath);
    }
}

Point::Point(int x, int y)
{
    x_ = x;
    y_ = y;
}
