#include <iostream>
#include <algorithm>

using namespace std;

class TreeNode {
private:
    int* data = nullptr;
    TreeNode* left = nullptr;
    TreeNode* right = nullptr;

public:
    TreeNode() {}

    // Obtener la altura del nodo
    int getHeight() {
        if (left == nullptr && right == nullptr) {
            return 0;
        }

        int leftHeight = 0, rightHeight = 0;

        if (left != nullptr) {
            leftHeight = left->getHeight() + 1;
        }
        if (right != nullptr) {
            rightHeight = right->getHeight() + 1;
        }

        return std::max(leftHeight, rightHeight);
    }

    // Obtener el factor de balanceo del nodo
    int getBalanceFactor() {
        int leftHeight = (left != nullptr) ? left->getHeight() + 1 : 0;
        int rightHeight = (right != nullptr) ? right->getHeight() + 1 : 0;
        return leftHeight - rightHeight;
    }

    // Rotación simple a la derecha
    TreeNode* rotateRight() {
        TreeNode* newRoot = left;
        left = newRoot->right;
        newRoot->right = this;
        return newRoot;
    }

    // Rotación simple a la izquierda
    TreeNode* rotateLeft() {
        TreeNode* newRoot = right;
        right = newRoot->left;
        newRoot->left = this;
        return newRoot;
    }

    // Inserción AVL
    TreeNode* insert(int n) {
        // Inserción normal como en un BST
        if (data == nullptr) {
            data = new int(n);
        } else {
            if (n < *data) {
                if (left == nullptr) {
                    left = new TreeNode();
                }
                left = left->insert(n);
            } else if (n > *data) {
                if (right == nullptr) {
                    right = new TreeNode();
                }
                right = right->insert(n);
            } else {
                // Si el valor ya existe, no se hace nada
                return this;
            }
        }

        // Balancear el árbol
        return balance();
    }

    // Balancear el nodo después de la inserción o eliminación
    TreeNode* balance() {
        int balanceFactor = getBalanceFactor();

        // Caso LL (Izquierda-Izquierda): Rotación simple a la derecha
        if (balanceFactor > 1 && left->getBalanceFactor() >= 0) {
            return rotateRight();
        }

        // Caso RR (Derecha-Derecha): Rotación simple a la izquierda
        if (balanceFactor < -1 && right->getBalanceFactor() <= 0) {
            return rotateLeft();
        }

        // Caso LR (Izquierda-Derecha): Rotación doble a la izquierda-derecha
        if (balanceFactor > 1 && left->getBalanceFactor() < 0) {
            left = left->rotateLeft();
            return rotateRight();
        }

        // Caso RL (Derecha-Izquierda): Rotación doble a la derecha-izquierda
        if (balanceFactor < -1 && right->getBalanceFactor() > 0) {
            right = right->rotateRight();
            return rotateLeft();
        }

        return this;
    }

    // Obtener el valor mínimo del subárbol derecho
    TreeNode* getMinNode() {
        TreeNode* current = this;
        while (current->left != nullptr) {
            current = current->left;
        }
        return current;
    }

    // Eliminar un nodo en AVL
    TreeNode* remove(int n) {
        if (data == nullptr) return this;

        // Realizar la eliminación normal en un BST
        if (n < *data) {
            if (left != nullptr) left = left->remove(n);
        } else if (n > *data) {
            if (right != nullptr) right = right->remove(n);
        } else {
            // Nodo con un solo hijo o sin hijos
            if (left == nullptr || right == nullptr) {
                TreeNode* temp = (left != nullptr) ? left : right;

                if (temp == nullptr) {
                    // No hay hijos
                    delete data;
                    return nullptr;
                } else {
                    // Un hijo
                    *this = *temp;
                }
            } else {
                // Nodo con dos hijos
                TreeNode* minNode = right->getMinNode();
                *data = *minNode->data;
                right = right->remove(*minNode->data);
            }
        }

        // Balancear el árbol después de la eliminación
        return balance();
    }

    // Obtener el dato del nodo
    int getData() {
        return data != nullptr ? *data : -1;
    }

    // Imprimir el árbol en orden
    void inorder() {
        if (left != nullptr) left->inorder();
        if (data != nullptr) cout << *data << " ";
        if (right != nullptr) right->inorder();
    }
};


