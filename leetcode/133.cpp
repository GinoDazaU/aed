
// 133. Clone Graph

#include <unordered_map>
#include <vector>
#include <stack>

using namespace std;

class Node {
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        neighbors = vector<Node*>();
    }
    Node(int _val) {
        val = _val;
        neighbors = vector<Node*>();
    }
    Node(int _val, vector<Node*> _neighbors) {
        val = _val;
        neighbors = _neighbors;
    }
};

class Solution {
public:
    Node* cloneGraph(Node* node) {
        if (!node) return nullptr;

        unordered_map<Node*, Node*> clones;
        stack<Node*> s;
        s.push(node);

        clones[node] = new Node(node->val);

        while (!s.empty()) {
            Node* current = s.top();
            s.pop();

            for (Node* neighbor : current->neighbors) {

                if (!clones.count(neighbor)) {
                    clones[neighbor] = new Node(neighbor->val);
                    s.push(neighbor);
                }

                clones[current]->neighbors.push_back(clones[neighbor]);
            }
        }

        return clones[node];
    }
};
