#pragma once
#include <unordered_map>
#include <vector>
#include <queue>
#include <limits>
#include "exceptions/TransitExceptions.h"

template <typename V, typename W = double>
class Graph {
    std::unordered_map<int, std::vector<std::pair<int, W>>> m_adj;
public:
    void addVertex(int id) { m_adj.emplace(id, std::vector<std::pair<int, W>>{}); }
    void addEdge(int from, int to, W weight) { m_adj[from].push_back({to, weight}); }
    bool hasVertex(int id) const { return m_adj.find(id) != m_adj.end(); }
};
