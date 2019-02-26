////
//// Created by jahongir on 12/15/18.
////
//
#include "CListGraph.h"

CListGraph::CListGraph(const IGraph *graph):
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

void CListGraph::AddEdge(int from, int to) {
    if (in.size() < out.size()) {
        for (int i: in[to]) {
            if (i == from) return;
        }
    } else {
        for (int i: out[from]) {
            if (i == to) return;
        }
    }

    in[to].push_back(from);
    out[from].push_back(to);
}

size_t CListGraph::VerticesCount() const {
    return verticesCount;
}

vector<int> CListGraph::GetNextVertices(int vertex) const {
    vector<int> vertices;
    for (int i: in[vertex])
        vertices.push_back(i);

    return vertices;
}

vector<int> CListGraph::GetPrevVertices(int vertex) const {
    vector<int> vertices;
    for (int i: out[vertex])
        vertices.push_back(i);

    return vertices;
}