#include <iostream>
#include <vector>
#include <queue>
using namespace std;

class Graph {
private:
    vector<vector<int>> adjList; // Lista de adyacencia
    int nodes; // Número de nodos

public:
    Graph(int n) : nodes(n) {
        adjList.resize(n);
    }

    // Agregar una arista
    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u); // Si es no dirigido
    }

    void dfsUtil(int node, vector<bool>& visited){
        visited[node] = true;
        cout << node << " ";
        for(int neighbor: adjList[node]){
            if(!visited[neighbor]){
                dfsUtil(neighbor, visited);
            }
        }
    }

    void dfs(int start) {
        vector<bool> visited(nodes, false);
        cout << "DFS desde el nodo " << start << ": ";
        dfsUtil(start, visited);
        cout << endl;
    }

    // BFS
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

            for (int neighbor : adjList[node]) {
                if (!visited[neighbor]) {
                    visited[neighbor] = true;
                    q.push(neighbor);
                }
            }
        }
        cout << endl;
    }

    // Mostrar lista de adyacencia
    void printGraph() {
        for (int i = 0; i < nodes; ++i) {
            cout << "Nodo " << i << ": ";
            for (int neighbor : adjList[i]) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    Graph g(6);

    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 5);

    g.printGraph();
    g.dfs(0);
    g.bfs(0);

    return 0;
}
