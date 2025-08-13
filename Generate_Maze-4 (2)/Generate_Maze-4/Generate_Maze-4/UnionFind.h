//
// Created by Colli on 11/10/2024.
//

#ifndef GENERATE_MAZE_4_UNIONFIND_H
#define GENERATE_MAZE_4_UNIONFIND_H
#include <iostream>
#include <vector>
#include <algorithm>
#include <random>


using namespace std;

// Union-Find structure for cycle detection
class UnionFind {
public:
    UnionFind(int size) : parent(size), rank(size, 0) {
        for (int i = 0; i < size; ++i) {
            parent[i] = i;
        }
    }

    int find(int u) {
        if (parent[u] != u) {
            parent[u] = find(parent[u]);
        }
        return parent[u];
    }

    void unionSets(int u, int v) {
        int rootU = find(u);
        int rootV = find(v);
        if (rootU != rootV) {
            if (rank[rootU] > rank[rootV]) {
                parent[rootV] = rootU;
            } else if (rank[rootU] < rank[rootV]) {
                parent[rootU] = rootV;
            } else {
                parent[rootV] = rootU;
                rank[rootU]++;
            }
        }
    }

private:
    vector<int> parent;
    vector<int> rank;
};

// Edge structure to store graph edges
struct Edge {
    int u, v, weight;

    bool operator<(const Edge &other) const {
        return weight < other.weight;
    }
};


#endif //GENERATE_MAZE_4_UNIONFIND_H
