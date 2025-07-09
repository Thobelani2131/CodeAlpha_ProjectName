#include <iostream>
#include <iomanip>
using namespace std;

int main() {
    int numCourses;
    double grade, totalGradePoints = 0;
    int credit, totalCredits = 0;

    cout << "Enter the number of modules you take for your course: ";
    cin >> numCourses;

    for (int i = 1; i <= numCourses; ++i) {
        cout << "Enter grade for each module " << i << ": ";
        cin >> grade;

        cout << "Enter credit hours for module " << i << ": ";
        cin >> credit;

        totalGradePoints += grade * credit;
        totalCredits += credit;

        cout << "Course " << i << ": Grade: " << grade << ", Credits: " << credit << endl;
    }

    double cgpa = totalGradePoints / totalCredits;

    cout << fixed << setprecision(2);
    cout << "\nTotal Credits: " << totalCredits << endl;
    cout << "Total Grade Points: " << totalGradePoints << endl;
    cout << "Final CGPA: " << cgpa << endl;

    return 0;
}
