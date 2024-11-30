
// 743. Network Delay Time

#include <vector>
#include <queue>
#include <climits>
#include <algorithm>

using namespace std;

class Solution {
public:
    int networkDelayTime(vector<vector<int>>& times, int n, int k) {
        vector<vector<pair<int, int>>> graph(n);
        for (auto edge : times) {
            graph[edge[0] - 1].push_back({edge[1] - 1, edge[2]});
        }

        vector<int> dist(n, INT_MAX);
        dist[k - 1] = 0;

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;
        pq.push({0, k - 1});

        while (!pq.empty()) {
            auto [currentDist, node] = pq.top();
            pq.pop();

            if (currentDist > dist[node]) continue;

            for (auto [neighbor, weight] : graph[node]) {
                int newDist = currentDist + weight;
                if (newDist < dist[neighbor]) {
                    dist[neighbor] = newDist;
                    pq.push({newDist, neighbor});
                }
            }
        }

        int maxDist = *max_element(dist.begin(), dist.end());
        return maxDist == INT_MAX ? -1 : maxDist;
    }
};
