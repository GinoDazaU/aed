// 207. Course Schedule I

#include <vector>
using namespace std;

class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {

        // Paso 1: Construir el grafo como lista de adyacencia
        vector<vector<int>> graph(numCourses);
        for (auto edge : prerequisites) {
            graph[edge[1]].push_back(edge[0]);
        }

        // Paso 2: Inicializar vectores para verificar ciclos
        vector<bool> checked(numCourses, false);
        vector<bool> visited(numCourses, false);

        // Paso 3: Revisar cada nodo en busca de ciclos
        for (int i = 0; i < numCourses; i++) {
            if (hasCycle(i, graph, visited, checked)) {
                return false;
            }
        }

        // Paso 4: Si no hay ciclos, se pueden completar los cursos
        return true;
    }

private:
    // Verificar si hay un ciclo partiendo de un nodo específico
    bool hasCycle(int node, vector<vector<int>>& graph, vector<bool>& visited, vector<bool>& checked) {

        // Paso A: Retornar si ya fue procesado o si está en el recorrido actual
        if (checked[node]) return false;
        if (visited[node]) return true;

        // Paso B: Marcar el nodo como visitado en el recorrido actual
        visited[node] = true;

        // Paso C: Verificar recursivamente los vecinos del nodo
        for (int neighbor : graph[node]) {
            if (hasCycle(neighbor, graph, visited, checked)) {
                return true; // Si se detecta un ciclo, retornar true
            }
        }

        // Paso D: Marcar el nodo como procesado y desmarcarlo del recorrido actual
        visited[node] = false;
        checked[node] = true;

        // No se detectaron ciclos desde este nodo
        return false; 
    }
};
