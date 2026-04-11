/*

// all in once

int *ptr = (int*)malloc(sizeof(int));
int *ptr = (int*)calloc(5, sizeof(int));
free(ptr);

int *ptr = new int(10);
delete ptr;
ptr = NULL;
int *arr = new int[5];
arr[2] = 3;
delete[] arr;
arr = NULL;

unique_ptr<int> ptr(new int(10));
unique_ptr<int> ptr = make_unique<int>(10);
cout << *ptr <<endl;

shared_ptr<int> ptr(new int(10));
shared_ptr<int> ptr = make_shared<int>(10);

weak_ptr<int> wptr = ptr

================================================================================
                    MEMORY MANAGEMENT IN C++ - COMPLETE GUIDE
================================================================================

MEMORY REGIONS IN C++:
1. STACK: Fast, automatic cleanup, limited size, LIFO (Last In First Out)
   - Local variables, function parameters
   - Automatically freed when scope ends
   - No manual handling needed

2. HEAP: Slower, manual/smart pointer cleanup, large size
   - Dynamic allocation using new/malloc
   - Must be freed manually or using smart pointers
   - Can cause memory leaks if not managed properly

================================================================================
                          MEMORY ALLOCATION METHODS
================================================================================

A. C-STYLE MEMORY MANAGEMENT (malloc/calloc/free)
   - Inherited from C
   - Returns void* (must cast)
   - No constructors/destructors called
   - Error-prone, not recommended for modern C++

B. C++-STYLE MEMORY MANAGEMENT (new/delete)
   - Modern approach
   - Calls constructors/destructors
   - Better type safety
   - Still prone to memory leaks if not careful

C. SMART POINTERS (unique_ptr/shared_ptr)
   - Modern C++ best practice
   - RAII - automatic cleanup
   - No manual delete needed
   - Prevents memory leaks

================================================================================
*/

#include <iostream>
#include <cstdlib>      // malloc, calloc, free
#include <memory>       // unique_ptr, shared_ptr
#include <cstring>      // memset

using namespace std;

// ============================================================================
// SECTION 1: C-STYLE MEMORY MANAGEMENT (malloc/calloc/free)
// ============================================================================
void c_style_memory_demo() {
    cout << "\n=== C-STYLE MEMORY MANAGEMENT ===" << endl;

    // 1. MALLOC - Manual Allocation
    // malloc(bytes) - allocates raw memory, uninitialized
    // Returns void*, must be cast to desired type
    cout << "\n1. MALLOC:" << endl;
    int *ptr1 = (int*) malloc(sizeof(int));      // allocate 4 bytes for 1 int
    if (ptr1 != NULL) {
        *ptr1 = 100;
        cout << "   ptr1 = " << *ptr1 << endl;
        free(ptr1);                               // MUST free manually
        ptr1 = NULL;                              // good practice: set to NULL
    }

    // 2. CALLOC - Allocation with Initialization
    // calloc(num_blocks, block_size) - allocates and initializes to 0
    cout << "\n2. CALLOC:" << endl;
    int *arr = (int*) calloc(5, sizeof(int));    // allocate array of 5 ints, init to 0
    if (arr != NULL) {
        cout << "   Array after calloc (initialized to 0): ";
        for (int i = 0; i < 5; i++) {
            cout << arr[i] << " ";
        }
        cout << endl;
        free(arr);                                // MUST free manually
        arr = NULL;
    }

    // 3. REALLOC - Resize allocated memory (not shown here, rarely used)
    cout << "\n3. Why avoid C-style malloc/calloc:" << endl;
    cout << "   - Returns void* (needs explicit cast)" << endl;
    cout << "   - Constructors NOT called (objects not initialized)" << endl;
    cout << "   - Easy to forget free() -> memory leak" << endl;
    cout << "   - No exception safety" << endl;
}

// ============================================================================
// SECTION 2: C++-STYLE MEMORY MANAGEMENT (new/delete)
// ============================================================================
void cpp_style_memory_demo() {
    cout << "\n=== C++-STYLE MEMORY MANAGEMENT ===" << endl;

    // 1. NEW - Allocate single object
    // new Type - allocates memory and calls constructor
    cout << "\n1. NEW (single object):" << endl;
    int *ptr = new int(50);                       // allocate and initialize to 50
    cout << "   *ptr = " << *ptr << endl;
    delete ptr;                                   // MUST delete manually
    ptr = NULL;                                   // good practice: set to NULL
    // if you forget delete, memory LEAKS

    // 2. NEW with array
    // new Type[size] - allocates array on heap
    cout << "\n2. NEW (array):" << endl;
    int *arr = new int[5];                        // allocate array of 5 ints on heap
    arr[0] = 10;
    arr[1] = 20;
    arr[2] = 30;
    arr[3] = 40;
    arr[4] = 50;
    cout << "   Array: ";
    for (int i = 0; i < 5; i++) {
        cout << arr[i] << " ";
    }
    cout << endl;
    delete[] arr;                                 // IMPORTANT: delete[] for arrays
    arr = NULL;
    // Forgetting [] causes undefined behavior and memory leak

    // 3. Memory leak example (what NOT to do)
    cout << "\n3. Memory Leak Example (DON'T DO THIS):" << endl;
    int *leak = new int(100);
    // forgot to delete leak -> MEMORY LEAK!
    cout << "   If we don't delete, memory is lost forever" << endl;

    // 4. Dangling pointer example (what NOT to do)
    cout << "\n4. Dangling Pointer (DON'T DO THIS):" << endl;
    int *dangle = new int(200);
    delete dangle;
    // dangle now points to freed memory -> UNDEFINED BEHAVIOR
    // cout << *dangle;  // CRASH!
    cout << "   After delete, pointer becomes dangling; accessing it causes crash" << endl;
}

// ============================================================================
// SECTION 3: SMART POINTERS (RAII - Resource Acquisition Is Initialization)
// ============================================================================
void smart_pointer_demo() {
    cout << "\n=== SMART POINTERS (MODERN C++ - BEST PRACTICE) ===" << endl;

    // 1. UNIQUE_PTR - Exclusive ownership
    // unique_ptr<T> - only one pointer can own the resource
    // Automatically deletes when out of scope
    cout << "\n1. UNIQUE_PTR (exclusive ownership):" << endl;
    {
        unique_ptr<int> u1(new int(100));         // allocate
        cout << "   u1 = " << *u1 << endl;
        // u1 automatically deleted here (scope ends)
    }
    cout << "   u1 automatically deleted (no manual delete needed)" << endl;

    // 2. UNIQUE_PTR with make_unique (preferred way)
    cout << "\n2. UNIQUE_PTR with make_unique (RECOMMENDED):" << endl;
    {
        auto u2 = make_unique<int>(200);
        cout << "   u2 = " << *u2 << endl;
    }
    cout << "   u2 automatically deleted" << endl;

    // 3. SHARED_PTR - Shared ownership
    // shared_ptr<T> - multiple pointers can own the resource
    // Reference counting: deleted only when last owner is destroyed
    cout << "\n3. SHARED_PTR (shared ownership with reference counting):" << endl;
    {
        shared_ptr<int> s1 = make_shared<int>(300);
        cout << "   s1 = " << *s1 << ", use_count = " << s1.use_count() << endl;

        {
            shared_ptr<int> s2 = s1;                // s1 and s2 share ownership
            cout << "   s2 = s1; use_count = " << s1.use_count() << endl;
        }
        // s2 goes out of scope, but s1 still owns it
        cout << "   After s2 goes out of scope, use_count = " << s1.use_count() << endl;
    }
    cout << "   After s1 goes out of scope, memory is deleted" << endl;

    // 4. WEAK_PTR - Non-owning reference to shared_ptr
    // weak_ptr<T> - observes but doesn't own
    // Prevents circular reference problems
    cout << "\n4. WEAK_PTR (non-owning observer):" << endl;
    {
        auto sp = make_shared<int>(400);
        weak_ptr<int> wp = sp;
        cout << "   weak_ptr created, use_count = " << sp.use_count() << endl;
        if (auto shared = wp.lock()) {           // lock() to use weak_ptr
            cout << "   *shared = " << *shared << endl;
        }
    }
    cout << "   weak_ptr doesn't prevent deletion" << endl;
}

// ============================================================================
// SECTION 4: PRACTICAL COMPARISONS & BEST PRACTICES
// ============================================================================
void comparison_and_best_practices() {
    cout << "\n=== COMPARISON & BEST PRACTICES ===" << endl;

    cout << "\nMALLOC vs NEW vs SMART POINTERS:" << endl;
    cout << "┌─────────────────────────────────────────────────────────────┐" << endl;
    cout << "│ MALLOC/CALLOC (C-style)                                     │" << endl;
    cout << "│ - No constructor/destructor called                          │" << endl;
    cout << "│ - Returns void* (needs cast)                                │" << endl;
    cout << "│ - Needs manual free()                                       │" << endl;
    cout << "│ - Error-prone, NOT recommended for C++                      │" << endl;
    cout << "├─────────────────────────────────────────────────────────────┤" << endl;
    cout << "│ NEW/DELETE (C++-style)                                      │" << endl;
    cout << "│ - Constructors/destructors called                           │" << endl;
    cout << "│ - Type-safe (returns correct type)                          │" << endl;
    cout << "│ - Needs manual delete (easy to forget)                      │" << endl;
    cout << "│ - Still error-prone without RAII                            │" << endl;
    cout << "├─────────────────────────────────────────────────────────────┤" << endl;
    cout << "│ SMART POINTERS (Modern C++ - PREFERRED)                     │" << endl;
    cout << "│ - Automatic cleanup via RAII                                │" << endl;
    cout << "│ - Type-safe and exception-safe                              │" << endl;
    cout << "│ - No manual delete needed                                   │" << endl;
    cout << "│ - Zero runtime overhead (optimized by compiler)             │" << endl;
    cout << "│ - Prevents memory leaks and dangling pointers               │" << endl;
    cout << "└─────────────────────────────────────────────────────────────┘" << endl;

    cout << "\nBEST PRACTICES:" << endl;
    cout << "1. Use unique_ptr<T> for exclusive ownership" << endl;
    cout << "2. Use shared_ptr<T> only when truly shared (rare)" << endl;
    cout << "3. Use make_unique<T>() / make_shared<T>() to create  them" << endl;
    cout << "4. Use weak_ptr<T> to break circular references" << endl;
    cout << "5. Avoid new/delete entirely in modern C++" << endl;
    cout << "6. Use stack allocation when possible (no manual cleanup needed)" << endl;
    cout << "7. NEVER use malloc/calloc in modern C++ unless interfacing with C" << endl;
}

// ============================================================================
// MAIN FUNCTION
// ============================================================================
int main() {
    cout << "\n╔════════════════════════════════════════════════════════════╗" << endl;
    cout << "║     C++ MEMORY MANAGEMENT - COMPREHENSIVE GUIDE            ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════╝" << endl;

    // Run all demonstrations
    c_style_memory_demo();
    cpp_style_memory_demo();
    smart_pointer_demo();
    comparison_and_best_practices();

    cout << "\n╔══════════════════════════════════════════════════════════╗" << endl;
    cout << "║                    KEY TAKEAWAY                            ║" << endl;
    cout << "║  USE SMART POINTERS (unique_ptr/shared_ptr) - NO LEAKS!    ║" << endl;
    cout << "╚════════════════════════════════════════════════════════════╝" << endl;

    return 0;
}






