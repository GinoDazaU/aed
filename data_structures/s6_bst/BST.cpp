#include <iostream>
#include <queue>

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

private:
    // Helper function for insert
    Node* insertRec(Node* node, int value) {
        if (node == nullptr) {
            return new Node(value);
        }

        if (value < node->data) {
            node->left = insertRec(node->left, value);
        } else if (value > node->data) {
            node->right = insertRec(node->right, value);
        }
        return node;
    }

    // Helper function for search
    bool searchRec(Node* node, int value) {
        if (node == nullptr) {
            return false;
        }
        if (value == node->data) {
            return true;
        } else if (value < node->data) {
            return searchRec(node->left, value);
        } else {
            return searchRec(node->right, value);
        }
    }

    // Helper function for removing a node
    Node* removeRec(Node* node, int value) {
        if (node == nullptr) return node;

        if (value < node->data) {
            node->left = removeRec(node->left, value);
        } else if (value > node->data) {
            node->right = removeRec(node->right, value);
        } else {
            // Node found - handle deletion

            // Case 1: Node with no children
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                return nullptr;
            }

            // Case 2: Node with one child
            if (node->left == nullptr) {
                Node* temp = node->right;
                delete node;
                return temp;
            }
            if (node->right == nullptr) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            // Case 3: Node with two children
            Node* successor = findMin(node->right);
            node->data = successor->data;
            node->right = removeRec(node->right, successor->data);
        }
        return node;
    }

    // Helper function to find the minimum value in a subtree
    Node* findMin(Node* node) {
        while (node && node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    // Helper function to find the maximum value in a subtree
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

