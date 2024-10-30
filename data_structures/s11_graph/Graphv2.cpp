#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>
#include <queue>

using namespace std;

class Graph {
private:
    unordered_map<int, list<int>> adjList; // Lista de adyacencia

public:
    // Constructor vacío
    Graph() {}

    // Constructor que inicializa el grafo a partir de vectores de valores y aristas
    Graph(const vector<int>& vals, const vector<pair<int, int>>& edges) {
        for (int i = 0; i < vals.size(); ++i) {
            adjList[i]; // Inicializa cada vértice en el mapa
        }
        for (const auto& edge : edges) {
            addEdge(edge.first, edge.second);
        }
    }

    // Método para agregar una arista
    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u); // Grafo no dirigido
    }

    // Método para realizar DFS desde un vértice
    void DFS(int start) {
        unordered_map<int, bool> visited;
        dfsHelper(start, visited);
        cout << endl;
    }

    // Helper para DFS (recursivo)
    void dfsHelper(int node, unordered_map<int, bool>& visited) {
        visited[node] = true;
        cout << node << " ";
        for (int neighbor : adjList[node]) {
            if (!visited[neighbor]) {
                dfsHelper(neighbor, visited);
            }
        }
    }

    // Método para realizar BFS desde un vértice
    void BFS(int start) {
        unordered_map<int, bool> visited;
        queue<int> q;
        q.push(start);
        visited[start] = true;

        while (!q.empty()) {
            int node = q.front();
            q.pop();
            cout << node << " ";
            for (int neighbor : adjList[node]) {
                if (!visited[neighbor]) {
                    q.push(neighbor);
                    visited[neighbor] = true;
                }
            }
        }
        cout << endl;
    }

    // Método para imprimir el grafo (para verificar la estructura)
    void printGraph() {
        for (const auto& vertex : adjList) {
            cout << vertex.first << " -> ";
            for (const auto& neighbor : vertex.second) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    // Datos de ejemplo para inicializar el grafo
    vector<int> vals = {1, 2, 3, 4, 5, 6};
    vector<pair<int, int>> edges = {{0, 1}, {1, 2}, {1, 3}, {3, 4}, {3, 5}};

    // Crear el grafo con valores y aristas
    Graph g(vals, edges);

    // Imprimir el grafo
    cout << "Grafo (Lista de Adyacencia):" << endl;
    g.printGraph();

    // Ejemplo de recorrido DFS
    cout << "\nDFS desde el vértice 0:" << endl;
    g.DFS(0);

    // Ejemplo de recorrido BFS
    cout << "\nBFS desde el vértice 0:" << endl;
    g.BFS(0);

    return 0;
}
