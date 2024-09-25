#ifndef VENDING_BANK_H_
#define VENDING_BANK_H_
#include <string>
class VendingBank
{
public:
    VendingBank();
    VendingBank(int id);
    // getters-setters
    int id() const;
    // FILL IN FURTHER PUBLIC FUNCTIONS HERE private :
    //  id_ is a unique identifier for the VendingBank
    //  much like a serial number
    int id_;
    // FILL IN FURTHER DATA MEMBERS HERE
};
#endif