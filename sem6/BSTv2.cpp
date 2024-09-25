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
