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
    enum currency
    {
        dollar_bill = 1,
        two_dollar_bill = 2,
        five_dollar_bill = 3,
        ten_dollar_bill = 4,
        twenty_dollar_bill = 5,
        penny = 6,
        nickle = 7,
        dime = 8,
        quarter = 9,
        half_dollar = 10,
        dollar_coin = 11
    };

    friend ostream &operator<<(ostream &os, const VendingBank &obj);

    bool IsValid(currencyScan scan); //currencyScan represents the data given by whatever scans/verifies the inputed bill/coin

    currency getCurrencyType(currencyScan scan);

    void add_to_current_amount(currency currency_to_add);
    void add_to_currency_reservoir(currency currency_to_add);

    void add_to_current_amount(currency currency_to_add[]);
    void add_to_currency_reservoir(currency currency_to_add[]);

    void remove_from_current_amount(currency currency_to_add);
    void remove_from_currency_reservoir(currency currency_to_add);

    void remove_from_current_amount(currency currency_to_add[]);
    void remove_from_currency_reservoir(currency currency_to_add[]);

    void processCurrency(currencyScan scan);
    void processCurrency(currencyScan scans[]);

    


    // FILL IN FURTHER PUBLIC FUNCTIONS HERE private :
private:
    //  id_ is a unique identifier for the VendingBank
    //  much like a serial number

    int id_;


    int current_dollars_;
    int current_cents_;


    //internal currency reservoir
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