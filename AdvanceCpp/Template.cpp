/*

- complier resolves the template's placeholder during complie time only
- complier will make multiple versions acc to need.

Types:
1. funtion template : generic fucn 
2. class template   
*/


#include <iostream>

using namespace std;

// Funciton template:
template <class X>      // alt way: template <typename X>
// template <class X, class Y>     // multiple place holders can be there
X big(X a, X b) {
    if(a > b) return a;
    else return b;
}


// class template:
template <class X>          // we have to write this everytime we are using it for func/class template
class Array {
    private:
        X arr[10];
        int sz;
    public:
        Array() : sz(10){}
        void insert(int idx, X val) {
            arr[idx] = val;
        }
        X getVal(int idx) {
            return arr[idx];
        }
};

int main(){
    cout << big(3, 4) << endl;          // placehokder decided autoamtically
    cout << big(3.3, 2.4) << endl;

    Array<int> o1;                       // placehokder need to be given
    Array<float> o2;            

    o1.insert(0, 1);
    cout << o1.getVal(0) << endl;

    o2.insert(0, 1.2);
    cout << o2.getVal(0) << endl;
}
