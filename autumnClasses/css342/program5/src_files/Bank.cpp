#include "Bank.h"
#include "FundsAPI.h"
#include <iostream>
#include <sstream>
#include <fstream>

Bank::Bank()
{
    for (int fund_id : GetAllFundIDs())
    {
        global_funds::funds_[fund_id] = (Fund(fund_id, GetFundName(fund_id)));
    }
}

void Bank::ReadTransactions(string file_name)
{
    ifstream ifs(file_name);
    if (!ifs.is_open())
    {
        cout << "File Does Not Exist" << endl;
        return;
    }
    string line;
    while (getline(ifs, line))
    {
        if (line.at(line.length() - 1) == '\r')
        {
            line.pop_back();
        }
        vector<string> tmp = split(line, ' ');
        transactions_.push(Transaction(tmp));
    }
    ifs.close();
}

void Bank::ExecuteTranactions()
{
    while (!transactions_.empty())
    {
        Transaction current_transaction = transactions_.front();
        transactions_.pop();
        switch (current_transaction.transaction_type())
        {
        case O:
            CreateAccount(current_transaction);
            break;
        case D:
            DepositFunds(current_transaction);
            AddToTransactionHistory(current_transaction);
            break;
        case W:
            WithdrawFunds(current_transaction);
            AddToTransactionHistory(current_transaction);
            break;
        case T:
            TransferFunds(current_transaction);
            AddToTransactionHistory(current_transaction);
            break;
        case A:
            PrintAccountTransactionHistory(current_transaction);
            break;
        case F:
            PrintFundTransactionHistoryForAccount(current_transaction);
            break;
        }
    }
    cout << "FINAL BALANCES:" << endl;
    cout << accounts_ << endl;
    /* Transaction tmp = Transaction(A, 1001);
    PrintAccountTransactionHistory(tmp); */
}

vector<string> Bank::split(string s, char delim)
{
    vector<string> tmp = vector<string>();
    stringstream ss = stringstream(s);
    string token;
    while (getline(ss, token, delim))
    {
        if (token.length() != 0)
        {
            tmp.push_back(token);
        }
    }
    return tmp;
}

bool Bank::CreateAccount(Transaction &transaction)
{
    if (DoesAccountExist(transaction.uid()))
    {
        cerr << "ERROR: Account With ID: " << to_string(transaction.uid()) << " Already Exists" << ". Transaction Refused" << endl;
        transaction.MarkAsFailed();
        return false;
    }
    else if (transaction.uid() < 0)
    {
        cerr << "ERROR: Account ID Cannot Be Negative" << ". Transaction Refused" << endl;
        transaction.MarkAsFailed();
        return false;
    }

    Account account_to_add = Account(transaction.first_name(), transaction.last_name(), transaction.uid());
    for (int fund_id : GetAllFundIDs())
    {
        global_funds::funds_[fund_id].RegisterAccount(account_to_add.uid());
    }
    accounts_.Insert(account_to_add);
    return true;
}

bool Bank::DepositFunds(Transaction &transaction)
{
    if (!isValidTransaction(transaction))
    {
        return false;
    }

    global_funds::funds_[transaction.fund_id()].Deposit(transaction.uid(), transaction.amount());
    return true;
}

bool Bank::WithdrawFunds(Transaction &transaction)
{
    if (!isValidTransaction(transaction))
    {
        return false;
    }

    //attempts to withdraw from fund, if not enough funds tries to cover from linked funds
    if (global_funds::funds_[transaction.fund_id()].GetAccountFunds(transaction.uid()) < transaction.amount())
    {
        // insufficient funds
        if (!TransferFundsBetweenElligibleFundsToCover(transaction))
        {
            Account *P_tmp = &accounts_.Get(transaction.uid());
            string account_name = P_tmp->first_name() + " " + P_tmp->last_name();
            cerr << "ERROR: " << account_name << " Has Insufficient Funds Within " << GetFundName(transaction.fund_id()) << endl;
            transaction.MarkAsFailed();
            return false;
        }
    }
    global_funds::funds_[transaction.fund_id()].Withdraw(transaction.uid(), transaction.amount());
    return true;
}

bool Bank::TransferFunds(Transaction &transaction)
{
    if (!isValidTransaction(transaction))
    {
        return false;
    }

    //attemps to withdraw amount from fund, if successful, depost into new fund
    if (!WithdrawFunds(transaction))
    {
        Account *P_tmp = &accounts_.Get(transaction.uid());
        string account_name = P_tmp->first_name() + " " + P_tmp->last_name();
        // cerr << "ERROR: " << account_name << " Has Insufficient Funds Within " << GetFundName(transaction.fund_id()) << endl;
        transaction.MarkAsFailed();
        return false;
    }
    Transaction tmp = Transaction(D, transaction.uid_to(), transaction.fund_id_to(), transaction.amount());
    DepositFunds(tmp);
    return true;
}

bool Bank::DoesAccountExist(int uid) const
{
    return accounts_.Contains(Account(uid));
}

Account &Bank::GetAccount(int uid) const
{
    return accounts_.Get(Account(uid));
}


bool Bank::TransferFundsBetweenElligibleFundsToCover(Transaction &transaction)
{
    if (!IsLinkedFund(transaction.fund_id()))
    {
        return false;
    }
    //gets overdraw amount
    int overdraw_amount = transaction.amount() - global_funds::funds_[transaction.fund_id()].GetAccountFunds(transaction.uid());
    vector<int> fundIds = GetLinkedFundIDs(transaction.fund_id()); //(IsBondFund(transaction.fund_id())) ? GetBondFundIDs() : GetMoneyMarketFundIDs();

    //calculates available amount to cover
    int total_amount = 0;
    for (int i = 0; i < fundIds.size(); i++)
    {
        if (fundIds[i] == transaction.fund_id() || fundIds[i] == transaction.fund_id_to())
        {
            continue;
        }
        total_amount += global_funds::funds_[fundIds[i]].GetAccountFunds(transaction.uid());
    }

    if (total_amount < overdraw_amount)
    {
        transaction.MarkAsFailed();
        return false;
    }

    //pulls from funds not being transfered from or too to cover
    int old_amount = global_funds::funds_[transaction.fund_id()].GetAccountFunds(transaction.uid());
    transaction.SetAmount(old_amount);

    for (int i = 0; i < fundIds.size() && overdraw_amount > 0; i++)
    {
        if (fundIds[i] == transaction.fund_id() || fundIds[i] == transaction.fund_id_to())
        {
            continue;
        }
        int amount = (global_funds::funds_[fundIds[i]].GetAccountFunds(transaction.uid()) < overdraw_amount) ? global_funds::funds_[fundIds[i]].GetAccountFunds(transaction.uid()) : overdraw_amount;
        global_funds::funds_[fundIds[i]].Withdraw(transaction.uid(), amount);
        Transaction tmp = Transaction(T, transaction.uid(), fundIds[i], transaction.uid_to(), transaction.fund_id_to(), amount);
        AddToTransactionHistory(tmp);
        if (transaction.transaction_type() == T)
        {
            global_funds::funds_[transaction.fund_id_to()].Deposit(transaction.uid_to(), amount);
        }
    }
    return true;
}

void Bank::PrintAccountTransactionHistory(Transaction &transaction)
{
    if (!isValidTransaction(transaction))
    {
        transaction.MarkAsFailed();
        return;
    }
    Account *account = &GetAccount(transaction.uid());
    cout << "Transaction History For " << account->last_name() << " " << account->first_name() << " By Fund." << endl;
    int total_transactions = 0;
    for (int fund_id : GetAllFundIDs())
    {
        string tmp = GetFundName(fund_id) + ": $" + to_string(global_funds::funds_[fund_id].GetAccountFunds(account->uid())) + "\n";
        int transactions = 0;
        for (Transaction t : fund_transaction_history_[fund_id])
        {
            if (t.uid() == account->uid() && t.fund_id() == fund_id || (t.transaction_type() == T && t.uid_to() == account->uid() && t.fund_id_to() == fund_id))
            {
                total_transactions++;
                transactions++;
                stringstream ss;
                ss << t;
                tmp += "   " + ss.str() + "\n";
            }
        }
        if (transactions > 0)
        {
            cout << tmp;
        }
    }
    if (total_transactions == 0)
    {
        cout << "   No Transaction History";
    }
    cout << endl;
}

void Bank::PrintFundTransactionHistoryForAccount(Transaction &transaction)
{
    if (!isValidTransaction(transaction))
    {
        transaction.MarkAsFailed();
        return;
    }

    Account *account = &GetAccount(transaction.uid());

    cout << "Transaction History For " << account->last_name() << " " << account->first_name() << " " << GetFundName(transaction.fund_id()) << ": $" << global_funds::funds_[transaction.fund_id()].GetAccountFunds(account->uid()) << endl;
    int total_transactions = 0;
    for (Transaction t : fund_transaction_history_[transaction.fund_id()])
    {
        if (t.uid() == account->uid() && t.fund_id() == transaction.fund_id() || (t.transaction_type() == T && t.uid_to() == account->uid() && t.fund_id_to() == transaction.fund_id()))
        {
            total_transactions++;
            cout << "   " << t << endl;
        }
    }
    if (total_transactions == 0)
    {
        cout << "   No Transaction History";
    }
    cout << endl;
}

//adds transaction to history if account/fund exists
void Bank::AddToTransactionHistory(Transaction &transaction)
{
    switch (transaction.transaction_type())
    {
    case D:
        if (DoesAccountExist(transaction.uid()))
        {
            account_transaction_history_[transaction.uid()].push_back(transaction);
        }
        if (DoesFundExist(transaction.fund_id()))
        {
            fund_transaction_history_[transaction.fund_id()].push_back(transaction);
        }
        break;
    case W:
        if (DoesAccountExist(transaction.uid()))
        {
            account_transaction_history_[transaction.uid()].push_back(transaction);
        }
        if (DoesFundExist(transaction.fund_id()))
        {
            fund_transaction_history_[transaction.fund_id()].push_back(transaction);
        }
        break;
    case T:
        if (DoesAccountExist(transaction.uid()))
        {
            account_transaction_history_[transaction.uid()].push_back(transaction);
        }
        if (DoesFundExist(transaction.fund_id()))
        {
            fund_transaction_history_[transaction.fund_id()].push_back(transaction);
        }

        if (DoesAccountExist(transaction.uid_to()) && transaction.uid_to() != transaction.uid())
        {
            account_transaction_history_[transaction.uid_to()].push_back(transaction);
        }
        if (DoesFundExist(transaction.fund_id_to()) && transaction.fund_id_to() != transaction.fund_id())
        {
            fund_transaction_history_[transaction.fund_id_to()].push_back(transaction);
        }
        break;
    }
}

//checks needed vars to ensure transaction is valid
bool Bank::isValidTransaction(Transaction &transaction)
{
    if (transaction.uid() < 0)
    {
        cerr << "ERROR: Account ID Cannot Be Negative" << ". Transaction Refused" << endl;
        transaction.MarkAsFailed();
        return false;
    }
    else if (!DoesAccountExist(transaction.uid()))
    {
        cerr << "ERROR: Account With ID: " << to_string(transaction.uid()) << " Does Not Exist" << ". Transaction Refused" << endl;
        transaction.MarkAsFailed();
        return false;
    }
    else if (transaction.transaction_type() == A)
    {
        return true;
    }
    else if (transaction.fund_id() < 0)
    {
        cerr << "ERROR: Fund ID Cannot Be Negative" << ". Transaction Refused" << endl;
        transaction.MarkAsFailed();
        return false;
    }
    else if (!DoesFundExist(transaction.fund_id()))
    {
        cerr << "ERROR: Fund With ID: " << to_string(transaction.fund_id()) << " Does Not Exist" << ". Transaction Refused" << endl;
        transaction.MarkAsFailed();
        return false;
    }
    else if (transaction.transaction_type() == F)
    {
        return true;
    }
    else if (transaction.amount() < 0)
    {
        cerr << "ERROR: Cannot Be Negative Amount" << ". Transaction Refused" << endl;
        transaction.MarkAsFailed();
        return false;
    }
    if (transaction.transaction_type() == T)
    {
        if (transaction.uid_to() < 0)
        {
            cerr << "ERROR: Account ID Cannot Be Negative" << ". Transaction Refused" << endl;
            transaction.MarkAsFailed();
            return false;
        }
        else if (!DoesAccountExist(transaction.uid_to()))
        {
            cerr << "ERROR: Account With ID: " << to_string(transaction.uid_to()) << " Does Not Exist" << ". Transaction Refused" << endl;
            transaction.MarkAsFailed();
            return false;
        }
        else if (transaction.fund_id_to() < 0)
        {
            cerr << "ERROR: Fund ID Cannot Be Negative" << ". Transaction Refused" << endl;
            transaction.MarkAsFailed();
            return false;
        }
        else if (!DoesFundExist(transaction.fund_id_to()))
        {
            cerr << "ERROR: Fund With ID: " << to_string(transaction.fund_id_to()) << " Does Not Exist" << ". Transaction Refused" << endl;
            transaction.MarkAsFailed();
            return false;
        }
    }
    return true;
}