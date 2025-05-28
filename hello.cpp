#include <iostream>
#include <fstream>
#include <iomanip>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Base class Person
class Person {
protected:
    string name;
    int rollNo;
public:
    Person() : name(""), rollNo(0) {}
    Person(string n, int r) : name(n), rollNo(r) {}
    void setName(string n) { name = n; }
    void setRollNo(int r) { rollNo = r; }
    string getName() const { return name; }
    int getRollNo() const { return rollNo; }
    virtual void display() const {
        cout << "Name: " << name << "\nRoll No: " << rollNo << endl;
    }
};

// Derived class Student
class Student : public Person {
private:
    vector<float> marks;
    float average;
    char grade;
public:
    Student() : Person(), average(0.0), grade('F') {}
    Student(string n, int r, vector<float> m) : Person(n, r), marks(m) {
        calculateAverage();
        assignGrade();
    }
    void setMarks(vector<float> m) {
        marks = m;
        calculateAverage();
        assignGrade();
    }
    vector<float> getMarks() const { return marks; }
    float getAverage() const { return average; }
    char getGrade() const { return grade; }
    void calculateAverage() {
        float sum = 0.0;
        for (float mark : marks) {
            sum += mark;
        }
        average = marks.empty() ? 0.0 : sum / marks.size();
    }
    void assignGrade() {
        if (average >= 90)
            grade = 'A';
        else if (average >= 80)
            grade = 'B';
        else if (average >= 70)
            grade = 'C';
        else if (average >= 60)
            grade = 'D';
        else
            grade = 'F';
    }
    void display() const override {
        Person::display();
        cout << "Marks: ";
        for (float mark : marks) {
            cout << mark << " ";
        }
        cout << "\nAverage: " << fixed << setprecision(2) << average
             << "\nGrade: " << grade << endl;
    }
};

// Function prototypes
void addStudent(vector<Student>& students);
void displayAllStudents(const vector<Student>& students);
void searchStudent(const vector<Student>& students);
void modifyStudent(vector<Student>& students);
void deleteStudent(vector<Student>& students);
void saveToFile(const vector<Student>& students, const string& filename);
void loadFromFile(vector<Student>& students, const string& filename);
void sortStudentsByAverage(vector<Student>& students);

int main() {
    vector<Student> students;
    string filename = "students.txt";
    loadFromFile(students, filename);

    int choice;
    do {
        cout << "\n--- Student Grading System ---\n";
        cout << "1. Add Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Search Student\n";
        cout << "4. Modify Student\n";
        cout << "5. Delete Student\n";
        cout << "6. Sort Students by Average\n";
        cout << "7. Save and Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addStudent(students);
                break;
            case 2:
                displayAllStudents(students);
                break;
            case 3:
                searchStudent(students);
                break;
            case 4:
                modifyStudent(students);
                break;
            case 5:
                deleteStudent(students);
                break;
            case 6:
                sortStudentsByAverage(students);
                break;
            case 7:
                saveToFile(students, filename);
                cout << "Data saved. Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 7);

    return 0;
}

void addStudent(vector<Student>& students) {
    string name;
    int rollNo, numSubjects;
    vector<float> marks;

    cout << "Enter student name: ";
    cin.ignore();
    getline(cin, name);
    cout << "Enter roll number: ";
    cin >> rollNo;
    cout << "Enter number of subjects: ";
    cin >> numSubjects;
    marks.resize(numSubjects);
    for (int i = 0; i < numSubjects; ++i) {
        cout << "Enter mark for subject " << i + 1 << ": ";
        cin >> marks[i];
    }

    students.emplace_back(name, rollNo, marks);
    cout << "Student added successfully.\n";
}

void displayAllStudents(const vector<Student>& students) {
    if (students.empty()) {
        cout << "No student records available.\n";
        return;
    }
    for (const Student& student : students) {
        student.display();
        cout << "-------------------------\n";
    }
}

void searchStudent(const vector<Student>& students) {
    int rollNo;
    cout << "Enter roll number to search: ";
    cin >> rollNo;
    for (const Student& student : students) {
        if (student.getRollNo() == rollNo) {
            student.display();
            return;
        }
    }
    cout << "Student not found.\n";
}

void modifyStudent(vector<Student>& students) {
    int rollNo;
    cout << "Enter roll number to modify: ";
    cin >> rollNo;
    for (Student& student : students) {
        if (student.getRollNo() == rollNo) {
            string name;
            int numSubjects;
            vector<float> marks;

            cout << "Enter new name: ";
            cin.ignore();
            getline(cin, name);
            cout << "Enter number of subjects: ";
            cin >> numSubjects;
            marks.resize(numSubjects);
            for (int i = 0; i < numSubjects; ++i) {
                cout << "Enter mark for subject " << i + 1 << ": ";
                cin >> marks[i];
            }

            student.setName(name);
            student.setMarks(marks);
            cout << "Student record updated.\n";
            return;
        }
    }
    cout << "Student not found.\n";
}

void deleteStudent(vector<Student>& students) {
    int rollNo;
    cout << "Enter roll number to delete: ";
    cin >> rollNo;
    auto it = remove_if(students.begin(), students.end(),
                        [rollNo](const Student& s) { return s.getRollNo() == rollNo; });
    if (it != students.end()) {
        students.erase(it, students.end());
        cout << "Student record deleted.\n";
    } else {
        cout << "Student not found.\n";
    }
}

void saveToFile(const vector<Student>& students, const string& filename) {
    ofstream outFile(filename);
    if (!outFile) {
        cerr << "Error opening file for writing.\n";
        return;
    }
    for (const Student& student : students) {
        outFile << student.getName() << '\n';
        outFile << student.getRollNo() << '\n';
        vector<float> marks = student.getMarks();
        outFile << marks.size() << '\n';
        for (float mark : marks) {
            outFile << mark << ' ';
        }
        outFile << '\n';
    }
    outFile.close();
}

void loadFromFile(vector<Student>& students, const string& filename) {
    ifstream inFile(filename);
    if (!inFile) {
        // File does not exist. No data to load.
        return;
    }
    string name;
    int rollNo, numSubjects;
    while (getline(inFile, name)) {
        inFile >> rollNo;
        inFile >> numSubjects;
        vector<float> marks(numSubjects);
        for (int i = 0; i < numSubjects; ++i) {
            inFile >> marks[i];
        }
        inFile.ignore(); // Ignore the newline character after marks
        students.emplace_back(name, rollNo, marks);
    }
    inFile.close();
}

void sortStudentsByAverage(vector<Student>& students) {
    sort(students.begin(), students.end(),
         [](const Student& a, const Student& b) {
             return a.getAverage() > b.getAverage();
         });
    cout << "Students sorted by average marks in descending order.\n";
}

