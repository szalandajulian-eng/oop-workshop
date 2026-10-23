//
// Created by wiktorw on 2025-01-29.
//

#include "Student.h"

using namespace std;

Student::Student(int studentId, string firstName, string lastName)
    : studentId(studentId), firstName(firstName), lastName(lastName)
{
    // this->studentId = studentId;  /* Prefer constructor initializer above! */
}

Student::~Student() {
}

string Student::getFirstName(){
    return firstName;
}

string Student::getLastName(){
    return lastName;
}

int Student::getStudentId() {
    return studentId;
}
