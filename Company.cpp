//
// Created by Muhammad Biadsy on 23/04/2022.
//

#include "Company.h"

Company::Company():company_id(0),value(0)
{
    sum_not_active_employees_grades = 0;
    employees = std::make_shared<HashTable>();
    active_employees = std::make_shared<AvlRankTree<Employee>>(getGrade);
}

Company::Company(int company_id1):company_id(company_id1),value(0),sum_not_active_employees_grades(0)
{
    employees = std::make_shared<HashTable>();
    active_employees = std::make_shared<AvlRankTree<Employee>>(getGrade);
}

int getId(const Company& company)
{
    return company.company_id;
}

void increaseValue(Company* company,double value1)
{
    company->value += value1;
}

bool operator<(const Company& company1, const Company& company2)
{
    if (company1.company_id >= company2.company_id)
    {
        return false;
    }
    return true;
}

bool operator>(const Company& company1, const Company& company2)
{
    if (company1.company_id <= company2.company_id)
    {
        return false;
    }
    return true;
}

bool operator==(const Company& company1, const Company& company2)
{
    if (company1.company_id == company2.company_id)
    {
        return true;
    }
    return false;
}

bool operator!=(const Company& company1, const Company& company2)
{
    if (company1 == company2)
    {
        return false;
    }
    return true;
}

bool operator>=(const Company& company1, const Company& company2)
{
    if (company1 < company2)
    {
        return false;
    }
    return true;
}

bool operator<=(const Company& company1, const Company& company2)
{
    if (company1 > company2)
    {
        return false;
    }
    return true;
}
