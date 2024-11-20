#include <iostream>
using namespace std;

template <class T>
class BST {
private:
    // Nodo del árbol
    struct Node {
        T data;
        Node* left;
        Node* right;

        Node(T value) : data(value), left(nullptr), right(nullptr) {}
    };

    Node* root; // Raíz del árbol

    // Insertar un valor en el árbol (recursivo)
    Node* insert(Node* node, T value) {
        if (!node) return new Node(value);
        if (value < node->data) {
            node->left = insert(node->left, value);
        } else if (value > node->data) {
            node->right = insert(node->right, value);
        }
        return node;
    }

    // Buscar un valor en el árbol (recursivo)
    bool search(Node* node, T value) const {
        if (!node) return false;
        if (value == node->data) return true;
        if (value < node->data) return search(node->left, value);
        return search(node->right, value);
    }

    // Eliminar un valor del árbol (recursivo)
    Node* remove(Node* node, T value) {
        if (!node) return nullptr;

        if (value < node->data) {
            node->left = remove(node->left, value);
        } else if (value > node->data) {
            node->right = remove(node->right, value);
        } else {
            if (!node->left) {
                Node* temp = node->right;
                delete node;
                return temp;
            } else if (!node->right) {
                Node* temp = node->left;
                delete node;
                return temp;
            }

            Node* temp = findMin(node->right);
            node->data = temp->data;
            node->right = remove(node->right, temp->data);
        }
        return node;
    }

    // Encontrar el nodo con el valor mínimo (subárbol izquierdo más profundo)
    Node* findMin(Node* node) const {
        while (node && node->left) node = node->left;
        return node;
    }

    // Imprimir en orden (recursivo)
    void inorder(Node* node) const {
        if (!node) return;
        inorder(node->left);
        cout << node->data << " ";
        inorder(node->right);
    }

    // Liberar memoria del árbol (recursivo)
    void clear(Node* node) {
        if (!node) return;
        clear(node->left);
        clear(node->right);
        delete node;
    }

public:
    BST() : root(nullptr) {}

    ~BST() {
        clear(root);
    }

    void insert(T value) {
        root = insert(root, value);
    }

    bool search(T value) const {
        return search(root, value);
    }

    void remove(T value) {
        root = remove(root, value);
    }

    void inorder() const {
        inorder(root);
        cout << endl;
    }
};

int main() {
    BST<int> bst;

    // Insertar elementos
    bst.insert(50);
    bst.insert(30);
    bst.insert(70);
    bst.insert(20);
    bst.insert(40);
    bst.insert(60);
    bst.insert(80);

    cout << "In-order traversal (sorted): ";
    bst.inorder();

    // Buscar elementos
    cout << "¿Está el 40? " << (bst.search(40) ? "Sí" : "No") << endl;
    cout << "¿Está el 100? " << (bst.search(100) ? "Sí" : "No") << endl;

    // Eliminar un elemento
    cout << "Eliminando 40..." << endl;
    bst.remove(40);
    cout << "In-order traversal después de eliminar 40: ";
    bst.inorder();

    // Eliminar un nodo raíz
    cout << "Eliminando 50..." << endl;
    bst.remove(50);
    cout << "In-order traversal después de eliminar 50: ";
    bst.inorder();

    return 0;
}
