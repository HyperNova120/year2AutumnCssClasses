#include "BinTree.h"

BinTree::BinTree() {}

BinTree::BinTree(const BinTree &other)
{
    *this = other;
}

BinTree::~BinTree()
{
    recursiveDelete(root);
}

bool BinTree::isEmpty() const
{
    return root == nullptr;
}

void BinTree::makeEmpty()
{
    this->~BinTree();
}

BinTree &BinTree::operator=(const BinTree &other)
{
    // TODO: insert return statement here
}

bool BinTree::operator==(const BinTree &other) const
{
    return recursiveEqualsCheck(root, other.root);
}

bool BinTree::operator!=(const BinTree &other) const
{
    return !(*this == other);
}

bool BinTree::insert(NodeData *data)
{
    Node *tmp = new Node();
    tmp->data = data;
    if (root == nullptr)
    {
        root = tmp;
        return true;
    }

    Node *reader = nullptr;
    Node *next = root;
    while (next != nullptr)
    {
        reader = next;
        if (*reader->data == *data)
        {
            return false;
        }
        next = (*data < *reader->data) ? reader->left : reader->right;
    }
    if (*data < *reader->data)
    {
        reader->left = tmp;
    }
    else
    {

        reader->right = tmp;
    }
    return true;
}

bool BinTree::retrieve(const NodeData &target, NodeData *&nodeData) const
{
    Node *targetNode = getNode(target);

    if (targetNode != nullptr && *targetNode->data == target)
    {
        nodeData = targetNode->data;
        return true;
    }
    nodeData = nullptr;
    return false;
}

void BinTree::recursiveDelete(Node *curNode)
{
    if (curNode == nullptr)
    {
        return;
    }
    recursiveDelete(curNode->left);
    curNode->left = nullptr;
    recursiveDelete(curNode->right);
    curNode->right = nullptr;
    delete curNode->data;
    curNode->data = nullptr;
    delete curNode;
}

bool BinTree::recursiveEqualsCheck(const Node *curNode, const Node *otherCurNode) const
{
    if ((curNode == nullptr) ^ (otherCurNode == nullptr))
    {
        return false;
    }
    else if ((curNode == nullptr) && (otherCurNode == nullptr))
    {
        return true;
    }
    if (*curNode->data != *otherCurNode->data)
    {
        return false;
    }
    return recursiveEqualsCheck(curNode->left, otherCurNode->left) &&
           recursiveEqualsCheck(curNode->right, otherCurNode->right);
}

int BinTree::getHeight(const Node *curNode) const
{
    if (curNode == nullptr)
    {
        return 0;
    }
    else if (curNode->left == nullptr && curNode->right == nullptr)
    {
        // leaf
        return 1;
    }
    int leftHeight = getHeight(curNode->left);
    int rightHeight = getHeight(curNode->right);

    return (leftHeight < rightHeight) ? leftHeight : rightHeight;
}

BinTree::Node *BinTree::getNode(const NodeData &target) const
{
    Node *reader = root;
    while (reader != nullptr && *reader->data != target)
    {
        reader = (target < *reader->data) ? reader->left : reader->right;
    }

    if (reader != nullptr && *reader->data == target)
    {
        // node found
        return reader;
    }
    return nullptr;
}

int BinTree::getHeight(const NodeData &target) const
{
    Node *targetNode = getNode(target);

    if (targetNode != nullptr)
    {
        // node found
        return getHeight(targetNode);
    }
    return 0;
}

//------------------------- displaySideways ---------------------------------
// Displays a binary tree as though you are viewing it from the side;
// hard coded displaying to standard output.
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
void BinTree::displaySideways() const
{
    sideways(root, 0);
}

//---------------------------- Sideways -------------------------------------
// Helper method for displaySideways
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
void BinTree::sideways(Node *current, int level) const
{
    if (current != NULL)
    {
        level++;
        sideways(current->right, level);

        // indent for readability, 4 spaces per depth level
        for (int i = level; i >= 0; i--)
        {
            cout << "    ";
        }

        cout << *current->data << endl; // display information of object
        sideways(current->left, level);
    }
}
