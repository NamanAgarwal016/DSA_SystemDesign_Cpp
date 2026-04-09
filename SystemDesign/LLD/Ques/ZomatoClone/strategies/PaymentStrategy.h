#ifndef PAYMENT_STRATEGY_H
#define PAYMENT_STRATEGY_H

#include <iostream>
#include <string>
using namespace std;

class PaymentStrategy {
public:
    virtual void pay(double amount) = 0;
    virtual ~PaymentStrategy() {}
};

#endif // PAYMENT_STRATEGY_H

// #ifndef PAYMENT_STARTEGY_H
// #define PAYMENT_STARTEGY_H

// #include <iostream>

// using namespace std;

// class PaymentStrategy {
// public:
//     virtual void pay(int amount) = 0;
//     virtual void getPaymentType() = 0;
// };


// #endif // PAYMENT_STARTEGY_H