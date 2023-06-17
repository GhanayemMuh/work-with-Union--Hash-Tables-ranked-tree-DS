//
// Created by Muhammad Biadsy on 09/06/2022.
//

#ifndef LIST_H_
#define LIST_H_

#include "Employee.h"


class Node {
public:
    Node *prev;
    Node *next;
    Employee data;
    Node(Node *p, Node *n,const Employee &d);
    ~Node() = default;
};


class List {
public:
    Node *first;
    Node *last;
    List();
    ~List();
    void add(const Employee &employee);
    void remove(int employee_id);
    Employee* get(int employee_id) const;
};


#endif //LIST_H_
