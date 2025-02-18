#ifndef graphl_H
#define graphl_H
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include "nodedata.h"
#include <stack>
const int MAXNODES =500;
using namespace std;

struct EdgeNode;
//Starting Node for the adjcency list
struct GraphNode{
    EdgeNode * edgeHead = nullptr;
    NodeData*data = nullptr;
    bool visited = false;
};

//Nodes to build the edges 
struct EdgeNode{
    int adjGraphNode = 0;
    EdgeNode* nextEdge = nullptr;
};

class GraphL{

    public:

    // ------------------------------------GraphL Constructor -------------------------------------------
    // Description: Sets size to 0
    // --------------------------------------------------------------------------------------------------
    GraphL();

    // ------------------------------------GraphL De-Constructor -----------------------------------------
    // Description: Deletes all dynamically alocated memory
    // ---------------------------------------------------------------------------------------------------
    ~GraphL();

    // ------------------------------------GraphL Build graph --------------------------------------------
    // Description: Reads a data file by refrence 
    // builds ajecency list with Nodedata for hte name of the nodes and edges
    // ---------------------------------------------------------------------------------------------------
    void buildGraph(ifstream &infile1);

    // ------------------------------------GraphL displayGraph -------------------------------------------
    // Description: Displays graph by the name of the starting node and its edges
    // ---------------------------------------------------------------------------------------------------
    void displayGraph();


    void depthFirstSearch();
    // ------------------------------------GraphL Depth First Search -------------------------------------
    // Description: Calculates the path using Depth first search on the Adjcency list
    // Prints out the path
    // ---------------------------------------------------------------------------------------------------

    private:
    int size_;
    GraphNode graph[MAXNODES];

};
#endif