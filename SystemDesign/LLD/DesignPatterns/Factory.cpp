// https://youtu.be/dMK4TbG29fk?list=PLQEaRBV9gAFvzp6XhcNFpk1WdOcyVo9qT

#include <iostream>
using namespace std;

// Product 1
class Burger {
public:
    virtual ~Burger() {}
    virtual void prepare() = 0;
};

class BasicBurger : public Burger {
public:
    void prepare() override {
        cout << "Preparing basic burger..." << endl;
    }
};

class PremiumBurger : public Burger {
public:
    void prepare() override {
        cout << "Preparing premium burger..." << endl;
    }
};

class BasicWheatBurger : public Burger {
public:
    void prepare() override {
        cout << "Preparing basic wheat burger..." << endl;
    }
};

class PremiumWheatBurger : public Burger {
public:
    void prepare() override {
        cout << "Preparing premium wheat burger..." << endl;
    }
};

//Product 2
class Sandwich {
public:
    virtual ~Sandwich() {}
    virtual void prepare() = 0;
};

class BasicSandwich : public Sandwich {
public:
    void prepare() override {
        cout << "Preparing basic Sandwich..." << endl;
    }
};

class PremiumSandwich : public Sandwich {
public:
    void prepare() override {
        cout << "Preparing premium Sandwich..." << endl;
    }
};

class BasicWheatSandwich : public Sandwich {
public:
    void prepare() override {
        cout << "Preparing basic wheat Sandwich..." << endl;
    }
};

class PremiumWheatSandwich : public Sandwich {
public:
    void prepare() override {
        cout << "Preparing premium wheat Sandwich..." << endl;
    }
};


// Object Factory abstract class
class MealFactory {
public:
    virtual Burger* createBurger(const string& type) = 0;
    virtual Sandwich* createSandwich(const string& type) = 0;
    virtual ~MealFactory() {}
};

// Object factory concrete classes
class SinghFoodJoint : public MealFactory {
public:
    virtual Burger* createBurger(const string& type) override {
        if(type == "premium") {
            return new PremiumBurger();
        } else if(type == "basic") {
            return new BasicBurger();
        } else {
            cout << "Invalid Burger type!!" << endl;
            return nullptr;
        }
    }
    virtual Sandwich* createSandwich(const string& type) override {
        if(type == "premium") {
            return new PremiumSandwich();
        } else if(type == "basic") {
            return new BasicSandwich();
        } else {
            cout << "Invalid Sandwich type!!" << endl;
            return nullptr;
        }
    }

};

class KingFoodJoint : public MealFactory {
public:
    virtual Burger* createBurger(const string& type) override {
        if(type == "premium") {
            return new PremiumWheatBurger(); 
        } else if(type == "basic") {
            return new BasicWheatBurger();
        } else {
            cout << "Invalid Burger type!!" << endl;
            return nullptr;
        }
    }

    virtual Sandwich* createSandwich(const string& type) override {
        if(type == "premium") {
            return new PremiumWheatSandwich();
        } else if(type == "basic") {
            return new BasicWheatSandwich();
        } else {
            cout << "Invalid Sandwich type!!" << endl;
            return nullptr;
        }
    }
};

int main(){  
    MealFactory* factory = new KingFoodJoint();
    // MealFactory* factory = new SinghFoodJoint();

    string burgerType = "premium";
    Burger* burger = factory->createBurger(burgerType);
    if(burger != nullptr)
        burger->prepare();
    
    string sandwichType = "basic";
    Sandwich* sandwich = factory->createSandwich(sandwichType);
    if(sandwich != nullptr)
        sandwich->prepare();

    delete sandwich;
    delete burger;
    delete factory;

    return 0;
}


/*

You separated product families (Burger vs Sandwich) and provided concrete factories (SinghFoodJoint, KingFoodJoint) — 
this is the Abstract Factory idea (a factory returns a family of related objects).
Product interfaces (Burger, Sandwich) have virtual destructors and virtual prepare() — good polymorphism.
Factories are polymorphic via MealFactory* — client code can switch families easily.
*/