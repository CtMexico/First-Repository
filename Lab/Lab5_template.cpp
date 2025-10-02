#include <iostream>
#include <string>
using namespace std;

// ================= Base Class: Student =================
class Student {
protected:
    // TODO: add id, name, school, phone

public:
    Student() {}
    Student(string id, string name, string school, string phone) {
        // TODO: assign values
    }

    virtual void display() {
        cout << "ID: " << id << ", Name: " << name
             << ", School: " << school << ", Phone: " << phone << endl;
    }

    string getName() { return name; }
};

// ================= CollegeStudent =================
class CollegeStudent : public Student {
    // TODO: add major, year, gpa, iCswl, ccwl

public:
    CollegeStudent() {}
    CollegeStudent(/* parameters */) {
        // TODO
    }

    void setCurrentWorkload(int w) { ccwl = w; }
    int getInitialWorkload() const { return iCswl; }
    int getCurrentWorkload() const { return ccwl; }

    void display() override {
        Student::display();
        cout << "Major: " << major << ", Year: " << year
             << ", GPA: " << gpa
             << ", Initial Workload: " << iCswl
             << ", Current Workload: " << ccwl << endl;
    }
};

// ================= GraduateStudent =================
class GraduateStudent : public Student {
    // TODO: add researchDir, advisor, year, igwl, ccwl

public:
    GraduateStudent() {}
    GraduateStudent(/* parameters */) {
        // TODO
    }

    void setCurrentWorkload(int w) { ccwl = w; }
    int getInitialWorkload() const { return igwl; }
    int getCurrentWorkload() const { return ccwl; }
    string getResearchDir() { return researchDir; }

    void display() override {
        Student::display();
        cout << "Research Direction: " << researchDir
             << ", Advisor: " << advisor
             << ", Year: " << year
             << ", Initial Workload: " << igwl
             << ", Current Workload: " << ccwl << endl;
    }
};

// ================= Project =================
class Project {
    // TODO: add projectId, name, startDate, endDate, grad, cs1, cs2, ppcp

public:
    // Default constructor: set progress to 0
    Project() : ppcp(0) {}

    void init(/* parameters */) {
        // TODO: initialize members
    }

    void updateWorkloads(int g, int c1, int c2) {
        // TODO: call grad/cs1/cs2.setCurrentWorkload and recalc
    }

    void calculateProgress() {
        // TODO: use getInitialWorkload + getCurrentWorkload
    }

    bool isCompleted() {
        // TODO: return true if progress == 100
        return false;
    }

    void display() {
        cout << "\n=== Project " << projectId << " Info ===" << endl;
        cout << "Name: " << name << endl;
        cout << "Start: " << startDate << ", End: " << endDate << endl;
        cout << "Leader (Grad): " << grad.getName() << endl;
        cout << "Competition Category: " << grad.getResearchDir() << endl;
        cout << "Project Progress: " << ppcp << "%" << endl;

        cout << "\nGraduate Student Info:" << endl;
        grad.display();
        cout << "\nCollege Student 1 Info:" << endl;
        cs1.display();
        cout << "\nCollege Student 2 Info:" << endl;
        cs2.display();
    }

    string getId() { return projectId; }
    string getName() { return name; }
    string getLeader() { return grad.getName(); }
    string getCategory() { return grad.getResearchDir(); }
};

// ================= Main Menu =================
int main() {
    int N;
    cout << "Enter number of projects: ";
    cin >> N;

    Project projects[100];
    int projectCount = 0;

    int choice;
    do {
        cout << "\n===== Project Management Menu =====" << endl;
        cout << "1. Input projects" << endl;
        cout << "2. Display project info by ID" << endl;
        cout << "3. Update workloads for a project" << endl;
        cout << "4. Count completed projects" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        if (choice == 1) {
            for (int i = 0; i < N; i++) {
                string pid, pname, sdate, edate;
                cout << "\nEnter Project ID, Name, Start Date, End Date: ";
                cin >> pid >> pname >> sdate >> edate;

                // Graduate
                string gid, gname, gschool, gphone, gresearch, gadvisor;
                int gyear, igwl, gccwl;
                cout << "Enter Graduate info (ID, Name, School, Phone, ResearchDir, Advisor, Year, InitialWorkload, CurrentWorkload): ";
                cin >> gid >> gname >> gschool >> gphone >> gresearch >> gadvisor >> gyear >> igwl >> gccwl;
                GraduateStudent g(gid, gname, gschool, gphone, gresearch, gadvisor, gyear, igwl, gccwl);

                // College1
                string cid1, cname1, cschool1, cphone1, cmajor1;
                int cyear1, iwl1, ccwl1;
                double gpa1;
                cout << "Enter College1 info (ID, Name, School, Phone, Major, Year, GPA, InitialWorkload, CurrentWorkload): ";
                cin >> cid1 >> cname1 >> cschool1 >> cphone1 >> cmajor1 >> cyear1 >> gpa1 >> iwl1 >> ccwl1;
                CollegeStudent c1(cid1, cname1, cschool1, cphone1, cmajor1, cyear1, gpa1, iwl1, ccwl1);

                // College2
                string cid2, cname2, cschool2, cphone2, cmajor2;
                int cyear2, iwl2, ccwl2;
                double gpa2;
                cout << "Enter College2 info (ID, Name, School, Phone, Major, Year, GPA, InitialWorkload, CurrentWorkload): ";
                cin >> cid2 >> cname2 >> cschool2 >> cphone2 >> cmajor2 >> cyear2 >> gpa2 >> iwl2 >> ccwl2;
                CollegeStudent c2(cid2, cname2, cschool2, cphone2, cmajor2, cyear2, gpa2, iwl2, ccwl2);

                projects[projectCount].init(pid, pname, sdate, edate, g, c1, c2);
                projectCount++;
            }
        }
        else if (choice == 2) {
            // TODO: Display project by ID
        }
        else if (choice == 3) {
            // TODO: Update workloads
        }
        else if (choice == 4) {
            // TODO: Count completed projects
        }
    } while (choice != 5);

    return 0;
}
