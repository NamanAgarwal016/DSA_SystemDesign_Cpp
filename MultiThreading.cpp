#include <iostream>
#include <mutex>
#include <thread>
using namespace std;


void print(string msg, int count) {
    int i = 0;
    while(count-- > 0) {
        i++;
        cout << msg << " " << i << endl;
    }
}

int main(){
    thread t1(print, "hello", 5);
    // t1.join();
    thread t2(print, "bye", 5);
    t2.join();
    // print("hello", 5);
    cout << "main thread ends" << endl;
    return 0;
}