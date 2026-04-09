#ifndef RESTAURANT_MANAGER_H
#define RESTAURANT_MANAGER_H

#include <vector>
#include <string>
#include <algorithm>
#include "../models/Restaurant.h"
using namespace std;

class RestaurantManager {
private:
    vector<Restaurant*> restaurants;
    static RestaurantManager* instance;

    RestaurantManager() {
        // private constructor
    }

public:
    static RestaurantManager* getInstance() {
        if (!instance) {
            instance = new RestaurantManager();
        }
        return instance;
    }

    void addRestaurant(Restaurant* r) {
        restaurants.push_back(r);
    }

    vector<Restaurant*> searchByLocation(string loc) {
        vector<Restaurant*> result;
        transform(loc.begin(), loc.end(), loc.begin(), ::tolower);
        for (auto r : restaurants) {
            string rl = r->getLocation();
            transform(rl.begin(), rl.end(), rl.begin(), ::tolower);
            if (rl == loc) {
                result.push_back(r);
            }
        }
        return result;
    }

    ~RestaurantManager() {
        for(auto r : restaurants) {
            delete r;
        }
        restaurants.clear();
    }
};

RestaurantManager* RestaurantManager::instance = nullptr;

#endif // RESTAURANT_MANAGER_H

// #ifndef RESTAURANT_MANAGER_H
// #define RESTAURANT_MANAGER_H

// #include <iostream>

// #include "../models/Restaurant.h"

// using namespace std;

// class RestaurantManager {
// private:
//     static RestaurantManager* instance;
//     RestaurantManager(){}
//     vector<Restaurant*> restaurants;
// public:
//     static RestaurantManager* getInstance(){
//         return instance;
//     }

//     void addRestaurant (Restaurant* restaurant) {
//         restaurants.push_back(restaurant);
//     }

//     Restaurant* searchByAddress(string address) {
//         for(auto restaurant: restaurants) {
//             if(address == restaurant->getRestAddress()){
//                 cout << "According to your location, selected restaurant is: " <<  restaurant->getRestName() << endl;
//                 return restaurant;
//             }
//         }
//         return nullptr;
//     }
// };

// RestaurantManager* RestaurantManager::instance = new RestaurantManager();

// #endif // RESTAURANT_MANAGER_H