#ifndef DELIVERY_ORDER_H
#define DELIVERY_ORDER_H

#include "Order.h"
using namespace std;

class DeliveryOrder : public Order {
private:
    string userAddress;

public:
    DeliveryOrder() {
        userAddress = "";
    }

    string getType() const override {
        return "Delivery";
    }

    //Getter and Setters
    void setUserAddress(const string& addr) {
        userAddress = addr;
    }

    string getUserAddress() const {
        return userAddress;
    }
};

#endif // DELIVERY_ORDER_H

// #ifndef DELIVERY_ORDER_H
// #define DELIVERY_ORDER_H

// #include <iostream>

// #include "Order.h"

// using namespace std;

// class DeliveryOrder : public Order {
// private:
//     string usrAddress;
// public:

//     DeliveryOrder(User* user, Restaurant* restaurant, PaymentStrategy* paymentMode) :
//         Order(user, restaurant, paymentMode) {
//             usrAddress = user->getUserAddress();
//     }

//     void getOrderType() override {
//         cout << "This is a delivery order for address: " << usrAddress << endl;
//     }    
// };

// #endif // DELIVERY_ORDER_H