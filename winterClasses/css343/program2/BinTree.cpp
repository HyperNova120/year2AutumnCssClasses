#include "bintree.h"

BinTree::BinTree() {}

BinTree::BinTree(const BinTree &other)
{
    *this = other;
}

BinTree::~BinTree()
{
    deleteHelper(root);
    root = nullptr;
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
    if (this == &other)
    {
        return *this;
    }
    this->~BinTree();
    assignmentHelper(other.root);
    return *this;
}

bool BinTree::operator==(const BinTree &other) const
{
    return equivalencyHelper(root, other.root);
}

bool BinTree::operator!=(const BinTree &other) const
{
    return !(*this == other);
}

bool BinTree::insert(NodeData *data)
{
    data = new NodeData(*data);
    Node *tmp = new Node();
    tmp->data = data;
    if (root == nullptr)
    {
        root = tmp;
        return true;
    }

    Node *parent = nullptr;
    Node *next = root;
    while (next != nullptr)
    {
        parent = next;
        if (*parent->data == *data)
        {
            return false;
        }
        next = (*data < *parent->data) ? parent->left : parent->right;
    }
    if (*data < *parent->data)
    {
        parent->left = tmp;
    }
    else
    {
        parent->right = tmp;
    }
    return true;
}

bool BinTree::retrieve(const NodeData &target, NodeData *&nodeData) const
{
    Node *targetNode = getNode(target);

    if (targetNode != nullptr && *targetNode->data == target)
    {
        nodeData = new NodeData(*targetNode->data);
        return true;
    }
    nodeData = nullptr;
    return false;
}

void BinTree::deleteHelper(Node *curNode)
{
    if (curNode == nullptr)
    {
        return;
    }
    deleteHelper(curNode->left);
    curNode->left = nullptr;
    deleteHelper(curNode->right);
    curNode->right = nullptr;
    if (curNode->data != nullptr)
    {
        delete curNode->data;
        curNode->data = nullptr;
    }
    delete curNode;
}

bool BinTree::equivalencyHelper(const Node *curNode, const Node *otherCurNode) const
{
    if ((curNode == nullptr) ^ (otherCurNode == nullptr))
    {
        return false;
    }
    else if ((curNode == nullptr) && (otherCurNode == nullptr))
    {
        return true;
    }
    else if (*curNode->data != *otherCurNode->data)
    {
        return false;
    }
    return equivalencyHelper(curNode->left, otherCurNode->left) &&
           equivalencyHelper(curNode->right, otherCurNode->right);
}

int BinTree::getHeightHelper(const Node *curNode) const
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
    int leftHeight = getHeightHelper(curNode->left);
    int rightHeight = getHeightHelper(curNode->right);

    int height = ((leftHeight > rightHeight) ? leftHeight : rightHeight);
    return 1 + height;
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
        return getHeightHelper(targetNode);
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

void BinTree::bstreeToArray(NodeData *arr[])
{
    for (int i = 0; i < K_ARRAY_MAX_SIZE; i++)
    {
        if (arr[i] != nullptr)
        {
            delete arr[i];
            arr[i] = nullptr;
        }
    }
    int index = 0;
    bstreeToArrayHelper(root, arr, index);
    this->~BinTree();
}

void BinTree::bstreeToArrayHelper(Node *curNode, NodeData *arr[], int &index)
{
    if (curNode == nullptr)
    {
        return;
    }
    bstreeToArrayHelper(curNode->left, arr, index);
    arr[index] = new NodeData(*curNode->data);
    index++;
    bstreeToArrayHelper(curNode->right, arr, index);
}

void BinTree::arrayToBSTree(NodeData *arr[])
{
    this->~BinTree();
    int arraySize = 0;
    for (int i = 0; i < K_ARRAY_MAX_SIZE; i++)
    {
        if (arr[i] != nullptr)
        {
            arraySize++;
        }
    }
    arrayToBSTreeHelper(arr, 0, arraySize - 1);
    for (int i = 0; i < arraySize; i++)
    {
        if (arr[i] != nullptr)
        {
            delete arr[i];
            arr[i] = nullptr;
        }
    }
}

void BinTree::arrayToBSTreeHelper(NodeData *arr[], int low, int high)
{
    if (high < low)
    {
        return;
    }
    int mid = (low + high) / 2;
    if (arr[mid] != nullptr)
    {
        NodeData *tmp = new NodeData(*arr[mid]);
        insert(tmp);
        delete arr[mid];
        arr[mid] = nullptr;
    }

    if (low == high)
    {
        return;
    }
    arrayToBSTreeHelper(arr, low, mid - 1);
    arrayToBSTreeHelper(arr, mid + 1, high);
}

ostream &operator<<(ostream &os, BinTree obj)
{
    obj.inorderHelper(obj.root, os);
    os << endl; // this is cursed
    return os;
}

void BinTree::inorderHelper(Node *curNode, ostream &os) const
{
    if (curNode == nullptr)
    {
        return;
    }
    if (curNode->left != nullptr)
    {
        inorderHelper(curNode->left, os);
        os << " ";
    }
    os << *curNode->data;
    if (curNode->right != nullptr)
    {
        os << " ";
        inorderHelper(curNode->right, os);
    }
}

void BinTree::assignmentHelper(Node *curNode)
{
    if (curNode == nullptr)
    {
        return;
    }
    insert(new NodeData(*curNode->data));
    assignmentHelper(curNode->left);
    assignmentHelper(curNode->right);
}