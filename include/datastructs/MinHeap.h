#pragma once
#include <vector>
#include <functional>

template <typename T, typename Compare = std::less<T>>
class MinHeap {
    std::vector<T> m_data;
    Compare m_compare{};

    void up(size_t i) {
        while (i > 0) {
            size_t p = (i - 1) / 2;
            if (!m_compare(m_data[i], m_data[p])) break;
            std::swap(m_data[i], m_data[p]);
            i = p;
        }
    }
    void down(size_t i) {
        for (;;) {
            size_t l = 2*i + 1, r = 2*i + 2, s = i;
            if (l < m_data.size() && m_compare(m_data[l], m_data[s])) s = l;
            if (r < m_data.size() && m_compare(m_data[r], m_data[s])) s = r;
            if (s == i) break;
            std::swap(m_data[i], m_data[s]);
            i = s;
        }
    }

public:
    void push(const T& v) { m_data.push_back(v); up(m_data.size() - 1); }
    T pop() { T v = m_data.front(); m_data.front() = m_data.back(); m_data.pop_back(); if (!m_data.empty()) down(0); return v; }
    bool empty() const { return m_data.empty(); }
    size_t size() const { return m_data.size(); }
};
