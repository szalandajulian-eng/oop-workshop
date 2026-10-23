#include <iostream>
#include "functions.h"
#include "Student.h"

using namespace std;

int main() {
    cout << "Hello there!" << endl;
    int year = welcome();
    cout << "This is the year " << year << "."
         << endl;
    cout << "And here we have:" << endl;

    Student stud(124, "Adam", "Smith");
    cout << " Student " << stud.getStudentId()
         << " - " << stud.getFirstName()
         << " " << stud.getLastName() << endl;
    return 0;
}