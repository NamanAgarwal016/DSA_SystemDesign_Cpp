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
    friend class HttpRequestStepBuilder;

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

//forward decalartions (so that dependency classes can be defined in any order)
class UrlStep;
class MethodStep;
class BodyStep;
class OptionalStep;

class OptionalStep {
public:
    virtual OptionalStep& withHeader(const string& key, const string& value) = 0;
    virtual OptionalStep& withQueryParams(const string& key, const string& value) = 0;
    virtual OptionalStep& withTimeout(int timeout) = 0;
    virtual HTTPRequest& build() = 0;
    virtual ~OptionalStep() {}
};

class BodyStep {
public:
    virtual OptionalStep& withBody(const string& body) = 0;
};

class MethodStep {
public:
    virtual BodyStep& withMethod(string method) = 0;
};

class UrlStep {
public:
    virtual MethodStep& withUrl(string url) = 0;
};

class HttpRequestStepBuilder : 
    public UrlStep, 
    public MethodStep, 
    public BodyStep, 
    public OptionalStep {

private:
    HTTPRequest req;

public:
    // Method chaining

    // UrlStep implementation
    MethodStep& withUrl(string url) override {
        req.url = url;
        return *this;
    }
    
    // MethodStep implementation
    BodyStep& withMethod(string method) override {
        req.method = method;
        return *this;
    }

    // BodyStep Implementation
    OptionalStep& withBody(const string& body) override {
        req.body = body;
        return *this;
    }
    
    // OptionalStep implementation
    OptionalStep& withHeader(const string& key, const string& value) override {
        req.headers[key] = value;
        return *this;
    }

    OptionalStep& withQueryParams(const string& key, const string& value) override {
        req.queryParams[key] = value;
        return *this;
    }
    
    OptionalStep& withTimeout(int timeout) override {
        req.timeout = timeout;
        return *this;
    }

    // Build method to create the immutable HttpRequest object
    HTTPRequest& build() override {
        // Validation logic can be added here
        if (req.url.empty()) {
            throw runtime_error("URL cannot be empty");
        }
        if(req.method.empty()) {
            throw runtime_error("Method can't be empty");
        }
        if(req.body.empty()) {
            throw runtime_error("Body can't be empty");
        }
        return req;
    }

    // Static method to start the building process
    static UrlStep& getBuilder() {
        // return *this;   // "this" not allowed in static methods
        return *(new HttpRequestStepBuilder());
    }
};

int main(){
    // Using Builder Pattern (nested class)

    // can't do this now:
    // HTTPRequest request = HTTPRequestBuilder()
    //     .withUrl("https://api.example.com")
    //     .withMethod("POST")
    //     .withHeader("Content-Type", "application/json")
    //     .withHeader("Accept", "application/json")
    //     .withQueryParams("key", "12345")
    //     .withBody("{\"name\": \"Aditya\"}")
    //     .withTimeout(60)
    //     .build();

    // Need to follow steps: url -> method -> body -> optional(header, QueryParam, timeout any order) -> build
    HTTPRequest request = HttpRequestStepBuilder::getBuilder()
        .withUrl("https://api.example.com")
        .withMethod("POST")
        .withBody("{\"name\": \"Aditya\"}")
        .withHeader("Content-Type", "application/json")
        .withHeader("Accept", "application/json")
        .withQueryParams("key", "12345")
        .withTimeout(60)
        .build();

    request.execute(); // Guaranteed to be in a consistent state
}
