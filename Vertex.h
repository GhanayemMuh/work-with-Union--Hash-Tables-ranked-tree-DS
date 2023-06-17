//
// Created by Muhammad Biadsy on 20/04/2022.
//

#ifndef VERTEX_H_
#define VERTEX_H_
#include <iostream>


template<class T>
class Vertex {
    Vertex* left;
    Vertex* right;
    T value;
    long long height;
    long long vertices_number;
    long long grades_sum;
    int (*getInternalValue)(const T&);
public:
    explicit Vertex(const T& value);
    ~Vertex() = default;
    Vertex* getLeft() const;
    Vertex* getRight() const;
    T& getValue();
    long long getHeight() const;
    long long getVerticesNumber() const;
    long long getGradesSum() const;
    int getVertexGrade() const;
    void setLeft(Vertex* vertex);
    void setRight(Vertex* vertex);
    void setValue(const T& value1);
    void setHeight(long long height1);
    void setVerticesNumber(long long vertices_number1);
    void setGradesSum(long long grades_sum1);
    void setGetInternalValue(int (*getInternalValue1)(const T&));
};

template<class T>
Vertex<T>::Vertex(const T &value):left(nullptr),right(nullptr),value(value)
{
    getInternalValue = nullptr;
    height  = 0;
    grades_sum = 0;
    vertices_number = 0;
}

template<class T>
Vertex<T> *Vertex<T>::getLeft() const
{
    if (!this)
    {
        return nullptr;
    }
    return this->left;
}

template<class T>
Vertex<T> *Vertex<T>::getRight() const
{
    if (!this)
    {
        return nullptr;
    }
    return this->right;
}

template<class T>
T &Vertex<T>::getValue()
{
    return this->value;
}

template<class T>
long long Vertex<T>::getHeight() const
{
    if (!this)
    {
        return -1;
    }
    return this->height;
}

template<class T>
long long Vertex<T>::getVerticesNumber()const
{
    if (!this)
    {
        return 0;
    }
    return this->vertices_number;
}

template<class T>
long long Vertex<T>::getGradesSum()const
{
    if (!this)
    {
        return 0;
    }
    return this->grades_sum;
}

template<class T>
int Vertex<T>::getVertexGrade()const
{
    if (!this)
    {
        return 0;
    }
    if (!this->getInternalValue)
    {
        return 0;
    }
    return this->getInternalValue(value);
}

template<class T>
void Vertex<T>::setLeft(Vertex<T> *vertex)
{
    if (!this)
    {
        return;
    }
    this->left = vertex;
}

template<class T>
void Vertex<T>::setRight(Vertex<T> *vertex)
{
    if (!this)
    {
        return;
    }
    this->right = vertex;
}

template<class T>
void Vertex<T>::setValue(const T &value1)
{
    if (!this)
    {
        return;
    }
    this->value = value1;
}

template<class T>
void Vertex<T>::setHeight(long long height1)
{
    if (!this)
    {
        return;
    }
    this->height = height1;
}

template<class T>
void Vertex<T>::setVerticesNumber(long long vertices_number1)
{
    if (!this)
    {
        return;
    }
    this->vertices_number = vertices_number1;
}

template<class T>
void Vertex<T>::setGradesSum(long long grades_sum1)
{
    if (!this)
    {
        return;
    }
    this->grades_sum = grades_sum1;
}

template<class T>
void Vertex<T>::setGetInternalValue(int (*getInternalValue1)(const T &))
{
    if (!this)
    {
        return;
    }
    this->getInternalValue = getInternalValue1;
}

#endif //VERTEX_H_
