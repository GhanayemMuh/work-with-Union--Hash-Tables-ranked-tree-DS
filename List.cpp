//
// Created by Muhammad Biadsy on 10/06/2022.
//

#include "List.h"


Node::Node(Node *p,Node *n,const Employee &d) : prev(p), next(n), data(Employee(d)){}

List::List() : first(nullptr),last(nullptr) {}

List::~List()
{
    while (first)
    {
        Node *tmp = first;
        first = first->next;
        delete tmp;
    }
    first = nullptr;
    last = nullptr;
}


void List::add(const Employee &employee)
{
    Node *n = nullptr;
    n = new Node(nullptr, nullptr,employee);
    if (!first)
    {
        first = n;
        last = n;
        return;
    }
    last->next = n;
    n->prev = last;
    last = n;
}

void List::remove(int employee_id)
{
    Node *current = first;
    while (current)
    {
        if (current->data.employee_id == employee_id)
        {
            if (current->next)
            {
                current->next->prev = current->prev;
            }
            if (current->prev)
            {
                current->prev->next = current->next;
            }
            if (current == first)
            {
                if (current->next)
                {
                    first = current->next;
                }
                else
                {
                    first = nullptr;
                }
            }
            if (current == last)
            {
                last = current->prev;
            }
            delete current;
            return;
        }
        current = current->next;
    }
}

Employee* List::get(int employee_id) const
{
    if (this)
    {
        Node *tmp = first;
        while (tmp)
        {
            if (tmp->data.employee_id == employee_id)
            {
                return &tmp->data;
            }
            tmp = tmp->next;
        }
    }
    return nullptr;
}