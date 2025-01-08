#include <iostream>
#include <sstream>
#include <cmath>
#include <string>
#include <vector>
#include "greedy_robot.h"
using namespace std;

int GreedyRobot::CalculateShortestPossibleDistance(const Point &from, const Point &to) const
{
    return abs(from.x_ - to.x_) + abs(from.y_ - to.y_);
}

void GreedyRobot::CalculatePaths(const int max_move_distance, const Point from, const Point to)
{
    max_move_distance_ = max_move_distance;
    max_path_length_ = CalculateShortestPossibleDistance(from, to);
    target_ = to;
    FindPaths(from, "", NA, max_move_distance);
}

void GreedyRobot::FindPaths(const Point &from, const string &current_path, const Direction &last_direction, const int &same_steps_remaining)
{
    if (current_path.length() > max_path_length_ )
    {
        //path too long/invalid
        return;
    }
    if (from == target_)
    {
        // found path
        cout << current_path << endl;
        known_paths_++;
        return;
    }


    //only move in the direction towards the target point
    if (target_.x_ > from.x_)
    {
        // east
        if (!((last_direction == E) && same_steps_remaining == 0))
        {
            FindPaths(Point(from.x_ + 1, from.y_), current_path + "E", E,
                      (last_direction == E) ? same_steps_remaining - 1 : max_move_distance_ - 1);
        }
    }
    else if (target_.x_ < from.x_)
    {
        // west
        if (!((last_direction == W) && same_steps_remaining == 0))
        {
            FindPaths(Point(from.x_ - 1, from.y_), current_path + "W", W,
                      (last_direction == W) ? same_steps_remaining - 1 : max_move_distance_ - 1);
        }
    }

    if (target_.y_ > from.y_)
    {
        // north
        if (!((last_direction == N) && same_steps_remaining == 0))
        {
            FindPaths(Point(from.x_, from.y_ + 1), current_path + "N", N,
                      (last_direction == N) ? same_steps_remaining - 1 : max_move_distance_ - 1);
        }
    }
    else if (target_.y_ < from.y_)
    {
        // south
        if (!((last_direction == S) && same_steps_remaining == 0))
        {
            FindPaths(Point(from.x_, from.y_ - 1), current_path + "S", S,
                      (last_direction == S) ? same_steps_remaining - 1 : max_move_distance_ - 1);
        }
    }
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

bool Point::operator==(const Point &other) const
{
    return x_ == other.x_ && y_ == other.y_;
}

int GreedyRobot::known_paths() const
{
    return known_paths_;
}

GreedyRobot::GreedyRobot(const Point robot_pos, const Point target_pos, const int max__move_distance_)
{
    if (max__move_distance_ <= 0)
    {
        cout << "Max Move Distance Must Be > 0" << endl;
        return;
    }
    if (target_pos == robot_pos)
    {
        cout << "Already There" << endl;
        cout << "Number of paths: 0" << endl;
        return;
    }
    CalculatePaths(max__move_distance_, robot_pos, target_pos);

    if (known_paths() == 0)
    {
        cout << "No Valid Paths" << endl;
        cout << "Number of paths: 0" << endl;
        return;
    }
    cout << "Number of paths: " << known_paths() << endl;
}
