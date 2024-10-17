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
    int CalculateShortestPossibleDistance(Point from, Point to);
    void CalculatePaths(int max_distance, Point from, Point to);
    
    set<string> knownPaths();
private:
    set<string> knownPaths_;
    Direction FindLeastLikelyDirection(Point from, Point to);
    void findPaths(Point from, Point to, string curPath, Direction lastDir, int sameStepsRemaining);
    int max_path_length_;
    int max_move_distance_;
};
#endif // GREEDY_ROBOT_H_