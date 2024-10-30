#include <iostream>
#include <vector>
#include <unordered_map>
#include <list>

using namespace std;

class Graph {
private:
    unordered_map<int, list<int>> adjList; // Lista de adyacencia

public:
    // Agregar un vértice
    void addVertex(int vertex) {
        adjList[vertex]; // Crea una entrada para el vértice si no existe
    }

    // Agregar una arista (u, v)
    void addEdge(int u, int v, bool isDirected = false) {
        adjList[u].push_back(v); // Agrega v a la lista de adyacencia de u
        if (!isDirected) {
            adjList[v].push_back(u); // Si es no dirigido, agrega u a la lista de adyacencia de v
        }
    }

    // Eliminar una arista
    void removeEdge(int u, int v) {
        adjList[u].remove(v);
        adjList[v].remove(u);
    }

    // Imprimir el grafo
    void printGraph() {
        for (const auto &vertex : adjList) {
            cout << vertex.first << " -> ";
            for (const auto &neighbor : vertex.second) {
                cout << neighbor << " ";
            }
            cout << endl;
        }
    }

    // Búsqueda en profundidad (DFS)
    void DFS(int startVertex, unordered_map<int, bool> &visited) {
        visited[startVertex] = true;
        cout << startVertex << " ";

        for (int neighbor : adjList[startVertex]) {
            if (!visited[neighbor]) {
                DFS(neighbor, visited);
            }
        }
    }

    // Iniciar DFS desde un vértice dado
    void startDFS(int startVertex) {
        unordered_map<int, bool> visited;
        for (const auto &vertex : adjList) {
            visited[vertex.first] = false;
        }
        DFS(startVertex, visited);
        cout << endl;
    }
};

int main() {
    Graph g;

    // Agregar vértices
    g.addVertex(1);
    g.addVertex(2);
    g.addVertex(3);
    g.addVertex(4);
    g.addVertex(5);

    // Agregar aristas
    g.addEdge(1, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 4);
    g.addEdge(3, 5);
    g.addEdge(4, 5);

    // Imprimir el grafo
    cout << "Grafo representado con lista de adyacencia:" << endl;
    g.printGraph();

    // Realizar DFS desde el vértice 1
    cout << "DFS desde el vértice 1: ";
    g.startDFS(1);

    return 0;
}
