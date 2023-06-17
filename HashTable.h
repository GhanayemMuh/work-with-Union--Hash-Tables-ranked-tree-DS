//
// Created by Muhammad Biadsy on 09/06/2022.
//

#ifndef HASHTABLE_H_
#define HASHTABLE_H_

#include "List.h"

class HashTable {
    List* list;
    long long size;
    long long elements_number;
public:
    HashTable();
    ~HashTable();
    bool add(const Employee& employee);
    bool remove(int id);
    Employee* get(int id);
    long long getSize() const;
    void mergeTable(const HashTable& hashTable);
};

#endif //HASHTABLE_H_
