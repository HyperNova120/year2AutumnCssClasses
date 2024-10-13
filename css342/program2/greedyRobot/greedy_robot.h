#ifndef GREEDY_ROBOT_H_
#define GREEDY_ROBOT_H_ ;
#include <set>
#include <string>
using namespace std;

struct Point
{
    int x_;
    int y_;
    Point(int x, int y);
};
enum Direction
{
    N,
    E,
    S,
    W
};


class GreedyRobot
{
public:
    int CalculateDist(Point from, Point to);
    Direction CalculateMostLikely(Point from, Point to);
    void CalculatePaths(int max_distance, Point from, Point to);
    string findPaths(Point from, Point to, string curPath);
private:
    set<string> knownPaths_;
    int smallestPath = __INT_MAX__;
    Direction lastDirection;
    int max_distance_;
    int cur_dist_traveled_ = 0;
};
#endif // GREEDY_ROBOT_H_