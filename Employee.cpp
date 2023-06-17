//
// Created by Muhammad Biadsy on 23/04/2022.
//

#include "Employee.h"

Employee::Employee(int employee_id1, int salary1, int grade1,int company_id1):
employee_id(employee_id1),salary(salary1),grade(grade1),company_id(company_id1) {}

Employee::Employee(int employee_id1):employee_id(employee_id1),salary(0),grade(0),company_id(0) {}

int getGrade(const Employee &employee)
{
    return employee.grade;
}

bool operator<(const Employee& employee1, const Employee& employee2)
{
    if (employee1.employee_id == employee2.employee_id)
    {
        return false;
    }
    return employee1.salary != employee2.salary ?
           employee1.salary < employee2.salary : employee1.employee_id < employee2.employee_id;
}

bool operator>(const Employee& employee1, const Employee& employee2)
{
    if (employee1.employee_id == employee2.employee_id)
    {
        return false;
    }
    return employee1.salary != employee2.salary ?
           employee1.salary > employee2.salary : employee1.employee_id > employee2.employee_id;
}

bool operator==(const Employee& employee1, const Employee& employee2)
{
    return (employee1.salary == employee2.salary) && (employee1.employee_id == employee2.employee_id);
}

bool operator!=(const Employee& employee1, const Employee& employee2)
{
    if (employee1 == employee2)
    {
        return false;
    }
    return true;
}

bool operator>=(const Employee& employee1, const Employee& employee2)
{
    if (employee1 < employee2)
    {
        return false;
    }
    return true;
}

bool operator<=(const Employee& employee1, const Employee& employee2)
{
    if (employee1 > employee2)
    {
        return false;
    }
    return true;
}
