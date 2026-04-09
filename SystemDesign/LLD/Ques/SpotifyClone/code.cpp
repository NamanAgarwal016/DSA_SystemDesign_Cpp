/*
Spotify Clone
https://youtu.be/DkLwFqbCsu8?list=PLQEaRBV9gAFvzp6XhcNFpk1WdOcyVo9qT

Functional Requirements:
- user can play pause song
- user can create playlist, add songs to it
- playlist can be played in Sequential, Random, Custom manner
- App shiould support Multiple O/p Device (Bluetooth, Earphone, Headphone)

Non Fun Req:
- Scalable design
- New o/p device can be added
- New startegy to play can be added


folder structure needs to be followed: menitoned in foldStruct.txt
folder name mentioned above each class
*/

#include <iostream>
#include <vector>
#include <string>
#include <map>
#include <stack>
#include <queue>

using namespace std;

//models
class Song {
private:
    string name;
    string artist;
    string lyrics;
public:
    Song(string name, string artist, string lyrics): name(name), artist(artist), lyrics(lyrics) {}
    string getSongName(){
        return name;
    }
    string getSongArtist(){
        return artist;
    }
    string getSongLyrics(){
        return lyrics;
    }
};

// Devices
//external
class BluetoothSpeakerAPI {
public:
    void playSoundViaBluetooth(string data){
        cout << "[BLUETOOTH]" << endl; 
        cout << "~$~" << data << "~$~\n"<< endl; 
    }
};

//external
class EarphoneSpeakerAPI {
public:
    void playSoundViaEarphone(string data){
        cout << "[EARPHONE]" << endl;  
        cout << "~$~" << data << "~$~\n"<< endl;  
    }
};

//external
class HeadphoneSpeakerAPI {
public:
    void playSoundViaHeadphone(string data){
        cout << "[HEADPHONE]" << endl; 
        cout << "~$~" << data << "~$~\n"<< endl;   
    }
};

//device
class IAudioOutputDevices {
public:
    virtual void playAudio(Song* song) = 0;
    virtual ~IAudioOutputDevices(){}
};

//device
class BluetoothSpeakerAdapter : public IAudioOutputDevices {
private:
    BluetoothSpeakerAPI* bs;
public:
    BluetoothSpeakerAdapter(BluetoothSpeakerAPI* bs) : bs(bs) {}
    void playAudio(Song* song) {
        bs->playSoundViaBluetooth(song->getSongLyrics());
    }
};

//device
class HeadphoneSpeakerAdapter : public IAudioOutputDevices {
private:
    HeadphoneSpeakerAPI* bs;
public:
    HeadphoneSpeakerAdapter(HeadphoneSpeakerAPI* bs) : bs(bs) {}
    void playAudio(Song* song) {
        bs->playSoundViaHeadphone(song->getSongLyrics());
    }
};

//device
class EarphoneSpeakerAdapter : public IAudioOutputDevices {
private:
    EarphoneSpeakerAPI* bs;
public:
    EarphoneSpeakerAdapter(EarphoneSpeakerAPI* bs) : bs(bs) {}
    void playAudio(Song* song) {
        bs->playSoundViaEarphone(song->getSongLyrics());
    }
};

//enums
enum class DeviceType {
    BLUETOOTH,
    HEADPHONE,
    EARPHONE
};

//factory
class DeviceFactory {
public:
    IAudioOutputDevices* createDeviceType(DeviceType dt){
        if(dt == DeviceType::BLUETOOTH){
            return new BluetoothSpeakerAdapter(new BluetoothSpeakerAPI());
        }
        if(dt == DeviceType::EARPHONE){
            return new EarphoneSpeakerAdapter(new EarphoneSpeakerAPI());
        }
        if(dt == DeviceType::HEADPHONE){
            return new HeadphoneSpeakerAdapter(new HeadphoneSpeakerAPI());
        }
        else {
            throw runtime_error("Incorrect device type selected!!");
        }
    }
};

// Singleton Manager class
//managers
class DeviceManager {
private:
    IAudioOutputDevices* currOutputDevice;
    DeviceFactory* factory;
    static DeviceManager* instance;
    DeviceManager(){
        currOutputDevice = nullptr;
        factory = nullptr;
    }
public:
    static DeviceManager* getInstance(){
        return instance;
    }
    void connect(DeviceType dt) {
        if (currOutputDevice) {
            delete currOutputDevice;
        }
        factory = new DeviceFactory();
        currOutputDevice = factory->createDeviceType(dt);

        switch(dt) {
            case DeviceType::BLUETOOTH:
                cout<< "Bluetooth device connected \n\n";
                break;
            case DeviceType::EARPHONE:
                cout<< "Earphones connected \n\n";
                break;
            case DeviceType::HEADPHONE:
                cout<< "Headphones connected \n\n";
        }
    }
    IAudioOutputDevices* getDevice(){
        if(currOutputDevice == nullptr){
            throw runtime_error("Connect the device first!!");
        }
        return currOutputDevice;
    }
    static void deleteInstance(){
        // delete factory;
        // delete ad;
        delete instance;
    }
};

DeviceManager* DeviceManager::instance = new DeviceManager();

//core
class AudioEngine {
private:
    Song* currSong;
    bool songIsPaused;
public:
    AudioEngine() {
        currSong = nullptr;
        songIsPaused = false;
    }
    void play(IAudioOutputDevices* ad, Song* song){
        if (song == nullptr) {
            throw runtime_error("Cannot play a null song.");
        }
        // Resume if same song was paused
        if (songIsPaused && song == currSong) {
            songIsPaused = false;
            cout << "Resuming song..." << song->getSongName() << " BY " << song->getSongArtist() << endl;
            ad->playAudio(song);
            return;
        }

        currSong = song;
        songIsPaused = false;
        cout << "Playing song: " << song->getSongName() << " BY " << song->getSongArtist() << endl;
        ad->playAudio(song);
    }   
    void pause(){
        if(currSong == nullptr){
            throw runtime_error("No song is currently playing to pause.");
        } 
        if (songIsPaused) {
            throw runtime_error("Song is already paused.");
        }
        songIsPaused = true;
        cout << "Pausing the song: " << currSong->getSongName() << endl;
    } 
    Song* getCurrPlayingSong(){
        if(currSong != nullptr)
            return currSong;
        else {
            throw runtime_error("No song is playing currently...");
            return nullptr;
        }
    }
};

// Playlist Design

//models
class Playlist {
private:
    string name;
    vector<Song*> songs;
public:
    Playlist(string name): name(name) {}
    string getPlaylistName(){
        return name;
    }
    void addSongToPlaylist(Song* song){
        if (song == nullptr) {
            throw runtime_error("Cannot add null song to playlist.");
        }
        songs.push_back(song);
    }
    const vector<Song*> getSongs(){
        return songs;
    }
    int getSize() {
        return (int)songs.size();
    }
};

//Singleton Manager Class
//managers
class PlaylistManager {
private:
    static PlaylistManager* instance;
    PlaylistManager(){}
    map<string, Playlist*> mp;
public:
    static PlaylistManager* getInstance(){
        return instance;
    }
    void createPlaylist(string name){
        mp[name] = new Playlist(name);
    }
    void addSongsToPlaylist(string pname, Song* song){
        mp[pname]->addSongToPlaylist(song);
    }
    Playlist* getPlaylist(string pname){
        return mp[pname];
    }
    static void deleteInstance(){
        // for(auto& p: mp)
        //     delete p.second;
        delete instance;
    }
};

PlaylistManager* PlaylistManager::instance = new PlaylistManager();

// Play Strategy for playlists, not interface(not pure abstract class)
//strategies
class PlayStrategy {
public:
    virtual ~PlayStrategy() {}
    virtual void setPlaylist(Playlist* pl) = 0;
    virtual bool hasNext() = 0;
    virtual Song* getNext() = 0;
    virtual bool hasPrevious() = 0;
    virtual Song* getPrevious() = 0;
    virtual void addToNext(Song* song){
        // not pure virtual
    }
};

//strategies
class SequentialPlayStrategy : public PlayStrategy {
private:
    Playlist* pl;
    int idx;
public:
    SequentialPlayStrategy(){
        pl = nullptr;
        idx = -1;
    }
    void setPlaylist(Playlist* p) override {
        pl = p;
        idx = -1;
    }
    bool hasNext() override {
        if(idx+1 < pl->getSize()){
            return true;
        }
        return false;
    }
    Song* getNext() override {
        idx++;
        return pl->getSongs()[idx];
    }
    bool hasPrevious() override {
        if(idx - 1 >= 0){
            return true;
        }
        return false;
    }
    Song* getPrevious() override {
        idx--;
        return pl->getSongs()[idx];
    }
};

//strategies
class RandomPlayStrategy : public PlayStrategy {
private:
    Playlist* currentPlaylist;
    vector<Song*> remainingSongs; 
    stack<Song*> history;
public:
    RandomPlayStrategy() {
        currentPlaylist = nullptr;
        srand((unsigned)time(nullptr));
    }
    void setPlaylist(Playlist* playlist) override {
        currentPlaylist = playlist;
        if (!currentPlaylist || currentPlaylist->getSize() == 0) return;

        remainingSongs = currentPlaylist->getSongs();
        history = stack<Song*>(); 
    }
    bool hasNext()override {
        return currentPlaylist && !remainingSongs.empty();
    }
    Song* getNext() override {
        if (!currentPlaylist || currentPlaylist->getSize() == 0) {
            throw runtime_error("No playlist loaded or playlist is empty.");
        }
        if (remainingSongs.empty()) {
            throw runtime_error("No songs left to play");
        }

        int idx = rand() % remainingSongs.size();
        Song* selectedSong = remainingSongs[idx];

        // Remove the selectedSong from the list. (Swap and pop to remove in O(1))
        swap(remainingSongs[idx], remainingSongs.back());
        remainingSongs.pop_back();

        history.push(selectedSong);
        return selectedSong;
    }
    bool hasPrevious() override {
        return history.size() > 0;
    }
    Song* getPrevious() override {
        if (history.empty()) {
            throw std::runtime_error("No previous song available.");
        }

        Song* song = history.top();
        history.pop();
        return song;
    }
};

//strategies
class CustomPlayStrategy : public PlayStrategy {
private:
    Playlist* currentPlaylist;
    int currentIndex;
    queue<Song*> nextQueue;
    stack<Song*> prevStack;

    Song* nextSequential() {
        if (currentPlaylist->getSize() == 0) {
            throw runtime_error("Playlist is empty.");
        }
        currentIndex = currentIndex + 1;
        return currentPlaylist->getSongs()[currentIndex];
    }

    Song* previousSequential() {
        if (currentPlaylist->getSize() == 0) {
            throw runtime_error("Playlist is empty.");
        }
        currentIndex = currentIndex - 1;
        return currentPlaylist->getSongs()[currentIndex];
    }
public:
    CustomPlayStrategy() {
        currentPlaylist = nullptr;
        currentIndex = -1;
    }
    void setPlaylist(Playlist* playlist) override {
        currentPlaylist = playlist;
        currentIndex = -1;
        while (!nextQueue.empty()) {
            nextQueue.pop();
        }
        while(!prevStack.empty()) {
            prevStack.pop();
        }
    }

    bool hasNext() override {
        return ((currentIndex + 1) < currentPlaylist->getSize());
    }

    Song* getNext() override {
        if (!currentPlaylist || currentPlaylist->getSize() == 0) {
            throw runtime_error("No playlist loaded or playlist is empty.");
        }

        if (!nextQueue.empty()) {
            Song* s = nextQueue.front();
            nextQueue.pop();
            prevStack.push(s);

            // update index to match queued song
            auto& list = currentPlaylist->getSongs();
            for (int i = 0; i < (int)list.size(); ++i) {
                if (list[i] == s) {
                    currentIndex = i;
                    break;
                }
            }
            return s;
        }

        // Otherwise sequential
        return nextSequential();
    }

    bool hasPrevious() override {
        return (currentIndex - 1 > 0);
    }

    Song* getPrevious() override {
        if (!currentPlaylist || currentPlaylist->getSize() == 0) {
            throw runtime_error("No playlist loaded or playlist is empty.");
        }

        if (!prevStack.empty()) {
            Song* s = prevStack.top();
            prevStack.pop();

            // update index to match stacked song
            auto& list = currentPlaylist->getSongs();
            for (int i = 0; i < (int)list.size(); ++i) {
                if (list[i] == s) {
                    currentIndex = i;
                    break;
                }
            }
            return s;
        }

        // Otherwise sequential
        return previousSequential();
    }

    void addToNext(Song* song) override {
        if (!song) {
            throw runtime_error("Cannot enqueue null song.");
        }
        nextQueue.push(song);
    }
};

//enums
enum class StrategyType {
    SEQUENTIAL,
    RANDOM,
    CUSTOM
};

// Singleton Manager class
//managers
class StrategyManager {
private:
    static StrategyManager* instance;
    PlayStrategy* ps;
    StrategyManager(){}
public:
    static StrategyManager* getInstance(){
        return instance;
    }
    PlayStrategy* getStrategy(StrategyType st){
        if(st == StrategyType::SEQUENTIAL) {
            return ps = new SequentialPlayStrategy();
        }
        if(st == StrategyType::RANDOM) {
            return ps = new RandomPlayStrategy();
        }
        if(st == StrategyType::CUSTOM) {
            return ps = new CustomPlayStrategy();
        }
        else {
            cout << "Playing Strategy not available!!" << endl;
            return nullptr;
        }
    }
    static void deleteInstance(){
        // delete ps;
        delete instance;
    }
};

StrategyManager* StrategyManager::instance = new StrategyManager();

// Singleton Facade Class
class MusicPlayerFacade {
private:
    static MusicPlayerFacade* instance;
    
    AudioEngine* ae;
    Playlist* currPl;
    PlayStrategy* ps;

    MusicPlayerFacade(){
        currPl = nullptr;
        ps = nullptr;
        ae = new AudioEngine();
    }

public:
    static MusicPlayerFacade* getInstance(){
        return instance;
    }
    static void deleteInstance(){
        // delete ae;
        StrategyManager::getInstance()->deleteInstance();
        DeviceManager::getInstance()->deleteInstance();
        PlaylistManager::getInstance()->deleteInstance();
        delete instance;
    }

    void connectDevice(DeviceType dt){
        DeviceManager::getInstance()->connect(dt);
    }

    void setStrategy(StrategyType st){
        ps = StrategyManager::getInstance()->getStrategy(st);
    }

    void loadPlaylist(string name){
        currPl = PlaylistManager::getInstance()->getPlaylist(name);
        if (!ps) {
            throw runtime_error("Play strategy not set before loading.");
        }
        ps->setPlaylist(currPl);
    }

    void playSong(Song* song){
        ae->play(DeviceManager::getInstance()->getDevice(), song);
    }

    void pauseSong(Song* song){
        if(ae->getCurrPlayingSong() == song)
            ae->pause();
        else{
            cout << "You're pausing the wrong song: " << song->getSongName() << endl;
            cout << "Currently playing: " << ae->getCurrPlayingSong()->getSongName() << endl;
        }
    }

    void playAll(){
        if (!currPl) {
            throw runtime_error("No playlist loaded.");
        }
        cout << "\nPlaying your playlist: " << currPl->getPlaylistName() << endl;
        while(ps->hasNext()){
            playSong(ps->getNext());
        }
        cout << "Completed playlist!!" << endl;
    }

    void playNext(){
        if (!currPl) {
            throw runtime_error("No playlist loaded.");
        }
        cout << "Playing Next Song..." << endl;
        if(ps->hasNext()){
            playSong(ps->getNext());
        } else {
            cout << "Playlist Ended!!" << endl;
        }
    }

    void playPrev(){
        if (!currPl) {
            throw runtime_error("No playlist loaded.");
        }
        cout << "Playing Prev Song..." << endl;
        if(ps->hasPrevious()){
            playSong(ps->getPrevious());
        } else {
            cout << "Playlist Ended!!" << endl;
        }
    }

    void addNextSong(Song* song){
        ps->addToNext(song);
    }

};

MusicPlayerFacade* MusicPlayerFacade::instance = new MusicPlayerFacade();

// Single App Class
class MusicPlayerApplication{
private:
    static MusicPlayerApplication* instance;
    MusicPlayerFacade* mpf;
    map<string, Song*> songLibrary;

    MusicPlayerApplication(){
        mpf = MusicPlayerFacade::getInstance();
    }
public:
    static MusicPlayerApplication* getInstance(){
        return instance;
    }
    static void deleteInstance(){
        MusicPlayerFacade::getInstance()->deleteInstance();
        delete instance;
    }

    void createSong(string name, string artist, string lyrics){
        songLibrary[name] = new Song(name, artist, lyrics);
    }

    void createPlaylist(string name) {
        PlaylistManager::getInstance()->createPlaylist(name);
    }

    void addSongsToPlaylist(string songName, string playlistName){
        PlaylistManager::getInstance()->addSongsToPlaylist(playlistName, songLibrary[songName]);
    }

    void connectDevice(DeviceType dt){
        mpf->connectDevice(dt);
    }

    void setStrategy(StrategyType st){
        mpf->setStrategy(st);
    }

    void loadPlaylist(string playlistName) {
        mpf->loadPlaylist(playlistName);
    }

    void playSong(string songName){
        mpf->playSong(songLibrary[songName]);
    } 

    void pauseSong(string songName){
        mpf->pauseSong(songLibrary[songName]);
    }

    void playNext(){
        mpf->playNext();
    }

    void playAll(){
        mpf->playAll();
    }

    void playPrev(){
        mpf->playPrev();
    }

    void addNextSong(string songName){
        mpf->addNextSong(songLibrary[songName]);
    }
};

MusicPlayerApplication* MusicPlayerApplication::instance = new MusicPlayerApplication();

int main(){
    try {
        MusicPlayerApplication* app = MusicPlayerApplication::getInstance();

        // Populate library
        app->createSong("Haseen", "Talwiinder", "Tu Hassen Tera Naam Hassen hai, \nTere Ishq da jaam hassen hai..");
        app->createSong("Ojhal", "Shunya", "Tu kabhi meri aankhon se ojhal hui, \nMeri aankhein mujhe hi satane lagi..");
        app->createSong("Jab Tu Sajan", "Mohit Chauhan", "Tere bina mai kya re, \nhun sanson se juda re..");

        // Create playlist and add songs
        app->createPlaylist("HipHop");
        app->addSongsToPlaylist("Haseen", "HipHop");
        app->addSongsToPlaylist("Ojhal", "HipHop");
        app->addSongsToPlaylist("Jab Tu Sajan", "HipHop");

        // Connect device
        app->connectDevice(DeviceType::BLUETOOTH);

        // Play/pause a single song
        app->playSong("Haseen");
        app->pauseSong("Haseen");
        app->playSong("Haseen");    // resume
        cout << endl;

        // Changing device
        app->connectDevice(DeviceType::HEADPHONE);

        cout << "\n-- Sequential Playback --\n";
        app->setStrategy(StrategyType::SEQUENTIAL);
        app->loadPlaylist("HipHop");
        app->playAll();

        cout << "\n-- Random Playback --\n";
        app->setStrategy(StrategyType::RANDOM);
        app->loadPlaylist("HipHop");
        app->playAll();

        cout << "\n-- Custom Queue Playback --\n";
        app->setStrategy(StrategyType::CUSTOM);
        app->loadPlaylist("HipHop");
        app->addNextSong("Ojhal");
        app->playAll();

        cout << "\n-- Play Previous in Sequential --\n";
        app->setStrategy(StrategyType::SEQUENTIAL);
        app->loadPlaylist("HipHop");
        app->playAll();
        app->playPrev();
        app->playPrev();

    } catch (const exception& error) {
        cerr << "Error: " << error.what() << endl;
    }

    return 0;
}