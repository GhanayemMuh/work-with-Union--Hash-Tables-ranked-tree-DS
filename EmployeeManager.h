//
// Created by Muhammad Biadsy on 09/06/2022.
//

#ifndef EMPLOYEEMANAGER_H_
#define EMPLOYEEMANAGER_H_

#include "library2.h"
#include "AvlRankTree.h"
#include "HashTable.h"
#include "Employee.h"
#include "Company.h"
#include "UnionFindCompany.h"

class EmployeeManager {
    int k;
    UnionFindCompany union_find;
    AvlRankTree<Employee> active_employees;
    HashTable employees;
    long long sum_not_active_employees_grades;
    int max_id;
public:
    explicit EmployeeManager(int k);
    ~EmployeeManager() = default;
    StatusType AddEmployee(int employeeID, int companyID, int grade);
    StatusType RemoveEmployee(int employeeID);
    StatusType AcquireCompany(int companyID1, int companyID2, double factor);
    StatusType EmployeeSalaryIncrease(int employeeID, int salaryIncrease);
    StatusType PromoteEmployee(int employeeID, int bumpGrade);
    StatusType SumOfBumpGradeBetweenTopWorkersByGroup(int companyID, int m);
    StatusType AverageBumpGradeBetweenSalaryByGroup(int companyID, int lowerSalary, int higherSalary);
    StatusType CompanyValue(int companyID);
};

#endif //EMPLOYEEMANAGER_H_
