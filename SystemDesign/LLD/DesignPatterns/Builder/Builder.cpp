/*
Builder Pattern:

Issues which this pattern solves:
1. Constructor Overloading (Telescoping)
2. Muttable class
3. Inconsistent state
4. Scattered Validation
*/

#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <map>
using namespace std;

class HTTPRequest {
private:
    string url;
    string method;
    map<string, string> headers;
    map<string, string> queryParams;
    string body;
    int timeout; // in seconds

    HTTPRequest(){};

public:
    friend class HTTPRequestBuilder;

    void execute(){
        cout << "Executing " << method << " request to " << url << endl;
        
        if (!queryParams.empty()) {
            cout << "Query Parameters:" << endl;
            for (const auto& param : queryParams) {
                cout << "  " << param.first << "=" << param.second << endl;
            }
        }

        cout << "Headers:" << endl;
        for (const auto& header : headers) {
            cout << "  " << header.first << ": " << header.second << endl;
        }
        
        if (!body.empty()) {
            cout << "Body: " << body << endl;
        }
        
        cout << "Timeout: " << timeout << " seconds" << endl;
        cout << "Request executed successfully!" << endl;
    }
};

class HTTPRequestBuilder {
private:
    HTTPRequest req;
public:
    // Method chaining
    HTTPRequestBuilder& withUrl(string url){
        req.url = url;
        return *this;
    }
    
    HTTPRequestBuilder& withMethod(string method) {
        req.method = method;
        return *this;
    }
    
    HTTPRequestBuilder& withHeader(const string& key, const string& value) {
        req.headers[key] = value;
        return *this;
    }

    HTTPRequestBuilder& withQueryParams(const string& key, const string& value) {
        req.queryParams[key] = value;
        return *this;
    }
    
    HTTPRequestBuilder& withBody(const string& body) {
        req.body = body;
        return *this;
    }
    
    HTTPRequestBuilder& withTimeout(int timeout) {
        req.timeout = timeout;
        return *this;
    }

    // Build method to create the immutable HttpRequest object
    HTTPRequest build() {
        // Validation logic can be added here
        if (req.url.empty()) {
            throw runtime_error("URL cannot be empty");
        }
        return req;
    }
};

int main(){
    // Using Builder Pattern (nested class)
    HTTPRequest request = HTTPRequestBuilder()
        .withUrl("https://api.example.com")
        .withMethod("POST")
        .withHeader("Content-Type", "application/json")
        .withHeader("Accept", "application/json")
        .withQueryParams("key", "12345")
        .withBody("{\"name\": \"Aditya\"}")
        .withTimeout(60)
        .build();

    request.execute(); // Guaranteed to be in a consistent state
}
