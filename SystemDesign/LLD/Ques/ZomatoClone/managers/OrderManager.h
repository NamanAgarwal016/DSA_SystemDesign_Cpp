#ifndef ORDER_MANAGER_H
#define ORDER_MANAGER_H

#include <vector>
#include <iostream>
#include "../models/Order.h"
using namespace std;

class OrderManager {
private:
    vector<Order*> orders;
    static OrderManager* instance;

    OrderManager() {
        // Private Constructor
    }

public:
    static OrderManager* getInstance() {
        if (!instance) {
            instance = new OrderManager();
        }
        return instance;
    }

    void addOrder(Order* order) {
        orders.push_back(order);
    }

    void listOrders() {
        cout << "\n--- All Orders ---" << endl;
        for (auto order : orders) {
            cout << order->getType() << " order for " << order->getUser()->getName()
                    << " | Total: ₹" << order->getTotal()
                    << " | At: " << order->getScheduled() << endl;
        }
    }

    ~OrderManager() {
        for(auto order : orders) {
            delete order;
        }
        orders.clear();
    }
};

OrderManager* OrderManager::instance = nullptr;

#endif // ORDER_MANAGER_H

// #ifndef ORDER_MANAGER_H
// #define ORDER_MANAGER_H

// #include <iostream>
// #include <vector>

// #include "../models/Order.h"

// using namespace std;

// class OrderManager {
// private:
//     static OrderManager* instance;
//     OrderManager(){}
//     vector<Order*> orderList;
// public: 
//     static OrderManager* getInstance(){
//         return instance;
//     }
//     void addOrder(Order* order) {
//         if(order != nullptr) {
//             orderList.push_back(order);
//         }
//     }

//     void listOrder(){
//         for(auto order: orderList) {
//             if(order != nullptr) {
//                 cout << "Order id: " << order->getOrderId() << endl;
//             }
//         }
//     } 

//     ~OrderManager() {
//         for(auto order: orderList) {
//             delete order;
//             order = nullptr;
//         }
//         orderList.clear();
//     }
// };


// OrderManager* OrderManager::instance = new OrderManager();

// #endif // ORDER_MANAGER_H