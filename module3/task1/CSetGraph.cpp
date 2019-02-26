//
// Created by jahongir on 12/15/18.
//

#include "CSetGraph.h"

CSetGraph::CSetGraph(const IGraph* graph):
        verticesCount(graph->VerticesCount()), in(verticesCount), out(verticesCount)
{
    vector<int> vertices;

    for (int i=0; i < verticesCount; i++) {
        vertices = graph->GetNextVertices(i);
        for (int j: vertices)
            AddEdge(i, j);

        vertices.clear();
    }
}

void CSetGraph::AddEdge(int from, int to) {
    in[to].insert(from);
    out[from].insert(to);
}

size_t CSetGraph::VerticesCount() const {
    return verticesCount;
}

vector<int> CSetGraph::GetNextVertices(int vertex) const {
    vector<int> vertices;
    for (int i: in[vertex])
        vertices.push_back(i);

    return vertices;
}

vector<int> CSetGraph::GetPrevVertices(int vertex) const {
    vector<int> vertices;
    for (int i: out[vertex])
        vertices.push_back(i);

    return vertices;
}