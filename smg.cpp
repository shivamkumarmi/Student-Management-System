#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

// Student class
class Student {
public:
    int roll;
    string name;
    string branch;
    float marks;

    Student() {}

    Student(int r, string n, string b, float m) {
        roll = r;
        name = n;
        branch = b;
        marks = m;
    }

    // Convert student data into one line for file
    string toFileLine() {
        stringstream ss;
        ss << roll << "," << name << "," << branch << "," << marks;
        return ss.str();
    }

    // Display student details
    void display() {
        cout << "Roll No : " << roll << endl;
        cout << "Name    : " << name << endl;
        cout << "Branch  : " << branch << endl;
        cout << "Marks   : " << marks << endl;
        cout << "----------------------------" << endl;
    }
};

const string FILENAME = "students.txt";

// Read students from file
vector<Student> loadStudents() {
    vector<Student> list;

    ifstream file(FILENAME);
    string line;

    while (getline(file, line)) {
        if (line.empty())
            continue;

        stringstream ss(line);

        string rollStr;
        string name;
        string branch;
        string marksStr;

        getline(ss, rollStr, ',');
        getline(ss, name, ',');
        getline(ss, branch, ',');
        getline(ss, marksStr, ',');

        Student s(
            stoi(rollStr),
            name,
            branch,
            stof(marksStr)
        );

        list.push_back(s);
    }

    file.close();

    return list;
}

// Save students to file
void saveStudents(vector<Student>& list) {
    ofstream file(FILENAME);

    for (auto& s : list) {
        file << s.toFileLine() << endl;
    }

    file.close();
}

// Add student
void addStudent() {
    vector<Student> list = loadStudents();

    int roll;
    string name;
    string branch;
    float marks;

    cout << "\nEnter Roll No: ";
    cin >> roll;

    cin.ignore();

    cout << "Enter Name: ";
    getline(cin, name);

    cout << "Enter Branch: ";
    getline(cin, branch);

    cout << "Enter Marks: ";
    cin >> marks;

    Student s(roll, name, branch, marks);

    list.push_back(s);

    saveStudents(list);

    cout << "\nStudent added successfully!\n";
}

// View all students
void viewAllStudents() {
    vector<Student> list = loadStudents();

    if (list.empty()) {
        cout << "\nNo records found.\n";
        return;
    }

    cout << "\n---- All Student Records ----\n";

    for (auto& s : list) {
        s.display();
    }
}

// Search student
void searchStudent() {
    vector<Student> list = loadStudents();

    int roll;

    cout << "\nEnter Roll No to search: ";
    cin >> roll;

    bool found = false;

    for (auto& s : list) {
        if (s.roll == roll) {
            cout << "\nStudent Found:\n";
            s.display();

            found = true;
            break;
        }
    }

    if (!found) {
        cout << "\nNo student found with Roll No "
             << roll << endl;
    }
}

// Delete student
void deleteStudent() {
    vector<Student> list = loadStudents();

    int roll;

    cout << "\nEnter Roll No to delete: ";
    cin >> roll;

    bool found = false;

    vector<Student> updatedList;

    for (auto& s : list) {
        if (s.roll == roll) {
            found = true;
        }
        else {
            updatedList.push_back(s);
        }
    }

    if (found) {
        saveStudents(updatedList);

        cout << "\nStudent record deleted successfully!\n";
    }
    else {
        cout << "\nNo student found with Roll No "
             << roll << endl;
    }
}

// Main function
int main() {

    int choice;

    do {
        cout << "\n===== STUDENT MANAGEMENT SYSTEM =====\n";
        cout << "1. Add Student\n";
        cout << "2. View All Students\n";
        cout << "3. Search Student by Roll No\n";
        cout << "4. Delete Student\n";
        cout << "5. Exit\n";

        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {

            case 1:
                addStudent();
                break;

            case 2:
                viewAllStudents();
                break;

            case 3:
                searchStudent();
                break;

            case 4:
                deleteStudent();
                break;

            case 5:
                cout << "\nExiting program. Goodbye!\n";
                break;

            default:
                cout << "\nInvalid choice, try again.\n";
        }

    } while (choice != 5);

    return 0;
}