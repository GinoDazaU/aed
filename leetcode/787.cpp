
// 787. Cheapest Flights Within K Stops

#include <vector>
#include <queue>
#include <climits>

using namespace std;

class Solution {
public:
    int findCheapestPrice(int n, vector<vector<int>>& flights, int src, int dst, int k) {
        vector<vector<pair<int, int>>> graph(n);
        for(auto edge : flights){
            graph[edge[0]].push_back({edge[1], edge[2]});
        }

        queue<pair<int, int>> q;
        q.push({src, 0});
        
        vector<int> minCost(n, INT_MAX);
        int stops = 0;
        while(!q.empty() && stops <= k){
            int size = q.size();
            while (size--) {
                auto [currNode, cost] = q.front();
                q.pop();
                for (auto& [neighbour, price] : graph[currNode]) {
                    if (price + cost < minCost[neighbour]){
                        minCost[neighbour] = price + cost;
                        q.push({neighbour, minCost[neighbour]});
                    }
                }
            }
            stops++;
        }
        if(minCost[dst] == INT_MAX)
            return -1;
        return minCost[dst];
    }
};