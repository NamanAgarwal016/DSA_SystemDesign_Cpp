// https://youtu.be/uQB7jNWnZaI

// Interview Ques: Implement String Class, with following asked functionalities.

// Solution:
// our String class is a custom implementation that mimics the behavior of the C++ std::string class.

// library for cout, cin & has string as well
#include <iostream>  
#include <cstring> // Using <cstring> functions like strlen and strcpy is a shortcut to handle character arrays, C-style strings

// #include <string> 

using namespace std;

class String{
public:
    
    // Default constructor
    // will be used for: String str1;
    String(){
        res = nullptr;
        len = 0;
    }

    // Paramterised Constructor
    // will be used for: String str2 = "Naman";
    // Why char* ?? In C++, a string literal like "Naman" is stored as a C-style string, which is essentially a character array (char[]) terminated by a null character ('\0').
    String(const char* ch){         // we're using const here as some const string is passed
        len = strlen(ch);
        res = new char[len + 1]; // extra 1 char for '/0' which marks ending of string

        // Memory allocation with new can fail, for this use follwoing;
        // res = new(std::nothrow) char[len + 1];
        // if (!res) {
        //     throw std::bad_alloc();
        // }

        // copy charcters in ch to our res
        strcpy(res, ch);        
    }

    /*
    Copy Constructor
    will be used for: String str3 = str1;  & for: String str4(str1);   
    const in argument here bcoz we don't want passed str to accidently change 
    Also pass by refrence is must here as if we pass by value, then it will need a copy constructor itself which we're making right now.
    if done by pass by value, it will throw an error
    */
    String(const String& str){     
        len = str.len;
        res = new char[len + 1];
        strcpy(res, str.res);
    }

    /*
    Copy Assignment Operator
    will be used for: str3 = str2; or for: str3 = "hello"
    Internal meanming of this stat for compiler: str3 is calling "equal to" opeartor func and passing str2 as a parameter
    How's it's different from copy const: 
    copy const only called when we're defining string for the first time and we're passing some other str
    But here, string will be already defined, and just copy is happening from other string
    */
    String& operator=(const String& str) {
        // self assignment check :str3 = str3 case 
        // this-> pointer which refers to the object which has called it, here str3
        if(this != &str)       // Why &str and not str? To compare the two objects (this and str), you need to compare their memory addresses. &str gives the memory address of the object being assigned (str2).
        {
            // first delete the memory occupied by previous str3's res , as it's already initialized before
            // prevents memory leak
            // res is an array (res = new char[len + 1]), so we need to do delete[] not just delete
            // One more thing is, memory allocation using new might fail someitmes, so we have don't want to loose old res at that time, hence stroing it is temp, deleting later on.
            char* temp = res;
            len = str.len;
            res = new char[len + 1];
            strcpy(res, str.res); 

            delete[] temp;
        }
        return *this;       // Why return *this and not simple : return this
        //*this gives a reference to the current object. This matches the return type of the function (String&).
        // Returning *this allows assignment chaining, like str1 = str2 = str3;
    }

    /*
    2nd way of implementing Copy Assignmemt operatot
    CAS: Copy & Swap idiom
    Here we're passing str through pass by value, so copy constructor will be called. str will have the copy of the string that was passed,
    Here str will get deleted automatically once this func execution is done. Parameter gets deleted after this scope.
    */
    // String& operator=(String str) {
    //     Swap(*this, str);        // we cannot use std::swap here as it doesn't know what String class is
    //     return *this;
    // }

    void Swap(String& str1, String& str2){
        std::swap(str1.res, str2.res);
        std::swap(str1.len, str2.len);
    }

    // Move constructor
    // will be used for: String str5 =  std::move(str2); 
    // && -> called as R value refrence. Used when to pass temp object
    String(String&& str) noexcept {     
        len = str.len;
        res = str.res;
        str.res = nullptr;
        str.len = 0;
    }

    // Move assignment operator
    String& operator=(String&& str) noexcept {
        if (this != &str) {
            delete[] res;
            len = str.len;
            res = str.res;
            str.res = nullptr;
            str.len = 0;
        }
        return *this;
    }

    unsigned int length() const {
        return len;
    }

    // Wherever this friend func is impelemented, it can access all private members of this class.
    friend ostream& operator<<(ostream& out, const String& str);
    friend istream& operator>>(istream& in, String& str);

    // Destructor
    ~String(){
        if(res) {
            delete[] res;
            res = nullptr;      // for avoiding dangling pointer
            len = 0;
        }
    }

private:
    // buffer is needed
    char* res; 

    // anytime provides the length of string
    unsigned int len; 
};

/* 
will be used for: cout >> str2;
cout will call ">>" operator func and str2 will go as parameter
we cannot go inside cout class and define the functionality, as we did for "=" operator. Bcoz this is our user defined class.
So we're going to make it global and overload >> operator
function << will be called & cout and str2 will be passed as arguments
*/
ostream& operator<<(ostream& out, const String& str) {
    // out ostream abject knows how to print const string
    // Also, res is a private member, so can't be used outside. So use friend func
    out << str.res; 
    return out;     // we're returning this bcoz we can use it for chaining ... cout << str2 << str1;
}

istream& operator>>(istream& in, String& str) {
    char buffer[1000]; // Temporary buffer for input
    in >> buffer;
    delete[] str.res; // Free existing memory
    str.len = strlen(buffer);
    str.res = new char[str.len + 1];
    strcpy(str.res, buffer);
    return in; 
}

int main(){
    // string c = "Naman";
    // cout << c << endl; 
 
    // First listing down all the functionalities interviewer wants from String class

    // User should be able to instantiate str with nullptr, not empty string, just a null string
    // implemented through default constructor
    String str1;       

    // User should be able to instantiate with const string
    // implemented through paramterised constructor
    String str2 = "Naman";       

    // User should be able to initialize the string with previously defined string
    // implemented through copy constructor
    String str3 = str2;         

    String str4(str2);  // This is same as String str3 = str1; will be taken care by copy constructor itself 

    str3 = str2;        // implemented through copy assignment operator

    // Move constructor
    // unlike copy constructor, str2 will become nullptr
    // Optimization over normal copy 
    String str5 = std::move(str2);  

    str1 = std::move(str5);

    // Get length of string anytime
    cout << "Length of str1: " << str1.length() << endl;

    // User should be able to print the string, output the string class object
    // implemented by overloading >> operator
    cout << "str1: " << str1 << endl;   
    cout << "str3: " << str3 << endl;
    cout << "str4: " << str4 << endl;

    // Input operator
    cout << "Enter a string: ";
    cin >> str1;
    cout << "You entered: " << str1 << endl;

    return 0;
}


// size_t custom_strlen(const char* str) {
//     size_t length = 0;
//     while (str[length] != '\0') {
//         length++;
//     }
//     return length;
// }


// char* custom_strcpy(char* dest, const char* src) {
//     char* original_dest = dest;
//     while (*src != '\0') {
//         *dest = *src;
//         dest++;
//         src++;
//     }
//     *dest = '\0'; // Add null terminator
//     return original_dest;
// }