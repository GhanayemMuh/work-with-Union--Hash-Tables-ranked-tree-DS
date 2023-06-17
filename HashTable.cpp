//
// Created by Muhammad Biadsy on 09/06/2022.
//

#include "HashTable.h"
#include "List.h"


HashTable::HashTable()
{
    list = new List[2];
    size = 2;
    elements_number = 0;
}

HashTable::~HashTable()
{
    delete[] list;
}

long long HashTable::getSize() const
{
    return elements_number;
}


bool HashTable::add(const Employee &employee)
{
    if (size == elements_number)
    {
        size = 2*size;
        List* new_list = new List[size];
        List* tmp = list;
        for (int i = 0; i < (size/2); i++)
        {
            if (tmp[i].first)
            {
                Node* first = tmp[i].first;
                while (first)
                {
                    new_list[first->data.employee_id%size].add(first->data);
                    first = first->next;
                }
            }
        }
        list = new_list;
        delete[] tmp;
    }
    list[employee.employee_id % size].add(employee);
    elements_number++;
    return true;
}

bool HashTable::remove(int employee_id)
{
    if (size == 4*elements_number)
    {
        size = size/2;
        List* new_list = new List[size];
        List* tmp = list;
        for (int i = 0; i < (size*2); i++)
        {
            if (tmp[i].first)
            {
                Node* first = tmp[i].first;
                while (first)
                {
                    new_list[first->data.employee_id%size].add(first->data);
                    first = first->next;
                }
            }
        }
        list = new_list;
        delete[] tmp;
    }
    list[employee_id%size].remove(employee_id);
    elements_number--;
    return true;
}

Employee *HashTable::get(int employee_id)
{
    return list[employee_id % size].get(employee_id);
}

void HashTable::mergeTable(const HashTable &hashTable)
{
    List* tmp = hashTable.list;
    for (int i = 0; i < hashTable.size; i++)
    {
        if (tmp[i].first)
        {
            Node* first = tmp[i].first;
            while (first)
            {
                this->add(Employee(first->data));
                first = first->next;
            }
        }
    }
}
