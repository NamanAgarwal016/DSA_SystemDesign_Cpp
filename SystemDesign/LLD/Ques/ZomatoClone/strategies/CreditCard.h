#ifndef CREDIT_CARD_PAYMENT_STRATEGY_H
#define CREDIT_CARD_PAYMENT_STRATEGY_H

#include "PaymentStrategy.h"
#include <iostream>
#include <string>
#include <iomanip>
using namespace std;

class CreditCardPaymentStrategy : public PaymentStrategy {
private:
    string cardNumber;
public:
    CreditCardPaymentStrategy(const string& card) {
        cardNumber = card;
    }

    void pay(double amount) override {
        cout << "Paid ₹" << amount << " using Credit Card (" << cardNumber << ")" << endl;
    }
};

#endif // CREDIT_CARD_PAYMENT_STRATEGY_H

// #ifndef CREDIT_CARD_H
// #define CREDIT_CARD_H

// #include <iostream>

// using namespace std;

// class CreditCard : public PaymentStrategy {
// private:
//     string cardNumber;
// public:
//     CreditCard(string cardNumber) : cardNumber(cardNumber) {}

//     void pay(int amount) override {
//         cout << "Paying Rs." << amount << " through Credit Card: " << cardNumber << endl;
//     }

//     void getPaymentType() {
//         cout << "Payment Mode selected is Credit Card..." << endl;
//     }
// };

// #endif // CREDIT_CARD_H