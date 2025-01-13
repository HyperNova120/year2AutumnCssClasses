#include "account.h"

Account::Account(const int kID, const string kLastName, const string kFirstName)
{
	id_ = kID;
	last_name_ = kLastName;
	first_name_ = kFirstName;
	funds_ = {};
}
bool Account::IsCorrect(const int kFType1, const int kMoney) {
	if ((funds_[kFType1] < kMoney && kFType1 > 3)
		|| (kFType1 < 2 && funds_[0] + funds_[1] < kMoney)
		|| (funds_[2] + funds_[3] < kMoney && kFType1 > 1 && kFType1 < 4)) {
		return false;
	}
	return true;
}
bool Account::Transfer(const int kFType1, const int kFType2,
	const int kMoney, Account& other_account)
{
	if (kFType1 ==2 && kFType2 == 3 && kMoney == 500)
	{
		bool breakHere = true;
	}


	if (!IsCorrect(kFType1, kMoney) ||
		(funds_[kFType1] < kMoney && (kFType1 == 0 && kFType2 == 1)
			|| (kFType1 == 2 && kFType2 == 3))) {
		cerr << "ERROR: Not enough money to transfer in "
			<< last_name_ << " " << first_name_
			<< "'s fund " << names_[kFType1] << endl;
		return false;
	}

	if (funds_[kFType1] >= kMoney) {
		Withdraw(kFType1, kMoney);
		other_account.Deposit(kFType2, kMoney);
		return true;
	}
	int f2;
	if (kFType1 == 0 || kFType1 == 2) {
		f2 = kFType1 + 1;
	}
	else {
		f2 = kFType1 - 1;
	}
	Withdraw(f2, kMoney - funds_[kFType1]);
	Transaction trans('T', getID(), f2, getID(), kFType1, kMoney - funds_[kFType1]);
	AddToHistory(trans);
	funds_[kFType1] = 0;
	other_account.Deposit(kFType2, kMoney);
	return true;	
}

bool Account::Withdraw(const int kFType1, const int kMoney)
{
	if (!IsCorrect(kFType1, kMoney)) {
		cerr << "ERROR: Not enough funds to withdraw "
			<< kMoney << " from " << first_name_ << " " << last_name_
			<< "'s " << names_[kFType1] << endl;
		return false;
	}

	if (funds_[kFType1] >= kMoney) {
		funds_[kFType1] -= kMoney;
		return true;
	}
	int f2;
	if (kFType1 == 0 || kFType1 == 2) {
		f2 = kFType1 + 1;
	}
	else {
		f2 = kFType1 - 1;
	}
	int transfer = kMoney - funds_[kFType1];
	funds_[f2] -= transfer; 
	funds_[kFType1] = 0; 
	return true;
}
bool Account::Deposit(const int kFType, const int kMoney)
{
	if (kMoney >= 0) {
		funds_[kFType] += kMoney;
		return true;
	}
	return false;
}

void Account::DisplayAccount() const
{
	cout << "Transaction History for "
		<< first_name_ << " " << last_name_ 
		<< " by fund." << endl;
	for (int i = 0; i < 8; i++) {
		DisplayFund(i);
	}
	cout << endl;

}

void Account::DisplayFund(const int kFType) const
{
	cout << names_[kFType] << ": $" << funds_[kFType] << endl;
	for (const auto& trans : transactions_) {
		if (trans.getFundType() == kFType || trans.getFundType2() == kFType) {
			cout << "  " << trans;
			cout << endl;
		}
	}
}

void Account::DisplayFinalBalance() const
{
	cout << first_name_ << " " << last_name_
		<< " Account ID: " << id_ << endl;
	for (int i = 0; i < 8; ++i) {
		cout << "    " << names_[i] << ": $" << funds_[i] << endl;
	}
	cout << endl;
}

void Account::AddToHistory(Transaction transaction)
{
	transactions_.push_back(transaction);
}

int Account::getID() {
	return id_;
}

string Account::getName() {
	string name = first_name_ + " " + last_name_;
	return name;
}