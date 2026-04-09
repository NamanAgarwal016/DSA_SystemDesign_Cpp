// https://youtu.be/CD3meit-WDc?list=PLQEaRBV9gAFvzp6XhcNFpk1WdOcyVo9qT

#include <iostream>
#include <mutex>

using namespace std;

// Not thread safe:
// class Singleton {
// private:
//     static Singleton* instance;
//     Singleton(){
//         cout << "Singleton object created..." << endl;
//     }
// public:
//     static Singleton* getInstance() {
//         if(instance == nullptr){
//             return instance = new Singleton();
//         }
//         return instance;
//     }    
// };

// Singleton* Singleton::instance = nullptr;

// int main() {
//     Singleton* s1 = Singleton::getInstance();
//     Singleton* s2 = Singleton::getInstance();
    
//     if(s1 != s2) {
//         cout << "Different objects" << endl;
//     } else {
//         cout << "Same object" << endl;
//     }
// }


// Thread safe using double locking:
// class Singleton {
// private:
//     static Singleton* instance;
//     static mutex mtx;
//     Singleton(){
//         cout << "Singleton object created..." << endl;
//     }
// public:
//     static Singleton* getInstance() {
//         if(instance == nullptr){
//             lock_guard<mutex> lock(mtx);
//             if(instance == nullptr){
//                 return instance = new Singleton();
//             }   
//         }
//         return instance;
//     }    
// };

// Singleton* Singleton::instance = nullptr;
// mutex Singleton::mtx;

// int main() {
//     Singleton* s1 = Singleton::getInstance();
//     Singleton* s2 = Singleton::getInstance();
    
//     if(s1 != s2) {
//         cout << "Different objects" << endl;
//     } else {
//         cout << "Same object" << endl;
//     }
// }


// Thread safe using Eager Initialization: Used only for light weight objects, as it will initialize before main(), needed or not needed later
class Singleton {
private:
    static Singleton* instance;
    Singleton(){
        cout << "Singleton object created..." << endl;
    }
    
    // delete copy/assignment to ensure no one can clone or reassign your singleton.
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
public:
    static Singleton* getInstance() {
        return instance;
    }    
};

Singleton* Singleton::instance = new Singleton();

int main() {
    Singleton* s1 = Singleton::getInstance();
    Singleton* s2 = Singleton::getInstance();
    
    if(s1 != s2) {
        cout << "Different objects" << endl;
    } else {
        cout << "Same object" << endl;
    }
}
