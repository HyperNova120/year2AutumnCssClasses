#ifndef GRAPHL_H_
#define GRAPHL_H_
#include "nodedata.h"
#include <climits>
#include <queue>
#include <stack>
#include <iostream>
using namespace std;
class GraphL
{
public:
    GraphL();

    void buildGraph(ifstream &infile);
    void insertEdge(int from, int to);
    void displayGraph();
    void depthFirstSearch();
    void depthFirstSearchHelper(int originNode, queue<int> &DFSOrder);

private:
    static const int maxNodes = 101; // allow for 100 nodes with 1 based indexing
    int size = 0;        
                // for calculation simplicity size = #nodes+1
    struct TableType
    {
        bool visited; // whether node has been visited
        int dist = 0; // shortest distance from source known so far
        int path = 0; // previous node in path of min dist
    };
    TableType pathTable[maxNodes][maxNodes];

    struct EdgeNode
    {
        int adjGraphNode; // subscript of the adjacent graph node
        EdgeNode *nextEdge;
    };
    struct GraphNode
    {                       // structs used for simplicity, use classes if desired
        EdgeNode *edgeHead; // head of the list of edges
        NodeData *data;     // data information about each node
        bool visited;
    };
    GraphNode NodeList[maxNodes];
};

#endif // GRAPHL_H_
