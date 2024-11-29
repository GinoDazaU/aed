#include <vector>
#include <queue>
using namespace std;

class Solution {
public:
    vector<int> findMinHeightTrees(int n, vector<vector<int>>& edges) {
        if (n == 1) return {0};

        // Paso 1: Construir el grafo como lista de adyacencia
        vector<vector<int>> graph(n);
        vector<int> degree(n, 0); // Grados de los nodos
        for (auto edge : edges) {
            graph[edge[0]].push_back(edge[1]);
            graph[edge[1]].push_back(edge[0]);
            degree[edge[0]]++;
            degree[edge[1]]++;
        }

        // Paso 2: Inicializar la cola con las hojas (nodos de grado 1)
        queue<int> leaves;
        for (int i = 0; i < n; i++) {
            if (degree[i] == 1) {
                leaves.push(i);
            }
        }

        // Paso 3: Reducir el grafo eliminando hojas nivel por nivel
        int remainingNodes = n;
        while (remainingNodes > 2) {
            int leavesCount = leaves.size();
            remainingNodes -= leavesCount;

            for (int i = 0; i < leavesCount; i++) {
                int leaf = leaves.front();
                leaves.pop();

                for (int neighbor : graph[leaf]) {
                    degree[neighbor]--;
                    if (degree[neighbor] == 1) {
                        leaves.push(neighbor);
                    }
                }
            }
        }

        // Paso 4: Los nodos restantes son las raíces de los MHT
        vector<int> result;
        while (!leaves.empty()) {
            result.push_back(leaves.front());
            leaves.pop();
        }

        return result;
    }
};