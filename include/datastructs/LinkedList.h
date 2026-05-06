#pragma once
#include <cstddef>
#include "exceptions/TransitExceptions.h"

template <typename T>
class LinkedList {
    struct Node { T data; Node* next; Node(const T& d):data(d),next(nullptr){} };
    Node* m_head{nullptr};
    int m_size{0};

public:
    LinkedList() = default;
    LinkedList(const LinkedList& o) : LinkedList() { for (auto* n = o.m_head; n; n = n->next) push_back(n->data); }
    ~LinkedList() { clear(); }

    int size() const { return m_size; }
    bool isEmpty() const { return m_size == 0; }

    void push_front(const T& value) { Node* n = new Node(value); n->next = m_head; m_head = n; ++m_size; }
    void push_back(const T& value) { Node* n = new Node(value); if (!m_head) m_head = n; else { Node* cur = m_head; while (cur->next) cur = cur->next; cur->next = n; } ++m_size; }

    void removeAt(int idx) {
        if (idx < 0 || idx >= m_size) throw IndexOutOfBoundsException("LinkedList remove", "LinkedList", 6001);
        Node* cur = m_head;
        if (idx == 0) { m_head = m_head->next; delete cur; --m_size; return; }
        for (int i = 0; i < idx - 1; ++i) cur = cur->next;
        Node* victim = cur->next; cur->next = victim->next; delete victim; --m_size;
    }

    T& operator[](int idx) {
        if (idx < 0 || idx >= m_size) throw IndexOutOfBoundsException("LinkedList access", "LinkedList", 6002);
        Node* cur = m_head; for (int i = 0; i < idx; ++i) cur = cur->next; return cur->data;
    }
    const T& operator[](int idx) const { return const_cast<LinkedList*>(this)->operator[](idx); }
    void clear() { while (m_head) { Node* n = m_head; m_head = m_head->next; delete n; } m_size = 0; }
    bool operator==(const LinkedList& o) const { if (m_size != o.m_size) return false; for (int i=0;i<m_size;++i) if (!( (*this)[i] == o[i])) return false; return true; }
};
