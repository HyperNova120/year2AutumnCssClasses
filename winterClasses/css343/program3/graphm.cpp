#include "graphm.h"

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

void GraphM::buildGraph(ifstream &infile)
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

void GraphM::insertEdge(int from, int to, int weight)
{
    if ((from < 1 || from > size) || (to < 1 || to > size))
    {
        return;
    }
    costMatrix[from][to] = weight;
}

void GraphM::removeEdge(int from, int to)
{
    if ((from < 1 || from > size) || (to < 1 || to > size))
    {
        return;
    }
    costMatrix[from][to] = INT_MAX;
}

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

void GraphM::display(int originNode, int endNode)
{
    stack<int> tmp = displayPlain(originNode, endNode);
    while (!tmp.empty())
    {
        cout << data[tmp.top()] << endl;
        tmp.pop();
    }
}

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
