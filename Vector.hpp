#pragma once

#include <iostream>
#include <vector>
#include <stdarg.h>

template<class T,class Alloc = std::allocator<T>>
class Vector
{
public:
    Vector():allocator(allocator){}
    explicit Vector(const Alloc& allocator):allocator(allocator){}

    T& operator[](const int& position);
    int size();
    int capacity();
    void push_back(T element);
    template <class... Args>
    void emplace_back(Args&&... args);
private:
    void resize();
    void resize(int size);

    T* elements;
    int numberOfElements = 0;
    int actualCapacity = 0;
    const Alloc& allocator;
};

template<class T, class Alloc>
T& Vector<T, Alloc>::operator[](const int& position)
{
    return elements[position];
}

template<class T, class Alloc>
int Vector<T, Alloc>::size()
{
    return numberOfElements;
}

template<class T, class Alloc>
void Vector<T, Alloc>::resize()
{
    if(actualCapacity == 0)
    {
        actualCapacity = 1;
        elements = new T[actualCapacity];
    }
    else resize(2 * actualCapacity);
}

template<class T, class Alloc>
void Vector<T, Alloc>::resize(int size)
{
    int newCapacity = 2 * actualCapacity;
    T* biggerArray = new T[newCapacity];
    copy(elements, elements + numberOfElements, biggerArray);
    elements = biggerArray;
    actualCapacity = newCapacity;
}

template<class T, class Alloc>
int Vector<T, Alloc>::capacity()
{
    return actualCapacity;
}

template<class T, class Alloc>
void Vector<T, Alloc>::push_back(T element)
{
    if(actualCapacity <= numberOfElements)
        resize();
    elements[numberOfElements++] = element;
}

template<class T, class Alloc>
template <class... Args>
void Vector<T, Alloc>::emplace_back(Args&&... args)
{
    push_back(Alloc(std::forward<T>(args)...));
}


