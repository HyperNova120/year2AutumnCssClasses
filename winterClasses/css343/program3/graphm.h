#ifndef GRAPHM_H_
#define GRAPHM_H_
#include "nodedata.h"
#include <climits>
#include <queue>
#include <stack>
#include <iostream>
using namespace std;
class GraphM
{
public:
    GraphM();

    void buildGraph(ifstream &infile);
    void insertEdge(int from, int to, int weight);
    void removeEdge(int from, int to);
    void findShortestPath();
    void displayAll();
    void display(int originNode, int endNode);
    stack<int> displayPlain(int originNode, int endNode);

private:
    static const int maxNodes = 101; // allow for 100 nodes with 1 based indexing
    int size = 0; //for calculation simplicity size = #nodes+1
    NodeData data[maxNodes];
    int costMatrix[maxNodes][maxNodes];
    struct TableType
    {
        bool visited; // whether node has been visited
        int dist = 0;     // shortest distance from source known so far
        int path = 0;     // previous node in path of min dist
    };
    TableType pathTable[maxNodes][maxNodes];
};

#endif // GRAPHM_H_
