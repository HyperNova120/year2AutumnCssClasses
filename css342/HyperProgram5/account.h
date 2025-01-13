#ifndef ACCOUNT_H_
#define ACCOUNT_H_

#include <iostream>
#include <string>
#include <array>
#include <vector>
#include "transaction.h"
using namespace std;
//Manipulates the funds of the account
//and stores the account's data
class Account
{
public:
	//Constructors
	Account() : funds_({}) {};
	Account(const int kID, const string kLastName, const string kFirstName);
	//Transfers from the given fund of the account which this is called on
	//to the given fund of the other account
	bool Transfer(const int kFType1, const int kFType_2, 
		const int kMoney, Account& account);
	//Removes the specified money amount from the fund
	bool Withdraw(const int KFType, const int kMoney);
	//Increases the money in the fund by the specified amount
	bool Deposit(const int kFType, const int kMoney);
	//Displays account information by fund
	void DisplayAccount() const;
	//Displays specific fund's information
	void DisplayFund(const int kFType) const;
	//Displays the final balance of the account
	void DisplayFinalBalance() const;
	//Adds the transaction to private transaction history.
	void AddToHistory(const Transaction kTransaction);
	//Returns the ID of the account
	int getID();
	string getName();
private:
	//Account's ID, first, and last name.
	int id_ = -1;
	string first_name_ = "No Name", last_name_ = "No Name";
	//Money stored in the funds
	array<int, 8> funds_;
	//Transaction history
	vector<Transaction> transactions_;
	//Fund names
	array<string, 8> names_ = { "Money Market", "Prime Money Market",
		"Long-Term Bond", "Short-Term Bond", "500 Index Fund", "Capital Value Fund",
		"Growth Equity Fund", "Growth Index Fund"};
	//Helper function for Transfer and Withdraw
	bool IsCorrect(const int kFType1, const int kMoney);
};
#endif