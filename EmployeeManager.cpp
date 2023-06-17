//
// Created by Muhammad Biadsy on 09/06/2022.
//

#include "EmployeeManager.h"
#include <cmath>

EmployeeManager::EmployeeManager(int k): k(k), union_find(k),active_employees(getGrade),employees(),
sum_not_active_employees_grades(0),max_id(0){}

StatusType EmployeeManager::AddEmployee(int employeeID, int companyID, int grade)
{
    if (employeeID <= 0 || companyID <= 0 || companyID > k || grade < 0)
    {
        return INVALID_INPUT;
    }
    Employee new_employee = Employee(employeeID,0,grade,union_find.find(companyID));
    if (employees.get(employeeID))
    {
        return FAILURE;
    }
    try
    {
        Company* company = union_find.companies[union_find.find(companyID)].
                getPtrValue(Company(union_find.find(companyID)));
        employees.add(new_employee);
        company->employees->add(new_employee);
        sum_not_active_employees_grades += grade;
        company->sum_not_active_employees_grades += grade;
        max_id = employeeID > max_id ? employeeID : max_id;
    }
    catch (std::bad_alloc&)
    {
        return ALLOCATION_ERROR;
    }
    return SUCCESS;
}

StatusType EmployeeManager::RemoveEmployee(int employeeID)
{
    if (employeeID <= 0)
    {
        return INVALID_INPUT;
    }
    if (!employees.get(employeeID))
    {
        return FAILURE;
    }
    try
    {
        Company* company =  union_find.companies[union_find.find(employees.get(employeeID)->company_id)].
                getPtrValue(Company(union_find.find(employees.get(employeeID)->company_id)));
        Employee edit_employee(employees.get(employeeID)->employee_id,
                               employees.get(employeeID)->salary,
                               employees.get(employeeID)->grade,
                               employees.get(employeeID)->company_id);
        company->employees->remove(employeeID);
        employees.remove(employeeID);
        if (edit_employee.salary > 0)
        {
            company->active_employees->remove(edit_employee);
            active_employees.remove(edit_employee);
        }
        else
        {
            sum_not_active_employees_grades -= edit_employee.grade;
            company->sum_not_active_employees_grades -= edit_employee.grade;
        }
    }
    catch (std::bad_alloc&)
    {
        return ALLOCATION_ERROR;
    }
    catch (Failure&)
    {
        return FAILURE;
    }
    return SUCCESS;
}

StatusType EmployeeManager::AcquireCompany(int companyID1, int companyID2, double factor)
{
    if (companyID1 <= 0 || companyID1 > k || companyID2 <= 0 || companyID2 > k ||
        companyID1 == companyID2 || factor <= 0.0 || union_find.find(companyID1) == union_find.find(companyID2))
    {
        return INVALID_INPUT;
    }
    try
    {
        union_find.uniteCompanies(companyID1,companyID2,factor);
    }
    catch (std::bad_alloc&)
    {
        return ALLOCATION_ERROR;
    }
    catch (Failure&)
    {
        return FAILURE;
    }
    return SUCCESS;
}

StatusType EmployeeManager::EmployeeSalaryIncrease(int employeeID, int salaryIncrease)
{
    if (employeeID <= 0 || salaryIncrease <= 0)
    {
        return INVALID_INPUT;
    }
    if (!employees.get(employeeID))
    {
        return FAILURE;
    }
    try
    {
        Company* company = union_find.companies[union_find.find(employees.get(employeeID)->company_id)].
                getPtrValue(Company(union_find.find(employees.get(employeeID)->company_id)));
        Employee edit_employee(employees.get(employeeID)->employee_id,
                               employees.get(employeeID)->salary,
                               employees.get(employeeID)->grade,
                               employees.get(employeeID)->company_id);
            employees.remove(employeeID);
            company->employees->remove(employeeID);
            if (edit_employee.salary > 0)
            {
                active_employees.remove(edit_employee);
                company->active_employees->remove(edit_employee);
            }
            else
            {
                sum_not_active_employees_grades -= edit_employee.grade;
                company->sum_not_active_employees_grades -= edit_employee.grade;
            }
            edit_employee.salary += salaryIncrease;
            employees.add(edit_employee);
            company->employees->add(edit_employee);
            active_employees.insert(edit_employee);
            company->active_employees->insert(edit_employee);
    }
    catch (std::bad_alloc&)
    {
        return ALLOCATION_ERROR;
    }
    catch (Failure&)
    {
        return FAILURE;
    }
    return SUCCESS;
}

StatusType EmployeeManager::PromoteEmployee(int employeeID, int bumpGrade)
{
    if (employeeID <= 0)
    {
        return INVALID_INPUT;
    }
    if (!employees.get(employeeID))
    {
        return FAILURE;
    }
    try
    {
        if(bumpGrade > 0)
        {
            Company* company = union_find.companies[union_find.find(employees.get(employeeID)->company_id)].
                    getPtrValue(Company(union_find.find(employees.get(employeeID)->company_id)));
            Employee edit_employee(employees.get(employeeID)->employee_id,
                                   employees.get(employeeID)->salary,
                                   employees.get(employeeID)->grade,
                                   employees.get(employeeID)->company_id);
                employees.remove(employeeID);
                company->employees->remove(employeeID);
                if (edit_employee.salary > 0)
                {
                    active_employees.remove(edit_employee);
                    company->active_employees->remove(edit_employee);
                }
                edit_employee.grade += bumpGrade;
                employees.add(edit_employee);
                company->employees->add(edit_employee);
                if (edit_employee.salary > 0)
                {
                    active_employees.insert(edit_employee);
                    company->active_employees->insert(edit_employee);
                }
                else
                {
                    sum_not_active_employees_grades += bumpGrade;
                    company->sum_not_active_employees_grades += bumpGrade;
                }
        }
    }
    catch (std::bad_alloc&)
    {
        return ALLOCATION_ERROR;
    }
    catch (Failure&)
    {
        return FAILURE;
    }
    return SUCCESS;
}

StatusType EmployeeManager::SumOfBumpGradeBetweenTopWorkersByGroup(int companyID, int m)
{
    if (companyID < 0 || companyID > k || m <= 0)
    {
        return INVALID_INPUT;
    }
    long long standing = 0;
    try
    {
        if (companyID > 0)
        {
            Company* company = union_find.companies[union_find.find(companyID)].
                               getPtrValue(Company(union_find.find(companyID)));
            if (company->active_employees->getSize() < m)
            {
                return FAILURE;
            }
            standing = company->active_employees->sumHighestSalaryEmployeesGrades(m);
        }
        else
        {
            if (active_employees.getSize() < m)
            {
                return FAILURE;
            }
            standing = active_employees.sumHighestSalaryEmployeesGrades(m);
        }
    }
    catch (std::bad_alloc&)
    {
        return ALLOCATION_ERROR;
    }
    catch (Failure&)
    {
        return FAILURE;
    }
    printf("SumOfBumpGradeBetweenTopWorkersByGroup: %lld\n", standing);
    return SUCCESS;
}

StatusType EmployeeManager::AverageBumpGradeBetweenSalaryByGroup(int companyID, int lowerSalary, int higherSalary)
{
    if (higherSalary < 0 || lowerSalary < 0 || lowerSalary > higherSalary || companyID > k || companyID < 0)
    {
        return INVALID_INPUT;
    }
    double standing = 0;
    long long sum = 0,num = 0;
    try
    {
        Employee e1(0,lowerSalary,0,0);
        Employee e2(max_id+1,higherSalary,0,0);
        if (companyID > 0)
        {
            Company* company = union_find.companies[union_find.find(companyID)].
                               getPtrValue(Company(union_find.find(companyID)));
            company->active_employees->sumGradesBetweenSalaryEmployees(&sum,&num,&e1,&e2);
            if (!lowerSalary)
            {
                if (!(num + company->employees->getSize() - company->active_employees->getSize()))
                {
                    return FAILURE;
                }
                standing = double (sum + company->sum_not_active_employees_grades)/(
                            num + company->employees->getSize() - company->active_employees->getSize());
            }
            else
            {
                if (!num)
                {
                    return FAILURE;
                }
                standing = double (sum)/num;
            }
        }
        else
        {
            active_employees.sumGradesBetweenSalaryEmployees(&sum,&num,&e1,&e2);
            if (!lowerSalary)
            {
                if (!(num + employees.getSize() - active_employees.getSize()))
                {
                    return FAILURE;
                }
                standing = double (sum + sum_not_active_employees_grades)/(
                            num + employees.getSize() - active_employees.getSize());
            }
            else
            {
                if (!num)
                {
                    return FAILURE;
                }
                standing = double (sum)/num;
            }
        }
    }
    catch (std::bad_alloc&)
    {
        return ALLOCATION_ERROR;
    }
    catch (Failure&)
    {
        return FAILURE;
    }
    printf("AverageBumpGradeBetweenSalaryByGroup: %.1f\n", floor(10 * standing + 0.5f) / 10);
    return SUCCESS;
}

StatusType EmployeeManager::CompanyValue(int companyID)
{
    if (companyID <= 0 || companyID > k)
    {
        return INVALID_INPUT;
    }
    double standing = 0.0;
    try
    {
        standing = union_find.companies[union_find.find(companyID)].getPtrValue(Company(companyID))->value;
    }
    catch (std::bad_alloc&)
    {
        return ALLOCATION_ERROR;
    }
    catch (Failure&)
    {
        return FAILURE;
    }
    printf("CompanyValue: %.1f\n", standing);
    return SUCCESS;
}