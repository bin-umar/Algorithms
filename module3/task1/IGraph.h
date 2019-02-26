//
// Created by jahongir on 12/15/18.
//

#ifndef ALGORITHMS_IGRAPH_H
#define ALGORITHMS_IGRAPH_H

#include <vector>
#include <list>
#include <set>
#include <utility>

using std::vector;

struct IGraph {
    virtual ~IGraph() {};

    // Добавление ребра от from к to.
    virtual void AddEdge(int from, int to) = 0;
    virtual size_t VerticesCount() const  = 0;

    virtual vector<int> GetNextVertices(int vertex) const = 0;
    virtual vector<int> GetPrevVertices(int vertex) const = 0;
};

#endif //ALGORITHMS_IGRAPH_H
