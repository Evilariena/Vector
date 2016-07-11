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
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;
    
    Vector():allocator(allocator_type()){}
    explicit Vector(const allocator_type& alloc):allocator(alloc){}
    explicit Vector(size_type count,
                    const allocator_type& alloc = allocator_type());
    explicit Vector(size_type count, 
                    const T& value,
                    const allocator_type& alloc = allocator_type());
    template<class InputIterator>
    Vector(InputIterator first, 
           InputIterator last,
           const allocator_type& alloc = allocator_type());
    Vector(const Vector& input);

    T& operator[](size_type position);
    const T& operator[](size_type position) const;
    size_type size() const;
    size_type capacity();
    void push_back(T element);
    template <class... Args>
    void emplace_back(Args&&... args);
    allocator_type get_allocator() const;
    
private:    
    void resize();
    void resizeWithZeroCapacity();
    void resize(size_type size);

    T* elements;
    size_type numberOfElements = 0;
    size_type actualCapacity = 0;
    allocator_type allocator;
};

template<class T, class Allocator>
Vector<T, Allocator>::Vector(const Vector& input)
{
    allocator = std::allocator_traits<allocator_type>::select_on_container_copy_construction(input.get_allocator());
}

template<class T, class Allocator>
Vector<T, Allocator>::Vector(size_type count,
                             const allocator_type& alloc) :numberOfElements(count), allocator(alloc)
{
    resize(count);
    for(size_type i = 0; i < numberOfElements; ++i)
        allocator.construct(elements + i, T());
}

template<class T, class Allocator>
Vector<T, Allocator>::Vector(size_type count, 
                             const T& value,
                             const allocator_type& alloc) :numberOfElements(count), allocator(alloc)
{
    resize(count);
    for(size_type i = 0; i < numberOfElements; ++i)
        allocator.construct(elements + i, value);
}

template<class T, class Allocator>
template<class InputIterator>
Vector<T, Allocator>::Vector(InputIterator first, 
                             InputIterator last,
                             const allocator_type& alloc) :allocator(alloc)
{
    numberOfElements = last - first;
    resize(numberOfElements);
    std::copy(first, last, elements);
}

template<class T, class Allocator>
T& Vector<T, Allocator>::operator[](size_type position)
{
    return elements[position];
}

template<class T, class Allocator>
const T& Vector<T, Allocator>::operator[](size_type position) const
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
        resizeWithZeroCapacity();
    }
    else resize(2 * actualCapacity);
}
template<class T, class Allocator>
void Vector<T, Allocator>::resizeWithZeroCapacity()
{
    actualCapacity = 1;
    elements = new T[actualCapacity];
}

template<class T, class Allocator>
void Vector<T, Allocator>::resize(size_type size)
{
    if(actualCapacity == 0)
    {
        resizeWithZeroCapacity();
    }
    size_type newCapacity = size;
    T* biggerArray = allocator.allocate(newCapacity);
    std::copy(elements, elements + numberOfElements, biggerArray);
    elements = biggerArray;
    actualCapacity = newCapacity;
}

template<class T, class Allocator>
typename Vector<T, Allocator>::size_type Vector<T, Allocator>::capacity()
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
typename Vector<T, Allocator>::allocator_type Vector<T, Allocator>::get_allocator() const
{
    return allocator;
}

template<class T, class Allocator>
template <class... Args>
void Vector<T, Allocator>::emplace_back(Args&&... args)
{
    push_back(Allocator(std::forward<T>(args)...));
}


