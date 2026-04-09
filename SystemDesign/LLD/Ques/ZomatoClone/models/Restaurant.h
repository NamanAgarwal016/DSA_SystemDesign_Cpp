#ifndef RESTAURANT_H
#define RESTAURANT_H

#include <iostream>
#include <string>
#include <vector>
#include "MenuItem.h"
using namespace std;

class Restaurant {
private:
    static int nextRestaurantId;
    int restaurantId;
    string name;
    string location;
    vector<MenuItem> menu;

public:
    Restaurant(const string& name, const string& location) {
        this->name = name;
        this->location = location;
        this->restaurantId = ++nextRestaurantId;
    }

    ~Restaurant() {
        // Optional: just for clarity or debug
        cout << "Destroying Restaurant: " << name << ", and clearing its menu." << endl;
        menu.clear();
    }

    //Getters and setters
    string getName() const {
        return name;
    }

    void setName(const string &n) {
        name = n;
    }

    string getLocation() const {
        return location;
    }

    void setLocation(const string &loc) {
        location = loc;
    }

    void addMenuItem(const MenuItem &item) {
        menu.push_back(item);
    }

    const vector<MenuItem>& getMenu() const {
        return menu;
    }
};

int Restaurant::nextRestaurantId = 0;

#endif // RESTAURANT_H

// #ifndef RESTAURANT_H
// #define RESTAURANT_H

// #include <iostream>
// #include <vector>

// #include "MenuItem.h"

// using namespace std;

// class Restaurant {
// private:
//     static int restaurantId;
//     string name;
//     string address;
//     vector<MenuItem> menu;
// public: 
//     Restaurant(const string& name, const string& address) : name(name), address(address) {
//         restaurantId++; 
//     }
    
//     void addMenuItem(MenuItem& item) {
//         menu.push_back(item);
//     }

//     vector<MenuItem>& getMenu() {
//         return menu;
//     }

//     string getRestAddress() const {
//         return address;
//     }

//     string getRestName() const {
//         return name;
//     }

//     void displayMenuItems(){
//         cout << "Welcome to " << name << ", Here's the menu: " << endl;
//         for(auto item: getMenu()){
//             cout << item.getItemCode() << ":\t" << item.getName() << "\tRs." << item.getPrice() << endl;
//         }
//     }

// };

// int Restaurant::restaurantId = 0;

// #endif // RESTAURANT_H