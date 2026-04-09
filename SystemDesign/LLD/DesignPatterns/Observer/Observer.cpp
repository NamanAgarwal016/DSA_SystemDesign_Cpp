
// definitiely check NotificationService.cpp for proper use of observ pattern.

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

class ISubscriber {
public: 
    virtual void update() = 0;
    virtual ~ISubscriber(){}
};

// Abstract Observable interface: a YouTube channel interface
class IChannel {
public:
    virtual void subscribe(ISubscriber* sub) = 0;
    virtual void unsubscribe(ISubscriber* sub) = 0;
    virtual void notifySubscribers() = 0;
    virtual ~IChannel() {}
};

// Concrete Subject: a YouTube channel that observers can subscribe to
class Channel : public IChannel {
private:
    string name;
    string latestVideo;
    vector<ISubscriber*> subscribers;           // this list can be in IChannel itself, better observable design 
public:
    Channel(const string& name) : name(name) {
        latestVideo = "";
    }

    // Add a subscriber (avoid duplicates)
    void subscribe(ISubscriber* sub) override {
        auto it = find(subscribers.begin(), subscribers.end(), sub);
        if(it == subscribers.end()){
            subscribers.push_back(sub);
        }
    }

    // Remove a subscriber if present
    void unsubscribe(ISubscriber* sub) override {
        auto it = find(subscribers.begin(), subscribers.end(), sub);
        if(it != subscribers.end()){
            subscribers.erase(it);
        }
    }

    // Notify all subscribers of the latest video
    void notifySubscribers() override {
        cout << "Notifying all subscribers..." << endl;
        auto snapshot = subscribers;        //Iterate over a snapshot to avoid invalidation, subscriber unsubscribing during notify
        for(ISubscriber* sub: snapshot){
            sub->update();
        }
    }

    // Upload a new video and notify all subscribers
    void uploadVideo(const string& newVideo) {
        latestVideo = newVideo;
        cout << "New video with title: " << newVideo << " has been uploaded!!" << endl;
        notifySubscribers();
    }

    string getLatestVideoTitle() const {
        return latestVideo;
    }

    string getChannelName() const {
        return name;
    }
};

// Concrete Observer: represents a subscriber to the channel
class Subscriber: public ISubscriber {
private:
    string name;
    Channel* channel;
public:
    Subscriber(const string& name, Channel* channel) : name(name), channel(channel) {}
    
    void update() override {
        cout << "\nHey " << name << endl;
        cout << "Your subscribed channel: " << channel->getChannelName() << " has uplaoded a new video titled: " << endl;
        cout << channel->getLatestVideoTitle() << endl;
    }
};

int main() {
    // Create a channel and subscribers
    Channel* channel = new Channel("TSeries");

    Subscriber* sub1 = new Subscriber("Naman", channel);
    Subscriber* sub2 = new Subscriber("Siddharth", channel);

    channel->subscribe(sub1);
    channel->subscribe(sub2);

    // Upload a video: both Naman and Siddharth are notified
    channel->uploadVideo("Antitode By KaranAjula");

    // Siddharth unsubscribes; Naman remains subscribed
    channel->unsubscribe(sub2);
    
    // Upload another video: only Naman is notified
    channel->uploadVideo("Wishes By Talwinder");

    return 0;
}