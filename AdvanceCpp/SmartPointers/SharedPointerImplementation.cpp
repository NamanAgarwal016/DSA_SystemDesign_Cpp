#include <iostream>
#include <utility>
#include <memory>
    
using namespace std;

// ==================== SHARED POINTER IMPLEMENTATION ====================
// Custom shared_ptr: Manages shared ownership of heap-allocated objects
// - Uses reference counting for automatic memory management
// - Multiple shared_ptrs can own the same resource
// - Resource deleted only when last shared_ptr is destroyed
// - Thread-unsafe (like std::shared_ptr without atomic)

template <class T>
class MySharedPtr {
private:
    T* ptr;      // Raw pointer to the managed heap object
    int* count;  // Pointer to reference count (shared among copies)

    // ==================== HELPER FUNCTIONS ====================
    // Increment reference count (called when new owner is added)
    void incrementCntr() {
        if (count) (*count)++;
    }

    // Decrement reference count (called when owner is removed)
    // If count reaches 0, delete the resource and count
    void decrementCntr() {
        if (count) {
            (*count)--;
            if (*count == 0) {
                delete ptr;     // Delete managed object
                delete count;   // Delete reference count
                ptr = nullptr;
                count = nullptr;
            }
        }
    }

public:
    // ==================== CONSTRUCTOR ====================
    // Default constructor: Takes ownership of raw pointer
    // Initializes reference count to 1
    MySharedPtr(T* ptr = nullptr) : ptr(ptr), count(new int(1)) {}

    // ==================== COPY CONSTRUCTOR ====================
    // Creates shared ownership: points to same resource, increments count
    // noexcept: guarantees no exceptions (STL preference)
    MySharedPtr(const MySharedPtr& other) noexcept {
        ptr = other.ptr;      // Share the pointer
        count = other.count;  // Share the count
        incrementCntr();      // New owner: count++
    }

    // ==================== COPY ASSIGNMENT OPERATOR ====================
    // Transfers ownership from 'other' to 'this'
    // Decrements current count, increments new count
    MySharedPtr& operator=(const MySharedPtr& other) noexcept {
        if (this != &other) {  // Self-assignment check
            decrementCntr();   // Release current ownership
            ptr = other.ptr;   // Take new ownership
            count = other.count;
            incrementCntr();   // Increment for new ownership
        }
        return *this;  // Enable chaining: a = b = c;
    }

    // ==================== DEREFERENCE OPERATORS ====================
    // operator*: Access the managed object (read/write)
    T& operator*() {
        return *ptr;
    }

    // operator->: Access members of managed object
    T* operator->() {
        return ptr;
    }

    // ==================== UTILITY METHODS ====================
    // use_count(): Returns current reference count
    // -1 if count is nullptr (shouldn't happen in normal use)
    int use_count() {
        if (count) return *count;
        return -1;
    }

    // reset(): Release current resource and optionally take new ownership
    // If new pointer provided, starts fresh count=1
    void reset(T* p = nullptr) {
        decrementCntr();  // Release current
        ptr = p;
        if (p) {
            count = new int(1);  // Fresh count for new resource
        } else {
            count = nullptr;
        }
    }

    // ==================== MOVE CONSTRUCTOR ====================
    // Transfers ownership from 'other' (efficient, no count changes)
    // 'other' left in empty state (ptr/count = nullptr)
    MySharedPtr(MySharedPtr&& other) {
        ptr = other.ptr;
        count = other.count;
        other.ptr = nullptr;    // 'other' no longer owns
        other.count = nullptr;
    }

    // ==================== MOVE ASSIGNMENT OPERATOR ====================
    // Transfers ownership from 'other' to 'this'
    // Releases current ownership first
    MySharedPtr& operator=(MySharedPtr&& other) {
        if (this != &other) {  // Self-move protection
            decrementCntr();   // Release current
            ptr = other.ptr;   // Take ownership
            count = other.count;
            other.ptr = nullptr;   // Nullify 'other'
            other.count = nullptr;
        }
        return *this;
    }

    // ==================== DESTRUCTOR ====================
    // Decrements count; deletes resource if count == 0
    // RAII: Automatic cleanup when shared_ptr goes out of scope
    ~MySharedPtr() {
        decrementCntr();
    }
};

// ==================== TEST CLASS ====================
class A {
public:
    int a;
    A(int a) : a(a) {}  // Constructor for testing
};

int main() {
    cout << "=== SHARED POINTER DEMO ===" << endl;

    // ==================== BASIC SHARED OWNERSHIP ====================
    MySharedPtr<int> p(new int(56));  // count = 1
    MySharedPtr<int> p1(p);           // copy ctor: count = 2
    MySharedPtr<int> p2;              // default: ptr=nullptr, count=nullptr
    p2 = p;                           // copy assign: count = 3

    // Dereference: all point to same value
    cout << *p << " " << *p1 << " " << *p2 << endl;  //      56 56 56

    // Reference count: 3 owners
    cout << p.use_count() << " " << p1.use_count() << " " << p2.use_count() << endl;  // 3 3 3

    // ==================== RESET: RELEASE OWNERSHIP ====================
    p.reset();  // p releases ownership: count = 2, p now empty
    cout << p1.use_count() << endl;  // 2 (p, p1, p2 still share)

    // ==================== MOVE SEMANTICS ====================
    MySharedPtr<A> p3(new A(100));  // count = 1
    MySharedPtr<A> p4(move(p3));    // move ctor: p4 owns, p3 empty

    // Access member via ->
    cout << p4->a << endl;  // 100
    p4->a = 200;            // Modify
    cout << p4->a << endl;  // 200

    // Move assignment: transfer to p5
    MySharedPtr<A> p5 = move(p4);  // p5 owns, p4 empty
    cout << p5->a << endl;         // 200
    cout << p5.use_count() << endl;  // 1

    // ==================== AUTOMATIC CLEANUP ====================
    // When main ends, destructors run:
    // p5: count=1 -> 0, delete A(200) and count
    // p4: empty, does nothing
    // p3: empty, does nothing
    // p2: count=2 -> 1, does nothing
    // p1: count=1 -> 0, delete int(56) and count
    // p: empty, does nothing

    cout << "Program ends - memory cleaned up automatically!" << endl;
    return 0;
}
