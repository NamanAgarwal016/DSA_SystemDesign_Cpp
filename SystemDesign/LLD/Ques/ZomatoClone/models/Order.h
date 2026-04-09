#ifndef ORDER_H
#define ORDER_H

#include <iostream>
#include <string>
#include <vector>
#include "User.h"
#include "Restaurant.h"
#include "MenuItem.h"
#include "../strategies/PaymentStrategy.h"
#include "../utils/Time.h"
using namespace std;

class Order {
protected:
    static int nextOrderId;
    int orderId;
    User* user;
    Restaurant* restaurant;
    vector<MenuItem> items;
    PaymentStrategy* paymentStrategy;
    double total;
    string scheduled;

public:
    Order() {
        user = nullptr;
        restaurant = nullptr;
        paymentStrategy = nullptr;
        total = 0.0;
        scheduled = "";
        orderId = ++nextOrderId;
    }

    virtual ~Order() {
        delete paymentStrategy;
    }

    bool processPayment() {
        if (paymentStrategy) {
            paymentStrategy->pay(total);
            return true;
        } else {
            cout << "Please choose a payment mode first" << endl;
            return false;
        }
    }

    virtual string getType() const = 0;

    //Getter and Setters
    int getOrderId() const {
        return orderId;
    }

    void setUser(User* u) {
        user = u;
    }

    User* getUser() const {
        return user;
    }

    void setRestaurant(Restaurant* r) {
        restaurant = r;
    }

    Restaurant* getRestaurant() const {
        return restaurant;
    }

    void setItems(const vector<MenuItem>& its) {
        items = its;
        total = 0;
        for (auto &i : items) {
            total += i.getPrice();
        }
    }

    const vector<MenuItem>& getItems() const {
        return items;
    }

    void setPaymentStrategy(PaymentStrategy* p) {
        paymentStrategy = p;
    }

    void setScheduled(const string& s) {
        scheduled = s;
    }

    string getScheduled() const {
        return scheduled;
    }

    double getTotal() const {
        return total;
    }

    void setTotal(int total) {
        this->total = total;
    }
};

int Order::nextOrderId = 0;

#endif // ORDER_H

// #ifndef ORDER_H
// #define ORDER_H

// #include <iostream>

// #include "User.h"
// #include "Restaurant.h"
// #include "../strategies/PaymentStrategy.h"
// #include "MenuItem.h"

// using namespace std;

// class Order {
// protected:
//     static int orderId;
//     User* user;
//     Restaurant* restaurant;
//     vector<MenuItem> items;
//     PaymentStrategy* paymentMode;
//     // int total;

// public:
//     Order(User* user, Restaurant* restaurant, PaymentStrategy* paymentMode) :
//         user(user), restaurant(restaurant), paymentMode(paymentMode) {
//             orderId++;
//         }
    
//     virtual void  getOrderType() = 0; 
//     virtual ~Order() {}  // Add virtual destructor
    
//     int getOrderId(){return orderId;}
//     User* getUser(){return user;}
//     Restaurant* getRestaurant(){return restaurant;}   

//     void makePayment() {
//         paymentMode->pay(user->getCart().totalCartPrice());
//     }

//     void printOrder() {
//         cout << "Following is your final order summary: " << endl;
//         user->getCart().displayCartItems();
//         getOrderType();
//         paymentMode->getPaymentType();
//     }

//     // void setItems(const vector<MenuItem>& its) {
//     //     items = its;
//     //     total = 0;
//     //     for (auto &i : items) {
//     //         total += i.getPrice();
//     //     }
//     // }
// };

// int Order::orderId = 0;

// #endif // ORDER_H