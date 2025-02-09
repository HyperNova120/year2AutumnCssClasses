#include "graphl.h"

GraphL::GraphL()
{
    size = 1;
    for (int i = 0; i < maxNodes; i++) // start
    {
        NodeList[i] = {nullptr, nullptr, false};
    }
}

void GraphL::buildGraph(ifstream &infile)
{
    if (infile.eof())
    {
        return;
    }
    string s = "";
    int numNodes;

    infile >> numNodes;
    getline(infile, s); // this is here to remove the \r at the end of the line.
    size = numNodes + 1;
    for (int i = 0; i < numNodes; i++)
    {
        getline(infile, s);
        NodeList[i + 1] = {nullptr, new NodeData(s), false};
        // data[i + 1] = NodeData(s);
    }
    int start, end;
    while (!infile.eof() && infile >> start >> end)
    {
        if (start == 0 && end == 0)
        {
            break;
        }
        insertEdge(start, end);
    }
}

void GraphL::insertEdge(int from, int to)
{
    if ((from < 1 || from > size) || (to < 1 || to > size))
    {
        return;
    }
    EdgeNode *tmp = new EdgeNode();
    tmp->adjGraphNode = to;
    tmp->nextEdge = NodeList[from].edgeHead;
    NodeList[from].edgeHead = tmp;
    // costMatrix[from][to] = weight;
}

void GraphL::displayGraph()
{
    cout << "Graph:" << endl;
    for (int i = 1; i < size; i++)
    {
        cout << "Node" << i << "\t" << *NodeList[i].data << endl << endl;
        EdgeNode *reader = NodeList[i].edgeHead;
        while (reader != nullptr)
        {
            cout << " edge " << i << " " << reader->adjGraphNode << endl;;
            reader = reader->nextEdge;
        }
    }
}

void GraphL::depthFirstSearch()
{
    queue<int> DFSOrder;
    depthFirstSearchHelper(1, DFSOrder);
    cout << "Depth-first ordering:";
    while (!DFSOrder.empty())
    {
        cout << "  " << DFSOrder.front();
        DFSOrder.pop();
    }
    cout << endl << endl;
}

void GraphL::depthFirstSearchHelper(int originNode, queue<int> &DFSOrder)
{
    if (NodeList[originNode].visited)
    {
        return;
    }
    DFSOrder.push(originNode);
    NodeList[originNode].visited = true;
    EdgeNode *reader = NodeList[originNode].edgeHead;
    while (reader != nullptr)
    {
        depthFirstSearchHelper(reader->adjGraphNode, DFSOrder);
        reader = reader->nextEdge;
    }
}
