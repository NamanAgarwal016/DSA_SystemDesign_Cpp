#include <iostream>
#include <unordered_map>
#include <queue>
#include <ctime>
#include <memory>

enum class SpotType { Compact, Large };

class ParkingSpot {
    int id;
    bool isAvailable;
    SpotType type;

public:
    ParkingSpot(int id, SpotType type) : id(id), isAvailable(true), type(type) {}
    void assign() { isAvailable = false; }
    void release() { isAvailable = true; }
    bool available() const { return isAvailable; }
    int getId() const { return id; }
    SpotType getType() const { return type; }
    virtual ~ParkingSpot() {}
};

class Ticket {
    int id;
    int spotId;
    SpotType type;
    time_t issueTime;

public:
    Ticket(int id, int spotId, SpotType type) : id(id), spotId(spotId), type(type) {
        issueTime = std::time(nullptr);
    }
    int getId() const { return id; }
    int getSpotId() const { return spotId; }
    time_t getIssueTime() const { return issueTime; }
};

class PaymentProcessor {
public:
    virtual void processPayment(double amt) = 0;
    virtual ~PaymentProcessor() {}
};

class CashProcessor : public PaymentProcessor {
public:
    void processPayment(double amt) override {
        std::cout << "Processing cash payment: $" << amt << "\n";
    }
};

struct SpotDistance {
    double distance;
    ParkingSpot* spot;

    bool operator>(const SpotDistance& other) const {
        return distance > other.distance;
    }
};

class ParkingAssignmentStrategy {
public:
    virtual ParkingSpot* getParkingSpot(int entryId) = 0;
    virtual void releaseSpot(ParkingSpot* spot) = 0;
    virtual ~ParkingAssignmentStrategy() {}
};

class NearestSpotAssignment : public ParkingAssignmentStrategy {
    std::unordered_map<int, std::priority_queue<SpotDistance, std::vector<SpotDistance>, std::greater<>>> heaps;

public:
    NearestSpotAssignment() {
        ParkingSpot* s1 = new ParkingSpot(1, SpotType::Compact);
        ParkingSpot* s2 = new ParkingSpot(2, SpotType::Large);

        heaps[1].push({5.0, s1});
        heaps[1].push({10.0, s2});
    }

    ParkingSpot* getParkingSpot(int entryId) override {
        if (heaps[entryId].empty()) return nullptr;
        SpotDistance sd = heaps[entryId].top();
        heaps[entryId].pop();
        sd.spot->assign();
        return sd.spot;
    }

    void releaseSpot(ParkingSpot* spot) override {
        spot->release();
        heaps[1].push({5.0, spot}); // For simplicity
    }
};

// ✅ ParkingLot wrapper
class ParkingLot {
    static ParkingLot* instance;
    ParkingAssignmentStrategy* strategy;
    std::unordered_map<int, ParkingSpot*> ticketMap;

    ParkingLot() {
        strategy = new NearestSpotAssignment();
    }

public:
    static ParkingLot* getInstance() {
        if (!instance)
            instance = new ParkingLot();
        return instance;
    }

    Ticket* vehicleEnters(int entryId) {
        ParkingSpot* spot = strategy->getParkingSpot(entryId);
        if (!spot) {
            std::cout << "Lot full!\n";
            return nullptr;
        }
        Ticket* t = new Ticket(rand(), spot->getId(), spot->getType());
        ticketMap[t->getId()] = spot;
        std::cout << "Vehicle entered. Ticket ID: " << t->getId() << "\n";
        return t;
    }

    void vehicleExits(Ticket* t, PaymentProcessor* processor) {
        time_t now = std::time(nullptr);
        double hours = std::difftime(now, t->getIssueTime()) / 3600.0;
        double fee = hours * 10.0;
        processor->processPayment(fee);

        ParkingSpot* spot = ticketMap[t->getId()];
        strategy->releaseSpot(spot);
        ticketMap.erase(t->getId());

        std::cout << "Vehicle exited. Spot released.\n";
    }
};

// static init
ParkingLot* ParkingLot::instance = nullptr;

int main() {
    ParkingLot* lot = ParkingLot::getInstance();

    Ticket* t = lot->vehicleEnters(1);

    CashProcessor cash;
    lot->vehicleExits(t, &cash);

    return 0;
}
