#include <iostream>
#include <algorithm> // Para std::max
using namespace std;

template <class T>
class AVLTree {
private:
    struct Node {
        T data;
        Node* left;
        Node* right;
        int height;

        Node(T value) : data(value), left(nullptr), right(nullptr), height(1) {}
    };

    Node* root;

    // Obtener la altura de un nodo
    int getHeight(Node* node) {
        return node ? node->height : 0;
    }

    // Calcular el factor de balanceo de un nodo
    int getBalanceFactor(Node* node) {
        return node ? getHeight(node->left) - getHeight(node->right) : 0;
    }

    // Rotación a la derecha
    Node* rotateRight(Node* y) {
        Node* x = y->left;
        Node* T = x->right;

        x->right = y;
        y->left = T;

        y->height = 1 + max(getHeight(y->left), getHeight(y->right));
        x->height = 1 + max(getHeight(x->left), getHeight(x->right));

        return x;
    }

    // Rotación a la izquierda
    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        Node* T = y->left;

        y->left = x;
        x->right = T;

        x->height = 1 + max(getHeight(x->left), getHeight(x->right));
        y->height = 1 + max(getHeight(y->left), getHeight(y->right));

        return y;
    }

    // Inserción de un nodo en el árbol
    Node* insert(Node* node, T value) {
        if (!node) return new Node(value);

        if (value < node->data) {
            node->left = insert(node->left, value);
        } else if (value > node->data) {
            node->right = insert(node->right, value);
        } else {
            return node; // No se permiten duplicados
        }

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));

        int balanceFactor = getBalanceFactor(node);

        // Rotaciones para balancear
        if (balanceFactor > 1 && value < node->left->data) {
            return rotateRight(node);
        }

        if (balanceFactor < -1 && value > node->right->data) {
            return rotateLeft(node);
        }

        if (balanceFactor > 1 && value > node->left->data) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        if (balanceFactor < -1 && value < node->right->data) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    // Nodo con el valor mínimo en un subárbol
    Node* getMinValueNode(Node* node) {
        while (node->left) node = node->left;
        return node;
    }

    // Eliminación de un nodo del árbol
    Node* remove(Node* node, T value) {
        if (!node) return nullptr;

        if (value < node->data) {
            node->left = remove(node->left, value);
        } else if (value > node->data) {
            node->right = remove(node->right, value);
        } else {
            if (!node->left || !node->right) {
                Node* temp = node->left ? node->left : node->right;
                delete node;
                return temp;
            } else {
                Node* temp = getMinValueNode(node->right);
                node->data = temp->data;
                node->right = remove(node->right, temp->data);
            }
        }

        node->height = 1 + max(getHeight(node->left), getHeight(node->right));

        int balanceFactor = getBalanceFactor(node);

        // Rotaciones para balancear
        if (balanceFactor > 1 && getBalanceFactor(node->left) >= 0) {
            return rotateRight(node);
        }

        if (balanceFactor > 1 && getBalanceFactor(node->left) < 0) {
            node->left = rotateLeft(node->left);
            return rotateRight(node);
        }

        if (balanceFactor < -1 && getBalanceFactor(node->right) <= 0) {
            return rotateLeft(node);
        }

        if (balanceFactor < -1 && getBalanceFactor(node->right) > 0) {
            node->right = rotateRight(node->right);
            return rotateLeft(node);
        }

        return node;
    }

    // Búsqueda de un valor en el árbol
    bool search(Node* node, T value) const {
        if (!node) return false;
        if (value == node->data) return true;
        return value < node->data ? search(node->left, value) : search(node->right, value);
    }

    // Recorrido en orden
    void inorder(Node* node) const {
        if (!node) return;
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

    // Liberar memoria
    void clear(Node* node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

public:
    AVLTree() : root(nullptr) {}

    ~AVLTree() {
        clear(root);
    }

    void insert(T value) {
        root = insert(root, value);
    }

    void remove(T value) {
        root = remove(root, value);
    }

    bool search(T value) const {
        return search(root, value);
    }

    void inorder() const {
        inorder(root);
        cout << endl;
    }
};

int main() {
    AVLTree<int> avl;

    // Insertar elementos
    avl.insert(10);
    avl.insert(20);
    avl.insert(30);
    avl.insert(40);
    avl.insert(50);
    avl.insert(25);

    cout << "Recorrido en orden (AVL balanceado): ";
    avl.inorder();

    // Buscar elementos
    cout << "¿Está el 25? " << (avl.search(25) ? "Sí" : "No") << endl;
    cout << "¿Está el 60? " << (avl.search(60) ? "Sí" : "No") << endl;

    // Eliminar un elemento
    avl.remove(30);
    cout << "Recorrido en orden después de eliminar 30: ";
    avl.inorder();

    return 0;
}
