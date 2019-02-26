//
// Created by jahongir on 12/15/18.
//

#ifndef ALGORITHMS_CARCGRAPH_H
#define ALGORITHMS_CARCGRAPH_H

#include "IGraph.h"
using std::pair;

class CArcGraph: public IGraph {
public:
    explicit CArcGraph(size_t v): verticesCount(v), edges(v) {};
    CArcGraph(IGraph *graph);

    void AddEdge(int from, int to) override;
    size_t VerticesCount() const override;
    vector<int> GetNextVertices(int vertex) const override;
    vector<int> GetPrevVertices(int vertex) const override;

private:
    size_t verticesCount;
    vector<pair<int, int>> edges;
};

#endif //ALGORITHMS_CARCGRAPH_H
