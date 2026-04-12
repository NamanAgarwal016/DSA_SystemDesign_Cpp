#include <iostream>
#include <mutex>
#include <thread>
#include <future>

using namespace std;

// ============================================================================
// MULTITHREADING BASICS IN C++
// ============================================================================

// Thread function: runs concurrently
void print(string msg, int count) {
    int i = 0;
    while(count-- > 0) {
        i++;
        cout << msg << " " << i << endl;
    }
    cout << "func thread id: " << this_thread::get_id() << endl;
}

// Passing by reference: use std::ref
void func(int& count) {
    cout << "Inside thread: count = " << count << endl;
    count++;
    cout << "Inside thread: count = " << count << endl;
}

// Async function: returns value via future
int asyncFunc(int value) {
    cout << "Async thread id: " << this_thread::get_id() << endl;
    cout << "Inside async func" << endl;
    return value;
}

int main(){
    // ============================================================================
    // 1. CREATING THREADS
    // ============================================================================
    thread t1(print, "hello", 2);       // Constructor: function + args
    thread t2 {print, "bye", 2};        // Alternative syntax with {}

    // ============================================================================
    // 2. JOINING THREADS
    // ============================================================================
    t1.join();                          // Wait for t1 to finish
    t2.join();                          // Wait for t2 to finish
    cout << "main thread reached here" << endl;

    // ============================================================================
    // 3. PASSING BY REFERENCE
    // ============================================================================
    int count = 2;
    thread t3(func, ref(count));        // Use std::ref for references
    t3.join();
    cout << "Inside main: count = " << count << endl;       // Modified by thread

    // ============================================================================
    // 4. THREAD IDENTIFIERS
    // ============================================================================
    cout << "main id: " << this_thread::get_id() << endl;   // Current thread ID

    // ============================================================================
    // 5. ASYNC & FUTURE (Non-blocking execution)
    // ============================================================================
    future<int> fn = async(launch::async, asyncFunc, 200);  // Launch async task
    cout << "asyncFunc returns: " << fn.get() << endl;       // Get result (blocks until ready)
    // launch::deferred: Run when get() called, in same thread

    return 0;
}