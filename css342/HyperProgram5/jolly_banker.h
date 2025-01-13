// Kyryll Kotyk
// 12/8/2024
// CSS 342
// Program 5: Jolly Banker
// Robert Dimpsey
#ifndef JOLLY_BANKER_H_
#define JOLLY_BANKER_H_

#include <queue>
#include <sstream>
#include "bstree.h"

//The JollyBanker class manages the banking system.
//It uses a binary search tree to store and manage accounts,
//and a queue to process customer transactions in order.
//Supports reading input files, validating transactions, 
//and executing various banking operations.
class JollyBanker
{
public:
	//Constructor
	JollyBanker() : accounts_() {};
	//Reads the file and calls the processing function
	void ReadFile(ifstream& file);
	//Does the transactions stored in the queue
	void QueueActions();
	//Displays final balances of the 
	void DisplayFinalBalances() const;
private:
	//Tree that holds the accounts
	BSTree accounts_;
	//Queue of inputs, same order as given in the file
	queue<Transaction> input_;
	//Checks whether the parameters are valid
	bool ValidParameters(Transaction& trans) const;
	//Executes the given transaction
	bool DoAction(Transaction& type);
	//Turns the string input into a Transaction object 
	void ProcessInput(string line);
};
#endif