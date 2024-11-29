
// 347. Number of Provinces

#include<vector>
#include<stack>
using namespace std;

class Solution {
public:
    int findCircleNum(vector<vector<int>>& isConnected) {

        // Paso 1: Construir el grafo como lista de adyacencia
        int n = isConnected.size();
        if (n == 1) return 1;

        vector<vector<int>> graph(n);
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (isConnected[i][j] == 1) {
                    graph[i].push_back(j); 
                    graph[j].push_back(i);
                }
            }
        }
        
        // Paso 2: Inicializar estructuras para el recorrido
        vector<bool> visited(n, false);
        stack<int> s;

        int counter = 0;

        // Paso 3: Realizar DFS para contar los componentes conexos
        for (int i = 0; i < n; i++) {
            if (!visited[i]) {
                counter++; 
                s.push(i);
                visited[i] = true;

                // Realizar DFS desde el nodo actual
                while (!s.empty()) {
                    int node = s.top();
                    s.pop();
                    for (int neighbor : graph[node]) {
                        if (!visited[neighbor]) {
                            s.push(neighbor);
                            visited[neighbor] = true;
                        }
                    }
                }
            }
        }

        // Paso 4: Retornar el número de componentos conexos (provincias)
        return counter;
    }
};
