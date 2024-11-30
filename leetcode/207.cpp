
#include <vector>

using namespace std;

class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        vector<vector<int>> graph(numCourses);
        for(auto& edge: prerequisites){
            graph[edge[0]].push_back(edge[1]);
        }

        vector<int> visited(numCourses, 0);

        for(int i = 0; i < numCourses; i++){
            if(visited[i] == 0 && hasCycle(i, graph, visited)){
                return false;
            }
        }

        return true;
    }
private:
    bool hasCycle(int node, vector<vector<int>>& graph, vector<int>& visited){
        if(visited[node] == 1) return true;
        if(visited[node] == 2) return false;

        visited[node] = 1;
        for(int neighbor: graph[node]){
            if(hasCycle(neighbor, graph, visited)){
                return true;
            }
        }

        visited[node] = 2;
        return false;
    }
};
