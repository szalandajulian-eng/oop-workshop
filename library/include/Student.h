//
// Created by wiktorw on 2025-01-29.
//

#ifndef STUDENT_H
#define STUDENT_H

#include <string>

class Student {
public:
    Student(int studentId, std::string firstName, std::string lastName);
    Student(const Student& orig) = default;
    virtual ~Student();
    
    [[nodiscard]] std::string getFirstName();
    [[nodiscard]] std::string getLastName();
    [[nodiscard]] int getStudentId();

private:
    int studentId;
    std::string firstName;
    std::string lastName;

};

#endif /* STUDENT_H_INCLUDED */

