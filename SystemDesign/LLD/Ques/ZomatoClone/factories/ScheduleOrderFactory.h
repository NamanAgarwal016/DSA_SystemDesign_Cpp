#ifndef SCHEDULED_ORDER_FACTORY_H
#define SCHEDULED_ORDER_FACTORY_H

#include "OrderFactory.h"
#include "../models/DeliveryOrder.h"
#include "../models/PickupOrder.h"
#include "../utils/Time.h"
using namespace std;

class ScheduledOrderFactory : public OrderFactory {
private:
    string scheduleTime;
public:
    ScheduledOrderFactory(string scheduleTime) {
        this->scheduleTime = scheduleTime;
    }

    Order* createOrder(User* user, Cart* cart, Restaurant* restaurant, const vector<MenuItem>& menuItems,
                        PaymentStrategy* paymentStrategy, double totalCost, const string& orderType) override {
        Order* order = nullptr;

        if(orderType == "Delivery") {
            auto deliveryOrder = new DeliveryOrder();
            deliveryOrder->setUserAddress(user->getAddress());
            order = deliveryOrder;
        } 
        else {
            auto pickupOrder = new PickupOrder();
            pickupOrder->setRestaurantAddress(restaurant->getLocation());
            order = pickupOrder;
        }
        order->setUser(user);
        order->setRestaurant(restaurant);
        order->setItems(menuItems);
        order->setPaymentStrategy(paymentStrategy);
        order->setScheduled(scheduleTime);
        order->setTotal(totalCost);
        return order;
    }
};

#endif // SCHEDULED_ORDER_FACTORY_H

// #ifndef SCHEDULE_ORDER_FACTORY_H
// #define SCHEDULE_ORDER_FACTORY_H

// #include <iostream>

// #include "../models/DeliveryOrder.h"
// #include "../models/PickupOrder.h"

// using namespace std;

// class ScheduleOrderFactory: public OrderFactory {
// private:
//     string scheduleTime;
// public: 
//     ScheduleOrderFactory(string scheduleTime) : scheduleTime(scheduleTime) {}

//     Order* createOrder(string type, User* user, Restaurant* restaurant, PaymentStrategy* paymentMode) {
//         if(user == nullptr || restaurant == nullptr || paymentMode == nullptr) {
//             cerr << "Error: Invalid parameters in ScheduleOrderFactory::createOrder" << endl;
//             return nullptr;
//         }
        
//         cout << "This Order is scheuled for time: " << scheduleTime << endl;
//         if(type == "delivery"){
//             return new DeliveryOrder(user, restaurant, paymentMode);
//         } else if(type == "pickup"){
//             return new PickupOrder(user, restaurant, paymentMode);
//         } else {
//             cout << "Invalid orderType selected.." << endl;
//             return nullptr;
//         }
//     }     
// };

// #endif // SCHEDULE_ORDER_FACTORY_H