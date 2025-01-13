#ifndef BSTREE_H_
#define BSTREE_H_
#include "account.h"
//Binary Search Tree for storing the accounts
//created in the jolly banker 
class BSTree
{
public:
	//Constructor
	BSTree() : root_(nullptr) {};
	//Destructor
	~BSTree();
	//Inserts the account into the tree by its ID
	bool Insert(Account* acc);
	//Finds the needed account and gives it to
	//the account parameter
	bool Retrieve(const int& id, Account*& retrieved) const;
	void DisplayInOrder() const;
private:
	//Simple Node for the tree
	struct Node {
		Account* curr;
		Node* right;
		Node* left;
		Node(Account* acc) : curr(acc), right(nullptr), left(nullptr) {};
	};
	void DisplayInOrderHelper(Node* node) const;
	void Clear(Node* node);
	Node* root_;
};
#endif