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
        cerr << "ERROR: Account With ID: " << to_string(transaction.uid()) << " Already Exists" << endl;
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
    if (!DoesAccountExist(transaction.uid()))
    {
        cerr << "ERROR: Account With ID: " << to_string(transaction.uid()) << " Does Not Exist" << endl;
        transaction.MarkAsFailed();
        return false;
    }
    else if (!DoesFundExist(transaction.fund_id()))
    {
        cerr << "ERROR: Fund With ID: " << to_string(transaction.fund_id()) << " Does Not Exist" << endl;
        transaction.MarkAsFailed();
        return false;
    }
    else if (transaction.amount() < 0)
    {
        cerr << "ERROR: Cannot Be Negative Amount" << endl;
        transaction.MarkAsFailed();
        return false;
    }

    global_funds::funds_[transaction.fund_id()].Deposit(transaction.uid(), transaction.amount());
    return true;
}

bool Bank::WithdrawFunds(Transaction &transaction)
{
    if (!DoesAccountExist(transaction.uid()))
    {
        cerr << "ERROR: Account With ID: " << to_string(transaction.uid()) << " Does Not Exist" << endl;
        transaction.MarkAsFailed();
        return false;
    }
    else if (!DoesFundExist(transaction.fund_id()))
    {
        cerr << "ERROR: Fund With ID: " << to_string(transaction.fund_id()) << " Does Not Exist" << endl;
        transaction.MarkAsFailed();
        return false;
    }
    else if (transaction.amount() < 0)
    {
        cerr << "ERROR: Cannot Be Negative Amount" << endl;
        transaction.MarkAsFailed();
        return false;
    }

    if (global_funds::funds_[transaction.fund_id()].GetAccountFunds(transaction.uid()) < transaction.amount())
    {
        // insufficient funds
        if (!TransferFundsBetweenElligibleFundsToCover(transaction))
        {
            cerr << "ERROR: Account With ID: " << to_string(transaction.uid()) << " Has Insufficient Funds Within Fund With ID: " << to_string(transaction.fund_id()) << endl;
            transaction.MarkAsFailed();
            return false;
        }
    }
    global_funds::funds_[transaction.fund_id()].Withdraw(transaction.uid(), transaction.amount());
    return true;
}

bool Bank::TransferFunds(Transaction &transaction)
{
    if (!DoesAccountExist(transaction.uid()))
    {
        cerr << "ERROR: Account With ID: " << to_string(transaction.uid()) << " Does Not Exist" << endl;
        transaction.MarkAsFailed();
        return false;
    }
    else if (!DoesFundExist(transaction.fund_id()))
    {
        cerr << "ERROR: Fund With ID: " << to_string(transaction.fund_id()) << " Does Not Exist" << endl;
        transaction.MarkAsFailed();
        return false;
    }
    else if (!DoesAccountExist(transaction.uid_to()))
    {
        cerr << "ERROR: Account With ID: " << to_string(transaction.uid_to()) << " Does Not Exist" << endl;
        transaction.MarkAsFailed();
        return false;
    }
    else if (!DoesFundExist(transaction.fund_id_to()))
    {
        cerr << "ERROR: Fund With ID: " << to_string(transaction.fund_id_to()) << " Does Not Exist" << endl;
        transaction.MarkAsFailed();
        return false;
    }
    /* else if ((transaction.uid() == transaction.uid_to()) &&
             ((IsBondFund(transaction.fund_id()) && IsBondFund(transaction.fund_id_to())) ||
              (IsMoneyMarketFund(transaction.fund_id()) && IsMoneyMarketFund(transaction.fund_id_to()))) &&
             global_funds::funds_[transaction.fund_id()].GetAccountFunds(transaction.uid()) < transaction.amount())
    {
        cerr << "ERROR: Account With ID: " << to_string(transaction.uid()) << " Has Insufficient Funds Within Fund With ID: " << to_string(transaction.fund_id()) << endl;
        transaction.MarkAsFailed();
        return false;
    } */
    else if (transaction.amount() < 0)
    {
        cerr << "ERROR: Cannot Be Negative Amount" << endl;
        transaction.MarkAsFailed();
        return false;
    }

    if (!WithdrawFunds(transaction))
    {
        cerr << "ERROR: Account With ID: " << to_string(transaction.uid()) << " Has Insufficient Funds Within Fund With ID: " << to_string(transaction.fund_id()) << endl;
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
    int overdraw_amount = transaction.amount() - global_funds::funds_[transaction.fund_id()].GetAccountFunds(transaction.uid());
    vector<int> fundIds = GetLinkedFundIDs(transaction.fund_id()); //(IsBondFund(transaction.fund_id())) ? GetBondFundIDs() : GetMoneyMarketFundIDs();

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
        Transaction tmp = Transaction(W, transaction.uid(), fundIds[i], amount);
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
    if (!DoesAccountExist(transaction.uid()))
    {
        cerr << "ERROR: Account With ID: " << to_string(transaction.uid()) << " Does Not Exist" << endl;
        transaction.MarkAsFailed();
        return;
    }
    Account *account = &GetAccount(transaction.uid());
    cout << "Transaction History For " << account->last_name() << " " << account->first_name() << " By Fund." << endl;
    for (int fund_id : GetAllFundIDs())
    {
        string tmp = GetFundName(fund_id) + ": $" + to_string(global_funds::funds_[fund_id].GetAccountFunds(account->uid())) + "\n";
        int transactions = 0;
        for (Transaction t : fund_transaction_history_[fund_id])
        {
            if (t.uid() == account->uid() || (t.transaction_type() == T && t.fund_id_to() == account->uid()))
            {
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
    cout << endl;
}

void Bank::PrintFundTransactionHistoryForAccount(Transaction &transaction)
{
    if (!DoesAccountExist(transaction.uid()))
    {
        cerr << "ERROR: Account With ID: " << to_string(transaction.uid()) << " Does Not Exist" << endl;
        transaction.MarkAsFailed();
        return;
    }
    else if (!DoesFundExist(transaction.fund_id()))
    {
        cerr << "ERROR: Fund With ID: " << to_string(transaction.fund_id()) << " Does Not Exist" << endl;
        transaction.MarkAsFailed();
        return;
    }

    Account *account = &GetAccount(transaction.uid());

    cout << "Transaction History For " << account->last_name() << " " << account->first_name() << " " << GetFundName(transaction.fund_id()) << ": $" << global_funds::funds_[transaction.fund_id()].GetAccountFunds(account->uid()) << endl;
    for (Transaction t : fund_transaction_history_[transaction.fund_id()])
    {
        if (t.uid() == account->uid() || (t.transaction_type() == T && t.fund_id_to() == account->uid()))
        {
            cout << "   " << t << endl;
        }
    }
    cout << endl;
}

void Bank::AddToTransactionHistory(Transaction &transaction)
{
    switch (transaction.transaction_type())
    {
    case D:
        account_transaction_history_[transaction.uid()].push_back(transaction);
        fund_transaction_history_[transaction.fund_id()].push_back(transaction);
        break;
    case W:
        account_transaction_history_[transaction.uid()].push_back(transaction);
        fund_transaction_history_[transaction.fund_id()].push_back(transaction);
        break;
    case T:
        account_transaction_history_[transaction.uid()].push_back(transaction);
        account_transaction_history_[transaction.uid_to()].push_back(transaction);
        fund_transaction_history_[transaction.fund_id()].push_back(transaction);
        fund_transaction_history_[transaction.fund_id_to()].push_back(transaction);
        break;
    }
}
