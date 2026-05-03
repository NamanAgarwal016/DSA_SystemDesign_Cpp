#include <iostream>
#include <memory>

using namespace std;

template <class T>
class MyStack {
private:
    int topIdx;
    static constexpr int sz = 100;
    T st[sz]; // fixed-size backing array
public:
    MyStack() : topIdx(-1) {
        cout << "\nStack Implementation Using Array" << endl;
        cout << "################################" << endl;
    }

    void push(const T& x) {
        if (full()) {
            cout << "stack is already full, can't push more" << endl;
            return;
        }
        st[++topIdx] = x;
    }

    void pop() {
        if (empty()) {
            cout << "stack is already empty, can't pop" << endl;
            return;
        }
        --topIdx;
    }

    T top() const {
        if (empty()) {
            cout << "stack is empty, can't fetch top" << endl;
            return T{};
        }
        return st[topIdx];
    }

    int size() const {
        return topIdx + 1;
    }

    bool empty() const {
        return topIdx < 0;
    }

    bool full() const {
        return size() == sz;
    }
};

template <class T>
class MyQueue {
private:
    int frontIdx;
    int lastIdx;
    int currSize;
    static constexpr int sz = 100;
    T q[sz];
public:
    MyQueue() : frontIdx(-1), lastIdx(-1), currSize(0) {
        cout << "\nQueue Implementation Using Array" << endl;
        cout << "################################" << endl;
    }

    void push(const T& x) {
        if (full()) {
            cout << "queue is full, can't push" << endl;
            return;
        }
        if (empty()) {
            frontIdx = lastIdx = 0;
        } else {
            lastIdx = (lastIdx + 1) % sz;
        }
        q[lastIdx] = x;
        ++currSize;
    }

    void pop() {
        if (empty()) {
            cout << "queue is already empty, can't pop" << endl;
            return;
        }
        if (currSize == 1) {
            frontIdx = lastIdx = -1;
        } else {
            frontIdx = (frontIdx + 1) % sz;
        }
        --currSize;
    }

    T front() const {
        if (empty()) {
            cout << "queue is empty, can't fetch front" << endl;
            return T{};
        }
        return q[frontIdx];
    }

    int size() const {
        return currSize;
    }

    bool empty() const {
        return currSize == 0;
    }

    bool full() const {
        return currSize == sz;
    }
};

template <class T>
class Node {
public:
    T val;
    // Node<T>* next;
    shared_ptr<Node<T>> next;
    Node(T val): val(val), next(nullptr) {}
};

template <class T>
class MyStackUsingLL {
private:
    int sz;
    // Node<T>* topNode;
    shared_ptr<Node<T>> topNode;
public:
    MyStackUsingLL() noexcept : sz(0), topNode(nullptr) {
        cout << "\nStack Implementation Using LinkedList" << endl;
        cout << "################################" << endl;
    }
    
    // Rule of Five: Prevent accidental copying
    MyStackUsingLL(const MyStackUsingLL&) = delete;
    MyStackUsingLL& operator=(const MyStackUsingLL&) = delete;
    
    // Destructor auto-managed by shared_ptr
    ~MyStackUsingLL() = default;
    
    void push(const T& x) {
        // Node<T>* node = new Node<T>(x);
        // shared_ptr<Node<T>> node(new Node<T>(x));
        auto node = make_shared<Node<T>>(x);
        node->next = topNode;
        topNode = node;
        sz++;
    }

    void pop() noexcept {
        if (empty()) {
            cout << "stack is already empty, can't pop" << endl;
            return;
        }
        // Node<T>* temp = topNode;
        // shared_ptr<Node<T>> temp(topNode);   // no need of ptr now as no deletion needed.
        topNode = topNode->next;
        // delete temp;
        // temp = nullptr;
        sz--;
    }

    T top() const {
        if (empty()) {
            cout << "stack is empty, can't fetch top" << endl;
            return T{};
        }
        return topNode->val;
    }

    int size() const noexcept {
        return sz;
    }

    bool empty() const noexcept {
        return sz == 0;
    }
};


template <class T>
class MyQueueUsingLL {
private:
    int sz;
    shared_ptr<Node<T>> frontNode;
    shared_ptr<Node<T>> lastNode;
public:
    MyQueueUsingLL() noexcept : sz(0), frontNode(nullptr), lastNode(nullptr) {
        cout << "\nQueue Implementation Using LinkedList" << endl;
        cout << "################################" << endl;
    }
    
    // Rule of Five: Prevent accidental copying
    MyQueueUsingLL(const MyQueueUsingLL&) = delete;
    MyQueueUsingLL& operator=(const MyQueueUsingLL&) = delete;
    
    // Destructor auto-managed by shared_ptr
    ~MyQueueUsingLL() = default;
    
    void push(const T& x) {
        // Node<T>* node = new Node<T>(x);
        // shared_ptr<Node<T>> node(new Node<T>(x));
        auto node = make_shared<Node<T>>(x);
        if (empty())
            frontNode = node;
        else 
            lastNode->next = node;
        lastNode = node;
        sz++;
    }

    void pop() noexcept {
        if (empty()) {
            cout << "queue is already empty, can't pop" << endl;
            return;
        }
        // shared_ptr<Node<T>> temp = frontNode;
        frontNode = frontNode->next;    
        // delete temp;
        // temp = nullptr;
        if (frontNode == nullptr) {
            lastNode = nullptr;
        }
        sz--;
    }

    T front() const {
        if (empty()) {
            cout << "queue is empty, can't fetch front" << endl;
            return T{};
        }
        return frontNode->val;
    }

    int size() const noexcept {
        return sz;
    }

    bool empty() const noexcept {
        return sz == 0;
    }
};


int main() {
    // stack<int> st;
    // st.push(1);
    // st.push(30);
    // cout << st.topIdx() << endl;
    // st.pop();
    // cout << st.topIdx() << endl;

    
    // MyStack<string> st;
    MyStackUsingLL<string> st;
    cout << st.top() << endl;
    st.push("Naman");
    st.push("Kuku");
    st.push("Us");
    cout << st.top() << endl;
    st.pop();
    cout << st.top() << endl;
    st.pop();
    cout << st.top() << endl;
    st.pop();
    st.pop();

    // MyQueue<string> q;
    MyQueueUsingLL<string> q;
    cout << q.front() << endl;
    q.push("Naman");
    q.push("Kuku");
    q.push("Us");
    cout << q.front() << endl;
    q.pop();
    cout << q.front() << endl;
    q.pop();
    cout << q.front() << endl;
    q.pop();
    q.pop();
    
    return 0;
}