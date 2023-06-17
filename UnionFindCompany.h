//
// Created by Muhammad Biadsy on 09/06/2022.
//

#ifndef UNIONFINDCOMPANY_H_
#define UNIONFINDCOMPANY_H_

#include "Company.h"

class UnionFindCompany {
public:
    AvlRankTree<Company>* companies;
    int *parents;
    int *acquirer;
    UnionFindCompany(int k);
    ~UnionFindCompany();
    int find(int company_id) const;
    void uniteCompanies(int company_id1,int company_id2, double factor);
    int getAcquirer(int company_id);
};

#endif //UNIONFINDCOMPANY_H_
