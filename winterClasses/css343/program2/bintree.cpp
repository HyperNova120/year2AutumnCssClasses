#include "bintree.h"

/// @brief defualt constructor
BinTree::BinTree() {}

/// @brief copy constructor
/// @param other BinTree to copy
BinTree::BinTree(const BinTree &other)
{
    *this = other;
}

/// @brief deconstructor
BinTree::~BinTree()
{
    deleteHelper(root);
    root = nullptr;
}

/// @brief returns if BinTree is empty
/// @return true if BinTree is empty, false if not
bool BinTree::isEmpty() const
{
    return root == nullptr;
}

/// @brief calls deconstructor to empty BinTree
void BinTree::makeEmpty()
{
    this->~BinTree();
}

/// @brief assignment operator
/// @param other BinTree to perform deep copy of
/// @return BinTree for chaining
BinTree &BinTree::operator=(const BinTree &other)
{
    if (this == &other)
    {
        return *this;
    }
    this->~BinTree();
    queue<Node *> curNodeToAdd;
    curNodeToAdd.push(other.root);
    while (curNodeToAdd.size() != 0)
    {
        Node *curNode = curNodeToAdd.front();
        if (curNode != nullptr)
        {
            NodeData *tmp = new NodeData(*curNode->data);
            if (!insert(tmp))
            {
                delete tmp;
            }
            curNodeToAdd.push(curNode->left);
            curNodeToAdd.push(curNode->right);
        }
        curNodeToAdd.pop();
    }
    return *this;
}

/// @brief equality operator
/// @param other BinTree to test equality of
/// @return true if BinTree is equal to other, false if not
bool BinTree::operator==(const BinTree &other) const
{
    if (this == &other)
    {
        return true;
    }
    return equivalencyHelper(root, other.root);
}

/// @brief non-equality operator
/// @param other BinTree to test non-equality of
/// @return true if BinTree is not equal to other, false if not
bool BinTree::operator!=(const BinTree &other) const
{
    return !(*this == other);
}

/// @brief inserts a deep copy of data into BinTree if no duplicate exists
/// @param data object to insert into BinTree
/// @return true if insertion was successful, false if a duplicate exist
bool BinTree::insert(NodeData *data)
{
    if (data == nullptr)
    {
        return false;
    }
    if (root == nullptr)
    {
        Node *tmp = new Node();
        tmp->data = data;
        // delete data;
        root = tmp;
        return true;
    }

    Node *reader = root;
    while (((*data < *reader->data) ? reader->left : reader->right) != nullptr)
    {
        if (*data == *reader->data)
        {
            // duplicate
            return false;
        }
        reader = (*data < *reader->data) ? reader->left : reader->right;
    }
    if (*data == *reader->data)
    {
        // duplicate
        return false;
    }
    Node *tmp = new Node();
    tmp->data = data;
    ((*data < *reader->data) ? reader->left : reader->right) = tmp;
    // delete data;
    return true;
}

/// @brief returns a pointer to the object within the BinTree if found
/// @param target NodeData to find
/// @param nodeData pointer to found object. gets set to nullptr if not found
/// @return true if target was found, false if not
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

/// @brief recursively deletes starting from curNode
/// @param curNode root of (sub)-tree to delete
void BinTree::deleteHelper(Node *curNode)
{
    if (curNode == nullptr)
    {
        return;
    }
    deleteHelper(curNode->left);
    deleteHelper(curNode->right);
    curNode->left = nullptr;
    curNode->right = nullptr;
    delete curNode->data;
    delete curNode;
}

/// @brief recursive helper to test equality
/// @param curNode BinTree node to test
/// @param otherCurNode other BinTree node to test
/// @return true if curNode == otherCurNode, false otherwise
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

/// @brief gets the height of curNode recursively
/// @param curNode node to get the height of
/// @return height of curNode
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

/// @brief returns a node pointer to the node containing target
/// @param target nodeData to search for
/// @return pointer to node containing target
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

/// @brief gets the height of the node containing target
/// @param target nodeData to search for
/// @return height of node containing target
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

/// @brief empties BinTree into array as in-order NodeData
/// @param arr nodeData ponter array to populate with BinTree nodes
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

/// @brief recursively adds nodes in-order to arr
/// @param curNode current node to add to arr
/// @param arr array to populate with BinTree
/// @param index arr index to set next NodeData to
void BinTree::bstreeToArrayHelper(Node *curNode, NodeData *arr[], int &index)
{
    if (curNode == nullptr)
    {
        return;
    }
    bstreeToArrayHelper(curNode->left, arr, index);
    arr[index] = curNode->data;
    curNode->data = nullptr;
    index++;
    bstreeToArrayHelper(curNode->right, arr, index);
}

/// @brief empties arr to create a balanced BinTree
/// @param arr NodeData array to remove and populate BinTree with
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

/// @brief recursively insert NodeData from arr into BinTree
/// @param arr NodeData array to populate BinTree with
/// @param low min arr index to populate from
/// @param high max arr index to populate from
void BinTree::arrayToBSTreeHelper(NodeData *arr[], int low, int high)
{
    if (high < low)
    {
        return;
    }
    int mid = (low + high) / 2;
    if (arr[mid] != nullptr)
    {
        // NodeData *tmp = new NodeData(*arr[mid]);
        insert(arr[mid]);
        //delete arr[mid];
        arr[mid] = nullptr;
    }

    if (low == high)
    {
        return;
    }
    arrayToBSTreeHelper(arr, low, mid - 1);
    arrayToBSTreeHelper(arr, mid + 1, high);
}

/// @brief ostream operator
/// @param os ostream object to output to
/// @param obj BinTree to print
/// @return ostream with obj printed to
ostream &operator<<(ostream &os, BinTree obj)
{
    obj.inorderHelper(obj.root, os);
    os << endl; // this is cursed
    return os;
}

/// @brief recursively output curNode in-order to os
/// @param curNode root of (sub)-tree to print out in-order
/// @param os ostream to print to
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
