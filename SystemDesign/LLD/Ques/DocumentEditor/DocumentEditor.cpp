// https://youtu.be/MT9qZFGQXOU?list=PLQEaRBV9gAFvzp6XhcNFpk1WdOcyVo9qT

#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

// 1. Bad Design

// class DocumentEditor {
// private:
//     vector<string> elements;
//     string renderedDoc;
// public:
//     void addText(string txt){
//         elements.push_back(txt);
//     }
//     void addImage(string imgPath){
//         elements.push_back(imgPath);
//     }
//     string renderDocument(){
//         if(renderedDoc.empty()) {
//             for(string element: elements) {
//                 //identify img element rule
//                 if(element.size() > 4 && (
//                     element.substr(element.size() - 4) == ".png" ||
//                     element.substr(element.size() - 4) == ".jpg")) {
//                         renderedDoc += "[Image: " + element + "]\n";
//                     }
//                 else {
//                     renderedDoc += element + "\n";
//                 }
//             }
//         }
//         return renderedDoc;
//     }
//     void saveToFile() {
//         ofstream file("output.txt");
//         if(file.is_open()) {
//             file << renderDocument();
//             file.close();
//             cout << "Document saved in output.txt!!" << endl;
//         } else {
//             cout << "Unable to open file" << endl;
//         }
//     }
// };

// int main() {
//     DocumentEditor doc;
//     doc.addText("Naman");
//     doc.addImage("familyPic.jpg");
//     doc.addText("Agarwal");

//     cout << doc.renderDocument() << endl;
//     doc.saveToFile();
//     return 0;
// }


// Good Design:

// Abstraction for document elements
class Element {
public:
    virtual ~Element() = default;
    virtual string renderElement() = 0;
};

class Text : public Element {
private:
    string txt;
public: 
    Text(string txt) : txt(txt) {}
    string renderElement() override {
        return txt + "\n";
    }
};

class Image : public Element {
private: 
    string imgPath;
public:
    Image(string imgPath) : imgPath(imgPath) {}
    string renderElement() override {
        return "[Image: " + imgPath + "]\n";
    }
};

class TabSpace : public Element {           // Proving Scalablility
public:
    string renderElement() override {
        return "\t";
    }
};

// Document class responsible for holding a collection of elements
class Document {
private:
    vector<Element*> elements;   
public:
    ~Document() { 
        for (auto e : elements) 
            delete e; 
    }
    void addElement(Element* element){
        elements.push_back(element);
    }

    // Renders the document by concatenating the render output of all elements.
    string renderDocument() {
        string renderedDoc;
        for(Element* element: elements) {
            renderedDoc += element->renderElement();
        }
        return renderedDoc;
    }
};

// Storage Abstraction
class Storage {
public:
    virtual ~Storage() = default;
    virtual void save(string renderedDoc) = 0;
};

class FileStorage : public Storage {
public:
    void save(string renderedDoc) override {
        ofstream file("output.txt");
        if(file.is_open()) {
            file << renderedDoc;
            file.close();
            cout << "Document saved in output.txt!!" << endl;
        } else {
            cout << "Unable to open file" << endl;
        }
    }
};

class DbStorage : public Storage {       // Proving Scalablility
public:
    void save(string renderedDoc) override {
        cout << "Saving to DB..." << endl;  
    }
}; 

class DocumentEditor {
public:
    Document* doc;
    Storage* storage;
public:
    DocumentEditor(Document* doc, Storage* storage) : doc(doc), storage(storage) {}

    void addText(string txt) {
        doc->addElement(new Text(txt));  // need memory management
    }
    void addImg(string imgPath) {
        // Image img(imgPath);          // NO issue with memory management
        // doc.addElement(&img);        // But giving Segmentation fault in renderDocument()
        doc->addElement(new Image(imgPath));
    }
    void addTabSpace() {
        doc->addElement(new TabSpace());
    }
    
    string renderDoc() {
        return doc->renderDocument();
    }
    
    void saveDoc() {
        storage->save(renderDoc());
    }
};

// Client Code:
int main() {
    Document* doc = new Document();
    Storage* file = new FileStorage();
    
    DocumentEditor* editor = new DocumentEditor(doc, file);

    editor->addText("Naman");   
    editor->addTabSpace();
    editor->addImg("familyPic.jpg");
    editor->addText("Agarwal");     

    cout << editor->renderDoc() << endl;

    editor->saveDoc();

    delete editor;
    delete file;
    delete doc;

    return 0;
}



// Client Code Desgin, More better:

// Abstraction for document elements
// class Element {
// public:
//     virtual ~Element() = default;
//     virtual string renderElement() = 0;
// };

// class Text : public Element {
// private:
//     string txt;
// public: 
//     Text(string txt) : txt(txt) {}
//     string renderElement() override {
//         return txt + "\n";
//     }
// };

// class Image : public Element {
// private: 
//     string imgPath;
// public:
//     Image(string imgPath) : imgPath(imgPath) {}
//     string renderElement() override {
//         return "[Image: " + imgPath + "]\n";
//     }
// };

// class TabSpace : public Element {           // Proving Scalablility
// public:
//     string renderElement() override {
//         return "\t";
//     }
// };

// // Document class responsible for holding a collection of elements
// class Document {
// private:
//     vector<Element*> elements;   
// public:
//     ~Document() { 
//         for (auto e : elements) 
//             delete e; 
//     }
//     void addElement(Element* element){
//         elements.push_back(element);
//     }

//     vector<Element*>& getElements() {
//         return elements;
//     }
    
// };

// class DocumentRenderer {
// public:
//     // Renders the document by concatenating the render output of all elements.
//     string renderDocument(Document *doc) {
//         string renderedDoc;
//         for(Element* element: doc->getElements()) {
//             renderedDoc += element->renderElement();
//         }
//         return renderedDoc;
//     }

// };

// // Storage Abstraction
// class Storage {
// public:
//     virtual ~Storage() = default;
//     virtual void save(string renderedDoc) = 0;
// };

// class FileStorage : public Storage {
// public:
//     void save(string renderedDoc) override {
//         ofstream file("output.txt");
//         if(file.is_open()) {
//             file << renderedDoc;
//             file.close();
//             cout << "Document saved in output.txt!!" << endl;
//         } else {
//             cout << "Unable to open file" << endl;
//         }
//     }
// };

// class DbStorage : public Storage {       // Proving Scalablility
// public:
//     void save(string renderedDoc) override {
//         cout << "Saving to DB..." << endl;  
//     }
// }; 

// class DocumentEditor {
// public:
//     Document* doc;
// public:
//     DocumentEditor(Document* doc) : doc(doc) {}

//     void addText(string txt) {
//         doc->addElement(new Text(txt));  // need memory management
//     }
//     void addImg(string imgPath) {
//         // Image img(imgPath);          // NO issue with memory management
//         // doc.addElement(&img);        // But giving Segmentation fault in renderDocument()
//         doc->addElement(new Image(imgPath));
//     }
//     void addTabSpace() {
//         doc->addElement(new TabSpace());
//     }
// };

// class Client {
// public:
//     Document* doc = new Document();         // unique_ptr<Document> doc = make_unique<Document>();
//     Storage* file = new FileStorage();
//     DocumentRenderer* renderer = new DocumentRenderer();
//     DocumentEditor* editor = new DocumentEditor(doc);

//     void editDocument() {
//         editor->addText("Naman");   
//         editor->addTabSpace();
//         editor->addImg("familyPic.jpg");
//         editor->addText("Agarwal"); 

//         cout << renderer->renderDocument(doc) << endl;

//         file->save(renderer->renderDocument(doc));
//     }

//     ~Client() {
//         delete editor;
//         delete renderer;
//         delete file;
//         delete doc;
//     }
// };

// // Client Code:
// int main() {

//     Client client;
//     client.editDocument();

//     return 0;
// }