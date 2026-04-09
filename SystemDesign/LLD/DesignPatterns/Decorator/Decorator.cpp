#include <iostream>
#include <string>
using namespace std;

// Component Interface: defines a common interface for Mario and all power-up decorators.
class ICharacter {
public:
    virtual void getAbilities() = 0;
    virtual ~ICharacter(){
        cout << "Deleting ICharacter" << endl;
    }
};

// Concrete Component: Basic Mario character with no power-ups.
class Mario : public ICharacter {
public:
    void getAbilities() override {
        cout << "Mario has been spawned!!" << endl;
    }
    ~Mario(){
        cout << "Deleting Mario" << endl;
    }
};

// Abstract Decorator: IDecorator "is-a" ICharatcer and "has-a" ICharacter.
class IDecorator : public ICharacter {
protected:
    ICharacter* ch;
public:
    IDecorator(ICharacter* ch) : ch(ch) {}
    virtual ~IDecorator(){
        delete ch;
        ch = nullptr;
        cout << "Deleting IDecorator" << endl;
    }
};

// Concrete Decorator: Height-Increasing Power-Up.
class HeightUpDecorator : public IDecorator {
public:
    HeightUpDecorator(ICharacter* ch) : IDecorator(ch) {}
    void getAbilities() override {
        ch->getAbilities();
        cout << "Now He's a Bigger Mario!!" << endl;
    }
    ~HeightUpDecorator(){
        cout << "Deleting HeightUpDecorator" << endl;
    }
};

// Concrete Decorator: Gun Shooting Power-Up.
class GunPowerDecorator : public IDecorator {
public:
    GunPowerDecorator(ICharacter* ch) : IDecorator(ch) {}
    void getAbilities() override {
        ch->getAbilities();
        cout << "Now He has a Gun Power!!" << endl;
    }
    ~GunPowerDecorator(){
        cout << "Deleting GunPowerDecorator" << endl;
    }
};

int main(){

    // ICharacter* mario = new Mario();
    // mario->getAbilities();

    // // Let's decorate him with powers
    // mario = new GunPowerDecorator(new HeightUpDecorator(mario));
    // mario->getAbilities();

    // all at once
    ICharacter* mario = new GunPowerDecorator(new HeightUpDecorator(new Mario()));
    mario->getAbilities();

    delete mario;
    mario = nullptr;
    return 0;
}



/*
Destructor call flow:

Step-by-step destruction:

1
~GunPowerDecorator() called
Prints: "Deleting GunPowerDecorator"
Then calls ~IDecorator() (base class destructor)

2
~IDecorator() called (inside GunPowerDecorator's base)
Calls delete ch; → deletes the next layer (HeightUpDecorator)
Before that, ~HeightUpDecorator() is triggered

3
~HeightUpDecorator() called
Prints: "Deleting HeightUpDecorator"
Then calls ~IDecorator() (base class destructor)

4
~IDecorator() called again (inside HeightUpDecorator's base)
Calls delete ch; → deletes the innermost layer (Mario)
Before that, ~Mario() is triggered

5
~Mario() called
Prints: "Deleting Mario"
Then calls ~ICharacter() (base class destructor)

6
~ICharacter() called (Mario's base)
Prints: "Deleting ICharacter"

7
Back to step 4 ~IDecorator() (HeightUpDecorator's base)
Prints: "Deleting IDecorator"
Then calls ~ICharacter() (base class destructor)

8
~ICharacter() called (IDecorator's base)
Prints: "Deleting ICharacter"

9
Back to step 2 ~IDecorator() (GunPowerDecorator's base)
Prints: "Deleting IDecorator"
Then calls ~ICharacter() (base class destructor)

10.
~ICharacter() called (IDecorator's base)
Prints: "Deleting ICharacter"
*/