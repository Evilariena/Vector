#pragma once

#include <RandomAccessIterator.h>

template<class T, class Allocator = std::allocator<T>>
class Vector
{
public:
    using value_type = T;
    using allocator_type = Allocator;
    using size_type = std::size_t;
    using difference_type = std::ptrdiff_t;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = typename std::allocator_traits<Allocator>::pointer;
    using const_pointer = typename std::allocator_traits<Allocator>::const_pointer;
    using iterator = RandomAccessIterator<T>;
    using const_iterator = const RandomAccessIterator<T>;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = 	std::reverse_iterator<const_iterator>;
    
    Vector():allocator(allocator){}
    explicit Vector(const Allocator& allocator):allocator(allocator){}

    T& operator[](const int& position);
    size_type size() const;
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
    const Allocator& allocator;
};

template<class T, class Allocator>
T& Vector<T, Allocator>::operator[](const int& position)
{
    return elements[position];
}

template<class T, class Allocator>
typename Vector<T, Allocator>::size_type Vector<T, Allocator>::size() const
{
    return numberOfElements;
}

template<class T, class Allocator>
void Vector<T, Allocator>::resize()
{
    if(actualCapacity == 0)
    {
        actualCapacity = 1;
        elements = new T[actualCapacity];
    }
    else resize(2 * actualCapacity);
}

template<class T, class Allocator>
void Vector<T, Allocator>::resize(int size)
{
    int newCapacity = 2 * actualCapacity;
    T* biggerArray = new T[newCapacity];
    copy(elements, elements + numberOfElements, biggerArray);
    elements = biggerArray;
    actualCapacity = newCapacity;
}

template<class T, class Allocator>
int Vector<T, Allocator>::capacity()
{
    return actualCapacity;
}

template<class T, class Allocator>
void Vector<T, Allocator>::push_back(T element)
{
    if(actualCapacity <= numberOfElements)
        resize();
    elements[numberOfElements++] = element;
}

template<class T, class Allocator>
template <class... Args>
void Vector<T, Allocator>::emplace_back(Args&&... args)
{
    push_back(Allocator(std::forward<T>(args)...));
}


