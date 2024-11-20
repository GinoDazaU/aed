#include <iostream>
#include <vector>
#include <queue>
#include <limits>
using namespace std;

class WeightedGraph {
private:
    vector<vector<pair<int, int>>> adjList; // Lista de adyacencia con pesos
    int nodes;

public:
    WeightedGraph(int n) : nodes(n) {
        adjList.resize(n);
    }

    void addEdge(int u, int v, int weight) {
        adjList[u].emplace_back(v, weight);
        adjList[v].emplace_back(u, weight); // Si es no dirigido
    }

    void dfsUtil(int node, vector<bool>& visited) {
        visited[node] = true;
        cout << node << " ";

        for (auto neighbor : adjList[node]) {
            if (!visited[neighbor.first]) {
                dfsUtil(neighbor.first, visited);
            }
        }
    }

    void dfs(int start) {
        vector<bool> visited(nodes, false);
        cout << "DFS desde el nodo " << start << ": ";
        dfsUtil(start, visited);
        cout << endl;
    }

    void bfs(int start) {
        vector<bool> visited(nodes, false);
        queue<int> q;

        visited[start] = true;
        q.push(start);

        cout << "BFS desde el nodo " << start << ": ";
        while (!q.empty()) {
            int node = q.front();
            q.pop();
            cout << node << " ";

            for (auto neighbor : adjList[node]) {
                if (!visited[neighbor.first]) {
                    visited[neighbor.first] = true;
                    q.push(neighbor.first);
                }
            }
        }
        cout << endl;
    }

    vector<int> dijkstra(int start) {
        vector<int> dist(nodes, numeric_limits<int>::max());
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

        dist[start] = 0;
        pq.emplace(0, start);

        while (!pq.empty()) {
            int currentDist = pq.top().first;
            int node = pq.top().second;
            pq.pop();

            if (currentDist > dist[node]) continue;

            for (auto neighbor : adjList[node]) {
                int nextNode = neighbor.first;
                int weight = neighbor.second;

                if (dist[node] + weight < dist[nextNode]) {
                    dist[nextNode] = dist[node] + weight;
                    pq.emplace(dist[nextNode], nextNode);
                }
            }
        }
        return dist;
    }

    vector<int> bellmanFord(int start) {
        vector<int> dist(nodes, numeric_limits<int>::max());
        dist[start] = 0;

        for (int i = 0; i < nodes - 1; ++i) {
            for (int u = 0; u < nodes; ++u) {
                for (auto neighbor : adjList[u]) {
                    int v = neighbor.first;
                    int weight = neighbor.second;

                    if (dist[u] != numeric_limits<int>::max() && dist[u] + weight < dist[v]) {
                        dist[v] = dist[u] + weight;
                    }
                }
            }
        }

        // Verificar ciclos negativos
        for (int u = 0; u < nodes; ++u) {
            for (auto neighbor : adjList[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;

                if (dist[u] != numeric_limits<int>::max() && dist[u] + weight < dist[v]) {
                    throw runtime_error("El grafo contiene un ciclo negativo.");
                }
            }
        }
        return dist;
    }

    void printGraph() {
        for (int i = 0; i < nodes; ++i) {
            cout << "Nodo " << i << ": ";
            for (auto neighbor : adjList[i]) {
                cout << "(" << neighbor.first << ", " << neighbor.second << ") ";
            }
            cout << endl;
        }
    }
};

int main() {
    WeightedGraph wg(6);

    wg.addEdge(0, 1, 4);
    wg.addEdge(0, 2, 2);
    wg.addEdge(1, 2, 5);
    wg.addEdge(1, 3, 10);
    wg.addEdge(2, 4, 3);
    wg.addEdge(4, 3, 4);
    wg.addEdge(3, 5, 11);

    wg.printGraph();
    wg.dfs(0);
    wg.bfs(0);

    cout << "Dijkstra desde 0: ";
    for (int dist : wg.dijkstra(0)) {
        cout << dist << " ";
    }
    cout << endl;

    cout << "Bellman-Ford desde 0: ";
    try {
        for (int dist : wg.bellmanFord(0)) {
            cout << dist << " ";
        }
    } catch (const runtime_error& e) {
        cout << e.what();
    }
    cout << endl;

    return 0;
}
