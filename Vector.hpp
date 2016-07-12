#pragma once

#include <RandomAccessIterator.h>
#include <iostream>

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
                    const value_type& value,
                    const allocator_type& alloc = allocator_type());
    template<class InputIterator, std::enable_if_t<std::is_base_of<std::input_iterator_tag,
                                  typename std::iterator_traits<InputIterator>::iterator_category>::value, int> = 0>
    Vector(InputIterator first, 
           InputIterator last,
           const allocator_type& alloc = allocator_type());
    Vector(const Vector& input);
    Vector(const Vector& x, const allocator_type& alloc);
    Vector(Vector&& x);
    Vector(Vector&& x, const allocator_type& alloc);
    Vector(std::initializer_list<value_type> initializerList,
           const allocator_type& alloc = allocator_type());

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

    value_type* elements;
    size_type numberOfElements = 0;
    size_type actualCapacity = 0;
    allocator_type allocator;
};

template<class T, class Allocator>
Vector<T, Allocator>::Vector(std::initializer_list<value_type> initializerList,
                             const allocator_type& alloc) :numberOfElements(initializerList.size()), allocator(alloc)
{
    resize(numberOfElements);
    for(size_type i = 0; i < numberOfElements; ++i)
        allocator.construct(elements + i, *(initializerList.begin() + i));
}

template<class T, class Allocator>
Vector<T, Allocator>::Vector(const Vector& input) :numberOfElements(input.size())
{
    allocator = std::allocator_traits<allocator_type>::select_on_container_copy_construction(input.get_allocator());
    resize(numberOfElements);
    for(size_type i = 0; i < numberOfElements; ++i)
        allocator.construct(elements + i, input[i]);
}

template<class T, class Allocator>
Vector<T, Allocator>::Vector(size_type count,
                             const allocator_type& alloc) :numberOfElements(count), allocator(alloc)
{
    resize(count);
    for(size_type i = 0; i < numberOfElements; ++i)
        new (elements + i) T();
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
template<class InputIterator, std::enable_if_t<std::is_base_of<std::input_iterator_tag,
                              typename std::iterator_traits<InputIterator>::iterator_category>::value, int>>
Vector<T, Allocator>::Vector(InputIterator first, 
                             InputIterator last,
                             const allocator_type& alloc) :allocator(alloc)
{
    numberOfElements = last - first;
    resize(numberOfElements);
    for(size_type i = 0; i < numberOfElements; ++i)
        allocator.construct(elements + i, *(first + i));
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
    allocator.allocate(actualCapacity);
}

template<class T, class Allocator>
void Vector<T, Allocator>::resize(size_type size)
{
    if(actualCapacity == 0)
    {
        resizeWithZeroCapacity();
    }
    
    T* biggerArray = allocator.allocate(size);    
    std::copy(elements, elements + numberOfElements, biggerArray);
    elements = biggerArray;    
    actualCapacity = size;
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
    allocator.construct(elements + numberOfElements++, element);
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


