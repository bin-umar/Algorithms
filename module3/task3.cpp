//
// Created by jahongir on 12/18/18.
//

/****
 * Требуется отыскать самый выгодный маршрут между городами. Требуемое время работы O((N+M)logN),
 * где N-количество городов, M-известных дорог между ними. Оптимизируйте ввод
 * Формат входных данных.
 * Первая строка содержит число N – количество городов.
 * Вторая строка содержит число M - количество дорог.
 * Каждая следующая строка содержит описание дороги (откуда, куда, время в пути).
 * Последняя строка содержит маршрут (откуда и куда нужно доехать).
 * Формат выходных данных.
 * Вывести длину самого выгодного маршрута.
 */

#include "list"
#include "vector"
#include "queue"
#include "iostream"

using namespace std;

class CListGraph {
public:
    explicit CListGraph(size_t v): verticesCount(v), edges(v) {}
    void AddEdge(int from, int to, int weight);
    int ShortestWay(int from, int to);

private:
    size_t verticesCount;
    vector<list<pair<int, int>>> edges;
};

void CListGraph::AddEdge(int from, int to, int weight) {
    edges[from].push_back(make_pair(to, weight));
    edges[to].push_back(make_pair(from, weight));
}

int CListGraph::ShortestWay(int from, int to) {

    vector<int> distance(verticesCount, 1000000);
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> queue;

    distance[from] = 0;
    queue.push(make_pair(0, from));

    list<pair<int, int>>::iterator i;

    while(!queue.empty()) {
        pair<int, int> top = queue.top();
        queue.pop();

        if (top.first > distance[top.second])
            continue;

        int u = top.second;

        for (i = edges[u].begin(); i != edges[u].end(); i++){
            int vertex = (*i).first;
            int weight = (*i).second;

            if (distance[vertex] > distance[u] + weight) {
                distance[vertex] = distance[u] + weight;
                queue.push(make_pair(distance[vertex], vertex));
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

    int from, to, weight;

    for (int i=0; i < v; i++) {
        cin >> from >> to >> weight;
        listGraph.AddEdge(from, to, weight);
    }

    cin >> from >> to;
    cout << listGraph.ShortestWay(from, to);

    return 0;
}

//9
//14
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
//0 3