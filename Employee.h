//
// Created by Muhammad Biadsy on 23/04/2022.
//

#ifndef EMPLOYEE_H_
#define EMPLOYEE_H_

#include <iostream>
#include <memory>


class Employee {
public:
    int employee_id;
    int salary;
    int grade;
    int company_id;
    Employee() = default;
    explicit Employee(int employee_id1);
    Employee(int employee_id1, int salary1, int grade1,int company_id1);
    ~Employee() = default;
    Employee(const Employee& other) = default;
    Employee& operator=(const Employee& other) = default;
    friend int getGrade(const Employee& employee);
};

int getGrade(const Employee& employee);
bool operator<(const Employee& employee1, const Employee& employee2);
bool operator>(const Employee& employee1, const Employee& employee2);
bool operator==(const Employee& employee1, const Employee& employee2);
bool operator>=(const Employee& employee1, const Employee& employee2);
bool operator<=(const Employee& employee1, const Employee& employee2);
bool operator!=(const Employee& employee1, const Employee& employee2);


#endif //EMPLOYEE_H_
