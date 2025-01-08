#ifndef VENDING_BANK_H_
#define VENDING_BANK_H_
#include <string>
#include <iostream>
#include <ostream>
using namespace std;
class VendingBank
{
public:
    ~VendingBank();
    VendingBank();
    VendingBank(int id);
    VendingBank(int id, int pennys, int nickels, int dimes, int quarters, int half_dollars, int dollar_coins);
    VendingBank(int id, int pennys[], int nickels[], int dimes[], int quarters[], int half_dollars[], int dollar_coins[]);
    // getters-setters
    int id() const;

    void reset();

    // returns if the current transaction can cover a given cost
    bool does_current_transaction_cover(const int cost_pennys, const int cost_nickels, const int cost_dimes, const int cost_quarters,
                                        const int cost_half_dollars, const int cost_dollar_coins) const;

    // adds given cost to currency revevoir and returns any extra
    void complete_transaction(const int pennys, const int nickels, const int dimes, const int quarters, const int half_dollars,
                              const int dollar_coins);

    // returns current transaction amounts
    friend ostream &operator<<(ostream &os, VendingBank &obj);

    friend istream &operator>>(istream &is, VendingBank &obj);

    // handles current transaction amounts
    void AddToTransactionAmount(int pennys, int nickels, int dimes, int quarters, int half_dollars, int dollar_coins);
    void AddToTransactionAmount(int pennys[], int nickels[], int dimes[], int quarters[], int half_dollars[], int dollar_coins[]);
    void RemoveFromTransactionAmount(int pennys, int nickels, int dimes, int quarters, int half_dollars, int dollar_coins);
    void RemoveFromTransactionAmount(int pennys[], int nickels[], int dimes[], int quarters[], int half_dollars[], int dollar_coins[]);
    void SetTransactionAmount(int pennys, int nickels, int dimes, int quarters, int half_dollars, int dollar_coins);

    //current transaction getters
    long transaction_penny() const;
    long transaction_nickle() const;
    long transaction_dime() const;
    long transaction_quarter() const;
    long transaction_half_dollar() const;
    long transaction_dollar_coin() const;



    //currency reservoir getters
    long penny() const;
    long nickle() const;
    long dime() const;
    long quarter() const;
    long half_dollar() const;
    long dollar_coin() const;

    void SetCurrencyReservoirAmount(int pennys, int nickels, int dimes, int quarters, int half_dollars, int dollar_coins);

    // FILL IN FURTHER PUBLIC FUNCTIONS HERE private :
private:
    //  id_ is a unique identifier for the VendingBank
    //  much like a serial number

    int id_;

    void AddToCurrencyReservoir(int pennys, int nickels, int dimes, int quarters, int half_dollars, int dollar_coins);

    void AddToCurrencyReservoir(int pennys[], int nickels[], int dimes[], int quarters[], int half_dollars[], int dollar_coins[]);

    void RemoveFromCurrencyReservoir(int pennys, int nickels, int dimes, int quarters, int half_dollars, int dollar_coins);

    void RemoveFromCurrencyReservoir(int penny[], int nickels[], int dimes[], int quarters[], int half_dollars[], int dollar_coins[]);

    // amount of money in the current transaction
    long transaction_penny_;
    long transaction_nickle_;
    long transaction_dime_;
    long transaction_quarter_;
    long transaction_half_dollar_;
    long transaction_dollar_coin_;

    // internal total currency reservoir
    long penny_;
    long nickle_;
    long dime_;
    long quarter_;
    long half_dollar_;
    long dollar_coin_;
    /**/
};
#endif