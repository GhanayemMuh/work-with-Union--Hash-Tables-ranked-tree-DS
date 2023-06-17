//
// Created by Muhammad Biadsy on 09/06/2022.
//

#include "UnionFindCompany.h"

UnionFindCompany::UnionFindCompany(int k):companies(new AvlRankTree<Company>[k+1]),parents(new int [k+1]),
acquirer(new int[k+1])
{
    for (int i = 0; i < k+1; i++)
    {
        Company new_company(i);
        new_company.value = i;
        companies[i].insert(new_company);
        parents[i] = i;
        acquirer[i] = i;
    }
}

UnionFindCompany::~UnionFindCompany()
{
    delete[] companies;
    delete[] parents;
    delete[] acquirer;
}

int UnionFindCompany::find(int company_id) const
{
    if (parents[company_id] == company_id)
    {
        return company_id;
    }
    return parents[company_id] = this->find(parents[company_id]);
}

void UnionFindCompany::uniteCompanies(int company_id1, int company_id2,double factor)
{
    Company* company1 = companies[find(company_id1)].getPtrValue(Company(find(company_id1)));
    Company* company2 = companies[find(company_id2)].getPtrValue(Company(find(company_id2)));
    double increase_value = companies[find(getAcquirer(company_id2))].
            getPtrValue(Company(getAcquirer(company_id2)))->value * factor;
    if (companies[find(company_id1)].getSize() > companies[find(company_id2)].getSize())
    {
        company1->employees->mergeTable(*company2->employees);
        company1->active_employees->mergeTree(*company2->active_employees);
        company2->active_employees->empty();
        company1->sum_not_active_employees_grades += company2->sum_not_active_employees_grades;
        companies[find(company_id1)].increaseFields(increase_value,increaseValue);
        companies[find(company_id1)].mergeTree(companies[find(company_id2)]);
        parents[find(company_id2)] = find(company_id1);
    }
    else if (companies[find(company_id1)].getSize() <= companies[find(company_id2)].getSize())
    {
        company2->employees->mergeTable(*company1->employees);
        company2->active_employees->mergeTree(*company1->active_employees);
        company1->active_employees->empty();
        company2->sum_not_active_employees_grades += company1->sum_not_active_employees_grades;
        companies[find(company_id1)].increaseFields(increase_value,increaseValue);
        companies[find(company_id2)].mergeTree(companies[find(company_id1)]);
        parents[find(company_id1)] = find(company_id2);
    }
    acquirer[getAcquirer(company_id2)] = getAcquirer(company_id1);
}

int UnionFindCompany::getAcquirer(int company_id)
{
    if (acquirer[company_id] == company_id)
    {
        return company_id;
    }
    return acquirer[company_id] = this->getAcquirer(acquirer[company_id]);
}
