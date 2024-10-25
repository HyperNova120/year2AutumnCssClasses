#include <iostream>
#include <sstream>
#include <cmath>
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
        //cout << current_path << endl;
        known_paths_++;
        return;
    }

    Direction least_likely = FindLeastLikelyDirection(from, to);

    if (least_likely != N && last_direction != S)
    {
        FindPaths(Point(from.x_, from.y_ + 1), to, current_path + "N", N,
                  (last_direction == N) ? same_steps_remaining - 1 : max_move_distance_ - 1);
    }
    if (least_likely != S && last_direction != N)
    {
        FindPaths(Point(from.x_, from.y_ - 1), to, current_path + "S", S,
                  (last_direction == S) ? same_steps_remaining - 1 : max_move_distance_ - 1);
    }
    if (least_likely != E && last_direction != W)
    {
        FindPaths(Point(from.x_ + 1, from.y_), to, current_path + "E", E,
                  (last_direction == E) ? same_steps_remaining - 1 : max_move_distance_ - 1);
    }
    if (least_likely != W && last_direction != E)
    {
        FindPaths(Point(from.x_ - 1, from.y_), to, current_path + "W", W,
                  (last_direction == W) ? same_steps_remaining - 1 : max_move_distance_ - 1);
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

Direction GreedyRobot::FindLeastLikelyDirection(const Point &from, const Point &to) const
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
