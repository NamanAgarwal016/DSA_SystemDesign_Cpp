/*
Smart pointers:
- Template classes having a raw pointer.
- when obj is made, address is passed & raw pointer starts pointing to that address
- in destructor of this class, we delete the raw pointer, hence no headache of memory leak

In technical correct terms:
- Smart pointers are RAII** wrappers around dynamically allocated objects/memory.
- They hold ownership semantics and automatically delete the managed object in their destructor, avoiding manual delete.

RAII**
RAII means "Resource Acquisition Is Initialization."
When an object is created, it acquires a resource (memory, file handle, socket, lock, etc.).
When that object is destroyed, its destructor releases the resource automatically.
Ownership and cleanup are tied to object lifetime.
Ex: unique_ptr:
constructor acquires ownership of heap memory
destructor deletes the memory

Types:
1. unique_ptr
2. shared_ptr   : https://youtu.be/P-QvI2oxrZ8
3. weak_ptr     : https://youtu.be/NXwb2j34BtA

unique_ptr:
owns a single object
not copyable, only movable
deletes the object when it goes out of scope

shared_ptr:
owns an object with shared ownership
uses reference counting
deletes the object only when the last shared_ptr reference is gone

weak_ptr:
does not own the object
observes an object managed by shared_ptr
does not contribute to reference count

*/

#include <iostream>
#include <bits/stdc++.h>
using namespace std;

int main() {
    int a = 10;     // mem allocated in stack

    int *p = &a; 
    cout << "Address of a: " << p << endl;
    cout << *p << endl;
    // delete p; // invalid because a was not allocated with new. 
                // Do not delete any mem aloocated from stack, only allocated from heap needs to be freed manually
    

    int *p1 = new int(20);
    cout << *p1 << endl;
    // delete p1;
    // cout << *p1 << endl; // p1 becomes a dangling pointer. Dereferencing or writing through it is undefined behavior.
    // *p1 = 100;
    // p1 = nullptr;           // now p1 is not a dangling pointer


    ///////////////////////////////////////////////////// Unique Ptr //////////////////////////////////////////////////////////////////

    // unique_ptr<int> q(&a); //invalid because unique_ptr takes ownership and will delete a when it goes out of scope
                              // Do not wrap a stack address in unique_ptr

    unique_ptr<int> q = make_unique<int>(30);       // int *q = new int(30); similar to this
    cout << *q << endl;                             // auto q = make_unique<int>(30); auto more easy & used

    unique_ptr<int> r(new int(40));                 // 2nd way of decalartion on unique_ptr
    cout << *r << endl;

    unique_ptr<int> s;                              // 3rd way of decalartion on unique_ptr, currently pointing to nullptr
    s.reset(new int(50)); 
    cout << *s << endl;
    s.reset();                  // fist memory is deleted/released and then now it points to nullptr
    s.reset(new int(60));       // fist memory is deleted/released and then now it points to new mem having 60
    cout << *s << endl;


    unique_ptr<int> t(new int(70));     
    // unique_ptr<int> t1 = t;      // copy assignemnt operator Not allowed, as it's unique, same address can't be pointed by another pointer
    // unique_ptr<int> t1(t);       // copy constructor Not allowed
    unique_ptr<int> t1 = move(t);   // unique_ptr is not copyable, but movable, ownership transfer is allowed. t -> nullptr


    ///////////////////////////////////////////////////// Shared Ptr //////////////////////////////////////////////////////////////////

    shared_ptr<int> m(new int(80));     // mem pointed by shared_ptr will be released only when all copies of shared_ptr is destroyed
    shared_ptr<int> n;
    n = m;                              // copy assignemtn works here, now pointing to same resource
    // n = move(m);                     // now here it puts nullptr in raw pointer of m
    cout << m.use_count() << endl;      // 2 -> #pointers poiting to thsi location
    cout << n.use_count() << endl;      // 2
    cout << m.get() << endl;            // 0xf31de0, to get address
    cout << n.get() << endl;            // 0xf31de0

    m.reset();
    cout << m.use_count() << endl;      // 0
    cout << n.use_count() << endl;      // 1
    cout << m.get() << endl;            // 0, nullptr
    cout << n.get() << endl;            // 0xf31de0

    auto k = make_shared<int>(100);
    cout << *k << endl;


    ///////////////////////////////////////////////////// Weak Ptr //////////////////////////////////////////////////////////////////

    shared_ptr<int> d(new int(110));     
    weak_ptr<int> e;                    // weak ptr is created as a copy of shared pte
    e = d;                              // copy assignment works here, now pointing to same resource
    cout << d.use_count() << endl;      // 1 -> #pointers pointing to this location
    cout << e.use_count() << endl;      // 1    weak pointers don't add upto refernece counts
    cout << d.get() << endl;            // 0xf31de0
    // cout << e.get() << endl;         // No such mtd for weak pointer

    d.reset();
    cout << d.use_count() << endl;      // 0 Memory will be released as well, as ref count = 0 
    cout << e.use_count() << endl;      // 0 
    cout << d.get() << endl;            // 0, nullptr

    /*
    Use case of weak pointers: cyclic dependency causing memory leaks bcoz of shared ptr:
    The video explains that cyclic dependency causes memory leaks because of how the reference count works in C++ shared pointers. 
    When two objects (like class A and class B) hold shared pointers to each other, their reference counts never drop to zero. (22:00 - 25:15)

    Specifically, the speaker notes that:

    Even when the original objects go out of scope, the memory location's reference count rema  ins at one because each object is still being pointed to by the other object's internal pointer. 
    
    Because the reference count never reaches zero, the destructors are never called and the memory is never automatically released, leading to a permanent memory leak.
    
    The speaker demonstrates that this can be resolved by using weak pointers instead, which do not participate in increasing the reference count, allowing the objects to be properly destroyed when their scope ends.
    */

    return 0;
}