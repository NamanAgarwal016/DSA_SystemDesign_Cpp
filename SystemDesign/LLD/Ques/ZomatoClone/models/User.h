#ifndef USER_H
#define USER_H

#include <string>
#include "Cart.h"
using namespace std;

class User {
private:
    int userId;
    string name;
    string address;
    Cart* cart;

public:
    User(int userId, const string& name, const string& address) {
        this->userId = userId;
        this->name = name;
        this->address = address;
        cart = new Cart();
    }

    ~User() {
        delete cart;
    }

    // Getters and Setters
    string getName() const {
        return name;
    }

    void setName(const string &n) {
        name = n;
    }

    string getAddress() const {
        return address;
    }

    void setAddress(const string &a) {
        address = a;
    }

    Cart* getCart() const {
        return cart;
    }
};

#endif // USER_H

// #ifndef USER_H
// #define USER_H

// #include <iostream>

// #include "Cart.h"

// using namespace std;

// class User {
// private:
//     static int userid;
//     string name;
//     string address;
//     Cart cart;
// public:
//     User(string name, string address) : name(name), address(address) {
//         userid++;
//         cout <<  "Welcome " << name << "!!" << endl;
//         cout << "Your current location is: " << address << endl;
//         cout << "Your User ID is: " << userid << endl;
//     }
    
//     string getUserName() const {return name;}
//     string getUserAddress() const {return address;}
//     int getUserId() const {return userid;}
//     Cart& getCart() {return cart;}
// };

// int User::userid = 0;

// #endif // USER_H