#include <iostream>
#include <memory>

using namespace std;

class A {
public:
    int a;
    A(int a) : a(a) {}
};

template <class T>
class MyUniquePtr {
private:
    T* ptr;  // Raw pointer to heap-allocated memory

public:
    // ==================== CONSTRUCTOR ====================
    // Takes ownership of a raw pointer
    // explicit: prevents implicit conversions from T* to MyUniquePtr<T>
    explicit MyUniquePtr(T* ptr = nullptr) : ptr(ptr) {}

    // ==================== DESTRUCTOR ====================
    // Automatically deletes the managed object when MyUniquePtr goes out of scope
    // This is RAII: Resource Acquisition Is Initialization
    ~MyUniquePtr() {
        if(ptr) delete ptr;
    }

    // ==================== DEREFERENCE OPERATORS ====================
    // operator*: Allows *ptr to access the object (like raw pointers)
    // Returns T& (reference) so you can read AND write the object
    T& operator*() {
        return *ptr;
    }

    // operator->: Allows ptr->member to access object members
    // Returns T* so -> can chain to the actual object members
    T* operator->() {
        return ptr;
    }

    // ==================== COPY CONSTRUCTOR & ASSIGNMENT (DELETED) ====================
    // unique_ptr has EXCLUSIVE ownership - only ONE pointer can own the resource
    // Copy would violate this rule (two owners = undefined behavior)
    // = delete: compiler error if you try to copy
    MyUniquePtr(const MyUniquePtr& other) = delete;
    MyUniquePtr& operator=(const MyUniquePtr& other) = delete;

    // ==================== MOVE CONSTRUCTOR ====================
    // Transfers ownership from 'other' to 'this'
    // MyUniquePtr&& other: rvalue reference (temporary or std::move'd object)
    // noexcept: guarantees no exceptions (STL containers prefer this)
    // After move: other.ptr = nullptr (other no longer owns the resource)
    MyUniquePtr(MyUniquePtr&& other) noexcept : ptr(other.ptr) {
        other.ptr = nullptr;
    }

    // ==================== MOVE ASSIGNMENT OPERATOR ====================
    // Transfers ownership from 'other' to 'this'
    // Returns MyUniquePtr& (lvalue reference) for chaining: a = move(b) = move(c)
    // self-check (this != &other): prevents a = move(a) from deleting itself
    MyUniquePtr& operator=(MyUniquePtr&& other) noexcept {
        if(this != &other) {  // Check if assigning to itself
            if(ptr) delete ptr;  // Delete current resource
            ptr = other.ptr;  // Take ownership
            other.ptr = nullptr;  // Leave 'other' empty
        }
        return *this;  // Return reference for chaining
    }

    // ==================== UTILITY METHODS ====================
    // get(): Returns the raw pointer WITHOUT transferring ownership
    // const: doesn't modify the MyUniquePtr object
    T* get() const {
        return ptr;
    }

    // reset(T* new_ptr): Delete current object and take ownership of new_ptr
    // Similar to calling destructor then constructor
    void reset(T* new_ptr = nullptr) {
        if(ptr) delete ptr;  // Delete old resource
        ptr = new_ptr;  // Point to new resource (or nullptr)
    }

    // release(): Returns raw pointer and releases ownership
    // Caller is now responsible for deleting the pointer
    T* release() {
        T* temp = ptr;
        ptr = nullptr;  // Relinquish ownership
        return temp;
    }

    // explicit operator bool(): Check if pointer is valid
    // explicit: prevents implicit conversion in if statements
    // Allows: if(ptr) { ... }  but NOT: bool b = ptr;
    explicit operator bool() const {
        return ptr != nullptr;
    }
};

int main(){
    // ==================== BASIC USAGE ====================
    MyUniquePtr<int> ptr1(new int(10));  // Create MyUniquePtr owning an int
    MyUniquePtr<A> ptr2(new A(100));     // Create MyUniquePtr owning an A object

    // operator* dereference: access the object
    cout << *ptr1 << endl;  // Output: 10

    // operator-> member access: access members of the object
    cout << ptr2->a << endl;  // Output: 100
    ptr2->a = 56;  // Modify member
    cout << ptr2->a << endl;  // Output: 56

    // ==================== COPY IS DELETED ====================
    // MyUniquePtr<int> ptr3(ptr1);   // COMPILER ERROR: copy ctor deleted
    // MyUniquePtr<int> ptr4 = ptr1;  // COMPILER ERROR: copy assignment deleted
    // Reason: unique_ptr has exclusive ownership

    // ==================== MOVE TRANSFERS OWNERSHIP ====================
    MyUniquePtr<int> ptr3(move(ptr1));  // Move constructor: ownership transfers to ptr3
    MyUniquePtr<A> ptr4 = move(ptr2);   // Move assignment: ownership transfers to ptr4

    // cout << *ptr1 << endl;   // SEGFAULT: ptr1 is now nullptr (released ownership)
    // cout << ptr2->a << endl; // SEGFAULT: ptr2 is now nullptr (released ownership)

    // ptr3 and ptr4 now own the resources
    cout << *ptr3 << endl;      // Output: 10
    cout << ptr4->a << endl;    // Output: 56

    // ==================== UTILITY METHODS ====================
    cout << *(ptr3.get()) << endl;  // get() returns raw pointer, dereference it

    // reset() deletes old and assigns new
    ptr3.reset(new int(999));
    cout << *ptr3 << endl;  // Output: 999

    // release() returns raw pointer and releases ownership
    int* raw = ptr3.release();
    cout << *raw << endl;  // Output: 999
    delete raw;  // Now WE are responsible for deletion

    // ==================== AUTOMATIC CLEANUP ====================
    // When ptr4 goes out of scope, its destructor runs
    // Destructor deletes the managed A object automatically
    // No memory leak!

    return 0;
}
