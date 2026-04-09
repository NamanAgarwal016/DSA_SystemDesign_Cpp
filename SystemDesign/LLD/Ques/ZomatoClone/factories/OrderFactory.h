#ifndef ORDER_FACTORY_H
#define ORDER_FACTORY_H

#include "../models/Order.h"
#include "../models/Cart.h"
#include "../models/Restaurant.h"
#include "../strategies/PaymentStrategy.h"
#include <vector>
#include <string>
using namespace std;

class OrderFactory {
public:
    virtual Order* createOrder(User* user, Cart* cart, Restaurant* restaurant, const vector<MenuItem>& menuItems,
                                PaymentStrategy* paymentStrategy, double totalCost, const string& orderType) = 0;
    virtual ~OrderFactory() {}
};

#endif // ORDER_FACTORY_H

// My code:
// #ifndef ORDER_FACTORY_H
// #define ORDER_FACTORY_H

// #include <iostream>

// #include "../models/Order.h"

// using namespace std;

// class OrderFactory{
// public: 
//     virtual Order* createOrder(string type, User* user, Restaurant* restaurant, PaymentStrategy* paymentMode) = 0;     

//     virtual ~OrderFactory() {}  // Add virtual destructor for polymorph
// };

// #endif // ORDER_FACTORY_H