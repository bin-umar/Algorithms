//
// Created by jahongir on 12/18/18.
//

/****
 * Дан невзвешенный неориентированный граф. В графе может быть несколько кратчайших путей между какими-то вершинами.
 * Найдите количество различных кратчайших путей между заданными вершинами. Требуемая сложность O(V+E).
 * Формат ввода.
 * v: кол-во вершин (макс. 50000),
 * n: кол-во ребер (макс. 200000),
 * n пар реберных вершин, пара вершин u, w для запроса. Формат вывода.
 * Количество кратчайших путей от u к w.
 */

#include "list"
#include "vector"
#include "queue"
#include "iostream"

using std::list;
using std::vector;
using std::queue;
using std::cout;
using std::cin;

class CListGraph {
public:
    explicit CListGraph(size_t v): verticesCount(v), edges(v) {}
    void AddEdge(int from, int to);
    int ShortestWays(int from, int to);

private:
    size_t verticesCount;
    vector<list<int>> edges;
};

void CListGraph::AddEdge(int from, int to) {
    for (int i: edges[from])
        if (i == to) return;

    edges[from].push_back(to);
    edges[to].push_back(from);
}

int CListGraph::ShortestWays(int from, int to) {

    if (from == to)
        return 0;

    vector<int> distance(verticesCount, 0);
    vector<int> length(verticesCount, 0);
    queue<int> queue;

    distance[from] = 1;
    queue.push(from);

    list<int>::iterator i;

    while(!queue.empty()) {
        int x = queue.front();
        queue.pop();

        for (i = edges[x].begin(); i != edges[x].end(); i++) {

            if (distance[*i] == 0){
                queue.push(*i);
                distance[*i] = distance[x];
                length[*i] = length[x] + 1;
            } else if (length[*i] == length[x] + 1) {
                distance[*i] += distance[x];
            }
        }
    }

    return distance[to];
}

int main() {

    size_t n;
    cin >> n;
    CListGraph listGraph(n);

    size_t v;
    cin >> v;

    int from, to;

    for (int i=0; i < v; i++) {
        cin >> from >> to;
        listGraph.AddEdge(from, to);
    }

    cin >> from >> to;
    cout << listGraph.ShortestWays(from, to);

    return 0;
}

//6
//8
//0 1
//0 4
//0 3
//1 2
//2 3
//2 5
//5 3
//3 4
//0 2
