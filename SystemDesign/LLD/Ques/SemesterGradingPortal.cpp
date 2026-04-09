#include <iostream>
#include <vector>
#include <string>
#include <memory>

using namespace std;

// Forward declarations
class GradingStrategy;
class Course;
class Semester;
class Student;

// Grading Strategy Interface (Strategy Pattern)
class GradingStrategy {
public:
    virtual double computeGrade(double score) = 0; // Returns GPA or percentage
    virtual string getGradeType() = 0;
    virtual ~GradingStrategy() {}
};

// Concrete Strategy: Letter Grade (A=4.0, B=3.0, etc.)
class LetterGradeStrategy : public GradingStrategy {
public:
    double computeGrade(double score) override {
        if (score >= 90) return 4.0;
        else if (score >= 80) return 3.0;
        else if (score >= 70) return 2.0;
        else if (score >= 60) return 1.0;
        else return 0.0;
    }
    string getGradeType() override { return "Letter Grade (GPA)"; }
};

// Concrete Strategy: Percentage (direct score as percentage)
class PercentageStrategy : public GradingStrategy {
public:
    double computeGrade(double score) override {
        return score; // Assuming score is already in percentage
    }
    string getGradeType() override { return "Percentage"; }
};

// Course Class
class Course {
private:
    string name;
    int credits;
    double rawScore; // Marks obtained or percentage
    double computedGrade;
public:
    Course(string n, int c, double s) : name(n), credits(c), rawScore(s), computedGrade(0.0) {}
    void computeGrade(shared_ptr<GradingStrategy> strategy) {
        computedGrade = strategy->computeGrade(rawScore);
    }
    string getName() const { return name; }
    int getCredits() const { return credits; }
    double getComputedGrade() const { return computedGrade; }
    double getRawScore() const { return rawScore; }
};

// Semester Class
class Semester {
private:
    string name;
    vector<shared_ptr<Course>> courses;
    double semesterGPA;
public:
    Semester(string n) : name(n), semesterGPA(0.0) {}
    void addCourse(shared_ptr<Course> course) {
        courses.push_back(course);
    }
    void computeGPA(shared_ptr<GradingStrategy> strategy) {
        double totalPoints = 0.0;
        int totalCredits = 0;
        for (auto& course : courses) {
            course->computeGrade(strategy);
            totalPoints += course->getComputedGrade() * course->getCredits();
            totalCredits += course->getCredits();
        }
        semesterGPA = totalCredits > 0 ? totalPoints / totalCredits : 0.0;
    }
    double getSemesterGPA() const { return semesterGPA; }
    string getName() const { return name; }
    const vector<shared_ptr<Course>>& getCourses() const { return courses; }
};

// Student Class
class Student {
private:
    string name;
    string id;
    string branch;
    vector<shared_ptr<Semester>> semesters;
    double cumulativeGPA;
public:
    Student(string n, string i, string b) : name(n), id(i), branch(b), cumulativeGPA(0.0) {}
    void addSemester(shared_ptr<Semester> sem) {
        semesters.push_back(sem);
    }
    void computeCumulativeGPA(shared_ptr<GradingStrategy> strategy) {
        double totalPoints = 0.0;
        int totalCredits = 0;
        for (auto& sem : semesters) {
            sem->computeGPA(strategy);
            for (auto& course : sem->getCourses()) {
                totalPoints += course->getComputedGrade() * course->getCredits();
                totalCredits += course->getCredits();
            }
        }
        cumulativeGPA = totalCredits > 0 ? totalPoints / totalCredits : 0.0;
    }
    string getName() const { return name; }
    string getId() const { return id; }
    string getBranch() const { return branch; }
    double getCumulativeGPA() const { return cumulativeGPA; }
    const vector<shared_ptr<Semester>>& getSemesters() const { return semesters; }
};

// Grading System Portal
class GradingPortal {
private:
    vector<shared_ptr<Student>> students;
    shared_ptr<GradingStrategy> currentStrategy;
public:
    GradingPortal(shared_ptr<GradingStrategy> strategy) : currentStrategy(strategy) {}
    void setGradingStrategy(shared_ptr<GradingStrategy> strategy) {
        currentStrategy = strategy;
    }
    void addStudent(shared_ptr<Student> student) {
        students.push_back(student);
    }
    void computeAllResults() {
        for (auto& student : students) {
            student->computeCumulativeGPA(currentStrategy);
        }
    }
    void displayResults() {
        cout << "Grading System Results (" << currentStrategy->getGradeType() << ")\n";
        cout << "========================================\n";
        for (auto& student : students) {
            cout << "Student: " << student->getName() << " (ID: " << student->getId() << ", Branch: " << student->getBranch() << ")\n";
            cout << "Cumulative GPA: " << student->getCumulativeGPA() << "\n";
            for (auto& sem : student->getSemesters()) {
                cout << "  Semester: " << sem->getName() << " - GPA: " << sem->getSemesterGPA() << "\n";
                for (auto& course : sem->getCourses()) {
                    cout << "    Course: " << course->getName() << " (Credits: " << course->getCredits() << ") - Grade: " << course->getComputedGrade() << "\n";
                }
            }
            cout << "\n";
        }
    }
};

int main() {
    // Create grading strategies
    auto letterStrategy = make_shared<LetterGradeStrategy>();   // LetterGradeStrategy* ls = new LetterGradeStrategy();
    auto percentageStrategy = make_shared<PercentageStrategy>();

    // Create portal with initial strategy
    GradingPortal portal(letterStrategy);

    // Create sample students
    auto student1 = make_shared<Student>("Alice", "S001", "CSE"); // Student* st1 = new Student("Alice", "S001", "CSE");
    auto student2 = make_shared<Student>("Bob", "S002", "EE");

    // Add semesters and courses for Alice
    auto sem1Alice = make_shared<Semester>("Semester 1");
    sem1Alice->addCourse(make_shared<Course>("Math", 4, 85)); // Score 85
    sem1Alice->addCourse(make_shared<Course>("Physics", 3, 92));
    student1->addSemester(sem1Alice);

    auto sem2Alice = make_shared<Semester>("Semester 2");
    sem2Alice->addCourse(make_shared<Course>("CS101", 4, 78));
    sem2Alice->addCourse(make_shared<Course>("Data Structures", 3, 88));
    student1->addSemester(sem2Alice);

    // Add semesters and courses for Bob
    auto sem1Bob = make_shared<Semester>("Semester 1");
    sem1Bob->addCourse(make_shared<Course>("Math", 4, 75));
    sem1Bob->addCourse(make_shared<Course>("Physics", 3, 80));
    student2->addSemester(sem1Bob);

    // Add students to portal
    portal.addStudent(student1);
    portal.addStudent(student2);

    // Compute and display results with Letter Grade
    portal.computeAllResults();
    portal.displayResults();

    // Switch to Percentage strategy and recompute
    cout << "\nSwitching to Percentage Grading...\n\n";
    portal.setGradingStrategy(percentageStrategy);
    portal.computeAllResults();
    portal.displayResults();

    return 0;
}
