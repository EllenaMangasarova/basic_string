#ifndef BASIC_STRING_H
#define BASIC_STRING_H

#include <memory>
#include <iterator>

template<typename CharT, typename Traits = std::char_traits<CharT>, typename Allocator = std::allocator<CharT>>
class BasicString {
public:
    // Member types
    using traits_type = Traits;
    using value_type = CharT;
    using allocator_type = Allocator;
    using size_type = typename std::allocator_traits<Allocator>::size_type;
    using difference_type = typename std::allocator_traits<Allocator>::difference_type;
    using reference = value_type&;
    using const_reference = const value_type&;
    using pointer = typename std::allocator_traits<Allocator>::pointer;
    using const_pointer = typename std::allocator_traits<Allocator>::const_pointer;
    using iterator = CharT*;
    using const_iterator = const CharT*;
    using reverse_iterator = std::reverse_iterator<iterator>;
    using const_reverse_iterator = std::reverse_iterator<const_iterator>;

    // Ctors
    BasicString();
    BasicString(const BasicString& other);
    BasicString(BasicString&& other) noexcept;
    BasicString(const CharT* s);
    ~BasicString();

    // Operator=
    BasicString& operator=(const BasicString& other);
    BasicString& operator=(BasicString&& other) noexcept;

    // Element access
    reference at(size_type pos);
    const_reference at(size_type pos) const;
    reference operator[](size_type pos);
    const_reference operator[](size_type pos) const;
    reference front();
    const_reference front() const;
    reference back();
    const_reference back() const;
    const CharT* data() const noexcept;
    const CharT* c_str() const noexcept;

    //Iterators
    iterator begin() noexcept;
    const_iterator begin() const noexcept;
    const_iterator cbegin() const noexcept;
    iterator end() noexcept;
    const_iterator end() const noexcept;
    const_iterator cend() const noexcept;
    reverse_iterator rbegin() noexcept;
    const_reverse_iterator rbegin() const noexcept;
    const_reverse_iterator crbegin() const noexcept;
    reverse_iterator rend() noexcept;
    const_reverse_iterator rend() const noexcept;
    const_reverse_iterator crend() const noexcept;

    //Capacity
    bool empty() const noexcept;
    size_type size() const noexcept;
    size_type length() const noexcept;
    size_type max_size() const noexcept;
    void reserve(size_type new_cap);
    size_type capacity() const noexcept;
    void shrink_to_fit();

    //Modifiers
    void clear() noexcept;
    BasicString& insert(size_type pos, const BasicString& str);
    BasicString& erase(size_type pos = 0, size_type count = npos);
    void push_back(CharT ch);
    void pop_back();
    BasicString& append(const BasicString& str);
    BasicString& replace(size_type pos, size_type count, const BasicString& str);
    void swap(BasicString& other) noexcept;

    //Search
    size_type find(const BasicString& str, size_type pos = 0) const noexcept;
    size_type rfind(const BasicString& str, size_type pos = npos) const noexcept;
    size_type find_first_of(const BasicString& str, size_type pos = 0) const noexcept;
    size_type find_first_not_of(const BasicString& str, size_type pos = 0) const noexcept;
    size_type find_last_of(const BasicString& str, size_type pos = npos) const noexcept;
    size_type find_last_not_of(const BasicString& str, size_type pos = npos) const noexcept;

    //Operations
    int compare(const BasicString& str) const noexcept;
    bool contains(const BasicString& str) const noexcept;
    BasicString substr(size_type pos = 0, size_type count = npos) const;

private:
    pointer _data;
    size_type _size;
    size_type _capacity;
    allocator_type _alloc;

    void reallocate(size_type new_cap);
};

#include "basic_string.cpp"

#endif // BASIC_STRING_H
