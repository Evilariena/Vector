template<typename T>
class AddingAllocator {
public : 
    typedef T value_type;
    typedef value_type* pointer;
    typedef const value_type* const_pointer;
    typedef value_type& reference;
    typedef const value_type& const_reference;
    typedef std::size_t size_type;
    typedef std::ptrdiff_t difference_type;

public : 

    template<typename U>
    struct rebind {
        typedef AddingAllocator<U> other;
    };

public : 
    inline explicit AddingAllocator() {}
    inline ~AddingAllocator() {}
    inline explicit AddingAllocator(AddingAllocator const&) {}
    template<typename U>
    inline explicit AddingAllocator(AddingAllocator<U> const&) {}

    inline pointer address(reference r) { return &r; }
    inline const_pointer address(const_reference r) { return &r; }

    inline pointer allocate(size_type cnt, typename std::allocator<void>::const_pointer = 0) 
    {
        return reinterpret_cast<pointer>(::operator new(cnt * sizeof (T))); 
    }
    inline void deallocate(pointer p, size_type) 
    { 
        ::operator delete(p); 
    }

    inline size_type max_size() const { 
        return std::numeric_limits<size_type>::max() / sizeof(T);
    }
    inline void construct(pointer p, const T& t) { new(p) T(t + 1); }
    inline void destroy(pointer p) { p->~T(); }

    inline bool operator==(AddingAllocator const&) { return true; }
    inline bool operator!=(AddingAllocator const& a) { return !operator==(a); }
};  