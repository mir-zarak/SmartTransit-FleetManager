#pragma once
#include <algorithm>
#include <iterator>
#include "exceptions/TransitExceptions.h"

template <typename T>
class DynamicArray {
    T* m_data;
    int m_size;
    int m_capacity;

    void grow() {
        int newCap = m_capacity == 0 ? 4 : m_capacity * 2;
        T* next = new T[newCap];
        for (int i = 0; i < m_size; ++i) next[i] = m_data[i];
        delete[] m_data;
        m_data = next;
        m_capacity = newCap;
    }

public:
    using iterator = T*;
    using const_iterator = const T*;

    DynamicArray() : m_data(nullptr), m_size(0), m_capacity(0) {}
    DynamicArray(const DynamicArray& o) : DynamicArray() { for (int i = 0; i < o.m_size; ++i) append(o.m_data[i]); }
    DynamicArray(DynamicArray&& o) noexcept : m_data(o.m_data), m_size(o.m_size), m_capacity(o.m_capacity) { o.m_data = nullptr; o.m_size = o.m_capacity = 0; }
    ~DynamicArray() { delete[] m_data; }

    DynamicArray& operator=(const DynamicArray& o) { if (this != &o) { clear(); for (int i = 0; i < o.m_size; ++i) append(o.m_data[i]); } return *this; }

    int size() const { return m_size; }
    int capacity() const { return m_capacity; }
    bool isEmpty() const { return m_size == 0; }

    void append(const T& value) { if (m_size == m_capacity) grow(); m_data[m_size++] = value; }
    void insert(int idx, const T& value) {
        if (idx < 0 || idx > m_size) throw IndexOutOfBoundsException("DynamicArray insert", "DynamicArray", 5001);
        if (m_size == m_capacity) grow();
        for (int i = m_size; i > idx; --i) m_data[i] = m_data[i - 1];
        m_data[idx] = value; ++m_size;
    }
    void remove(int idx) {
        if (idx < 0 || idx >= m_size) throw IndexOutOfBoundsException("DynamicArray remove", "DynamicArray", 5002);
        for (int i = idx; i < m_size - 1; ++i) m_data[i] = m_data[i + 1];
        --m_size;
    }
    T& get(int idx) { if (idx < 0 || idx >= m_size) throw IndexOutOfBoundsException("DynamicArray get", "DynamicArray", 5003); return m_data[idx]; }
    const T& get(int idx) const { if (idx < 0 || idx >= m_size) throw IndexOutOfBoundsException("DynamicArray get", "DynamicArray", 5003); return m_data[idx]; }
    void set(int idx, const T& value) { get(idx) = value; }
    void clear() { delete[] m_data; m_data = nullptr; m_size = m_capacity = 0; }
    bool contains(const T& value) const { for (int i = 0; i < m_size; ++i) if (m_data[i] == value) return true; return false; }
    void sort() { std::sort(begin(), end()); }

    T& operator[](int idx) { return get(idx); }
    const T& operator[](int idx) const { return get(idx); }
    bool operator==(const DynamicArray& o) const {
        if (m_size != o.m_size) return false;
        for (int i = 0; i < m_size; ++i) if (!(m_data[i] == o.m_data[i])) return false;
        return true;
    }

    iterator begin() { return m_data; }
    iterator end() { return m_data + m_size; }
    const_iterator begin() const { return m_data; }
    const_iterator end() const { return m_data + m_size; }
};
