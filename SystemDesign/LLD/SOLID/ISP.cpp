#include <iostream>
using namespace std;

// ISP Followed

// Separate interface for 2D shapes
class Shape2d {
    virtual void area() = 0;
};

// Separate interface for 3D shapes
class Shape3d {
public:    
    virtual void area() = 0;
    virtual void vol() = 0;
};

class Square: public Shape2d {
private:
    int a;
public:
    Square(int a) : a(a) {}
    void area() override {
        cout << "Square Area: " << (a*a) << endl;
    }
};

class Rectangle: public Shape2d {
private:
    int l, w;
public:
    Rectangle(int l, int w) : l(l), w(w) {}
    void area() override {
        cout << "Rectangle Area: " << (l*w) << endl;
    }
};

class Cube: public Shape3d {
private:
    int a;
public:
    Cube(int a) : a(a) {}
    void area() override {
        cout << "Cube Area: " << (6*(a*a)) << endl;
    }
    void vol() override {
        cout << "Cube Volume: " << (a*a*a) << endl;
    }
};

int main(){
    Shape2d *sq = new Square(5);
    sq->area();

    Shape2d *rect = new Rectangle(5, 10);
    rect->area();
    
    Shape3d *cube = new Cube(5);
    cube->area();
    cube->vol();
    

    return 0;
}