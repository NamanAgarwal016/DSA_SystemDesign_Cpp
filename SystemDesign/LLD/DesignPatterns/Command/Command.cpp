#include <iostream>
#include <vector>
using namespace std;

// ICommand Interface
class ICommand {
public:
    virtual void execute() = 0;
    virtual void undo() = 0;
    virtual ~ICommand(){}
};

// Receivers
class Light {
public:
    void on(){
        cout << "Light is ON" << endl;
    }
    void off(){
        cout << "Light is OFF" << endl;
    }
};

// Concrete ICommand for Light
class LightCommand : public ICommand {
private: 
    Light* light;
public:
    LightCommand(Light* light) : light(light) {} 
    void execute(){
        light->on();
    }
    void undo() {
        light->off();
    }
    ~LightCommand(){
       light = nullptr; 
    }
};

// Receivers
class Fan {
public:
    void on(){
        cout << "Fan is ON" << endl;
    }
    void off(){
        cout << "Fan is OFF" << endl;
    }
};

// Concrete ICommand for Fan
class FanCommand : public ICommand {
private: 
    Fan* fan;
public:
    FanCommand(Fan* fan) : fan(fan) {} 
    void execute(){
        fan->on();
    }
    void undo() {
        fan->off();
    }
    ~FanCommand() {
        fan = nullptr;
    }
};

// Invoker: Remote Controller with static 2D array of 6 buttons (3 rows, 2 cols)
class RemoteController {
private:
    static const int numButtons = 4;
    ICommand* buttons[numButtons];
    bool buttonPressed[numButtons];

public:
    RemoteController() {
        for (int i = 0; i < numButtons; i++) {
            buttons[i] = nullptr;
            buttonPressed[i] = false;  // false = off, true = on
        }
    }

    void setCommand(int idx, ICommand* cmd) {
        if (idx >= 0 && idx < numButtons) {
            if (buttons[idx] != nullptr)
                delete buttons[idx];
            buttons[idx] = cmd;
            buttonPressed[idx] = false;
        }
    }

    void pressButton(int idx) {
        if (idx >= 0 && idx < numButtons && buttons[idx] != nullptr) {
            if (buttonPressed[idx] == false) {
                buttons[idx]->execute();
            } else {
                buttons[idx]->undo();
            }
            buttonPressed[idx] = !buttonPressed[idx];
        } else {
            cout << "No command assigned at button " << idx << endl;
        }
    }

    ~RemoteController() {
        for (int i = 0; i < numButtons; i++) {
            if (buttons[i] != NULL)
                delete buttons[i];
        }
    }
};

int main() {

    Light* livingRoomLight = new Light();
    Fan* ceilingFan = new Fan();

    RemoteController* remote = new RemoteController();

    remote->setCommand(0, new LightCommand(livingRoomLight));
    remote->setCommand(1, new FanCommand(ceilingFan));

    // Simulate button presses (toggle behavior)
    cout << "--- Toggling Light Button 0 ---" << endl;
    remote->pressButton(0);  // ON
    remote->pressButton(0);  // OFF

    cout << "--- Toggling Fan Button 1 ---" << endl;
    remote->pressButton(1);  // ON
    remote->pressButton(1);  // OFF

    // Press unassigned button to show default message
    cout << "--- Pressing Unassigned Button 2 ---" << endl;
    remote->pressButton(2);

    // Clean up
    delete remote;
    delete livingRoomLight;
    delete ceilingFan;

    return 0;
}

/*
Why Appliances Should NOT Be Owned by Commands
Core Reason: Separation of Concerns
Commands are about "what to do" (encapsulate an action/request).
Appliances are about "what things exist" (the actual objects being controlled).
Commands should NOT manage the lifecycle of things they control — that violates SRP.


Interview Answer (1-liner)
"Commands should be non-owning wrappers around appliances — they encapsulate the action, not the object. Ownership and lifecycle should be decoupled; RemoteControl owns commands, client owns appliances. This prevents double-deletes and enables command reuse and sharing."

Analogy: A TV remote (command) doesn't own the TV (appliance) — the TV exists independently, and the remote just sends signals to it. If the remote is deleted, the TV still exists.

*/


/*
Final ICommand Pattern Review — Short & Crisp
Overall Score: 4.5 / 5
Significantly improved. Ownership is clean, lifecycle is safe, pattern is well-applied.

What's Fixed ✓
Ownership separation: Commands don't own appliances; client owns both.
No double-delete: Commands only nullify references; RemoteControl deletes commands only.
Clear lifecycle: Client controls shutdown order (rc → light → fan).
Bounds check: pressButton validates index.
Clean destructors: Commands just set pointers to nullptr.
What's Good ✓
Pattern usage: ICommand encapsulates action; appliances are injected (DI).
SRP: Commands control "what to do"; appliances control "what things are."
Reusability: Same Light/Fan can work with multiple commands.
State tracking: IsButtonOn toggle works for this simple use case.
Remaining Minor Issues (Optional Improvements)
Issue	Severity	Note
Toggle state fragile	Low	Assumes toggle only; doesn't support true undo-stack.
No command history	Low	Can't redo or maintain execution history.
cerr without #include <iostream>	Low	You included it; good.
Interview Talking Points (Ready)
Pattern purpose: "ICommand encapsulates a request as an object — decouples invoker (RemoteControl) from receiver (Light/Fan)."

Ownership model: "Commands are non-owning wrappers; they reference appliances passed via DI. RemoteControl owns commands. Client owns appliances. Clean separation prevents double-deletes."

SRP: "Commands have one job: invoke an action. They don't manage object lifecycle."

Extensibility: "Adding AC command? Just inherit ICommand and pass AC reference — no changes to RemoteControl."

If asked about undo: "Current design uses toggle (on→off→on). For true undo/redo, maintain a history stack of executed commands and pop to undo."

One-Sentence Verdict
"Well-designed ICommand Pattern with correct ownership, clean lifecycle, and DI — interview-ready. Mention undo-stack as a next enhancement."

Completed (1/1) Final review of ICommand Pattern code

Done! Code is solid. Ready for your interview. 🎯

*/