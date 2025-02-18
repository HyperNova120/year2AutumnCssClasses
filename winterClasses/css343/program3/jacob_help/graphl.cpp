#include "graphl.h"

// ------------------------------------GraphL Constructor -------------------------------------------
// Description: Sets size to 0
// --------------------------------------------------------------------------------------------------
GraphL::GraphL()
{
    size_ = 0;

} // End GraphL Constructor

// ------------------------------------GraphL De-Constructor -----------------------------------------
// Description: Deletes all dynamically alocated memory
// ---------------------------------------------------------------------------------------------------
GraphL::~GraphL()
{
    for (int i = 1; i <= size_; i++)
    {
        delete graph[i].data;
        graph[i].data = nullptr;
        graph[i].visited = false;
        EdgeNode *currentEdge = graph[i].edgeHead;
        while (currentEdge != nullptr)
        {
            EdgeNode *temp = currentEdge;

            currentEdge = currentEdge->nextEdge;

            delete temp;
        }
        graph[i].edgeHead = nullptr;
        // delete graph[i];
    }
    size_ = 0;
} // End Graphl De-constructor

// ------------------------------------GraphL Build graph --------------------------------------------
// Description: Reads a data file by refrence
// builds ajecency list with Nodedata for hte name of the nodes and edges
// ---------------------------------------------------------------------------------------------------
void GraphL::buildGraph(ifstream &infile1)
{

    string line;

    // Read the size of the graph
    if (getline(infile1, line))
    {
        stringstream ss(line);
        ss >> size_;
    }

    // Read node names
    for (int i = 1; i <= size_; i++)
    {
        string nodeName;
        if (getline(infile1, nodeName))
        {
            // GraphNode *temp = new GraphNode();
            // temp->data =  new NodeData(nodeName);
            graph[i].data = new NodeData(nodeName);
            graph[i].edgeHead = nullptr;
        }
    }
    int from, to;
    while (getline(infile1, line))
    {
        stringstream ss(line);
        ss >> from >> to;

        // If we reach the end marker (0 0 0), break the loop
        if (from == 0 && to == 0)
        {
            break;
        }
        EdgeNode *temp = new EdgeNode;
        temp->adjGraphNode = to;

        temp->nextEdge = graph[from].edgeHead;
        graph[from].edgeHead = temp;
    }

} // End GraphL build graph

// ------------------------------------GraphL displayGraph -------------------------------------------
// Description: Displays graph by the name of the starting node and its edges
// ---------------------------------------------------------------------------------------------------
void GraphL::displayGraph()
{
    cout << "Graph:" << endl;
    for (int i = 1; i <= size_; i++)
    {
        cout << " Node" << i << "\t" << *graph[i].data << endl;
        EdgeNode *temp = graph[i].edgeHead;
        while (temp != nullptr)
        {
            cout << "    " << i << "\t" << (temp->adjGraphNode) << endl;
            temp = temp->nextEdge;
        }
    }
} // End GraphL Display graph

// ------------------------------------GraphL Depth First Search -------------------------------------
// Description: Calculates the path using Depth first search on the Adjcency list
// Prints out the path
// ---------------------------------------------------------------------------------------------------
void GraphL::depthFirstSearch()
{
    string output;
    stack<int> path;

    // Reset visited nodes before traversal
    for (int i = 1; i <= size_; i++)
    {
        graph[i].visited = false;
    }

    path.push(1);
    graph[1].visited = true;

    while (!path.empty())
    {
        int node = path.top();
        path.pop();
        output += to_string(node) + " ";

        // Push neighbors onto the stack in REVERSE order to process correctly in DFS
        EdgeNode *temp = graph[node].edgeHead;
        EdgeNode *prev = nullptr; // Track previous node for reversing
        while (temp != nullptr)
        {
            EdgeNode *next = temp->nextEdge;
            temp->nextEdge = prev;
            prev = temp;
            temp = next;
        }

        // Push reversed list to the stack
        temp = prev; // prev is now the head of reversed list
        while (temp != nullptr)
        {
            if (!graph[temp->adjGraphNode].visited)
            {
                path.push(temp->adjGraphNode);
                graph[temp->adjGraphNode].visited = true;
            }
            temp = temp->nextEdge;
        }
    }
    cout << endl;
    cout << "Depth First search:" << endl;
    cout << output << endl;
    cout << endl;
} // End GraphL Depth First Search