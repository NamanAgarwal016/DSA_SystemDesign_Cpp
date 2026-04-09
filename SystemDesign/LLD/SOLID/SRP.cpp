// https://github.com/adityatandon15/LLD/blob/main/Lecture%2005/C%2B%2B%20Code/SRP/SRP_followed.cpp
// https://youtu.be/UsNl8kcU4UA?list=PLQEaRBV9gAFvzp6XhcNFpk1WdOcyVo9qT

#include <iostream>
#include <vector>

using namespace std;

// Always Value semantics is preffered over pointer semnatics,
// Reason: pointers needs to be deleted proeproly, else use unique_ptr

// 1. SRP violated:
//     a. using value semantics:

class Product {
 public:
    string name;
    double price;

    Product(string name, double price) {
        this->name = name;
        this->price = price;
    }
};

class ShoppingCart {
 private:
    vector<Product> products;

 public:
    void addProduct(const Product& product) {
        products.push_back(product);
    }

    const vector<Product>& getProducts() {
        return products;
    }

    double calculateTotalPrice(){
        double total = 0.00;
        for(const Product& p: products){
            total += p.price;
        }
        return total;
    }

    void printInvoice(){
        for(const Product& p: products){
            cout << p.name << ": " << p.price << endl;
        }
        cout << "Total price: " << calculateTotalPrice() << endl;
    }

    void saveToDB(){
        cout << "Saving to DB...." << endl;
    }
};

int main() {
    Product car("Car", 20.00);
    Product bike("Bike", 10.00);
    ShoppingCart cart;
    cart.addProduct(car);
    cart.addProduct(bike);
    cart.printInvoice();
    cart.saveToDB();
}


    // b. using pointer semantics
class Product {
 public:
    string name;
    double price;

    Product(string name, double price) {
        this->name = name;
        this->price = price;
    }
};

class ShoppingCart {
 private:
    vector<Product*> products;

 public:
    void addProduct(Product* product) {
        products.push_back(product);
    }

    const vector<Product*>& getProducts() {
        return products;
    }

    double calculateTotalPrice(){
        double total = 0.00;
        for(Product* p: products){
            total += p->price;
        }
        return total;
    }

    void printInvoice(){
        for(Product* p: products){
            cout << p->name << ": " << p->price << endl;
        }
        cout << "Total price: " << calculateTotalPrice() << endl;
    }

    void saveToDB(){
        cout << "Saving to DB...." << endl;
    }
};

int main() {
    Product *p1 = new Product("Car", 20.00);
    Product *p2 = new Product("Bike", 10.00);

    ShoppingCart *cart = new ShoppingCart();
    cart->addProduct(p1);
    cart->addProduct(p2);
    
    cart->printInvoice();
    cart->saveToDB();
}


// 2. SRP followed:
    // a. Pointer semantics

class Product {
 public:   
    string name;
    double price;

    Product(string name, double price) {
        this->name = name;
        this->price = price;
    }
};

class ShoppingCart {
 private:
    vector<Product*> products;
    
 public:
    void addProducts(Product* p){
        products.push_back(p);
    }

    const vector<Product*>& getProducts() const {
        return products;
    }

    double calculateTotal() const {
        double total = 0.0;
        for(Product* p: products){
            total += p->price;
        }
        return total;
    }
};

class InvoicePrinter {
 private:
    ShoppingCart* cart;
 public:
    InvoicePrinter(ShoppingCart* cart){
        this->cart = cart;
    }
    void printInvoice(){
        for(Product* p: cart->getProducts()){
            cout << p->name << " : " << p->price << endl;
        }
        cout << "Total: " << cart->calculateTotal() << endl;
    }
};

class DBManager {
 private:
    ShoppingCart* cart;
 public:
    DBManager(ShoppingCart* cart){
        this->cart = cart;
    }
    void saveToDB(){
        cout << "Saving to DB..." << endl;
    }
};

int main() {
    Product* car = new Product("car", 100.00);
    Product* bike = new Product("bike", 50.00);

    ShoppingCart* cart = new ShoppingCart();
    cart->addProducts(car);
    cart->addProducts(bike);

    // ShoppingCart cart;
    // cart.addProduct(make_unique<Product>("car", 100.0));
    // cart.addProduct(make_unique<Product>("bike", 50.0));

    InvoicePrinter* ip = new InvoicePrinter(cart);
    ip->printInvoice();

    DBManager* db = new DBManager(cart);
    db->saveToDB();

    return 0;
    
}

    // b. Value Semantics
class Product {
 public: 
    string name;   
    double price;

    Product(string name, double price) : name(name), price(price) {}
};

class ShoppingCart {
 private:
    vector<Product> products;
 public:
    void addProduct(const Product& p){
        products.push_back(p);
    }
    const vector<Product>& getProducts() const {
        return products;
    }

    double calculateTotal() const {
        double total = 0.00;
        for(const Product& p: products){
            total += p.price;
        }
        return total;
    }
};

class InvoicePrinter {
 private:   
    const ShoppingCart& cart;     // very imp, reference to the real cart, Printer/DB should work on the live cart (no unexpected snapshots).
 public:
    InvoicePrinter(const ShoppingCart& cart) : cart(cart) {}

    void printInvoice(){
        for(const Product& p: cart.getProducts()){
            cout << p.name << ": " << p.price << endl;
        }
        cout << "Total: " << cart.calculateTotal() << endl;
    }
};

class DBManager{
 private:   
    const ShoppingCart& cart;
 public:
    DBManager(const ShoppingCart& cart) : cart(cart) {}

    void saveToDB(){
        cout << "Saving to DB... " << endl;
    }
};

int main(){
    Product car("car", 100.00);
    Product bike("bike", 80.00);
    ShoppingCart cart;
    cart.addProduct(car);
    cart.addProduct(bike);
    InvoicePrinter ip(cart);
    ip.printInvoice();
    DBManager db(cart);
    db.saveToDB();
    return 0;
}




