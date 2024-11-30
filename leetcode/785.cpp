
// 785. Is Graph Bipartite?

#include <vector>
#include <stack>
using namespace std;

class Solution {
public:
    bool isBipartite(vector<vector<int>>& graph) {
        vector<char> visited(graph.size(), 'w');

        for (int i = 0; i < graph.size(); i++) {
            if (visited[i] == 'w') {
                if (!dfs(i, graph, visited)) {
                    return false;
                }
            }
        }

        return true;
    }

private:
    bool dfs(int node, vector<vector<int>>& graph, vector<char>& visited) {
        stack<int> s;
        s.push(node);
        visited[node] = 'b';
        while (!s.empty()) {
            int current = s.top();
            s.pop();

            for (int neighbor : graph[current]) {
                if (visited[neighbor] == 'w') {
                    visited[neighbor] = (visited[current] == 'b' ? 'r' : 'b');
                    s.push(neighbor);
                } else if (visited[neighbor] == visited[current]) {
                    return false;
                }
            }
        }

        return true;
    }
};
