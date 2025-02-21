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
    GraphM(); // consructor

    // build graph from file
    void buildGraph(ifstream &infile);

    // add edge between from/to
    void insertEdge(int from, int to, int weight);

    // remove edge between from/to
    void removeEdge(int from, int to);

    // calculate shortest path between all noes
    void findShortestPath();

    // display graph
    void displayAll();

    // display path betwen origin/end
    void display(int originNode, int endNode);

    // display only path between origin/end
    stack<int> displayPlain(int originNode, int endNode);

private:
    static const int maxNodes = 101; // allow for 100 nodes with 1 based indexing

    int size = 0; // for calculation simplicity size = #nodes+1

    NodeData data[maxNodes];            // nodes of graph
    int costMatrix[maxNodes][maxNodes]; // cost of edges
    struct TableType
    {
        bool visited; // whether node has been visited
        int dist = 0; // shortest distance from source known so far
        int path = 0; // previous node in path of min dist
    };
    TableType pathTable[maxNodes][maxNodes]; // data for shortest path
};

#endif // GRAPHM_H_
