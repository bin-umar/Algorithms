//
// Created by jahongir on 12/15/18.
//

#include "CArcGraph.h"

CArcGraph::CArcGraph(IGraph *graph):
            verticesCount(graph->VerticesCount()), edges(verticesCount)
{
    vector<int> vertices;

    for (int i=0; i < verticesCount; i++) {
        vertices = graph->GetNextVertices(i);
        for (int j: vertices)
            AddEdge(i, j);

        vertices.clear();
    }
}

void CArcGraph::AddEdge(int from, int to) {
    for (const auto& edge: edges) {
        if (edge.first == from && edge.second == to)
            return;
    }

    edges.emplace_back(std::make_pair(from, to));
}

size_t CArcGraph::VerticesCount() const {
    return verticesCount;
}

vector<int> CArcGraph::GetNextVertices(int vertex) const {
    vector<int> vertices;

    for(const auto& edge: edges) {
        if (edge.first == vertex)
            vertices.push_back(edge.second);
    }
    return vertices;
}

vector<int> CArcGraph::GetPrevVertices(int vertex) const {
    vector<int> vertices;

    for(const auto& edge: edges) {
        if (edge.second == vertex)
            vertices.push_back(edge.first);
    }
    return vertices;
}
