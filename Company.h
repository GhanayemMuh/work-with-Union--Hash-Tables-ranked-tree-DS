//
// Created by Muhammad Biadsy on 23/04/2022.
//

#ifndef COMPANY_H_
#define COMPANY_H_

#include <iostream>
#include "AvlRankTree.h"
#include "HashTable.h"
#include "Employee.h"

class Company{
public:
    int company_id;
    double value;
    std::shared_ptr<AvlRankTree<Employee>> active_employees;
    std::shared_ptr<HashTable> employees;
    long long sum_not_active_employees_grades;
    explicit Company(int company_id1);
    Company();
    ~Company() = default;
    Company(const Company& other) = default;
    Company& operator=(const Company& other) = default;
    friend void increaseValue(Company* company,double value1);
    friend int getId(const Company& company);
};

void increaseValue(Company* company,double value1);
int getId(const Company& company);
bool operator<(const Company& company1, const Company& company2);
bool operator>(const Company& company1, const Company& company2);
bool operator==(const Company& company1, const Company& company2);
bool operator>=(const Company& company1, const Company& company2);
bool operator<=(const Company& company1, const Company& company2);
bool operator!=(const Company& company1, const Company& company2);

#endif //COMPANY_H_
