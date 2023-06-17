//
// Created by Muhammad Biadsy on 20/04/2022.
//

#ifndef AVLRANKTREE_H_
#define AVLRANKTREE_H_

#include <iostream>
#include <memory>
#include "Vertex.h"

class Failure : public std::exception {};

template<class T>
class AvlRankTree {
    Vertex<T>* root;
    Vertex<T>* max;
    long long size;
    int (*getInternalValue)(const T&);
public:
    AvlRankTree();
    explicit AvlRankTree(int (*func)(const T&));
    ~AvlRankTree();
    AvlRankTree(const AvlRankTree& other) = default;
    AvlRankTree& operator=(const AvlRankTree& other) = default;
    void empty();
    Vertex<T>* getRoot() const;
    Vertex<T>* getMax() const;
    Vertex<T>* getMin() const;
    long long getSize() const;
    void insert(const T& value);
    void remove(const T& value);
    void mergeTree(const AvlRankTree<T>& avl_tree);
    T* getPtrValue(const T& value);
    long long sumHighestSalaryEmployeesGrades(int m);
    void sumGradesBetweenSalaryEmployees(long long *sum,long long *num,T* low_value,T* high_value);
    void increaseFields(double value,void (*func)(T*,double));
    void updateArray(int id,int (*func)(const T&),int* array);
};

template<class T>
AvlRankTree<T>::AvlRankTree() :root(nullptr),max(nullptr),size(0),getInternalValue(nullptr) {}

template<class T>
AvlRankTree<T>::AvlRankTree(int (*func)(const T &)) :root(nullptr),max(nullptr),size(0),getInternalValue(func) {}

template<class T>
static void clear(Vertex<T> *vertex)
{
    if (vertex)
    {
        clear(vertex->getLeft());
        clear(vertex->getRight());
        delete vertex;
    }
}

template<class T>
AvlRankTree<T>::~AvlRankTree<T>()
{
    if (root)
    {
        clear(root);
    }
    root = nullptr;
    max = nullptr;
}

template<class T>
void AvlRankTree<T>::empty()
{
    if (root)
    {
        clear(root);
    }
    root = nullptr;
    max = nullptr;
}

template<class T>
Vertex<T> *AvlRankTree<T>::getRoot() const
{
    if (!this || !root)
    {
        return nullptr;
    }
    return root;
}

template<class T>
Vertex<T> *AvlRankTree<T>::getMax() const
{
    if (!this || !root)
    {
        return nullptr;
    }
    return max;
}

template<class T>
Vertex<T> *AvlRankTree<T>::getMin() const
{
    if (!this || !root)
    {
        return nullptr;
    }
    Vertex<T>* min = root;
    while(min->getLeft())
    {
        min = min->getLeft();
    }
    return min;
}

template<class T>
long long AvlRankTree<T>::getSize() const
{
    if (!this || !root)
    {
        return 0;
    }
    return size;
}

static long long getMaxInt(long long x, long long y)
{
    return (x >= y) ? x : y;
}

template<class T>
static Vertex<T>* rotateRight(Vertex<T> *vertex)
{
    Vertex<T>* left = vertex->getLeft();
    vertex->setLeft(left->getRight());
    vertex->setHeight(getMaxInt(vertex->getLeft()->getHeight(),vertex->getRight()->getHeight())+1);
    vertex->setVerticesNumber(vertex->getRight()->getVerticesNumber() + vertex->getLeft()->getVerticesNumber() + 1);
    vertex->setGradesSum(vertex->getRight()->getGradesSum() + vertex->getLeft()->getGradesSum() +
                         vertex->getVertexGrade());
    left->setRight(vertex);
    left->setHeight(getMaxInt(left->getLeft()->getHeight(),left->getRight()->getHeight()) + 1);
    left->setVerticesNumber(left->getRight()->getVerticesNumber() + left->getLeft()->getVerticesNumber() + 1);
    left->setGradesSum(left->getRight()->getGradesSum() + left->getLeft()->getGradesSum() +
                        left->getVertexGrade());
    return left;
}

template<class T>
static Vertex<T>* rotateLeft(Vertex<T> *vertex)
{
    Vertex<T>* right = vertex->getRight();
    vertex->setRight(right->getLeft());
    vertex->setHeight(getMaxInt(vertex->getLeft()->getHeight(),vertex->getRight()->getHeight()) + 1);
    vertex->setVerticesNumber(vertex->getRight()->getVerticesNumber() + vertex->getLeft()->getVerticesNumber() + 1);
    vertex->setGradesSum(vertex->getRight()->getGradesSum() + vertex->getLeft()->getGradesSum() +
                         vertex->getVertexGrade());
    right->setLeft(vertex);
    right->setHeight(getMaxInt(right->getLeft()->getHeight(),right->getRight()->getHeight()) + 1);
    right->setVerticesNumber(right->getRight()->getVerticesNumber() + right->getLeft()->getVerticesNumber() + 1);
    right->setGradesSum(right->getRight()->getGradesSum() + right->getLeft()->getGradesSum() +
            right->getVertexGrade());
    return right;
}

template<class T>
static Vertex<T>* RR(Vertex<T>* vertex)
{
    return rotateLeft(vertex);
}

template<class T>
static Vertex<T>* RL(Vertex<T>* vertex)
{
    vertex->setRight(rotateRight(vertex->getRight()));
    return rotateLeft(vertex);
}

template<class T>
static Vertex<T>* LR(Vertex<T>* vertex)
{
    vertex->setLeft(rotateLeft(vertex->getLeft()));
    return rotateRight(vertex);
}

template<class T>
static Vertex<T>* LL(Vertex<T>* vertex)
{
    return rotateRight(vertex);
}


template<class T>
static int getBalanceFactor(const Vertex<T> *vertex)
{
    if (vertex)
    {
        return (vertex->getLeft()->getHeight() - vertex->getRight()->getHeight());
    }
    return 0;
}

template<class T>
static Vertex<T>* balance(Vertex<T>* vertex)
{
    if (getBalanceFactor(vertex) < -1 && getBalanceFactor(vertex->getRight()) <= 0)
    {
        return RR(vertex);
    }
    if (getBalanceFactor(vertex) < -1 && getBalanceFactor(vertex->getRight()) > 0)
    {
        return RL(vertex);
    }
    if (getBalanceFactor(vertex) > 1 && getBalanceFactor(vertex->getLeft()) < 0)
    {
        return LR(vertex);
    }
    if (getBalanceFactor(vertex) > 1 && getBalanceFactor(vertex->getLeft()) >= 0)
    {
        return LL(vertex);
    }
    return vertex;
}

template<class T>
static Vertex<T>* insertAndBalance(Vertex<T> *vertex, Vertex<T> *to_add)
{
    if (!vertex)
    {
        return nullptr;
    }
    if (vertex->getValue() > to_add->getValue())
    {
        if (vertex->getLeft())
        {
            vertex->setLeft(insertAndBalance(vertex->getLeft(),to_add));
        }
        else
        {
            vertex->setLeft(to_add);
        }
    }
    else
    {
        if (vertex->getRight())
        {
            vertex->setRight(insertAndBalance(vertex->getRight(),to_add));
        }
        else
        {
            vertex->setRight(to_add);
        }
    }
    vertex->setHeight(getMaxInt(vertex->getRight()->getHeight(),vertex->getLeft()->getHeight())+1);
    vertex->setVerticesNumber(vertex->getRight()->getVerticesNumber() + vertex->getLeft()->getVerticesNumber() + 1);
    vertex->setGradesSum(vertex->getRight()->getGradesSum() + vertex->getLeft()->getGradesSum() +
                                    vertex->getVertexGrade());
    return balance(vertex);
}

template<class T>
static Vertex<T> *getVertexByValue(Vertex<T> *vertex, const T &value)
{
    if (vertex)
    {
        if (vertex->getValue() == value)
        {
            return vertex;
        }
        else if (vertex->getValue() > value)
        {
            return getVertexByValue(vertex->getLeft(),value);
        }
        else
        {
            return getVertexByValue(vertex->getRight(),value);
        }
    }
    return nullptr;
}

template<class T>
void AvlRankTree<T>::insert(const T &value)
{
    if (getVertexByValue(root,value))
    {
        throw Failure();
    }
    Vertex<T>* new_vertex = new Vertex<T>(value);
    if (!new_vertex)
    {
        return;
    }
    if (getInternalValue)
    {
        new_vertex->setGetInternalValue(getInternalValue);
        new_vertex->setVerticesNumber(1);
        new_vertex->setGradesSum(getInternalValue(value));
    }
    if (!root)
    {
        root = new_vertex;
        max = new_vertex;
    }
    else
    {
        root = insertAndBalance(root,new_vertex);
        if (max &&  (value > max->getValue()))
        {
            max = new_vertex;
        }
    }
    size++;
}

template<class T>
static Vertex<T>* removeAndBalance(Vertex<T> *vertex, const T &value)
{
    if (!vertex)
    {
        return nullptr;
    }
    if (vertex->getValue() > value)
    {
        vertex->setLeft(removeAndBalance(vertex->getLeft(),value));
    }
    else if (vertex->getValue() < value)
    {
        vertex->setRight(removeAndBalance(vertex->getRight(),value));
    }
    else
    {
        Vertex<T>* tmp;
        if (!vertex->getLeft() && !vertex->getRight())
        {
            tmp = vertex;
            vertex = nullptr;
            delete tmp;
        }
        else if (!vertex->getRight() || !vertex->getLeft())
        {
            tmp = vertex->getLeft() ? vertex->getLeft() : vertex->getRight();
            delete vertex;
            vertex = tmp;
        }
        else
        {
            tmp = vertex->getRight();
            while (tmp->getLeft())
            {
                tmp = tmp->getLeft();
            }
            T tmp_value = vertex->getValue();
            vertex->setValue(tmp->getValue());
            tmp->setValue(tmp_value);
            vertex->setRight(removeAndBalance(vertex->getRight(),tmp_value));
        }
    }
    if (!vertex)
    {
        return nullptr;
    }
    vertex->setHeight(getMaxInt(vertex->getLeft()->getHeight(),vertex->getRight()->getHeight())+1);
    vertex->setVerticesNumber(vertex->getRight()->getVerticesNumber() + vertex->getLeft()->getVerticesNumber() + 1);
    vertex->setGradesSum(vertex->getRight()->getGradesSum() + vertex->getLeft()->getGradesSum() +
                         vertex->getVertexGrade());
    return balance(vertex);
}

template<class T>
void AvlRankTree<T>::remove(const T &value)
{
    if (!getVertexByValue(root,value))
    {
        throw Failure();
    }
    root = removeAndBalance(root,value);
    Vertex<T>* tmp = root;
    while(tmp->getRight())
    {
        tmp = tmp->getRight();
    }
    max = tmp;
    size--;
}

template<class T>
static void inorderIteration(Vertex<T>* vertex,long long number, T *array, long long * index)
{
    if (vertex && *index < number)
    {
        inorderIteration(vertex->getLeft(),number,array,index);
        if (*index >= number)
        {
            return;
        }
        array[*index] = vertex->getValue();
        (*index)++;
        inorderIteration(vertex->getRight(),number,array,index);
    }
}

template<class T>
static T* mergeTwoArrays(const T* array1, const T* array2, long long n1, long long n2)
{
    T* merged = new T[n1+n2];
    long long i = 0;
    long long j = 0;
    long long k = 0;
    while (i < n1 && j < n2)
    {
        if (array1[i] < array2[j])
        {
            merged[k++] = array1[i++];
        }
        else
        {
            merged[k++] = array2[j++];
        }
    }
    while (i < n1)
    {
        merged[k++] = array1[i++];
    }
    while (j < n2)
    {
        merged[k++] = array2[j++];
    }
    return merged;
}

template<class T>
static Vertex<T>* sortedArrayToAvlRankTree(int (*func)(const T&),const T array[],
                                           long long first, long long last)
{
    if (first > last)
    {
        return nullptr;
    }
    long long mid = (first + last)/2;
    Vertex<T>* vertex(new Vertex<T>(array[mid]));
    vertex->setGetInternalValue(func);
    vertex->setLeft(sortedArrayToAvlRankTree(func,array,first,mid-1));
    vertex->setRight(sortedArrayToAvlRankTree(func,array,mid+1,last));
    vertex->setHeight(getMaxInt(vertex->getLeft()->getHeight(),vertex->getRight()->getHeight())+1);
    vertex->setVerticesNumber(vertex->getLeft()->getVerticesNumber() + vertex->getRight()->getVerticesNumber() + 1);
    vertex->setGradesSum(vertex->getLeft()->getGradesSum() + vertex->getRight()->getGradesSum() +
                                    vertex->getVertexGrade());
    return vertex;
}

template<class T>
void AvlRankTree<T>::mergeTree(const AvlRankTree<T> &avl_tree)
{
    if (!avl_tree.size)
    {
        return;
    }
    long long n1 = avl_tree.getSize();
    long long i1 = 0;
    long long i2 = 0;
    T* array1 = n1 > 0 ? new T[n1]() : nullptr;
    T* array2 = size > 0 ? new T[size]() : nullptr;
    inorderIteration(avl_tree.root,n1,array1,&i1);
    inorderIteration(root,size,array2,&i2);
    T* array3 = mergeTwoArrays(array1,array2,n1,size);
    delete[] array1;
    delete[] array2;
    clear(root);
    root = sortedArrayToAvlRankTree(getInternalValue,array3,0,n1 + size - 1);
    delete[] array3;
    Vertex<T>* tmp = root;
    while (tmp->getRight())
    {
        tmp = tmp->getRight();
    }
    max = tmp;
    size += n1;
}

template<class T>
T *AvlRankTree<T>::getPtrValue(const T &value)
{
    Vertex<T>* vertex = getVertexByValue(root,value);
    if (!vertex)
    {
        return nullptr;
    }
    return &vertex->getValue();
}

template<class T>
static long long sumGradesBeforeIndex(Vertex<T>*vertex,long long index)
{
    if (!vertex)
    {
        return 0;
    }
    long long sum = 0;
    long long i = 0;
    Vertex<T>* tmp = vertex;
    while (tmp)
    {
        long long t = tmp->getLeft() ? tmp->getVertexGrade() + tmp->getLeft()->getGradesSum() : tmp->getVertexGrade();
        long long m = tmp->getLeft() ? 1 + tmp->getLeft()->getVerticesNumber() : 1;
        if (i + m == index)
        {
            sum += t;
            return sum;
        }
        else if (i + m < index)
        {
            sum += t;
            i += m;
            tmp = tmp->getRight();
        }
        else
        {
            tmp = tmp->getLeft();
        }
    }
    return sum;
}

template<class T>
long long AvlRankTree<T>::sumHighestSalaryEmployeesGrades(int m)
{
    return sumGradesBeforeIndex(root, size) - sumGradesBeforeIndex(root, size-m);
}

template<class T>
static long long getIndex(Vertex<T>* vertex,T* value)
{
    if (!vertex)
    {
        return 0;
    }
    long long t = vertex->getLeft() ? 1 + vertex->getLeft()->getVerticesNumber() : 1;
    if (vertex->getValue() == *value)
    {
        return t;
    }
    else if (vertex->getValue() < *value)
    {
        return t + getIndex(vertex->getRight(),value);
    }
    else
    {
        return getIndex(vertex->getLeft(),value);
    }
}

template<class T>
void AvlRankTree<T>::sumGradesBetweenSalaryEmployees(long long *sum,long long *num,T* low_value,T* high_value)
{
    this->insert(*low_value);
    this->insert(*high_value);
    long long low_index = getIndex(root,low_value) ;
    long long high_index = getIndex(root,high_value);
    *sum = sumGradesBeforeIndex(root, high_index) - sumGradesBeforeIndex(root,low_index);
    this->remove(*low_value);
    this->remove(*high_value);
    *num = high_index - low_index -1;
}

template<class T>
static void increaseFieldsInorder(Vertex<T>* vertex,double value, void (*func)(T*, double))
{
    if (vertex)
    {
        increaseFieldsInorder(vertex->getLeft(),value,func);
        func(&vertex->getValue(),value);
        increaseFieldsInorder(vertex->getRight(),value,func);
    }
}

template<class T>
void AvlRankTree<T>::increaseFields(double value, void (*func)(T *, double))
{
    increaseFieldsInorder(root,value,func);
}

#endif //AVLRANKTREE_H_
