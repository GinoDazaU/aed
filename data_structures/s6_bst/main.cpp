



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





// 324. Convert Sorted Array to Binary Search Tree:

// Construye un BST balanceado a partir de un array ordenado.
public:
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
};




// 235. Lowest Common Ancestor of a Binary Search Tree:

// Encuentra el ancestro común más bajo de dos nodos.
    Node* lowestCommonAncestor(Node* root, Node* p, Node* q) {
        if (root->data > p->data && root->data > q->data)
            return lowestCommonAncestor(root->left, p, q);
        if (root->data < p->data && root->data < q->data)
            return lowestCommonAncestor(root->right, p, q);
        return root;
    }
};

"""

"""
98. Validate Binary Search Tree:

// Verifica si el árbol es un BST válido.
    bool isValidBST(Node* root) {
        return validate(root, nullptr, nullptr);
    }

    bool validate(Node* node, Node* minNode, Node* maxNode) {
        if (!node) return true;
        if ((minNode && node->data <= minNode->data) || 
            (maxNode && node->data >= maxNode->data)) return false;
        return validate(node->left, minNode, node) &&
               validate(node->right, node, maxNode);
    }
};

"""

"""
700. Search in a Binary Search Tree:

// Busca un valor en el BST.
    Node* searchBST(Node* root, int val) {
        if (!root || root->data == val) return root;
        return val < root->data ? searchBST(root->left, val) : searchBST(root->right, val);
    }
};

"""

"""
701. Insert into a Binary Search Tree:

// Inserta un valor en el BST.

    Node* insertIntoBST(Node* root, int val) {
        if (!root) return new Node(val);
        if (val < root->data) root->left = insertIntoBST(root->left, val);
        else root->right = insertIntoBST(root->right, val);
        return root;
    }
};

"""

"""
450. Delete Node in a BST:

// Elimina un nodo en el BST.

    Node* deleteNode(Node* root, int key) {
        if (!root) return root;
        if (key < root->data) root->left = deleteNode(root->left, key);
        else if (key > root->data) root->right = deleteNode(root->right, key);
        else {
            if (!root->left) return root->right;
            if (!root->right) return root->left;
            root->data = findMin(root->right)->data;
            root->right = deleteNode(root->right, root->data);
        }
        return root;
    }

    Node* findMin(Node* node) {
        while (node->left) node = node->left;
        return node;
    }
};

"""

"""
108. Convert Sorted Array to BST:

// Convierte un array ordenado en un BST balanceado.

    Node* sortedArrayToBST(vector<int>& nums) {
        return helper(nums, 0, nums.size() - 1);
    }

    Node* helper(vector<int>& nums, int left, int right) {
        if (left > right) return nullptr;
        int mid = (left + right) / 2;
        Node* node = new Node(nums[mid]);
        node->left = helper(nums, left, mid - 1);
        node->right = helper(nums, mid + 1, right);
        return node;
    }
};

"""

"""
653. Two Sum IV - Input is a BST:

// Encuentra si hay dos números que sumen un valor en el BST.

    bool findTarget(Node* root, int k) {
        unordered_set<int> set;
        return dfs(root, k, set);
    }

    bool dfs(Node* root, int k, unordered_set<int>& set) {
        if (!root) return false;
        if (set.count(k - root->data)) return true;
        set.insert(root->data);
        return dfs(root->left, k, set) || dfs(root->right, k, set);
    }
};

"""

"""
230. Kth Smallest Element in a BST:

// Encuentra el k-ésimo elemento más pequeño en un BST.

    int kthSmallest(Node* root, int k) {
        stack<Node*> st;
        while (root || !st.empty()) {
            while (root) {
                st.push(root);
                root = root->left;
            }
            root = st.top();
            st.pop();
            if (--k == 0) return root->data;
            root = root->right;
        }
        return -1;
    }
};

"""

"""
538. Convert BST to Greater Tree:

// Convierte el BST para que cada nodo contenga la suma de todos los valores mayores o iguales a él.

    Node* convertBST(Node* root) {
        int sum = 0;
        traverse(root, sum);
        return root;
    }

    void traverse(Node* node, int& sum) {
        if (!node) return;
        traverse(node->right, sum);
        sum += node->data;
        node->data = sum;
        traverse(node->left, sum);
    }
};

"""

"""
110. Balanced Binary Tree:

// Determina si un árbol es balanceado.

    bool isBalanced(Node* root) {
        return height(root) != -1;
    }

    int height(Node* node) {
        if (!node) return 0;
        int left = height(node->left);
        int right = height(node->right);
        if (left == -1 || right == -1 || abs(left - right) > 1) return -1;
        return max(left, right) + 1;
    }
};

"""

"""
1038. Binary Search Tree to Greater Sum Tree:

// Convierte un BST en un árbol donde cada nodo contiene la suma de todos los nodos mayores.

    Node* bstToGst(Node* root) {
        int sum = 0;
        dfs(root, sum);
        return root;
    }

    void dfs(Node* node, int& sum) {
        if (!node) return;
        dfs(node->right, sum);
        sum += node->data;
        node->data = sum;
        dfs(node->left, sum);
    }
};

"""

"""
222. Count Complete Tree Nodes:

// Cuenta el número de nodos en un árbol binario completo.

    int countNodes(Node* root) {
        if (!root) return 0;
        return 1 + countNodes(root->left) + countNodes(root->right);
    }
};

"""

"""
144. Binary Tree Preorder Traversal:

// Realiza un recorrido preorden de un árbol binario.

    vector<int> preorderTraversal(Node* root) {
        vector<int> res;
        stack<Node*> st;
        if (root) st.push(root);
        while (!st.empty()) {
            Node* node = st.top();
            st.pop();
            res.push_back(node->data);
            if (node->right) st.push(node->right);
            if (node->left) st.push(node->left);
        }
        return res;
    }
};

"""

"""
145. Binary Tree Postorder Traversal:

// Realiza un recorrido postorden de un árbol binario.

    vector<int> postorderTraversal(Node* root) {
        vector<int> res;
        stack<Node*> st;
        Node* last = nullptr;
        while (root || !st.empty()) {
            while (root) {
                st.push(root);
                root = root->left;
            }
            Node* node = st.top();
            if (!node->right || node->right == last) {
                res.push_back(node->data);
                st.pop();
                last = node;
            } else {
                root = node->right;
            }
        }
        return res;
    }
};

"""

"""
94. Binary Tree Inorder Traversal:

// Realiza un recorrido inorden de un árbol binario.

    vector<int> inorderTraversal(Node* root) {
        vector<int> res;
        stack<Node*> st;
        while (root || !st.empty()) {
            while (root) {
                st.push(root);
                root = root->left;
            }
            root = st.top();
            st.pop();
            res.push_back(root->data);
            root = root->right;
        }
        return res;
    }
};

"""

"""
515. Find Largest Value in Each Tree Row:

// Encuentra el valor más grande en cada fila de


    vector<int> largestValues(Node* root) {
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
};

"""

"""
105. Construct Binary Tree from Preorder and Inorder Traversal:

// Reconstruye un árbol binario a partir de sus recorridos preorden e inorden.

    Node* buildTree(vector<int>& preorder, vector<int>& inorder) {
        int preIndex = 0;
        return build(preorder, inorder, preIndex, 0, inorder.size() - 1);
    }

    Node* build(vector<int>& preorder, vector<int>& inorder, int& preIndex, int inStart, int inEnd) {
        if (inStart > inEnd) return nullptr;
        Node* node = new Node(preorder[preIndex++]);
        int inIndex = find(inorder.begin() + inStart, inorder.begin() + inEnd, node->data) - inorder.begin();
        node->left = build(preorder, inorder, preIndex, inStart, inIndex - 1);
        node->right = build(preorder, inorder, preIndex, inIndex + 1, inEnd);
        return node;
    }
};

"""

"""
106. Construct Binary Tree from Inorder and Postorder Traversal:

// Reconstruye un árbol binario a partir de sus recorridos inorden y postorden.

    Node* buildTree(vector<int>& inorder, vector<int>& postorder) {
        int postIndex = postorder.size() - 1;
        return build(inorder, postorder, postIndex, 0, inorder.size() - 1);
    }

    Node* build(vector<int>& inorder, vector<int>& postorder, int& postIndex, int inStart, int inEnd) {
        if (inStart > inEnd) return nullptr;
        Node* node = new Node(postorder[postIndex--]);
        int inIndex = find(inorder.begin() + inStart, inorder.begin() + inEnd, node->data) - inorder.begin();
        node->right = build(inorder, postorder, postIndex, inIndex + 1, inEnd);
        node->left = build(inorder, postorder, postIndex, inStart, inIndex - 1);
        return node;
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

    // Find successor and predecessor
    int value = 50;
    Node* successor = bst.findSuccessor(value);
    Node* predecessor = bst.findPredecessor(value);

    if (successor) {
        cout << "Successor of " << value << ": " << successor->data << endl;
    } else {
        cout << "No successor for " << value << endl;
    }

    if (predecessor) {
        cout << "Predecessor of " << value << ": " << predecessor->data << endl;
    } else {
        cout << "No predecessor for " << value << endl;
    }

    return 0;
}


#include <iostream>
#include <queue>
#include <stack>

using namespace std;

struct Node {
    int data;
    Node* left;
    Node* right;

    Node(int value) : data(value), left(nullptr), right(nullptr) {}
    ~Node() {
        // Destructor para liberar memoria
        delete left;
        delete right;
    }
};

class BST {
public:
    Node* root;

    BST() : root(nullptr) {}
    ~BST() {
        delete root;
    }

    // Insertar un valor en el BST (permite duplicados)
    void insert(int value) {
        root = insertRec(root, value);
    }

    // Buscar un valor en el BST
    bool search(int value) {
        return searchRec(root, value);
    }

    // Eliminar un valor del BST
    void remove(int value) {
        root = removeRec(root, value);
    }

    // Encontrar el sucesor de un nodo
    Node* findSuccessor(int value) {
        Node* current = root;
        Node* successor = nullptr;

        while (current != nullptr) {
            if (value < current->data) {
                successor = current;  // Potencial sucesor
                current = current->left;
            } else if (value > current->data) {
                current = current->right;
            } else {
                if (current->right != nullptr) {
                    return findMin(current->right);  // Sucesor en el subárbol derecho
                }
                break;
            }
        }
        return successor;
    }

    // Encontrar el predecesor de un nodo
    Node* findPredecessor(int value) {
        Node* current = root;
        Node* predecessor = nullptr;

        while (current != nullptr) {
            if (value > current->data) {
                predecessor = current;  // Potencial predecesor
                current = current->right;
            } else if (value < current->data) {
                current = current->left;
            } else {
                if (current->left != nullptr) {
                    return findMax(current->left);  // Predecesor en el subárbol izquierdo
                }
                break;
            }
        }
        return predecessor;
    }

    // Calcular la altura del árbol
    int height() {
        return heightRec(root);
    }

    // Verificar si el árbol es un BST válido
    bool isValidBST() {
        return isValidBSTRec(root, nullptr, nullptr);
    }

    // Recorrido en profundidad (DFS): Preorden
    void preorder() {
        preorderRec(root);
        cout << endl;
    }

    // DFS: Inorden
    void inorder() {
        inorderRec(root);
        cout << endl;
    }

    // DFS: Postorden
    void postorder() {
        postorderRec(root);
        cout << endl;
    }

    // Recorrido inorden iterativo
    void inorderIterative() {
        if (root == nullptr) return;
        stack<Node*> s;
        Node* current = root;

        while (current != nullptr || !s.empty()) {
            while (current != nullptr) {
                s.push(current);
                current = current->left;
            }
            current = s.top();
            s.pop();
            cout << current->data << " ";
            current = current->right;
        }
        cout << endl;
    }

    // Recorrido en anchura (BFS)
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
    // Función auxiliar para insertar (permite duplicados a la izquierda)
    Node* insertRec(Node* node, int value) {
        if (node == nullptr) {
            return new Node(value);
        }

        if (value <= node->data) {
            node->left = insertRec(node->left, value);
        } else {
            node->right = insertRec(node->right, value);
        }
        return node;
    }

    // Función auxiliar para buscar
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

    // Función auxiliar para eliminar un nodo
    Node* removeRec(Node* node, int value) {
        if (node == nullptr) return node;

        if (value < node->data) {
            node->left = removeRec(node->left, value);
        } else if (value > node->data) {
            node->right = removeRec(node->right, value);
        } else {
            // Nodo encontrado - manejar eliminación

            // Caso 1: Nodo sin hijos
            if (node->left == nullptr && node->right == nullptr) {
                delete node;
                return nullptr;
            }

            // Caso 2: Nodo con un hijo
            if (node->left == nullptr) {
                Node* temp = node->right;
                node->left = node->right = nullptr;
                delete node;
                return temp;
            }
            if (node->right == nullptr) {
                Node* temp = node->left;
                node->left = node->right = nullptr;
                delete node;
                return temp;
            }

            // Caso 3: Nodo con dos hijos
            Node* successor = findMin(node->right);
            node->data = successor->data;
            node->right = removeRec(node->right, successor->data);
        }
        return node;
    }

    // Función auxiliar para encontrar el valor mínimo en un subárbol
    Node* findMin(Node* node) {
        while (node && node->left != nullptr) {
            node = node->left;
        }
        return node;
    }

    // Función auxiliar para encontrar el valor máximo en un subárbol
    Node* findMax(Node* node) {
        while (node && node->right != nullptr) {
            node = node->right;
        }
        return node;
    }

    // Recorrido preorden (Raíz, Izquierda, Derecha)
    void preorderRec(Node* node) {
        if (node == nullptr) return;
        cout << node->data << " ";
        preorderRec(node->left);
        preorderRec(node->right);
    }

    // Recorrido inorden (Izquierda, Raíz, Derecha)
    void inorderRec(Node* node) {
        if (node == nullptr) return;
        inorderRec(node->left);
        cout << node->data << " ";
        inorderRec(node->right);
    }

    // Recorrido postorden (Izquierda, Derecha, Raíz)
    void postorderRec(Node* node) {
        if (node == nullptr) return;
        postorderRec(node->left);
        postorderRec(node->right);
        cout << node->data << " ";
    }

    // Función auxiliar para calcular la altura del árbol
    int heightRec(Node* node) {
        if (node == nullptr) return -1;
        int leftHeight = heightRec(node->left);
        int rightHeight = heightRec(node->right);
        return max(leftHeight, rightHeight) + 1;
    }

    // Función auxiliar para validar el BST
    bool isValidBSTRec(Node* node, Node* minNode, Node* maxNode) {
        if (node == nullptr) return true;
        if ((minNode != nullptr && node->data <= minNode->data) ||
            (maxNode != nullptr && node->data >= maxNode->data)) {
            return false;
        }
        return isValidBSTRec(node->left, minNode, node) &&
               isValidBSTRec(node->right, node, maxNode);
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
    bst.insert(70); // Insertar duplicado

    cout << "Inorden (DFS): ";
    bst.inorder();

    cout << "Inorden iterativo (DFS): ";
    bst.inorderIterative();

    cout << "Preorden (DFS): ";
    bst.preorder();

    cout << "Postorden (DFS): ";
    bst.postorder();

    cout << "Recorrido en anchura (BFS): ";
    bst.bfs();

    // Encontrar sucesor y predecesor
    int value = 50;
    Node* successor = bst.findSuccessor(value);
    Node* predecessor = bst.findPredecessor(value);

    if (successor) {
        cout << "Sucesor de " << value << ": " << successor->data << endl;
    } else {
        cout << "No hay sucesor para " << value << endl;
    }

    if (predecessor) {
        cout << "Predecesor de " << value << ": " << predecessor->data << endl;
    } else {
        cout << "No hay predecesor para " << value << endl;
    }

    cout << "Altura del árbol: " << bst.height() << endl;

    cout << "Es un BST válido: " << (bst.isValidBST() ? "Sí" : "No") << endl;

    return 0;
}
