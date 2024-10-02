#ifndef VENDING_BANK_H_
#define VENDING_BANK_H_
#include <string>
#include <iostream>
#include <ostream>
using namespace std;
class VendingBank
{
public:
    VendingBank();
    VendingBank(int id);
    // getters-setters
    int id() const;

    friend ostream &operator<<(ostream &os, const VendingBank &obj);

    //returns if the current transaction can cover a given cost
    bool does_current_transaction_cover(int cost_bills, int cost_cents);

    //adds given cost to currency revevoir and returns any extra
    void complete_transaction(int cost_bills, int cost_cents);

    

    //handles current transaction amounts
    void AddToTransactionAmount(int bills_to_add, int cents_to_add);
    void AddToTransactionAmount(int bills_to_add[], int cents_to_add[]);
    void RemoveFromTransactionAmount(int bills_to_add[], int cents_to_add[]);
    void RemoveFromTransactionAmount(int bills_to_add[], int cents_to_add[]);

    // FILL IN FURTHER PUBLIC FUNCTIONS HERE private :
private:
    //  id_ is a unique identifier for the VendingBank
    //  much like a serial number

    int id_;

    void AddToCurrencyReservoir(int bills_to_add, int cents_to_add);

    void AddToCurrencyReservoir(int bills_to_add[], int cents_to_add[]);

    void RemoveFromCurrencyReservoir(int bills_to_add[], int cents_to_add[]);

    void RemoveFromCurrencyReservoir(int bills_to_add[], int cents_to_add[]);


    //amount of money in the current transaction
    int current_dollars_;
    int current_cents_;


    //internal total currency reservoir
    long dollar_bills_;
    long two_dollar_bills_;
    long five_dollar_bills_;
    long ten_dollar_bills_;
    long twenty_dollar_bills_;
    long penny_;
    long nickle_;
    long dime_;
    long quarter_;
    long half_dollar_;
    long dollar_coin_;
};
#endif