/*
Notification System:

Requirements:
1. Play n Plug Model
2. extensible & scalable: sms, email, pop-up
3. notification enahcement dynamically like, adding headers, footers
4. store all notifications.
5. logging all the logs.
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;


// Decorator Pattern for making notification:

class INotification {
public:
    virtual string getContent() = 0;
    virtual ~INotification(){}
};

// Concrete Notification: simple text notification.
class SimpleNotification : public INotification {
private:
    string text;
public:
    SimpleNotification(string text) : text(text) {}
    string getContent() override {
        return text;
    }
};

// Abstract Decorator: wraps a Notification object.
class INotificationDecorator : public INotification {
protected:
    INotification* notification;
public:
    INotificationDecorator(INotification* notification) : notification(notification) {}
    virtual ~INotificationDecorator(){
        delete notification;
    }
};

// Decorator to add a timestamp to the content.
class TimestampDecorator : public INotificationDecorator {
private:
    string timestamp;
public:
    TimestampDecorator(INotification *notification, string timestamp) : INotificationDecorator(notification), timestamp(timestamp) {}
    string getContent () override {
        return "[" + timestamp + "]: " + notification->getContent();
    }
};

// Decorator to append a signature to the content.
class SignatureDecorator : public INotificationDecorator {
private:
    string sign;
public:
    SignatureDecorator(INotification *notification, string sign) : INotificationDecorator(notification), sign(sign) {}
    string getContent () override {
        return notification->getContent() + " ~" + sign;
    }
};


// Strategy desgin pattern for sending notification via different channels

// Abstract class for different Notification Strategies.
class INotificationStrategy {
public:
    virtual void sendNotification(string content) = 0;
    virtual ~INotificationStrategy() {}
};

class EmailStrategy : public INotificationStrategy {
private:
    string usrEmailAddr;
public:
    EmailStrategy(string usrEmailAddr) : usrEmailAddr(usrEmailAddr) {}
    void sendNotification(string content) override {
        cout << "Notifcation sent to email addr: " << usrEmailAddr << endl;
        cout <<  content << endl;
    }
};

class SmsStrategy : public INotificationStrategy {
private:
    string usrPhoneNumber;
public:
    SmsStrategy(string usrPhoneNumber) : usrPhoneNumber(usrPhoneNumber) {}
    void sendNotification(string content) override {
        cout << "Notifcation sent to Phone Number: " << usrPhoneNumber << endl;
        cout <<  content << endl;
    }
};

class PopUpStrategy : public INotificationStrategy {
private:
    string usrId;
public:
    PopUpStrategy(string usrId) : usrId(usrId) {}
    void sendNotification(string content) override {
        cout << "Notifcation PopUp sent to usrId: " << usrId << endl;
        cout << content << endl;
    }
};


//  Observer Pattern for pushing notifications to observers like logger & notificationEngine

// Observer interface: each observer gets an update with a Notification pointer.
class IObserver {
public:
    virtual void update() = 0;
    virtual ~IObserver(){}
};

class IObservable {
public:
    vector<IObserver*> observers;
    virtual void addObserver(IObserver* obs) = 0;
    virtual void removeObserver(IObserver* obs) = 0;
    virtual void notifyObservers() = 0;
    virtual ~IObservable(){}
};

// Concrete Observable
class NotificationObservable : public IObservable {
private:
    INotification* currentNotification;
public:
    NotificationObservable() : currentNotification(nullptr) {}

    void addObserver(IObserver* obs) override {
        observers.push_back(obs);
    }

    void removeObserver(IObserver* obs) override {
        observers.erase(remove(observers.begin(), observers.end(), obs), observers.end());
    }

    void notifyObservers() override {
        for(auto obs: observers){
            obs->update();
        }
    }

    void setNotification(INotification* notification){
        if(currentNotification != nullptr) {
            // delete currentNotification; // we can't delete previous notication, as we want to maintain the history in notificationService class
        }
        currentNotification = notification;
        notifyObservers();
    }

    INotification* getNotification(){
        return currentNotification;
    }
};

// Concrete Observer 1
class Logger : public IObserver {
private:
    NotificationObservable* NotiObservable;
public:
    Logger(NotificationObservable* NotiObservable) : NotiObservable(NotiObservable) {
        NotiObservable->addObserver(this);   // added here itself, not left for client to register
    }
    void update() override {
        cout << "[Logger] : " << NotiObservable->getNotification()->getContent() << endl;
        cout << endl;
    }
    ~Logger() override {
        NotiObservable->removeObserver(this);  // RAII: unregister on destruction to avoid dangling pointers
    }
};

class NotificationEngine : public IObserver {
protected:
    NotificationObservable* NotiObservable;
    vector<INotificationStrategy*> strategies;
public:
    NotificationEngine(NotificationObservable* NotiObservable) : NotiObservable(NotiObservable) {
        NotiObservable->addObserver(this);      // added here itself, not left for client to register
    }
    void addNotificationStrategy(INotificationStrategy* ns){
        strategies.push_back(ns);
    }
    void update() override {
        string content = NotiObservable->getNotification()->getContent();
        for(auto ns: strategies){
            ns->sendNotification(content);
            cout << endl;
        }
    }

    ~NotificationEngine() override {
        // Unregister before cleaning up strategies to avoid calling update() with deleted pointers
        NotiObservable->removeObserver(this);
        for(auto ns: strategies){
            delete ns;
            ns = nullptr;
        }
    }
};


// The NotificationService manages notifications. It keeps track of notifications. 
// Any client code will interact with this service.

// Singleton class
class NotificationService {
private:
    static NotificationService* instance;
    NotificationObservable* NotiObservable;
    vector<INotification*> notifications; // for storing all notifcations

    NotificationService() {
        NotiObservable = new NotificationObservable();
    }

public:
    static NotificationService* getInstance(){
        return instance;
    }

    static void destroyInstance(){
        delete instance;
        instance = nullptr;
    }

    // Creates a new Notification and notifies observers.
    void sendNotification(INotification* notification){
        notifications.push_back(notification);  // saving notification
        NotiObservable->setNotification(notification);
    }

    void getAllNotifications() {
        cout << "Printing all notifications: " << endl;
        for(auto n: notifications){
            cout << n->getContent() << endl;
        }
    }

    NotificationObservable* getNotificationObservable(){
        return NotiObservable;
    }

    ~NotificationService() {
        for (auto n : notifications) delete n;
        notifications.clear();
        delete NotiObservable;
    }
};

NotificationService* NotificationService::instance = new NotificationService();


// Client

int main() {
    
    string msg = "Your PIZZA is Ready!!";
    string timestamp = "12:30PM";
    string sign = "D O M I N O S";
    string usrEmailAddr = "namanagarwal016@gmail.com";
    string usrPhoneNumber = "7240054419";
    string usrId = "naman123";

    // Set Strategies
    INotificationStrategy* email = new EmailStrategy(usrEmailAddr);
    INotificationStrategy* sms = new SmsStrategy(usrPhoneNumber);
    INotificationStrategy* popup = new PopUpStrategy(usrId);
    
    // Set NotificationService
    NotificationService* ns = NotificationService::getInstance();
    
    // Set Observers & Observable
    NotificationObservable* observable = ns->getNotificationObservable();

    // Add Logger Observer
    IObserver* logger = new Logger(observable);
    // observable->addObserver(logger);    // this can be done in observer constructor itself

    // Add notification engine observer
    NotificationEngine* engine = new NotificationEngine(observable);        // check why can't we use IObserver* C++ is statically typed — only members on the pointer's compile-time type are accessible. The compiler doesn't look at the runtime type to permit calls.
    engine->addNotificationStrategy(email);
    engine->addNotificationStrategy(sms);
    engine->addNotificationStrategy(popup);
    // observable->addObserver(engine);     // this can be done in observer constructor itself
    
    // Make notification
    INotification* notification1 = new SignatureDecorator(new TimestampDecorator(new SimpleNotification(msg), timestamp), sign);
    INotification* notification2 = new SignatureDecorator(new TimestampDecorator(new SimpleNotification("Heyy"), "9:25AM"), "WHATSAPP");
    
    ns->sendNotification(notification1);
    ns->sendNotification(notification2);

    ns->getAllNotifications();

    // Observers unregister themselves in destructors via RAII
    delete logger;
    delete engine;
    NotificationService::destroyInstance();
    
    return 0;
}

/* Old code anaylisis:
Quick executive summary
Short verdict: Good use of design patterns (Decorator, Strategy, Observer) — design shows solid LLD thinking and meets the functional requirements conceptually. Main issues: raw-pointer ownership, memory leaks/undefined deletes, no thread-safety, and poor testability due to globals/singleton. Overall interview rating: 3.5 / 5.

Ratings (1–5)
Play-n-Plug (modular patterns): 4 / 5
Extensibility & scalability (adding channels): 4 / 5
Dynamic enhancement (decorator usage): 5 / 5
Storage of notifications (history/persistence): 3 / 5
Logging (observer/logger): 4 / 5
Memory safety & ownership: 2 / 5
Thread-safety / concurrency readiness: 1 / 5
Testability: 3 / 5

Pros (compact)
Correct selection of patterns: Decorator for content, Strategy for channels, Observer for event propagation — demonstrates LLD knowledge.
Notification pipeline is simple and clearly separated (builders/decorators -> observable -> engine/strategies).
Notification history is tracked (vector), and observers exist for logging & sending.
Cons / Risks (compact)
Raw pointers everywhere -> multiple ownership problems, leaks, double-delete risk (e.g., NotificationObservable deletes currentNotification, NotificationService keeps pointers and never deletes them).
Singleton and global static allocation make testing and lifecycle control hard.
Observers vector holds raw pointers with no unregister or lifetime control — dangling pointer risk if observers deleted.
No concurrency control — not safe if used in multithreaded server.
No persistence API for notifications (only in-memory vector). No TTL/size-limits.
No clear error handling (strategy send failures not surfaced).


Final short checklist to present in interview (if asked)
Show pattern choices and why (Decorator: dynamic composition; Strategy: pluggable channels; Observer: decouple producers/consumers).
Call out ownership bug (potential double-delete + leak) and show quick fix: migrate to shared_ptr and pass notification in notify call.
Mention threading & persistence as next priorities.

*/

/*
New Code Analysis:
Final Code Review — Notification System
Overall Assessment
Score: 4 / 5 — Strong LLD design with correct patterns, now with improved lifecycle management and RAII. Ready for SDE2 interview.

Patterns & Architecture (Excellent)
✓ Decorator: Dynamic notification enhancement (timestamp, signature) — elegant and extensible.
✓ Strategy: Pluggable channels (Email, SMS, PopUp) — true plug-n-play.
✓ Observer: Loose coupling between observable and observers (logger, engine).
✓ Singleton: Centralized NotificationService with lazy cleanup via destroyInstance().

Ownership & Lifecycle (Good)
✓ Notifications: NotificationService owns history vector and deletes all notifications in destructor.
✓ Strategies: NotificationEngine owns strategies vector and deletes them in destructor.
✓ Observers: Self-register in constructor (injected), auto-unregister in destructor via RAII — no dangling pointers.
✓ Singleton cleanup: destroyInstance() method for explicit, safe teardown.
✓ No leaks: All objects have clear ownership and safe deletion order.

SOLID Compliance (Good)
Principle	Score	Notes
SRP	3.5/5	NotificationService does service + observable exposure; could split storage into repository.
OCP	4/5	New channels/decorators don't modify existing code; extensible design.
LSP	4/5	Subtypes honor contracts; ownership pattern documented.
ISP	4/5	Focused interfaces (INotification, IStrategy, IObserver); no bloat.
DIP	4/5	Depends on abstractions; DI via constructor injection for observers.
Code Quality (Strong)
✓ Includes: #include <algorithm> for STL remove.
✓ RAII: Destructors handle cleanup (observers unregister, strategies deleted).
✓ Memory safety: Clear ownership, no dangling pointers or double-deletes.
✓ Naming: Clear class/method names; good inline comments.
✓ Client code: Clean, minimal — only business logic visible.

Remaining Minor Issues (Low Priority)
Issue	Severity	Mitigation
No thread-safety	Medium	Add mutex around observer list + notification sends for production.
No persistence	Low	Extract INotificationRepository for file/DB storage if needed.
No error handling	Low	Strategy sendNotification could return status or throw exceptions.
Const-correctness	Low	getContent() not const; consider making getContent() const.
Interview Talking Points (1-liners, ready to use)
Pattern selection: "Decorator for dynamic composition, Strategy for pluggable channels, Observer for loose coupling — each has a clear responsibility."

Self-registration + RAII: "Observers receive injected observable, register in constructor, and auto-unregister in destructor — this is RAII; prevents dangling pointers and is exception-safe."

Ownership clarity: "NotificationService owns history, NotificationEngine owns strategies, observers own their lifecycle via destructors — no ambiguity, no leaks."

Singleton safety: "Singleton is initialized at static load time and destroyed via explicit destroyInstance() — not ideal, but safe and controllable."

Extensibility: "Want a new channel? Just implement INotificationStrategy — no changes to existing code. Same for decorators or observers."

Next improvements (if asked):

Add mutex around observers/notification list for thread-safety.
Extract repository pattern for persistent storage.
Make getContent() const for better const-correctness.
Add return status to strategy sendNotification for error handling.
Demo/Test Scenario
Your current code:

Creates email, SMS, popup strategies ✓
Builds notifications with timestamp + signature decorators ✓
Sends notifications (logs + sends via all channels) ✓
Stores history ✓
Cleans up safely on shutdown ✓
Final Score Breakdown
Aspect	Rating	Reason
Pattern knowledge	5/5	Correct choice & usage of 3 major patterns.
Architecture	4/5	Clean separation; DI used well; singleton could be optional.
Memory safety	4/5	RAII, ownership clear, no leaks; but raw pointers (acceptable).
SOLID principles	4/5	Strong compliance across all 5 principles.
Code readability	4/5	Clear, well-commented, professional naming.
Production-readiness	3/5	Missing thread-safety, error handling, persistence.
Overall	4/5	Strong LLD; interview-ready with awareness of follow-ups.
One-Sentence Closing
"This is a well-architected notification system that demonstrates solid design-pattern knowledge, proper ownership and lifecycle management, and good SOLID compliance — ready to discuss in interviews and scale with thread-safety and persistence as needed."

Marking complete.

Completed (1/1) Final review of entire notification system

You're all set! The code is clean, compiles, and is interview-ready. Use the talking points above when presenting, and be ready to discuss the follow-ups (thread-safety, persistence, error handling).
*/

