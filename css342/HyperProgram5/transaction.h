#ifndef TRANSACTION_H_
#define TRANSACTION_H_

#include <string>
#include <fstream>
using namespace std;
//This class is a transaction data storage
//It doesn't check whether the transaction
//is good or not.
class Transaction
{
public:
	//Constructors for every
	//transaction type
	Transaction() {};
	Transaction(const char kTransaction, const int kID, const int kFType, const int kMoney);
	Transaction(const char kTransaction, int kID, int kFType, int kID2, int kFType2, int kMoney);
	Transaction(const char kTransaction, int kID);
	Transaction(const char kTransaction, const int kID, const int kFType);
	Transaction(const char kTransaction, const int kID, const string kLastName, string kFirstName);
	//Getters
	int getID() const;
	int getID2() const;
	int getFundType() const;
	int getFundType2() const;
	char getTransactionType() const;
	string getLastName() const;
	string getFirstName() const;
	int getMoney() const;
	//Changes the fail state if needed
	void Fail();
	//Prints the information 
	friend ostream& operator<<(ostream& os, const Transaction& trans);
private:
	//Transaction information
	int id_ = -1, id_2_ = -1, f_type_ = -1, money_ = -1, f_type_2_ = -1;
	string last_name_ = "No Name", first_name_ = "No Name";
	char transaction_type_ = 'L';
	string fail_ = "";
};
#endif
