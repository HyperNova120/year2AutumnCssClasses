#ifndef GREEDY_ROBOT_H_
#define GREEDY_ROBOT_H_ ;
#include <set>
#include <string>
using namespace std;

struct Point
{
    int x_;
    int y_;
    Point();
    Point(int x, int y);
    bool operator==(const Point &other) const;
};
enum Direction
{
    N,
    E,
    S,
    W,
    NA
};

class GreedyRobot
{
public:
    GreedyRobot(const Point robot_pos, const Point target_pos, const int max__move_distance_);

    int known_paths() const;

private:
    int CalculateShortestPossibleDistance(const Point &from, const Point &to) const;
    void CalculatePaths(const int max_distance, const Point from, const Point to);
    Direction FindLeastLikelyDirection(const Point &from, const Point &to) const;
    void FindPaths(Point from, Point to, string current_path, Direction last_direction, int same_steps_remaining);
    int known_paths_ = 0;
    int max_path_length_ = 0;
    int max_move_distance_ = 0;
};
#endif // GREEDY_ROBOT_H_