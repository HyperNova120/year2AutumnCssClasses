#include "graphm.h"

/// @brief default constructor
GraphM::GraphM()
{
    size = 1;
    for (int i = 0; i < maxNodes; i++) // start
    {
        for (int j = 0; j < maxNodes; j++) // moveTo
        {
            costMatrix[i][j] = INT32_MAX;
            pathTable[i][j] = {false, INT32_MAX, 0};
        }
        costMatrix[i][i] = 0;
        pathTable[i][i] = {false, 0, 0};
    }
}

/// @brief creates graph from data stored in file
/// @param infile file to build graph from
void GraphM::buildGraph(ifstream &infile)
{
    if (infile.eof())
    {
        return;
    }
    string s = "";
    int numNodes = 0;

    infile >> numNodes;
    getline(infile, s); // this is here to remove the \r at the end of the line.
    size = numNodes + 1;
    for (int i = 0; i < numNodes; i++)
    {
        getline(infile, s);
        data[i + 1] = NodeData(s);
    }
    int start, end, cost;
    while (!infile.eof() && infile >> start >> end >> cost)
    {
        if (start == 0 && end == 0 && cost == 0)
        {
            break;
        }
        insertEdge(start, end, cost);
    }
}

/// @brief adds an edge betwen from and to
/// @param from node edge originates from
/// @param to node edge points to
/// @param weight cost of taking that edge
void GraphM::insertEdge(int from, int to, int weight)
{
    if ((from < 1 || from >= size) || (to < 1 || to >= size))
    {
        return;
    }
    costMatrix[from][to] = weight;
}

/// @brief removes an edge between from and to
/// @param from node edge originates from
/// @param to node edge points to
void GraphM::removeEdge(int from, int to)
{
    if ((from < 1 || from >= size) || (to < 1 || to >= size))
    {
        return;
    }
    costMatrix[from][to] = INT_MAX;
}

/// @brief calculates shortest path between every node
void GraphM::findShortestPath()
{
    // start at 1 b/e we 1 based index for nodes :(
    // size = #nodes+1
    for (int i = 1; i < size; i++)
    {
        queue<int> nodesToVisit = queue<int>();
        nodesToVisit.push(i);
        while (!nodesToVisit.empty())
        {
            int curNode = nodesToVisit.front();
            for (int j = 0; j < size; j++)
            {
                if (i != j && costMatrix[curNode][j] < INT32_MAX)
                {
                    // has edge
                    int edgeCost = pathTable[i][curNode].dist + costMatrix[curNode][j];
                    if (edgeCost < pathTable[i][j].dist)
                    {
                        // path dist is smaller
                        pathTable[i][j].dist = edgeCost;
                        pathTable[i][j].path = curNode;
                        nodesToVisit.push(j);
                    }
                    // nodesToVisit.push(j);
                }
            }
            nodesToVisit.pop();
        }
    }
}

/// @brief displays all nodes with shortest paths
void GraphM::displayAll()
{
    cout << "Description\t\tFrom Node  To Node   Dijkstra's  Path" << endl;
    for (int i = 1; i < size; i++)
    {
        cout << data[i] << endl;
        for (int j = 1; j < size; j++)
        {
            if (i == j)
            {
                continue;
            }
            cout << "\t\t\t";
            displayPlain(i, j);
        }
    }
}

/// @brief displays data for paths between nodes
/// @param originNode start node
/// @param endNode end node
void GraphM::display(int originNode, int endNode)
{
    stack<int> tmp = displayPlain(originNode, endNode);
    while (!tmp.empty())
    {
        cout << data[tmp.top()] << endl;
        tmp.pop();
    }
}

/// @brief calculates only the path data for given nodes
/// @param originNode node to start from
/// @param endNode node to end at
/// @return path as int stack
stack<int> GraphM::displayPlain(int originNode, int endNode)
{
    stack<int> returner;
    if (pathTable[originNode][endNode].dist == INT_MAX)
    {
        // path from i
        cout << "\t" << originNode << "\t" << endNode;
        cout << "\t" << "----" << "\t" << endl;
    }
    else if (endNode != originNode)
    {
        // path from i
        cout << "\t" << originNode << "\t" << endNode;
        cout << "\t" << pathTable[originNode][endNode].dist << "\t";
        string path = "";
        int currenPathPos = endNode;
        returner.push(currenPathPos);
        do
        {
            path = to_string(currenPathPos) + " " + path;
            currenPathPos = pathTable[originNode][currenPathPos].path;
            returner.push(currenPathPos);
        } while (currenPathPos != originNode && currenPathPos != 0);
        path = to_string(originNode) + " " + path;
        cout << path << endl;
    }
    return returner;
}
