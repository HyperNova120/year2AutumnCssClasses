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

    GreedyRobot greedy_robot;
    greedy_robot.CalculatePaths(max__move_distance_, robot_pos, target_pos);

    if (greedy_robot.known_paths().size() == 0)
    {
        cout << "No Valid Paths" << endl;
        // cout << "Number of paths: " << greedy_robot.known_paths().size() << endl;
        return 0;
    }

    for (string s : greedy_robot.known_paths())
    {
        cout << s << endl;
    }

    cout << "Number of paths: " << greedy_robot.known_paths().size() << endl;
}

int GreedyRobot::CalculateShortestPossibleDistance(Point from, Point to)
{
    return abs(from.x_ - to.x_) + abs(from.y_ - to.y_);
}

void GreedyRobot::CalculatePaths(int max_move_distance, Point from, Point to)
{
    max_move_distance_ = max_move_distance;
    max_path_length_ = CalculateShortestPossibleDistance(from, to);
    FindPaths(from, to, "", NA, max_move_distance);
}

void GreedyRobot::FindPaths(Point from, Point to, string current_path, Direction last_direction, int same_steps_remaining)
{
    if (current_path.length() > max_path_length_                                                   // checks if the path we have taken is longer than possible
        || same_steps_remaining < 0                                                                // checks if we have moved passed allowed moves in same direction
        || current_path.length() + CalculateShortestPossibleDistance(from, to) > max_path_length_) // checks if this path is even possible in best case scenario
    {
        return;
    }
    if (from == to)
    {
        // found path
        known_paths_.insert(current_path);
        return;
    }
    Direction least_likely = FindLeastLikelyDirection(from, to);

    if (least_likely != N && last_direction != S)
        FindPaths(Point(from.x_, from.y_ + 1), to, current_path + "N", N, (last_direction == N) ? same_steps_remaining - 1 : max_move_distance_ - 1);
    if (least_likely != S && last_direction != N)
        FindPaths(Point(from.x_, from.y_ - 1), to, current_path + "S", S, (last_direction == S) ? same_steps_remaining - 1 : max_move_distance_ - 1);
    if (least_likely != E && last_direction != W)
        FindPaths(Point(from.x_ + 1, from.y_), to, current_path + "E", E, (last_direction == E) ? same_steps_remaining - 1 : max_move_distance_ - 1);
    if (least_likely != W && last_direction != E)
        FindPaths(Point(from.x_ - 1, from.y_), to, current_path + "W", W, (last_direction == W) ? same_steps_remaining - 1 : max_move_distance_ - 1);
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

set<string> GreedyRobot::known_paths()
{
    return known_paths_;
}

Direction GreedyRobot::FindLeastLikelyDirection(Point from, Point to)
{
    if (abs(to.x_ - from.x_))
    {
        // x largest dir
        if (to.x_ - from.x_ > 0)
        {
            return W;
        }
        return E;
    }

    if (to.y_ - from.y_ > 0)
    {
        return S;
    }
    return N;
}
