#include "basic_string.h"
#include <algorithm>
#include <stdexcept>
#include <cstring>

// Constructors
template<typename CharT, typename Traits, typename Allocator>
BasicString<CharT, Traits, Allocator>::BasicString()
    : _data(nullptr), _size(0), _capacity(0), _alloc(Allocator()) {}

template<typename CharT, typename Traits, typename Allocator>
BasicString<CharT, Traits, Allocator>::BasicString(const BasicString& other)
    : _size(other._size), _capacity(other._capacity), _alloc(other._alloc) {
    _data = _alloc.allocate(_capacity);
    std::copy(other._data, other._data + _size, _data);
}

template<typename CharT, typename Traits, typename Allocator>
BasicString<CharT, Traits, Allocator>::BasicString(BasicString&& other) noexcept
    : _data(other._data), _size(other._size), _capacity(other._capacity), _alloc(std::move(other._alloc)) {
    other._data = nullptr;
    other._size = 0;
    other._capacity = 0;
}

template<typename CharT, typename Traits, typename Allocator>
BasicString<CharT, Traits, Allocator>::BasicString(const CharT* s)
    : _size(std::strlen(s)), _capacity(_size), _alloc(Allocator()) {
    _data = _alloc.allocate(_capacity);
    std::copy(s, s + _size, _data);
}

template<typename CharT, typename Traits, typename Allocator>
BasicString<CharT, Traits, Allocator>::~BasicString() {
    if (_data) {
        _alloc.deallocate(_data, _capacity);
    }
}

// Operator=
template<typename CharT, typename Traits, typename Allocator>
BasicString<CharT, Traits, Allocator>& BasicString<CharT, Traits, Allocator>::operator=(const BasicString& other) {
    if (this != &other) {
        BasicString temp(other);
        swap(temp);
    }
    return *this;
}

template<typename CharT, typename Traits, typename Allocator>
BasicString<CharT, Traits, Allocator>& BasicString<CharT, Traits, Allocator>::operator=(BasicString&& other) noexcept {
    if (this != &other) {
        swap(other);
        other._data = nullptr;
        other._size = 0;
        other._capacity = 0;
    }
    return *this;
}

// Element access
template<typename CharT, typename Traits, typename Allocator>
typename BasicString<CharT, Traits, Allocator>::reference
BasicString<CharT, Traits, Allocator>::at(size_type pos) {
    if (pos >= _size) throw std::out_of_range("BasicString::at");
    return _data[pos];
}

template<typename CharT, typename Traits, typename Allocator>
typename BasicString<CharT, Traits, Allocator>::const_reference
BasicString<CharT, Traits, Allocator>::at(size_type pos) const {
    if (pos >= _size) throw std::out_of_range("BasicString::at");
    return _data[pos];
}

template<typename CharT, typename Traits, typename Allocator>
typename BasicString<CharT, Traits, Allocator>::reference
BasicString<CharT, Traits, Allocator>::operator[](size_type pos) {
    return _data[pos];
}

template<typename CharT, typename Traits, typename Allocator>
typename BasicString<CharT, Traits, Allocator>::const_reference
BasicString<CharT, Traits, Allocator>::operator[](size_type pos) const {
    return _data[pos];
}

template<typename CharT, typename Traits, typename Allocator>
typename BasicString<CharT, Traits, Allocator>::reference
BasicString<CharT, Traits, Allocator>::front() {
    return _data[0];
}

template<typename CharT, typename Traits, typename Allocator>
typename BasicString<CharT, Traits, Allocator>::const_reference
BasicString<CharT, Traits, Allocator>::front() const {
    return _data[0];
}

template<typename CharT, typename Traits, typename Allocator>
typename BasicString<CharT, Traits, Allocator>::reference
BasicString<CharT, Traits, Allocator>::back() {
    return _data[_size - 1];
}

template<typename CharT, typename Traits, typename Allocator>
typename BasicString<CharT, Traits, Allocator>::const_reference
BasicString<CharT, Traits, Allocator>::back() const {
    return _data[_size - 1];
}

template<typename CharT, typename Traits, typename Allocator>
const CharT* BasicString<CharT, Traits, Allocator>::data() const noexcept {
    return _data;
}

template<typename CharT, typename Traits, typename Allocator>
const CharT* BasicString<CharT, Traits, Allocator>::c_str() const noexcept {
    return _data;
}

// Iterators
template<typename CharT, typename Traits, typename Allocator>
typename BasicString<CharT, Traits, Allocator>::iterator
BasicString<CharT, Traits, Allocator>::begin() noexcept {
    return _data;
}

template<typename CharT, typename Traits, typename Allocator>
typename BasicString<CharT, Traits, Allocator>::const_iterator
BasicString<CharT, Traits, Allocator>::begin() const noexcept {
    return _data;
}

template<typename CharT, typename Traits, typename Allocator>
typename BasicString<CharT, Traits, Allocator>::const_iterator
BasicString<CharT, Traits, Allocator>::cbegin() const noexcept {
    return _data;
}

template<typename CharT, typename Traits, typename Allocator>
typename BasicString<CharT, Traits, Allocator>::iterator
BasicString<CharT, Traits, Allocator>::end() noexcept {
    return _data + _size;
}

template<typename CharT, typename Traits, typename Allocator>
typename BasicString<CharT, Traits, Allocator>::const_iterator
BasicString<CharT, Traits, Allocator>::end() const noexcept {
    return _data + _size;
}

template<typename CharT, typename Traits, typename Allocator>
typename BasicString<CharT, Traits, Allocator>::const_iterator
BasicString<CharT, Traits, Allocator>::cend() const noexcept {
    return _data + _size;
}

template<typename CharT, typename Traits, typename Allocator>
typename BasicString<CharT, Traits, Allocator>::reverse_iterator
BasicString<CharT, Traits, Allocator>::rbegin() noexcept {
    return reverse_iterator(end());
}

template<typename CharT, typename Traits, typename Allocator>
typename BasicString<CharT, Traits, Allocator>::const_reverse_iterator
BasicString<CharT, Traits, Allocator>::rbegin() const noexcept {
    return const_reverse_iterator(end());
}

template<typename CharT, typename Traits, typename Allocator>
typename BasicString<CharT, Traits, Allocator>::const_reverse_iterator
BasicString<CharT, Traits, Allocator>::crbegin() const noexcept {
    return const_reverse_iterator(end());
}

template<typename CharT, typename Traits, typename Allocator>
typename BasicString<CharT, Traits, Allocator>::reverse_iterator
BasicString<CharT, Traits, Allocator>::rend() noexcept {
    return reverse_iterator(begin());
}

template<typename CharT, typename Traits, typename Allocator>
typename BasicString<CharT, Traits, Allocator>::const_reverse_iterator
BasicString<CharT, Traits, Allocator>::rend() const noexcept {
    return const_reverse_iterator(begin());
}

template<typename CharT, typename Traits, typename Allocator>
typename BasicString<CharT, Traits, Allocator>::const_reverse_iterator
BasicString<CharT, Traits, Allocator>::crend() const noexcept {
    return const_reverse_iterator(begin());
}

// Capacity
template<typename CharT, typename Traits, typename Allocator>
bool BasicString<CharT, Traits, Allocator>::empty() const noexcept {
    return _size == 0;
}

template<typename CharT, typename Traits, typename Allocator>
typename BasicString<CharT, Traits, Allocator>::size_type
BasicString<CharT, Traits, Allocator>::size() const noexcept {
    return _size;
}

template<typename CharT, typename Traits, typename Allocator>
typename BasicString<CharT, Traits, Allocator>::size_type
BasicString<CharT, Traits, Allocator>::length() const noexcept {
    return _size;
}

template<typename CharT, typename Traits, typename Allocator>
typename BasicString<CharT, Traits, Allocator>::size_type
BasicString<CharT, Traits, Allocator>::max_size() const noexcept {
    return _alloc.max_size();
}

template<typename CharT, typename Traits, typename Allocator>
void BasicString<CharT, Traits, Allocator>::reserve(size_type new_cap) {
    if (new_cap > _capacity) {
        reallocate(new_cap);
    }
}

template<typename CharT, typename Traits, typename Allocator>
typename BasicString<CharT, Traits, Allocator>::size_type
BasicString<CharT, Traits, Allocator>::capacity() const noexcept {
    return _capacity;
}

template<typename CharT, typename Traits, typename Allocator>
void BasicString<CharT, Traits, Allocator>::shrink_to_fit() {
    if (_capacity > _size) {
        reallocate(_size);
    }
}

// Modifiers
template<typename CharT, typename Traits, typename Allocator>
void BasicString<CharT, Traits, Allocator>::clear() noexcept {
    _size = 0;
}

template<typename CharT, typename Traits, typename Allocator>
BasicString<CharT, Traits, Allocator>& BasicString<CharT, Traits, Allocator>::insert(size_type pos, const BasicString& str) {
    if (pos > _size) throw std::out_of_range("BasicString::insert");
    if (_size + str._size > _capacity) {
        reserve(_size + str._size);
    }
    std::move_backward(_data + pos, _data + _size, _data + _size + str._size);
    std::copy(str._data, str._data + str._size, _data + pos);
    _size += str._size;
    return *this;
}

template<typename CharT, typename Traits, typename Allocator>
BasicString<CharT, Traits, Allocator>& BasicString<CharT, Traits, Allocator>::erase(size_type pos, size_type count) {
    if (pos >= _size) throw std::out_of_range("BasicString::erase");
    if (count == npos || pos + count >= _size) {
        _size = pos;
    } else {
        std::move(_data + pos + count, _data + _size, _data + pos);
        _size -= count;
    }
    return *this;
}

template<typename CharT, typename Traits, typename Allocator>
void BasicString<CharT, Traits, Allocator>::push_back(CharT ch) {
    if (_size + 1 > _capacity) {
        reserve(_capacity == 0 ? 1 : _capacity * 2);
    }
    _data[_size++] = ch;
}

template<typename CharT, typename Traits, typename Allocator>
void BasicString<CharT, Traits, Allocator>::pop_back() {
    if (_size > 0) {
        --_size;
    }
}

template<typename CharT, typename Traits, typename Allocator>
BasicString<CharT, Traits, Allocator>& BasicString<CharT, Traits, Allocator>::append(const BasicString& str) {
    if (_size + str._size > _capacity) {
        reserve(_size + str._size);
    }
    std::copy(str._data, str._data + str._size, _data + _size);
    _size += str._size;
    return *this;
}

template<typename CharT, typename Traits, typename Allocator>
BasicString<CharT, Traits, Allocator>& BasicString<CharT, Traits, Allocator>::replace(size_type pos, size_type count, const BasicString& str) {
    if (pos > _size) throw std::out_of_range("BasicString::replace");
    if (pos + count >= _size) {
        count = _size - pos;
    }
    if (_size - count + str._size > _capacity) {
        reserve(_size - count + str._size);
    }
    std::move(_data + pos + count, _data + _size, _data + pos + str._size);
    std::copy(str._data, str._data + str._size, _data + pos);
    _size = _size - count + str._size;
    return *this;
}

template<typename CharT, typename Traits, typename Allocator>
void BasicString<CharT, Traits, Allocator>::swap(BasicString& other) noexcept {
    std::swap(_data, other._data);
    std::swap(_size, other._size);
    std::swap(_capacity, other._capacity);
    std::swap(_alloc, other._alloc);
}

// Search
template<typename CharT, typename Traits, typename Allocator>
typename BasicString<CharT, Traits, Allocator>::size_type
BasicString<CharT, Traits, Allocator>::find(const BasicString& str, size_type pos) const noexcept {
    for (size_type i = pos; i <= _size - str._size; ++i) {
        if (std::equal(str._data, str._data + str._size, _data + i)) {
            return i;
        }
    }
    return npos;
}

template<typename CharT, typename Traits, typename Allocator>
typename BasicString<CharT, Traits, Allocator>::size_type
BasicString<CharT, Traits, Allocator>::rfind(const BasicString& str, size_type pos) const noexcept {
    if (_size < str._size) return npos;
    for (size_type i = std::min(pos, _size - str._size); i != npos; --i) {
        if (std::equal(str._data, str._data + str._size, _data + i)) {
            return i;
        }
    }
    return npos;
}

template<typename CharT, typename Traits, typename Allocator>
typename BasicString<CharT, Traits, Allocator>::size_type
BasicString<CharT, Traits, Allocator>::find_first_of(const BasicString& str, size_type pos) const noexcept {
    for (size_type i = pos; i < _size; ++i) {
        if (std::find(str._data, str._data + str._size, _data[i]) != str._data + str._size) {
            return i;
        }
    }
    return npos;
}

template<typename CharT, typename Traits, typename Allocator>
typename BasicString<CharT, Traits, Allocator>::size_type
BasicString<CharT, Traits, Allocator>::find_first_not_of(const BasicString& str, size_type pos) const noexcept {
    for (size_type i = pos; i < _size; ++i) {
        if (std::find(str._data, str._data + str._size, _data[i]) == str._data + str._size) {
            return i;
        }
    }
    return npos;
}

template<typename CharT, typename Traits, typename Allocator>
typename BasicString<CharT, Traits, Allocator>::size_type
BasicString<CharT, Traits, Allocator>::find_last_of(const BasicString& str, size_type pos) const noexcept {
    for (size_type i = std::min(pos, _size - 1); i != npos; --i) {
        if (std::find(str._data, str._data + str._size, _data[i]) != str._data + str._size) {
            return i;
        }
    }
    return npos;
}

template<typename CharT, typename Traits, typename Allocator>
typename BasicString<CharT, Traits, Allocator>::size_type
BasicString<CharT, Traits, Allocator>::find_last_not_of(const BasicString& str, size_type pos) const noexcept {
    for (size_type i = std::min(pos, _size - 1); i != npos; --i) {
        if (std::find(str._data, str._data + str._size, _data[i]) == str._data + str._size) {
            return i;
        }
    }
    return npos;
}

// Operations
template<typename CharT, typename Traits, typename Allocator>
int BasicString<CharT, Traits, Allocator>::compare(const BasicString& str) const noexcept {
    size_type min_size = std::min(_size, str._size);
    int result = Traits::compare(_data, str._data, min_size);
    if (result != 0) {
        return result;
    }
    if (_size < str._size) {
        return -1;
    }
    if (_size > str._size) {
        return 1;
    }
    return 0;
}

template<typename CharT, typename Traits, typename Allocator>
bool BasicString<CharT, Traits, Allocator>::contains(const BasicString& str) const noexcept {
    return find(str) != npos;
}

template<typename CharT, typename Traits, typename Allocator>
BasicString<CharT, Traits, Allocator> BasicString<CharT, Traits, Allocator>::substr(size_type pos, size_type count) const {
    if (pos > _size) throw std::out_of_range("BasicString::substr");
    if (count == npos || pos + count > _size) {
        count = _size - pos;
    }
    return BasicString(_data + pos, _data + pos + count);
}

template<typename CharT, typename Traits, typename Allocator>
void BasicString<CharT, Traits, Allocator>::reallocate(size_type new_cap) {
    pointer new_data = _alloc.allocate(new_cap);
    std::move(_data, _data + _size, new_data);
    if (_data) {
        _alloc.deallocate(_data, _capacity);
    }
    _data = new_data;
    _capacity = new_cap;
}