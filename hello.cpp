#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

class Student {
private:
    string name;
    int rollNumber;
    float marks;

public:
    void getDetails() {
        cout << "Enter student's name: ";
        getline(cin >> ws, name);
        cout << "Enter roll number: ";
        cin >> rollNumber;
        cout << "Enter marks: ";
        cin >> marks;
        cin.ignore(); // Clear input buffer
    }

    void displayDetails() const {
        cout << "\nStudent Details:\n";
        cout << "Name: " << name << endl;
        cout << "Roll Number: " << rollNumber << endl;
        cout << "Marks: " << marks << endl;
    }

    int getRollNumber() const {
        return rollNumber;
    }

    void modifyDetails() {
        cout << "Modifying details for roll number: " << rollNumber << endl;
        getDetails();
    }

    string toFileString() const {
        return name + "," + to_string(rollNumber) + "," + to_string(marks);
    }
};

vector<Student> students;
string filename = "students.txt";

void addStudent() {
    Student s;
    s.getDetails();
    students.push_back(s);
    cout << "Student added successfully.\n";
}

void displayAllStudents() {
    if (students.empty()) {
        cout << "No student records found.\n";
        return;
    }

    for (const auto& s : students) {
        s.displayDetails();
    }
}

void modifyStudent() {
    int roll;
    cout << "Enter roll number of the student to modify: ";
    cin >> roll;

    for (auto& s : students) {
        if (s.getRollNumber() == roll) {
            s.modifyDetails();
            cout << "Details updated.\n";
            return;
        }
    }
    cout << "Student with roll number " << roll << " not found.\n";
}

void deleteStudent() {
    int roll;
    cout << "Enter roll number of the student to delete: ";
    cin >> roll;

    for (auto it = students.begin(); it != students.end(); ++it) {
        if (it->getRollNumber() == roll) {
            students.erase(it);
            cout << "Student deleted successfully.\n";
            return;
        }
    }
    cout << "Student with roll number " << roll << " not found.\n";
}

void saveToFile(const string& fname) {
    ofstream outFile(fname);
    for (const auto& s : students) {
        outFile << s.toFileString() << endl;
    }
    outFile.close();
    cout << "Data saved to file.\n";
}

int main() {
    int choice;

    do {
        cout << "\nStudent Management System\n";
        cout << "1. Add New Student\n";
        cout << "2. Display All Students\n";
        cout << "3. Modify Student\n";
        cout << "4. Delete Student\n";
        cout << "5. Save and Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore(); // Ignore trailing newline

        switch (choice) {
            case 1:
                addStudent();
                break;
            case 2:
                displayAllStudents();
                break;
            case 3:
                modifyStudent();
                break;
            case 4:
                deleteStudent();
                break;
            case 5:
                saveToFile(filename);
                cout << "Exiting...\n";
                break;
            default:
                cout << "Invalid choice. Please try again.\n";
        }
    } while (choice != 5);

    return 0;
}


