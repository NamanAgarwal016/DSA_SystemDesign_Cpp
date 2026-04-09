#include <iostream>
#include <vector>

using namespace std;

// Here you have to use polymorphism to implement OCP
// So, pointer semantics is needed. Value semantics will make code dirty.

// // 1. OCP violated:

// class Product {
//  public: 
//     string name;   
//     double price;

//     Product(string name, double price) : name(name), price(price) {}
// };

// class ShoppingCart {
//  private:
//     vector<Product> products;
//  public:
//     void addProduct(const Product& p){
//         products.push_back(p);
//     }
//     const vector<Product>& getProducts() const {
//         return products;
//     }

//     double calculateTotal() const {
//         double total = 0.00;
//         for(const Product& p: products){
//             total += p.price;
//         }
//         return total;
//     }
// };

// class InvoicePrinter {
//  private:   
//     const ShoppingCart& cart;     
//  public:
//     InvoicePrinter(const ShoppingCart& cart) : cart(cart) {}

//     void printInvoice(){
//         for(const Product& p: cart.getProducts()){
//             cout << p.name << ": " << p.price << endl;
//         }
//         cout << "Total: " << cart.calculateTotal() << endl;
//     }
// };

// class DBManager{
//  private:   
//     const ShoppingCart& cart;
//  public:
//     DBManager(const ShoppingCart& cart) : cart(cart) {}

//     void saveToSQLDB(){
//         cout << "Saving to SQL DB... " << endl;
//     }

//     void saveToMongoDB() {
//         cout << "Saving to Mongo DB... " << endl;
//     }

//     void saveToFile() {
//         cout << "Saving to File... " << endl;
//     }
// };

// int main(){
//     Product car("car", 100.00);
//     Product bike("bike", 80.00);

//     ShoppingCart cart;
//     cart.addProduct(car);
//     cart.addProduct(bike);

//     InvoicePrinter ip(cart);
//     ip.printInvoice();

//     DBManager db(cart);
//     db.saveToSQLDB();
//     db.saveToMongoDB();
//     db.saveToFile();

//     return 0;
// }


// 2. OCP followed:

class Product {
 public: 
    string name;   
    double price;

    Product(string name, double price) : name(name), price(price) {}
};

// Value semantics for products
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

// Uses reference since it just reads the cart
class InvoicePrinter {
 private:   
    const ShoppingCart& cart;     
 public:
    InvoicePrinter(const ShoppingCart& cart) : cart(cart) {}

    void printInvoice() const {
        for(const Product& p: cart.getProducts()){
            cout << p.name << ": " << p.price << endl;
        }
        cout << "Total: " << cart.calculateTotal() << endl;
    }
};

// Base class for different DB implementations
class DBManager {  
 public:
    virtual ~DBManager() {}  
    // Virtual destructor needed, 
    // so that derived class destructor also runs when base class cleans up

    virtual void saveToDB(const ShoppingCart& cart) = 0;
};

class SQLDB : public DBManager {
 public:
    void saveToDB(const ShoppingCart& cart) override {
        cout << "Total of cart is: $" << cart.calculateTotal() << endl;
        cout << "Saving to SQL DB..." << endl;
    }
};

class MongoDB : public DBManager {
 public:
    void saveToDB(const ShoppingCart& cart) override {
        cout << "Total of cart is: $" << cart.calculateTotal() << endl;
        cout << "Saving to MongoDB..." << endl;
    }
};

class File : public DBManager {
 public:
    void saveToDB(const ShoppingCart& cart) override {
        cout << "Total of cart is: $" << cart.calculateTotal() << endl;
        cout << "Saving to File..." << endl;
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

    // Create DB managers and set the cart
    DBManager* sql = new SQLDB();
    DBManager* mongo = new MongoDB();
    DBManager* file = new File();

    sql->saveToDB(cart);
    mongo->saveToDB(cart);
    file->saveToDB(cart);

    // Clean up the managers
    delete sql;
    delete mongo;
    delete file;

    return 0;
}
