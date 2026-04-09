
#ifndef TOMATO_APP_H
#define TOMATO_APP_H

#include <vector>
#include <string>
#include "models/User.h"
#include "models/Restaurant.h"
#include "models/Cart.h"
#include "managers/RestaurantManager.h"
#include "managers/OrderManager.h"
#include "strategies/PaymentStrategy.h"
#include "strategies/NetBanking.h"
#include "factories/NowOrderFactory.h"
#include "factories/ScheduleOrderFactory.h"
#include "services/NotificationService.h"
#include "utils/Time.h"
using namespace std;

class TomatoApp {
public:
    TomatoApp() {
        initializeRestaurants();
    }

    void initializeRestaurants() {
        Restaurant* restaurant1 = new Restaurant("Bikaner", "Delhi");
        restaurant1->addMenuItem(MenuItem("P1", "Chole Bhature", 120));
        restaurant1->addMenuItem(MenuItem("P2", "Samosa", 15));

        Restaurant* restaurant2 = new Restaurant("Haldiram", "Kolkata");
        restaurant2->addMenuItem(MenuItem("P1", "Raj Kachori", 80));
        restaurant2->addMenuItem(MenuItem("P2", "Pav Bhaji", 100));
        restaurant2->addMenuItem(MenuItem("P3", "Dhokla", 50));

        Restaurant* restaurant3 = new Restaurant("Saravana Bhavan", "Chennai");
        restaurant3->addMenuItem(MenuItem("P1", "Masala Dosa", 90));
        restaurant3->addMenuItem(MenuItem("P2", "Idli Vada", 60));
        restaurant3->addMenuItem(MenuItem("P3", "Filter Coffee", 30));

        RestaurantManager* restaurantManager = RestaurantManager::getInstance();
        restaurantManager->addRestaurant(restaurant1);
        restaurantManager->addRestaurant(restaurant2);
        restaurantManager->addRestaurant(restaurant3);

        // Add other sample restaurants...
    }

    vector<Restaurant*> searchRestaurants(const string& location) {
        return RestaurantManager::getInstance()->searchByLocation(location);
    }

    void selectRestaurant(User* user, Restaurant* restaurant) {
        Cart* cart = user->getCart();
        cart->setRestaurant(restaurant);
    }

    void addToCart(User* user, const string& itemCode) {
        Restaurant* restaurant = user->getCart()->getRestaurant();
        if (!restaurant) {
            cout << "Please select a restaurant first." << endl;
            return;
        }
        for (const auto& item : restaurant->getMenu()) {
            if (item.getCode() == itemCode) {
                user->getCart()->addItem(item);
                break;
            }
        }
    }

    Order* checkoutNow(User* user, const string& orderType, PaymentStrategy* paymentStrategy) {
        return checkout(user, orderType, paymentStrategy, new NowOrderFactory());
    }

    Order* checkoutScheduled(User* user, const string& orderType, PaymentStrategy* paymentStrategy, const string& scheduleTime) {
        return checkout(user, orderType, paymentStrategy, new ScheduledOrderFactory(scheduleTime));
    }

    Order* checkout(User* user, const string& orderType, 
        PaymentStrategy* paymentStrategy, OrderFactory* orderFactory) {
        if (user->getCart()->isEmpty())
        return nullptr;

        Cart* userCart = user->getCart();
        Restaurant* orderedRestaurant = userCart->getRestaurant();
        vector<MenuItem> itemsOrdered = userCart->getItems();
        double totalCost = userCart->getTotalCost();

        Order* order = orderFactory->createOrder(user, userCart, orderedRestaurant, itemsOrdered, paymentStrategy, totalCost, orderType);
        OrderManager::getInstance()->addOrder(order);
        return order;
    }

    void payForOrder(User* user, Order* order) {
        bool isPaymentSuccess = order->processPayment();

        // clear user cart if payment is successful.
        if(isPaymentSuccess) {
            NotificationService* notification = new NotificationService();
            notification->notify(order);
            user->getCart()->clear();
        }  
    }

    void printUserCart(User* user) {
        cout << "Items in cart:" << endl;
        cout << "------------------------------------" << endl;
        for (const auto& item : user->getCart()->getItems()) {
            cout << item.getCode() << " : " << item.getName() << " : ₹" << item.getPrice() << endl;
        }
        cout << "------------------------------------" << endl;
        cout << "Grand total : ₹" << user->getCart()->getTotalCost() << endl;
    }
};

#endif // TOMATO_APP_H


// My First code & understanding:

// /*
// User Journey:
// 1. User will open the app (App Setup already done)
// 2. He will be created as a user with unique user id, name & his address. A cart will be assigned to him.
// 3. He will choose the restaurant according to his location.
// 4. Choose the menu items, add into his cart.
// 5. Choose the option for schdeule order or order Now.
// 6. Choose the option for delivery or Pickup order.
// 7. Get the final details of order: order id, menuitems, totalprice, delivery type, delivery time
// 8. Choose the option for payment: credit card or netBanking
// 9. Make the payement.
// 10. Get the notification about his order.

// App Setup:
// 1. Populate restaurants: id, name, loc.
// 2. for every restaurant, populate menu items: itemCode, name, price.
// 3. Follow the user journey
// */

// #ifndef TOMATO_H
// #define TOMATO_H

// #include <iostream>

// #include "models\MenuItem.h"
// #include "models\Restaurant.h"
// #include "managers\RestaurantManager.h"
// #include "models\User.h"
// #include "factories\OrderFactory.h"
// #include "factories\NowOrderFactory.h"
// #include "factories\ScheduleOrderFactory.h"
// #include "strategies\PaymentStrategy.h"
// #include "strategies\CreditCard.h"
// #include "strategies\NetBanking.h"
// #include "services\NotificationService.h"
// #include "utils/OrderEnums.h"

// using namespace std;

// // Singleton class
// class Tomato {
// private:
//     static Tomato* instance;
//     Tomato(){};
// public:
//     static Tomato* getInstance(){
//         return instance;
//     }
//     void runApp(string usrname, string usraddress, string orderTimeType, string orderDeliveryType, string paymentType) {
        
//         // App Setup:

//         // Set Menuitems
//         MenuItem pizza("ff1", "Pizza", 400);
//         MenuItem coke("d1", "Coke", 20);
//         MenuItem pasta("ff2", "Pasta", 250);
//         MenuItem choleBhature("ff3", "Chole Bhature", 180);
//         MenuItem lassi("d2", "Lassi", 60);

//         // Set Restaurants 
//         Restaurant dominos("Dominos", "Whitefield");
//         dominos.addMenuItem(pizza);
//         dominos.addMenuItem(coke);
//         dominos.addMenuItem(pasta);

//         Restaurant natraj("Natraj Chole Bhature", "AECS layout");
//         natraj.addMenuItem(choleBhature);
//         natraj.addMenuItem(lassi);
//         natraj.addMenuItem(coke);

//         RestaurantManager* rm = RestaurantManager::getInstance();
//         rm->addRestaurant(&dominos);
//         rm->addRestaurant(&natraj);

//         // User Journey:

//         // Set User
//         User user(usrname, usraddress);
//         cout << endl;

//         // User selects the restaurant
//         Restaurant* selectedRest = rm->searchByAddress(user.getUserAddress());
//         if(selectedRest == nullptr) {
//             cerr << "Error: No restaurant found for your address." << endl;
//             return;
//         }
//         cout << endl;

//         selectedRest->displayMenuItems();
//         cout << endl;

//         // User selects the menu items & add in his cart
//         user.getCart().addToCart(pasta);
//         user.getCart().addToCart(coke);
        
//         user.getCart().displayCartItems();
//         cout << endl;

//         // Validate cart not empty
//         if(user.getCart().totalCartPrice() <= 0) {
//             cerr << "Error: Cart is empty. Cannot place order." << endl;
//             return;
//         }

//         OrderFactory* factory = nullptr;
//         if(orderTimeType == "now") {
//             factory = new NowOrderFactory();
//         } else if(orderTimeType == "schedule") {
//             factory = new ScheduleOrderFactory("8PM");
//         } else {
//             cerr << "Error: Invalid order time type." << endl;
//             return;
//         }
        
//         PaymentStrategy* paymentMode = nullptr;
//         if(paymentType == "creditcard") {
//             paymentMode = new CreditCard(paymentType);
//         } else if(paymentType == "netbanking"){
//             paymentMode = new NetBanking(paymentType);
//         } else {
//             cerr << "Error: Invalid payment type." << endl;
//             delete factory;
//             factory = nullptr;
//             return;
//         }

//         Order* order = factory->createOrder(orderDeliveryType, &user, selectedRest, paymentMode);

//         if(order == nullptr) {
//             cerr << "Error: Failed to create order." << endl;
//             delete paymentMode;
//             delete factory;
//             return;
//         }

//         order->printOrder();
//         cout << endl;

//         order->makePayment();
//         cout << endl;

//         NotificationService ns(order);
//         ns.notifyUser();
//         cout << endl;

//          // Manual cleanup
//         delete order;
//         order = nullptr;
//         delete paymentMode;
//         paymentMode = nullptr;
//         delete factory;
//         factory = nullptr;
//     }
// };

// Tomato* Tomato::instance = new Tomato();

// #endif // TOMATO_H
