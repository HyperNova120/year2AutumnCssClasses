#include "transaction.h"

Transaction::Transaction(const char kTransaction, const int kID, const int kFType, const int kMoney)
{
	transaction_type_ = kTransaction;
	id_ = kID;
	f_type_ = kFType;
	money_ = kMoney;
}

Transaction::Transaction(const char kTransaction, int kID, int kFType, int kID2, int kFType2, int kMoney)
{
	transaction_type_ = kTransaction;
	id_ = kID;
	id_2_ = kID2;
	f_type_ = kFType;
	f_type_2_ = kFType2;
	money_ = kMoney;
}
Transaction::Transaction(const char kTransaction, int kID)
{
	transaction_type_ = kTransaction;
	id_ = kID;
}
Transaction::Transaction(const char kTransaction, const int kID, const int kFType)
{
	transaction_type_ = kTransaction;
	id_ = kID;
	f_type_ = kFType;
}
Transaction::Transaction(const char kTransaction, const int kID, const string kLastName, string kFirstName)
{
	transaction_type_ = kTransaction;
	id_ = kID;
	last_name_ = kLastName;
	first_name_ = kFirstName;
}

int Transaction::getID() const
{
	return id_;
}

int Transaction::getID2() const
{
	return id_2_;
}

int Transaction::getFundType() const
{
	return f_type_;
}

int Transaction::getFundType2() const
{
	return f_type_2_;
}

char Transaction::getTransactionType() const
{
	return transaction_type_;
}

string Transaction::getLastName() const
{
	return last_name_;
}

string Transaction::getFirstName() const
{
	return first_name_;
}

int Transaction::getMoney() const
{
	return money_;
}

void Transaction::Fail()
{
	fail_ = "(Failed)";
}

ostream& operator<<(ostream& os, const Transaction& transaction) {
	os << transaction.transaction_type_ << " "
		<< transaction.id_ << " ";
	if (transaction.last_name_ != "No Name") {
		os << transaction.last_name_ << " "
			<< transaction.first_name_ << " ";
	}
	else {
		if (transaction.f_type_ != -1) {
			os << transaction.f_type_ << " ";
		}
		if (transaction.id_2_ != -1) {
			os << transaction.id_2_ << " "
				<< transaction.f_type_2_ << " ";
		}
		if (transaction.f_type_ != -1) {
			os << transaction.money_ << " ";
		}
	}
	os << transaction.fail_;
	return os;
}
