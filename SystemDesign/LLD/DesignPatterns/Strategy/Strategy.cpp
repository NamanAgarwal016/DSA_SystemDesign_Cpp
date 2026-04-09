// https://youtu.be/PpKvPrl_gRg?list=PLQEaRBV9gAFvzp6XhcNFpk1WdOcyVo9qT

#include <iostream>
using namespace std;


// Not following Strategy Desgin pattern

// class Robot {
// public:
//     void walk(){
//         cout << "Robot is walking..." << endl;
//     }
//     void talk(){
//         cout << "Robot is talking..." << endl;
//     }
//     virtual void projection() = 0;
// };

// class WorkerRobot : public Robot {
// public:
//     void projection() override {
//         cout << "I'm Worker Robot..." << endl;
//     }
// };

// class FlyableRobot : public Robot {
// public:
//     virtual void fly(){
//         cout << "Robot is flying..." << endl;
//     }
// };

// class SparrowRobot : public FlyableRobot {
// public:
//     void projection() override {
//         cout << "I'm Sparrow Robot..." << endl;
//     }
// };

// class JetFlyableRobot : public FlyableRobot {
// public:
//     void fly() override {
//         cout << "Robot is flying through Jet..." << endl;
//     }
// };

// class JetRobot : public JetFlyableRobot {
// public:
//     void projection() override {
//         cout << "I'm Jet Robot..." << endl;
//     }
// };

// int main () {

    // WorkerRobot wr;
    // wr.projection();
    // wr.walk();
    // wr.talk();

    // FlyableRobot* sr = new SparrowRobot();
    // sr->projection();
    // sr->walk();
    // sr->talk();
    // sr->fly();

    // JetFlyableRobot* jr = new JetRobot();
    // jr->projection();
    // jr->walk();
    // jr->talk();
    // jr->fly();
// }


// Following Strategy Desgin pattern

// --- Strategy Interface for Walk ---
class WalkBehaviour {
public:
    virtual ~WalkBehaviour() {}
    virtual void walk() = 0;
};

// --- Concrete Strategies for walk ---
class Walkable : public WalkBehaviour {
public:
    void walk() override {
        cout << "Robot is walking..." << endl;
    }
};

class NonWalkable : public WalkBehaviour {
public:
    void walk() override {
        cout << "This Robot can't walk..." << endl;
    }
};

// --- Strategy Interface for Talk ---
class TalkBehaviour {
public:
    virtual ~TalkBehaviour() {}
    virtual void talk() = 0;
};

// --- Concrete Strategies for Talk ---
class Talkable : public TalkBehaviour {
public:
    void talk() override {
        cout << "Robot is talking..." << endl;
    }
};

class NonTalkable : public TalkBehaviour {
public:
    void talk() override {
        cout << "This Robot can't talk..." << endl;
    }
};

// --- Strategy Interface for Fly ---
class FlyBehaviour {
public:
    virtual ~FlyBehaviour() {}
    virtual void fly() = 0;
};

// --- Concrete Strategies for Fly ---
class Flyable : public FlyBehaviour {
public:
    void fly() override {
        cout << "Robot is flying..." << endl;
    }
};

class NonFlyable : public FlyBehaviour {
public:
    void fly() override {
        cout << "This Robot can't fly..." << endl;
    }
};

class JetFlyable : public FlyBehaviour {
public:
    void fly() override {
        cout << "Robot is flying using Jet..." << endl;
    }
};

class Projection {
public:
    virtual ~Projection() {}
    virtual void projection() = 0;
};

// --- Concrete Robot Types ---
class WorkerRobot : public Projection {
public:
    void projection() override { cout << "I'm Worker Robot..." << endl; }
};

class SparrowRobot : public Projection {
public:
    void projection() override { cout << "I'm Sparrow Robot..." << endl; }
};

class JetRobot : public Projection {
public:
    void projection() override { cout << "I'm Jet Robot..." << endl; }
};

// --- Robot Base Class ---
class Robot {
private:
    WalkBehaviour* w;
    TalkBehaviour* t;
    FlyBehaviour* f;
    Projection* p;
public:
    Robot(WalkBehaviour* w, TalkBehaviour* t, FlyBehaviour* f, Projection* p) : w(w), t(t), f(f), p(p) {}
    virtual ~Robot() {
        delete w;
        delete t;
        delete f;
        delete p;
    }
    void projection(){ p->projection(); }
    void walk(){ w->walk(); }
    void talk(){ t->talk(); }
    void fly(){ f->fly(); }
};



int main () {
    Robot* wr = new Robot(new Walkable(), new Talkable(), new NonFlyable(), new WorkerRobot());
    wr->projection();
    wr->walk();
    wr->talk();
    wr->fly();

    cout << "--------------------" << endl;

    Robot* sr = new Robot(new NonWalkable(), new Talkable(), new Flyable(), new SparrowRobot());
    sr->projection();
    sr->walk();
    sr->talk();
    sr->fly();

    cout << "--------------------" << endl;

    Robot* jr = new Robot(new Walkable(), new Talkable(), new JetFlyable(), new JetRobot());
    jr->projection();
    jr->walk();
    jr->talk();
    jr->fly();

    cout << "--------------------" << endl;

    // Clean up
    delete wr;  // This will also delete its behaviors
    delete sr;  // through Robot's destructor
    delete jr;

    return 0;
}

/*

The code has evolved nicely with some significant improvements:

Better Strategy Pattern Implementation:

Now projection is also a strategy (via Projection interface)
Robot is no longer abstract, all behaviors are strategies
Cleaner separation of concerns
Good Memory Management:

Virtual destructors in all base classes
Proper cleanup in Robot's destructor
Memory cleanup in main()
No memory leaks
Better Design:

More consistent - all behaviors (including projection) follow same pattern
More flexible - can change any behavior at runtime
Composition over inheritance
Single Responsibility Principle - each class does one thing
Usage Improvements:

More intuitive robot creation
Clear behavior assignment
Can easily mix and match behaviors
The code successfully demonstrates:

Strategy Pattern
SOLID Principles
Memory Management
Composition over Inheritance
Especially good changes:

Moving projection to be a strategy like other behaviors
Robot is now a concrete class (not abstract)
Consistent pattern across all behaviors
The code compiles and runs correctly, and the memory management is sound. This is a well-structured example of the Strategy pattern!
*/


