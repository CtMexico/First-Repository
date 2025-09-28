#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Struct definition - TODO for students
struct Student {
    string id;
    string name;
    string major;
    string hobby;
    double gpa;
    string email;
    string city;
};

// =======================
// Function Definitions (Your TODOs)
// =======================
// Because we have no function prototypes, you must define all functions here, BEFORE main.

// TODO: Complete the parameter list and implement the function body.
void inputAndSave(Student students[], int &n) {
    cout << "Enter number of students: " << endl;
    cin >> n;

    ofstream fout("students.txt");
    if(!fout) {
        cout << "Error opening file for writing." << endl;
        return;
    }

    for(int i = 0; i < n; ++i) {
        cout << "Enter data for student " << (i + 1) << ":\n";
        cout << "ID: "; cin >> students[i].id;
        cout << "Name: "; cin >> students[i].name;
        cout << "Major: "; cin >> students[i].major;
        cout << "Hobby: "; cin >> students[i].hobby;
        cout << "GPA: "; cin >> students[i].gpa;
        cout << "Email: "; cin >> students[i].email;
        cout << "City: "; cin >> students[i].city;

        fout << students[i].id << " "
             << students[i].name << " "
             << students[i].major << " "
             << students[i].hobby << " "
             << students[i].gpa << " "
             << students[i].email << " "
             << students[i].city << endl;
    }
    fout.close();
    cout << "Data saved to students.txt\n";
}

// TODO: Complete the parameter list and implement the function body.
int loadStudents(Student students[]) {
    ifstream fin("students.txt");
    if (!fin) {
        cout << "Error opening file for reading." << endl;
        return 0;
    }

    int count = 0;
    while (fin >> students[count].id
               >> students[count].name
               >> students[count].major
               >> students[count].hobby
               >> students[count].gpa
               >> students[count].email
               >> students[count].city) {
        count++;
    }
    fin.close();
    cout << count << " students loaded from file.\n";
    return count;
}

// TODO: Complete the parameter list and implement the function body.
void displayStudents(Student students[], int n) {
    cout << "\n=== Students in Memory ===\n";
    for(int i = 0; i < n; i++) {
        cout << students[i].name << endl;
    }
}

// TODO: Complete the parameter list and implement the function body.
void queryByCity(Student students[], int n, const string &city) {
    cout << "\nStudents from " << city << ":\n";
    bool found = false;
    for (int i = 0; i < n; i++) {
        if (students[i].city == city) {
            cout << students[i].name << endl;
            found = true;
        }
    }
    if (!found) {
        cout << "No students found from " << city << ".\n";
    }
}

// TODO: Complete the parameter list and implement the function body.
int countHonors(Student students[], int n) {
    int count = 0;
    for(int i = 0; i < n; i++) {
        if(students[i].gpa >= 3.0) {
            count++;
        }
    }
    return count;
}


// =======================
// Main Function 
// =======================
int main() {
    Student students[100];  
    int n = 0;              
    int choice;

    do {
        cout << "\n=== Student Information Management ===\n";
        cout << "1. Input students and store to file\n";
        cout << "2. Read students from file and display\n";
        cout << "3. Query student information by city\n";
        cout << "4. Count students with GPA >= 3.0\n";
        cout << "5. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        if (choice == 1) {
            inputAndSave(students, n);            
        } else if (choice == 2) {
            n = loadStudents(students);
            displayStudents(students, n);
        } else if (choice == 3) {
            string city;
            cout << "Enter city: ";
            cin >> city;
            queryByCity(students, n, city);

        } else if (choice == 4) {
            int honorsCount = countHonors(students, n);
            cout << "Number of students with GPA >= 3.0: " << honorsCount << endl;
        }
    } while (choice != 5);

    return 0;
}
