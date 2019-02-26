//
// Created by jahongir on 12/21/18.
//
****
* Дан неориентированный связный граф. Требуется найти вес минимального остовного дерева в этом графе.
* Вариант 1. Для построения минимального остовного дерева используйте алгоритм Крускала.
*/

#include "list"
#include "vector"
#include "queue"
#include "algorithm"
#include "iostream"

using namespace std;

class DSU {
public:
    explicit DSU(size_t v): parent(v+1), rnk(v+1) {
        for (int i=0; i <= v; i++) {
            rnk[i] = 0;
            parent[i] = i;
        }
    }

    int FindSet(int i) {
        if (i == parent[i])
            return i;
        return parent[i] = FindSet(parent[i]);
    }

    void MergeSet(int from, int to) {
        from = FindSet(from);
        to = FindSet(to);

        if (from != to) {
            if (rnk[from] < rnk[to])
                swap(from, to);

            parent[to] = from;

            if (rnk[from] == rnk[to])
                rnk[from]++;
        }
    }

private:
    vector<int> parent;
    vector<int> rnk;
};

class CListGraph {
public:
    explicit CListGraph(size_t v): verticesCount(v), graph(v), parent(v+1) {
        for (int i=0; i <= v; i++)
            parent[i] = i;
    }

    void AddEdge(int from, int to, int weight) {
        graph.push_back({ weight, {from, to}});
    }

    int Kruskal() {
        int mst_wt = 0;
        sort(graph.begin(), graph.end());

        DSU dsu(verticesCount);

        for (auto &i: graph) {
            int u_set = dsu.FindSet(i.second.first);
            int v_set = dsu.FindSet(i.second.second);

            if (u_set != v_set) {
                mst_wt += i.first;
                parent[u_set] = parent[v_set];
                dsu.MergeSet(u_set, v_set);
            }
        }

        return  mst_wt;
    }

    typedef pair<int, int> edge;

private:
    size_t verticesCount;
    vector<pair<int, edge>> graph;
    vector<int> parent;
};

int main() {

    size_t n, m;
    cin >> n >> m;
    CListGraph listGraph(n);

    int from, to, weight;

    for (int i=0; i < m; i++) {
        cin >> from >> to >> weight;
        listGraph.AddEdge(from, to, weight);
    }

    cout << listGraph.Kruskal();

    return 0;
}

//9 14
//0 1 4
//0 7 8
//1 2 8
//1 7 11
//2 3 7
//2 8 2
//2 5 4
//3 4 9
//3 5 14
//4 5 10
//5 6 2
//6 7 1
//6 8 6
//7 8 7
// 37
