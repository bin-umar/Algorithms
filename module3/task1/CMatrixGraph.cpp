//
// Created by jahongir on 12/15/18.
//

#include "CMatrixGraph.h"

CMatrixGraph::CMatrixGraph(size_t v): verticesCount(v), edges(v) {
    for (vector<bool>& edge: edges) {
        edge.assign(verticesCount, false);
    }
}

CMatrixGraph::CMatrixGraph(const IGraph *graph) {
    CMatrixGraph(graph->VerticesCount());
    vector<int> vertices;

    for (int i=0; i < verticesCount; i++) {
        vertices = graph->GetNextVertices(i);
        for (int j: vertices)
            AddEdge(i, j);

        vertices.clear();
    }
}

void CMatrixGraph::AddEdge(int from, int to) {
    edges[from][to] = true;
}

size_t CMatrixGraph::VerticesCount() const {
    return verticesCount;
}

vector<int> CMatrixGraph::GetNextVertices(int vertex) const {
    vector<int> vertices;

    for (int i=0; i < verticesCount; i++) {
        if (edges[i][vertex])
            vertices.push_back(i);
    }

    return vertices;
}

vector<int> CMatrixGraph::GetPrevVertices(int vertex) const {
    vector<int> vertices;

    for (int i=0; i < verticesCount; i++) {
        if (edges[vertex][i])
            vertices.push_back(i);
    }

    return vertices;
}