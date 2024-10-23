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
    bool operator==(const Point &other);
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
    GreedyRobot(Point robot_pos, Point target_pos, int max__move_distance_);

    set<string> known_paths();

private:
    int CalculateShortestPossibleDistance(Point from, Point to);
    void CalculatePaths(int max_distance, Point from, Point to);
    Direction FindLeastLikelyDirection(Point from, Point to);
    void FindPaths(Point from, Point to, string current_path, Direction last_direction, int same_steps_remaining);
    set<string> known_paths_;
    int max_path_length_;
    int max_move_distance_;
};
#endif // GREEDY_ROBOT_H_