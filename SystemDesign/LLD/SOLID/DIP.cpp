#include <iostream>
using namespace std;

// 1. DIP violated

// Low-level module
// class MongoDB {
// public:
//     void save(){
//         cout << "Saving to MongoDB..." << endl;
//     }
// };

// // Low-level module
// class SqlDB {
// public:
//     void save(){
//         cout << "Saving to SqlDB..." << endl;
//     }
// };

// // High-level module (Tightly coupled)
// class App {
// public:
//     MongoDB mongoDB;
//     SqlDB sqlDB;
//     App(MongoDB& mongoDB, SqlDB& sqlDB) : mongoDB(mongoDB), sqlDB(sqlDB) {}

//     void saveToMongoDB(){
//         mongoDB.save();
//     }
//     void saveToSqlDB(){
//         sqlDB.save();
//     }
// };

// int main(){
//     MongoDB mongoDB;
//     SqlDB sqlDB;
//     App app(mongoDB, sqlDB);
//     app.saveToMongoDB();
//     app.saveToSqlDB();
// }



// 2. DIP Followed

// Abstraction (Interface)
class Database {
public:
    virtual ~Database() = default;
    virtual void save() = 0;
};

// MongoDB implementation (Low-level module)
class MongoDB : public Database {
public:
    void save() override {
        cout << "Saving to MongoDB..." << endl;
    }
};

class SqlDB : public Database {
public:
    void save() override {
        cout << "Saving to SqlDB..." << endl;
    }
};

// High-level module (Now loosely coupled)
class App {
private:
    Database* p;  // Dependency Injection
public:
    App(Database* p) : p(p) {}
    void saveToDB(){
        p->save();
    }
};

int main(){ 
    // pointer semantics
    // Database* sqlDB = new SqlDB();
    // App app1(sqlDB);
    // app1.saveToDB();

    // Database* mongoDB = new MongoDB();
    // App app2(mongoDB);
    // app2.saveToDB();

    // delete sqlDB;
    // delete mongoDB;

    SqlDB sqlDB;
    App app1(&sqlDB);
    app1.saveToDB();

    MongoDB mongoDB;
    App app2(&mongoDB);
    app2.saveToDB();

    return 0;
}

