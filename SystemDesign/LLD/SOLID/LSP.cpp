#include <iostream>
#include <vector>
using namespace std;

// 1. LSP Violated:
// class Account {
// public:
//     virtual void deposit(double amount) = 0;
//     virtual void withdraw(double amount) = 0;
// };

// class CurrentAccount : public Account {
// private:
//     double balance = 0;
// public:
//     void deposit(double amount) override {
//         balance += amount;
//         cout << "Deposited " << amount << " in Current Acc. New Balance: " << balance << endl;
//     }
//     void withdraw(double amount) override {
//         if(amount > balance) {
//             cout << "Insufficient funds..." << endl;
//         } else {
//             balance -= amount;
//             cout << "Withdrawn " << amount << " from Current Acc. New Balance: " << balance << endl;
//         }
        
//     }
// };

// class SavingsAccount : public Account {
// private:
//     double balance = 0;
// public:
//     void deposit(double amount) override {
//         balance += amount;
//         cout << "Deposited " << amount << " in Savings Acc. New Balance: " << balance << endl;
//     }
//     void withdraw(double amount) override {
//         if(amount > balance) {
//             cout << "Insufficient funds..." << endl;
//         } else {
//             balance -= amount;
//             cout << "Withdrawn " << amount << " from Savings Acc. New Balance: " << balance << endl;
//         }
        
//     }
// };

// class FixedDepositAccount : public Account {
// private:
//     double balance = 0;
// public:
//     void deposit(double amount) override {
//         balance += amount;
//         cout << "Deposited " << amount << " in FD Acc. New Balance: " << balance << endl;
//     }
//     void withdraw(double amount) override {
//         throw logic_error("Withdrawal not allowed from FD Accout");
//     }
// };

// class BankClient {
// private:
//     vector<Account*> accounts;
// public: 
//     BankClient(vector<Account*>& acc) : accounts(acc) {}

//     void processTransaction() {
//         for(auto acc: accounts){
//             acc->deposit(1000);

//             // assuming all accounts supporting withdrawal (LSP violation)
//             acc->withdraw(500);
//             // try{
//             //     acc->withdraw(500);
//             // } catch(const logic_error& e) {
//             //     cout << "Exception: " << e.what() << endl;
//             // }
//         }
//     }
// };

// int main(){
//     vector<Account*> accounts;
//     accounts.push_back(new CurrentAccount());
//     accounts.push_back(new SavingsAccount());
//     accounts.push_back(new FixedDepositAccount());
        
//     BankClient* client = new BankClient(accounts);
//     client->processTransaction();

//     return 0;
// }


// 1. LSP Followed:
class NonWithdrawableAccount {
public:
    virtual void deposit(double amount) = 0;
};

class WithdrawableAccount : public NonWithdrawableAccount {
public:
    virtual void withdraw(double amount) = 0;
};

class CurrentAccount : public WithdrawableAccount {
private:
    double balance = 0;
public:
    void deposit(double amount) override {
        balance += amount;
        cout << "Deposited " << amount << " in Current Acc. New Balance: " << balance << endl;
    }
    void withdraw(double amount) override {
        if(amount > balance) {
            cout << "Insufficient funds..." << endl;
        } else {
            balance -= amount;
            cout << "Withdrawn " << amount << " from Current Acc. New Balance: " << balance << endl;
        }
        
    }
};

class SavingsAccount : public WithdrawableAccount {
private:
    double balance = 0;
public:
    void deposit(double amount) override {
        balance += amount;
        cout << "Deposited " << amount << " in Savings Acc. New Balance: " << balance << endl;
    }
    void withdraw(double amount) override {
        if(amount > balance) {
            cout << "Insufficient funds..." << endl;
        } else {
            balance -= amount;
            cout << "Withdrawn " << amount << " from Savings Acc. New Balance: " << balance << endl;
        }
        
    }
};

class FixedDepositAccount : public NonWithdrawableAccount {
private:
    double balance = 0;
public:
    void deposit(double amount) override {
        balance += amount;
        cout << "Deposited " << amount << " in FD Acc. New Balance: " << balance << endl;
    }
};

class BankClient {
private:
    vector<WithdrawableAccount*> withdrawableAccounts;
    vector<NonWithdrawableAccount*> nonWithdrawableAccounts;
public: 
    BankClient(vector<WithdrawableAccount*>& acc1, vector<NonWithdrawableAccount*>& acc2) 
    : withdrawableAccounts(acc1), nonWithdrawableAccounts(acc2) {}

    void processTransaction() {
        for(auto acc: withdrawableAccounts){
            acc->deposit(1000);
            acc->withdraw(500);
        }
        for(auto acc: nonWithdrawableAccounts){
            acc->deposit(1000);
            acc->withdraw(500);
        }
    }
};

int main(){
    vector<WithdrawableAccount*> withdrawableAccounts;
    withdrawableAccounts.push_back(new CurrentAccount());
    withdrawableAccounts.push_back(new SavingsAccount());

    vector<NonWithdrawableAccount*> nonWithdrawableAccounts;
    nonWithdrawableAccounts.push_back(new FixedDepositAccount());
        
    BankClient* client = new BankClient(withdrawableAccounts, nonWithdrawableAccounts);
    client->processTransaction();

    return 0;
}