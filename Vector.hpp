#pragma once

#include <RandomAccessIterator.h>
#include <iostream>


class resize;
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
    Vector(const Vector& input, const allocator_type& alloc);
    
    Vector(Vector&& x);
    Vector(Vector&& x, const allocator_type& alloc);
    
    Vector(std::initializer_list<value_type> input,
           const allocator_type& alloc = allocator_type());
    
    ~Vector();
    
    Vector& operator=(const Vector& input);
    Vector& operator=(Vector&& input);
    Vector& operator=(std::initializer_list<value_type> input);

    value_type& operator[](size_type position);
    const value_type& operator[](size_type position) const;
    
    size_type size() const;
    size_type capacity();
    void push_back(T element);
    void clear();
    template <class... Args>
    void emplace_back(Args&&... args);
    allocator_type get_allocator() const;
    
private:    
    void resizeWithDoubledCapacity();
    void resizeWithZeroCapacity();
    void resize(size_type size);
    void resizeAndCopyElements(const Vector<T, Allocator>& input);
    void resizeAndMoveElements(Vector<T, Allocator>& input);
    
    value_type* elements;
    size_type numberOfElements = 0;
    size_type actualCapacity = 0;
    allocator_type allocator;
};

template<class T, class Allocator>
void Vector<T, Allocator>::resizeAndCopyElements(const Vector<T, Allocator>& input)
{
    size_type newNumberOfElemetns = input.size();
    resize(newNumberOfElemetns);
    for(size_type i = 0; i < newNumberOfElemetns; ++i)
        allocator.construct(elements + i, input[i]); 
    numberOfElements = newNumberOfElemetns;
}

template<class T, class Allocator>
void Vector<T, Allocator>::resizeAndMoveElements(Vector<T, Allocator>& input)
{
    size_type newNumberOfElemetns = input.size();
    resize(newNumberOfElemetns);
    for(size_type i = 0; i < newNumberOfElemetns; ++i)
        elements[i] = std::move(input[i]);
    numberOfElements = newNumberOfElemetns;
}

template<class T, class Allocator>
void Vector<T, Allocator>::clear()
{
    if(!std::is_trivial<T>::value && numberOfElements)
    {
        for(size_type i = 0; i < numberOfElements; ++i)
        {
            allocator.destroy(elements + i);
        }
    }
    if(actualCapacity)
        allocator.deallocate(elements, actualCapacity);
    numberOfElements = 0;
    actualCapacity = 0;
}

template<class T, class Allocator>
Vector<T, Allocator>& Vector<T, Allocator>::operator=(const Vector& input)
{
    auto inputAllocator = input.get_allocator();
    if(__gnu_cxx::__alloc_traits<allocator_type>::_S_propagate_on_copy_assign())
    {
        if(allocator == inputAllocator)
        {
            allocator = inputAllocator;
            clear();
        }
        else
        {
            clear();
            allocator = inputAllocator;
        }
    }
    else
        clear();
    resizeAndCopyElements(input);
    return *this;
}

template<class T, class Allocator>
Vector<T, Allocator>& Vector<T, Allocator>::operator=(Vector&& input)
{
    auto inputAllocator = input.get_allocator();
    if(__gnu_cxx::__alloc_traits<allocator_type>::_S_propagate_on_move_assign())
    {
        if(allocator == inputAllocator)
        {
            allocator = inputAllocator;
            if(numberOfElements > input.size())
            {
                for(std::size_t i = input.size(); i < numberOfElements; ++i)
                    allocator.destroy(elements + i);
            }
        }
        else
        {
            clear();
            allocator = inputAllocator;
        }
    }
    else
        clear();
    resizeAndMoveElements(input);
    return *this;
}

template<class T, class Allocator>
Vector<T, Allocator>::~Vector()
{
    clear();
}

template<class T, class Allocator>
Vector<T, Allocator>::Vector(std::initializer_list<value_type> input,
                             const allocator_type& alloc) :allocator(alloc)
{
    std::size_t newNumberOfElemetns = input.size();
    resize(newNumberOfElemetns);
    for(size_type i = 0; i < newNumberOfElemetns; ++i)
        allocator.construct(elements + i, *(input.begin() + i));
    numberOfElements = newNumberOfElemetns;
}

template<class T, class Allocator>
Vector<T, Allocator>::Vector(const Vector& input) 
{
    allocator = std::allocator_traits<allocator_type>::select_on_container_copy_construction(input.get_allocator());
    resizeAndCopyElements(input);
}

template<class T, class Allocator>
Vector<T, Allocator>::Vector(const Vector& input,
                             const allocator_type& alloc) :allocator(alloc)
{
    resizeAndCopyElements(input);
}

template<class T, class Allocator>
Vector<T, Allocator>::Vector(Vector&& input) 
{
    allocator = std::allocator_traits<allocator_type>::select_on_container_copy_construction(input.get_allocator());
    resizeAndMoveElements(input);
}

template<class T, class Allocator>
Vector<T, Allocator>::Vector(Vector&& input,
                             const allocator_type& alloc) :allocator(alloc)
{
    resizeAndMoveElements(input);
}

template<class T, class Allocator>
Vector<T, Allocator>::Vector(size_type count,
                             const allocator_type& alloc) :allocator(alloc)
{
    resize(count);
    for(size_type i = 0; i < count; ++i)
        new (elements + i) T();
    numberOfElements = count;
}

template<class T, class Allocator>
Vector<T, Allocator>::Vector(size_type count, 
                             const T& value,
                             const allocator_type& alloc) :allocator(alloc)
{
    resize(count);
    for(size_type i = 0; i < count; ++i)
        allocator.construct(elements + i, value);
    numberOfElements = count;
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
void Vector<T, Allocator>::resizeWithDoubledCapacity()
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

template<class T, class Alloc>
bool operator==(const Vector<T, Alloc> &lhs,
                const Vector<T, Alloc> &rhs)
{
    if(lhs.size() != rhs.size())
        return false;
    for(std::size_t i = 0; i < lhs.size(); ++i)
    {
        if(!(lhs[i] == rhs[i]))
            return false;
    }
    return true;
}
