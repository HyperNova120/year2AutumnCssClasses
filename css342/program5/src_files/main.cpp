#include "Bank.h"

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        cout << "This Program Requires A File To Run" << endl;
        return 0;
    }
    Bank bank = Bank();
    bank.ReadTransactions(string(argv[1]));
    bank.ExecuteTranactions();
}