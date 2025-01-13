#include "bstree.h"

BSTree::~BSTree() {
	Clear(root_);
}
bool BSTree::Insert(Account* account)
{
	int id = account->getID();
	Node* node = root_;
	if (node == nullptr) {
		root_ = new Node(account);
		return true;
	}

	while (node != nullptr) {
		int id_2 = node->curr->getID();
		if (id == id_2) {
			return false;
		}

		if (id < id_2) {
			if (node->left != nullptr) {
				node = node->left;
			}
			else {
				node->left = new Node(account);
				return true;
			}
		
		}
		else {
			if (node->right != nullptr) {
				node = node->right;
			}
			else {
				node->right = new Node(account);
				return true;
			}
		
		}
	}
	return false;	
}

bool BSTree::Retrieve(const int& id, Account*& retrieved) const
{
	Node* node = root_;
	while (node != nullptr) {
		if (id == node->curr->getID()) {
			retrieved = node->curr;
			return true;
		}
		if (id > node->curr->getID()) {
			node = node->right;
		}
		else {
			node = node->left;
		}
	}
	return false;
}

void BSTree::DisplayInOrder() const {
	DisplayInOrderHelper(root_);
}

void BSTree::DisplayInOrderHelper(Node* node) const {
	if (node == nullptr) {
		return;
	}
	DisplayInOrderHelper(node->left);
	node->curr->DisplayFinalBalance();
	DisplayInOrderHelper(node->right);
}
void BSTree::Clear(Node* node) {
	if (node != nullptr) {
		Clear(node->left);
		Clear(node->right);
		delete node->curr;
		delete node;       
	}
}