// YourName_Lab2.cpp — CSCI 272 Week 2 (Arrays + Function Overloading)
#include <iostream>
#include <string>
#include <limits>
#include <iomanip>
using namespace std;

const int MAX = 5; // 1–5
// Score[i][0]=Math, [1]=C Programming, [2]=Operating Systems

// ---------- Define functions BEFORE main (fill the TODOs) ----------
void inputGrades(int n, string NameArr[], double Score[][3]) {
    cin.ignore(numeric_limits<streamsize>::max(), '\n');
    for (int i = 0; i < n; i++) {
        cout << "Enter name of student " << (i + 1) << ": ";
        getline(cin, NameArr[i]);

        for (int j = 0; j < 3; j++) {
            string subject;
            if (j == 0) subject = "Math";
            else if (j == 1) subject = "C Programming";
            else subject = "Operating Systems";

            do {
                cout << "Enter " << subject << " grade (0-100): ";
                cin >> Score[i][j];
                if (cin.fail() || Score[i][j] < 0 || Score[i][j] > 100) {
                    cout << "Invalid grade! Try again.\n";
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                } else break;
            } while (true);
        }
    }
}

void calculateStudent(int i, double Score[][3], double &total, double &avg) {
    
    total = 0;
    for (int j = 0; j < 3; j++)
        total += Score[i][j];
    avg = total / 3.0;
    
}

int findTopStudent(int n, double Score[][3]) {

    int topIdx = 0;
    double topTotal = -1;
    for (int i = 0; i < n; i++) {
        double total, avg;
        calculateStudent(i, Score, total, avg);
        if (total > topTotal) {
            topTotal = total;
            topIdx = i;
        }
    }
    
    return topIdx;
}

// Overloading (Part 2): print one & print all
void printInfo(string name, double scores[3]) {

    double total = 0, avg = 0;
    for (int j = 0; j < 3; j++)
        total += scores[j];
    avg = total / 3.0;

    cout << left << setw(12) << name;
    for (int j = 0; j < 3; j++)
        cout << setw(8) << scores[j];
    cout << setw(8) << total << setw(8) << avg << endl;
    
}

void printInfo(int n, string NameArr[], double Score[][3]) {

    cout << left << setw(12) << "Name"
         << setw(8) << "Math"
         << setw(8) << "C_Prog"
         << setw(8) << "OS"
         << setw(8) << "Total"
         << setw(8) << "Avg" << endl;
    cout << string(50, '-') << endl;

    for (int i = 0; i < n; i++) {
        printInfo(NameArr[i], Score[i]);
    }
    
}

// Part 1: display all (initial version). After overloading, update this to call printInfo(n, NameArr, Score).
void displayAll(int n, string NameArr[], double Score[][3]) {
    printInfo(n, NameArr, Score);
}

// ------------------------------ main ------------------------------
int main() {
    string NameArr[MAX];
    double Score[MAX][3] = {}; // zero-initialize
    int n = 0;
    bool hasData = false;

    cout << fixed << setprecision(2);

    int choice;
    do {
        cout << "\n--- Menu ---\n"
             << "1) Record grades\n"
             << "2) Calculate one student's total & average\n"
             << "3) Display all students\n"
             << "4) Find top student\n"
             << "5) Exit\n"
             << "Enter choice: ";
        cin >> choice;

        switch (choice) {
        case 1: {
        
            cout << "How many students (1-" << MAX << ")? ";
            cin >> n;
            if (n > 0 && n <= MAX) {
                inputGrades(n, NameArr, Score);
                hasData = true;
            } else {
                cout << "Invalid number of students.\n";
            }
            
            break;
        }
        case 2: {
            
            if (!hasData) {
                cout << "Please record grades first (option 1).\n";
            } else {
                int idx;
                cout << "Enter student index (0.." << (n - 1) << "): ";
                cin >> idx;
                if (idx >= 0 && idx < n) {
                    double total, avg;
                    calculateStudent(idx, Score, total, avg);
                    cout << NameArr[idx] << " - Total: " << total
                         << ", Average: " << avg << endl;
                } else {
                    cout << "Invalid index.\n";
                }
            }
            
            break;
        }
        case 3: {

            if (!hasData) {
                cout << "Please record grades first (option 1).\n";
            } else {
                displayAll(n, NameArr, Score);
            }
            
            break;
        }
        case 4: {

            if (!hasData) {
                cout << "Please record grades first (option 1).\n";
            } else {
                int idx = findTopStudent(n, Score);
                double total, avg;
                calculateStudent(idx, Score, total, avg);
                cout << "Top student: " << NameArr[idx]
                     << " (Total: " << total << ", Avg: " << avg << ")\n";
            }
            
            break;
        }
        case 5:
            cout << "Bye!\n"; break;
        default:
            cout << "Invalid choice. Try 1–5.\n";
        }
    } while (choice != 5);

    return 0;
}
