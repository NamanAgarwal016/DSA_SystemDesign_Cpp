#ifndef UPI_PAYMENT_STRATEGY_H
#define UPI_PAYMENT_STRATEGY_H

#include "PaymentStrategy.h"
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

class UpiPaymentStrategy : public PaymentStrategy {
private:
    string mobile;
public:
    UpiPaymentStrategy(const string& mob) {
        mobile = mob;
    }

    void pay(double amount) override {
        cout << "Paid ₹" << amount << " using UPI (" << mobile << ")" << endl;
    }
};

#endif // UPI_PAYMENT_STRATEGY_H

// #ifndef NET_BANKING_H
// #define NET_BANKING_H

// #include <iostream>

// using namespace std;

// class NetBanking : public PaymentStrategy {
// private:
//     string bankid;
// public:
//     NetBanking(string bankid) : bankid(bankid) {}

//     void pay(int amount) {
//         cout << "Paying Rs." << amount << " through NetBanking ID: " << bankid << endl;
//     }

//     void getPaymentType() {
//         cout << "Payment Mode selected is NetBanking..." << endl;
//     }
// };

// #endif // NET_BANKING_H