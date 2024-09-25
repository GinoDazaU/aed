#include <iostream>
#include <queue>
#include <vector>
#include <unordered_set>
#include <stack>

using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int value) : data(value), left(nullptr), right(nullptr) {}
};

class BST {
public:
    Node* root;

    BST() : root(nullptr) {}

    // Insert a value in the BST
    void insert(int value) {
        root = insertRec(root, value);
    }

    // Search for a value in the BST
    bool search(int value) {
        return searchRec(root, value);
    }

    // Remove a value from the BST
    void remove(int value) {
        root = removeRec(root, value);
    }

    // Find the successor of a node
    Node* findSuccessor(int value) {
        Node* current = root;
        Node* successor = nullptr;

        while (current != nullptr) {
            if (value < current->data) {
                successor = current;  // Potential successor
                current = current->left;
            } else if (value > current->data) {
                current = current->right;
            } else {
                if (current->right != nullptr) {
                    return findMin(current->right);  // Sucesor está en el subárbol derecho
                }
                break;
            }
        }
        return successor;
    }

    // Find the predecessor of a node
    Node* findPredecessor(int value) {
        Node* current = root;
        Node* predecessor = nullptr;

        while (current != nullptr) {
            if (value > current->data) {
                predecessor = current;  // Potential predecessor
                current = current->right;
            } else if (value < current->data) {
                current = current->left;
            } else {
                if (current->left != nullptr) {
                    return findMax(current->left);  // Predecesor está en el subárbol izquierdo
                }
                break;
            }
        }
        return predecessor;
    }

    // Depth-First Search (DFS): Preorder
    void preorder() {
        preorderRec(root);
        cout << endl;
    }

    // DFS: Inorder
    void inorder() {
        inorderRec(root);
        cout << endl;
    }

    // DFS: Postorder
    void postorder() {
        postorderRec(root);
        cout << endl;
    }

    // Breadth-First Search (BFS)
    void bfs() {
        if (root == nullptr) return;
        queue<Node*> q;
        q.push(root);

        while (!q.empty()) {
            Node* current = q.front();
            q.pop();
            cout << current->data << " ";

            if (current->left != nullptr) {
                q.push(current->left);
            }
            if (current->right != nullptr) {
                q.push(current->right);
            }
        }
        cout << endl;
    }

    // 324. Convert Sorted Array to BST
    Node* sortedArrayToBST(vector<int>& nums) {
        return buildBST(nums, 0, nums.size() - 1);
    }

    Node* buildBST(vector<int>& nums, int left, int right) {
        if (left > right) return nullptr;
        int mid = left + (right - left) / 2;
        Node* node = new Node(nums[mid]);
        node->left = buildBST(nums, left, mid - 1);
        node->right = buildBST(nums, mid + 1, right);
        return node;
    }

    // 235. Lowest Common Ancestor of a BST
    Node* lowestCommonAncestor(Node* p, Node* q) {
        return lowestCommonAncestorRec(root, p, q);
    }

    Node* lowestCommonAncestorRec(Node* node, Node* p, Node* q) {
        if (node->data > p->data && node->data > q->data)
            return lowestCommonAncestorRec(node->left, p, q);
        if (node->data < p->data && node->data < q->data)
            return lowestCommonAncestorRec(node->right, p, q);
        return node;
    }

    // 98. Validate BST
    bool isValidBST() {
        return validate(root, nullptr, nullptr);
    }

    bool validate(Node* node, Node* minNode, Node* maxNode) {
        if (!node) return true;
        if ((minNode && node->data <= minNode->data) || 
            (maxNode && node->data >= maxNode->data)) return false;
        return validate(node->left, minNode, node) &&
               validate(node->right, node, maxNode);
    }

    // 700. Search in a BST
    Node* searchBST(int val) {
        return searchBSTRec(root, val);
    }

    Node* searchBSTRec(Node* node, int val) {
        if (!node || node->data == val) return node;
        return val < node->data ? searchBSTRec(node->left, val) : searchBSTRec(node->right, val);
    }

    // 701. Insert into a BST
    Node* insertIntoBST(int val) {
        return insertIntoBSTRec(root, val);
    }

    Node* insertIntoBSTRec(Node* node, int val) {
        if (!node) return new Node(val);
        if (val < node->data) node->left = insertIntoBSTRec(node->left, val);
        else node->right = insertIntoBSTRec(node->right, val);
        return node;
    }

    // 450. Delete Node in a BST
    Node* deleteNode(int key) {
        return deleteNodeRec(root, key);
    }

    Node* deleteNodeRec(Node* node, int key) {
        if (!node) return node;
        if (key < node->data) node->left = deleteNodeRec(node->left, key);
        else if (key > node->data) node->right = deleteNodeRec(node->right, key);
        else {
            if (!node->left) return node->right;
            if (!node->right) return node->left;
            node->data = findMin(node->right)->data;
            node->right = deleteNodeRec(node->right, node->data);
        }
        return node;
    }

    // 653. Two Sum IV
    bool findTarget(int k) {
        unordered_set<int> set;
        return findTargetRec(root, k, set);
    }

    bool findTargetRec(Node* node, int k, unordered_set<int>& set) {
        if (!node) return false;
        if (set.count(k - node->data)) return true;
        set.insert(node->data);
        return findTargetRec(node->left, k, set) || findTargetRec(node->right, k, set);
    }

    // 230. Kth Smallest Element in a BST
    int kthSmallest(int k) {
        stack<Node*> st;
        Node* node = root;
        while (node || !st.empty()) {
            while (node) {
                st.push(node);
                node = node->left;
            }
            node = st.top();
            st.pop();
            if (--k == 0) return node->data;
            node = node->right;
        }
        return -1;
    }

    // 538. Convert BST to Greater Tree
    void convertBSTToGreaterTree() {
        int sum = 0;
        convertBSTRec(root, sum);
    }

    void convertBSTRec(Node* node, int& sum) {
        if (!node) return;
        convertBSTRec(node->right, sum);
        sum += node->data;
        node->data = sum;
        convertBSTRec(node->left, sum);
    }

    // 110. Balanced Binary Tree
    bool isBalanced() {
        return checkBalance(root) != -1;
    }

    int checkBalance(Node* node) {
        if (!node) return 0;
        int left = checkBalance(node->left);
        int right = checkBalance(node->right);
        if (left == -1 || right == -1 || abs(left - right) > 1) return -1;
        return max(left, right) + 1;
    }

    // 222. Count Complete Tree Nodes
    int countNodes() {
        return countNodesRec(root);
    }

    int countNodesRec(Node* node) {
        if (!node) return 0;
        return 1 + countNodesRec(node->left) + countNodesRec(node->right);
    }

    // 515. Find Largest Value in Each Tree Row
    vector<int> largestValues() {
        vector<int> res;
        if (!root) return res;
        queue<Node*> q;
        q.push(root);
        while (!q.empty()) {
            int size = q.size(), maxVal = INT_MIN;
            for (int i = 0; i < size; ++i) {
                Node* node = q.front();
                q.pop();
                maxVal = max(maxVal, node->data);
                if (node->left) q.push(node->left);
                if (node->right) q.push(node->right);
            }
            res.push_back(maxVal);
        }
        return res;
    }

    // Helper functions to find the minimum value in a subtree
    Node* findMin(Node* node) {
        while (node && node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    // Helper functions to find the maximum value in a subtree
    Node* findMax(Node* node) {
        while (node && node->right != nullptr) {
            node = node->right;
        }
        return node;
    }

    // Preorder traversal (Root, Left, Right)
    void preorderRec(Node* node) {
        if (node == nullptr) return;
        cout << node->data << " ";
        preorderRec(node->left);
        preorderRec(node->right);
    }

    // Inorder traversal (Left, Root, Right)
    void inorderRec(Node* node) {
        if (node == nullptr) return;
        inorderRec(node->left);
        cout << node->data << " ";
        inorderRec(node->right);
    }

    // Postorder traversal (Left, Right, Root)
    void postorderRec(Node* node) {
        if (node == nullptr) return;
        postorderRec(node->left);
        postorderRec(node->right);
        cout << node->data << " ";
    }
};

int main() {
    BST bst;
    bst.insert(50);
    bst.insert(30);
    bst.insert(70);
    bst.insert(20);
    bst.insert(40);
    bst.insert(60);
    bst.insert(80);

    cout << "Inorder (DFS): ";
    bst.inorder();

    cout << "Preorder (DFS): ";
    bst.preorder();

    cout << "Postorder (DFS): ";
    bst.postorder();

    cout << "Breadth-First Search (BFS): ";
    bst.bfs();

    return 0;
}
