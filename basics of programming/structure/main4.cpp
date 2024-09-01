/*Define a structure for a student (Student) that includes the following details:
Student ID (integer)
Full name (string or character array with a maximum length of 20)
Year of admission (integer)
GPA (floating-point number)
Next, implement the following operations:
Command name x: By providing the student's full name (x), the details of that student will be printed.
Command gpa x: Print the details of all students whose GPA is at least x.
Command year x: Print the details of all students whose year of admission is x.
Write a function that takes a Student structure as input and prints all the details in the following format: name id year gpa.
In main, create an array of length n from the Student structure and read the students' details from the input.
Write a program that, based on input commands, prints the result using the function you wrote.
Input:
The first line of input includes two integers, n (the number of students) and t (the number of commands). In the next n lines, the students' information is entered (in the order: student ID, full name, year of admission, and GPA). Then, in the next t lines, the commands (name x, year x, and gpa x) are provided (where x is the parameter). The names of the students are unique.
Output:
For each command, print the corresponding result. Ensure that decimal numbers are printed with two decimal places.
Example Input 1:
4 2
9836230
ArmanRezaei
1398
12.8
40136130
SabaAhmadi
1401
15.25
9936130
SepideRahmati
1399
19.99
40136230
AliTavakoli
1401
14.36
name AliTavakoli
gpa 15
Example Output 1:
AliTavakoli 40136230 1401 14.36
SabaAhmadi 40136130 1401 15.25
SepideRahmati 9936130 1399 19.99
In this output, the first line contains the student whose name is AliTavakoli, and the second and third lines contain students whose GPA is above 15.
*/
#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

struct Student {
    int id;
    string name;
    int year;
    float gpa;
};

void printStudent(const Student &s) {

    cout << s.name << " " << s.id << " " << s.year << " " << fixed << setprecision(2) << s.gpa << endl;
}

int main() {
    int n, t;
    cin >> n >> t;

    Student students[n];

    for (int i = 0; i < n; i++) {
        cin >> students[i].id;
        cin.ignore();
        getline(cin, students[i].name);
        cin >> students[i].year >> students[i].gpa;
    }

    for (int i = 0; i < t; i++) {
        string command, param;
        cin >> command;
        if (command == "name") {
            cin.ignore();
            getline(cin, param);
            bool found = false;
            for (int j = 0; j < n; j++) {
                if (students[j].name == param) {
                    printStudent(students[j]);
                    found = true;
                    break;
                }
            }
            if (!found) {
                cout << "Student not found\n";
            }
        } else if (command == "gpa") {
            float minGpa;
            cin >> minGpa;
            for (int j = 0; j < n; j++) {
                if (students[j].gpa >= minGpa) {
                    printStudent(students[j]);
                }
            }
        } else if (command == "year") {
            int year;
            cin >> year;
            for (int j = 0; j < n; j++) {
                if (students[j].year == year) {
                    printStudent(students[j]);
                }
            }
        }
    }

    return 0;
}