#ifndef MENUITEM_H
#define MENUITEM_H

#include <string>
using namespace std;

class MenuItem {
private:
    string code;
    string name;
    int price;

public:
    MenuItem(const string& code, const string& name, int price) {
        this->code = code;
        this->name = name;
        this->price = price;
    }

    //Getters and setters
    string getCode() const {
        return code;
    }

    void setCode(const string &c) {
        code = c;
    }

    string getName() const {
        return name;
    }

    void setName(const string &n) {
        name = n;
    }

    int getPrice() const {
        return price;
    }

    void setPrice(int p) {
        price = p;
    }
};

#endif // MENUITEM_H

// #ifndef MENU_ITEM_H
// #define MENU_ITEM_H

// using namespace std;

// class MenuItem {
// private:
//     string itemCode;
//     string name;
//     int price;
// public:
//     MenuItem(const string& itemCode, const string& name, int price) : itemCode(itemCode), name(name), price(price) {}

//     string getItemCode() const { return itemCode; }
//     string getName() const { return name; }
//     int getPrice() const { return price; }
// };

// #endif // MENU_ITEM_H