#include "jolly_banker.h"

bool JollyBanker::ValidParameters(Transaction& trans) const {
    if (trans.getID() < 0) {
            cerr << "ERROR: Account ID " << trans.getID()
                << " not found. Transferal refused.\n";
            trans.Fail();
            return false;
    }
    Account* acc;
    bool check = true;
    int type = trans.getTransactionType();
    if (type == 'O') {
        if (accounts_.Retrieve(trans.getID(), acc)) {
            cerr << "ERROR: Account " << trans.getID()
                << " is already open. Transaction refused.\n";
            trans.Fail();
            return false;
        }
        return true;
    }
    if (!accounts_.Retrieve(trans.getID(), acc)) {
        cerr << "ERROR: Account ID " << trans.getID()
            << " not found. Transaction refused.\n";
        check = false;
    }
    if (type == 'T') {
        if (trans.getID2() < 0) {
            trans.Fail();
            return false;
        }
        Account* acc2;
        if (!accounts_.Retrieve(trans.getID2(), acc2)) {
            cerr << "ERROR: Account ID " << trans.getID2()
                << " not found. Transferal refused.\n";
            check = false;
        }
        if (trans.getFundType2() < 0 || trans.getFundType2() > 7) {
            cerr << "ERROR: Invalid fund. Fund must be between 0 and 7.\n";
            check = false;
        }
    }
    if ((trans.getFundType() < 0 || trans.getFundType() > 7) && type != 'A') {
        cerr << "ERROR: Invalid fund. Fund must be between 0 and 7.\n";
        check = false;
    } 
    if (trans.getMoney() < 0 && type != 'F' && type != 'A') {
        cerr << "ERROR: Invalid money amount. Must be 0 or more\n";
        check = false;
    }
    if (!check) {
        trans.Fail();
    }
    return check;
}

bool JollyBanker::DoAction(Transaction& type)
{
    char transaction = type.getTransactionType();
    bool check = false;
    if (transaction == 'O') {
        Account* acc = new Account(type.getID(), type.getLastName(), type.getFirstName());
        check = accounts_.Insert(acc);
        if (!check) {
            delete acc;
        }
        return check;
    }
    Account* acc;
    accounts_.Retrieve(type.getID(), acc);
    if (transaction == 'D') {
        check = (*acc).Deposit(type.getFundType(), type.getMoney());
    }
    else if (transaction == 'W') {
        check = (*acc).Withdraw(type.getFundType(), type.getMoney());
    }
    else if (transaction == 'F') {
        cout << "Transaction History for " << acc->getName() << " ";
        (*acc).DisplayFund(type.getFundType());
        cout << endl;
        return true;
    }
    else if (transaction == 'A') {
        (*acc).DisplayAccount();
        return true;
    }
    else if (transaction == 'T') {
        Account* acc2;
        accounts_.Retrieve(type.getID2(), acc2);
        check = (*acc).Transfer(type.getFundType(), 
            type.getFundType2(), type.getMoney(), *acc2);
    }
    else {
        cerr << "ERROR: Unrecognized transaction type "
            << transaction << " , allowed transactions: A, F, O, W, D, T";
    }
    return check;
}

void JollyBanker::ProcessInput(string line)
{
    stringstream ss(line);
    int id;
    char check;
    ss >> check >> id;
    if (check == 'O') {
        string l_n, f_n;
        ss >> l_n >> f_n;
        Transaction open(check, id, l_n, f_n);
        input_.push(open);
    }
    else if (check == 'D' || check == 'W') {
        int f_type, money;
        ss >> f_type >> money;
        Transaction dep_or_with(check, id, f_type, money);
        input_.push(dep_or_with);
    }
    else if (check == 'F') {
        int f_type;
        ss >> f_type;
        Transaction display_fund(check, id, f_type);
        input_.push(display_fund);
    }
    else if (check == 'T') {
        int f_type, f_type_2, id_2, money;
        ss >> f_type >> id_2 >> f_type_2 >> money;
        Transaction transfer(check, id, f_type, id_2, f_type_2, money);
        input_.push(transfer);
    }
    else {
        Transaction display(check, id);
        input_.push(display);
    }
}

void JollyBanker::ReadFile(ifstream& file)
{
    string line;
    while (getline(file, line)) {
        ProcessInput(line);
    }
}

void JollyBanker::QueueActions() {
    while (!input_.empty()) {
        Transaction& current = input_.front();
        bool didntFail = true;
        if (ValidParameters(current)) {
            didntFail = DoAction(current);
        }
        if (!didntFail) {
            current.Fail();
        }
        if (current.getTransactionType() != 'A' &&
            current.getTransactionType() != 'F') {
            Account* acc;
            if (accounts_.Retrieve(current.getID(), acc)) {
                (*acc).AddToHistory(current);
            }
            if (current.getTransactionType() == 'T') {
                Account* acc2;
                if (accounts_.Retrieve(current.getID2(), acc2) &&
                    acc2->getID() != current.getID()) {
                    (*acc2).AddToHistory(current);
                }
            }
        }
        input_.pop();
    }
}

void JollyBanker::DisplayFinalBalances() const {
    cout << "FINAL BALANCES:" << endl;
    accounts_.DisplayInOrder();
}

int main(int argc, char* argv[]) {
    if (argc < 2) {
        cerr << "ERROR: Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }

    ifstream inFile(argv[1]);
    if (!inFile) {
        cerr << "ERROR: Couldn't open file" << endl;
        return 1;
    }

    JollyBanker bank;
    bank.ReadFile(inFile);
    inFile.close();
    bank.QueueActions();
    bank.DisplayFinalBalances();
    return 0;
}