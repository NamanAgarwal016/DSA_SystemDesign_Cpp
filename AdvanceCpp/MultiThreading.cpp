#include <iostream>
#include <mutex>
#include <thread>
#include <future>
#include <condition_variable>

using namespace std;

// ============================================================================
// C++ MULTITHREADING - INTERVIEW PREP GUIDE
// ============================================================================
// Multithreading: Running multiple threads concurrently for better performance.
// Key concepts: Threads, synchronization, async programming.

// ============================================================================
// 1. BASIC THREAD OPERATIONS
// ============================================================================

// Thread function: What runs in a separate thread
void printMessage(string msg, int count) {
    for(int i = 1; i <= count; i++) {
        cout << msg << " " << i << endl;
    }
    cout << "Thread ID: " << this_thread::get_id() << endl;
}

// Passing data by reference to threads
void incrementCounter(int& counter) {
    counter++;
    cout << "Counter in thread: " << counter << endl;
}

int main() {
    cout << "\n=== 1. CREATING AND JOINING THREADS ===" << endl;

    // Create threads: Pass function + arguments
    thread t1(printMessage, "Hello", 3);
    thread t2(printMessage, "World", 2);

    // Join: Wait for threads to finish (important!)
    t1.join();
    t2.join();
    cout << "Both threads finished" << endl;

    cout << "\n=== 2. PASSING BY REFERENCE ===" << endl;

    int counter = 5;
    thread t3(incrementCounter, ref(counter));  // Use std::ref for references
    t3.join();
    cout << "Counter in main: " << counter << endl;  // Modified by thread

    cout << "\n=== 3. THREAD IDENTIFIERS ===" << endl;

    cout << "Main thread ID: " << this_thread::get_id() << endl;

    // ============================================================================
    // 2. SYNCHRONIZATION - MUTEX
    // ============================================================================
    cout << "\n=== 4. MUTEX - PREVENTING RACE CONDITIONS ===" << endl;

    mutex mtx;

    // BAD: Manual lock/unlock (error-prone)
    // mtx.lock();  // Can forget to unlock!
    // // do work
    // mtx.unlock();

    // GOOD: RAII with lock_guard (automatic unlock)
    {
        lock_guard<mutex> guard(mtx);
        cout << "Protected section with lock_guard" << endl;
        // Automatically unlocks when scope ends
    }

    // Thread function using mutex
    auto workerWithMutex = [](mutex& m) {
        lock_guard<mutex> lock(m);
        cout << "Worker thread has the lock" << endl;
        this_thread::sleep_for(chrono::seconds(2));
        // Lock released automatically
    };

    thread t4(workerWithMutex, ref(mtx));
    this_thread::sleep_for(chrono::seconds(1));  // Let thread start

    // unique_lock: More flexible (can lock/unlock manually)
    unique_lock<mutex> ulock(mtx);
    cout << "Main thread got the lock back" << endl;
    ulock.unlock();  // Manual unlock
    t4.join();

    // ============================================================================
    // 3. CONDITION VARIABLES - THREAD COMMUNICATION
    // ============================================================================
    cout << "\n=== 5. CONDITION VARIABLES - THREAD SYNCHRONIZATION ===" << endl;

    mutex cvMutex;
    condition_variable cv;

    // Thread that waits for notification
    auto waitingThread = [](mutex& m, condition_variable& c) {
        unique_lock<mutex> lock(m);
        cout << "Waiting thread: Going to sleep..." << endl;
        c.wait(lock);  // Releases lock and waits
        cout << "Waiting thread: Woke up!" << endl;
    };

    thread t5(waitingThread, ref(cvMutex), ref(cv));
    this_thread::sleep_for(chrono::seconds(2));  // Let waiting thread start

    // Notify the waiting thread
    {
        lock_guard<mutex> lock(cvMutex);
        cout << "Main thread: Notifying..." << endl;
        cv.notify_one();  // Wake up one waiting thread
    }

    t5.join();

    // ============================================================================
    // 4. ASYNC PROGRAMMING - FUTURE & PROMISE
    // ============================================================================
    cout << "\n=== 6. ASYNC & FUTURE - NON-BLOCKING TASKS ===" << endl;

    // Async function
    auto asyncTask = [](int value) -> int {
        cout << "Async task running in thread: " << this_thread::get_id() << endl;
        this_thread::sleep_for(chrono::seconds(1));
        return value * 2;
    };

    // Launch async task
    future<int> result = async(launch::async, asyncTask, 10);
    cout << "Main thread continues while async runs..." << endl;

    // Get result (blocks until ready)
    int finalResult = result.get();
    cout << "Async result: " << finalResult << endl;

    // ============================================================================
    // 5. HARDWARE CONCURRENCY
    // ============================================================================
    cout << "\n=== 7. HARDWARE CONCURRENCY ===" << endl;

    unsigned int cores = thread::hardware_concurrency();
    cout << "Available hardware threads: " << cores << endl;
    cout << "Use this to decide how many threads to create" << endl;

    // ============================================================================
    // SUMMARY
    // ============================================================================
    cout << "\n=== MULTITHREADING KEY POINTS ===" << endl;
    cout << "• Always join() or detach() threads" << endl;
    cout << "• Use std::ref() for passing references" << endl;
    cout << "• Mutex prevents race conditions" << endl;
    cout << "• lock_guard: Simple, automatic" << endl;
    cout << "• unique_lock: Flexible, manual control" << endl;
    cout << "• Condition variables: Thread communication" << endl;
    cout << "• Async: Non-blocking tasks with futures" << endl;
    cout << "• Check hardware_concurrency() for optimal thread count" << endl;

    return 0;
}