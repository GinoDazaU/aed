// Gino Daza, Milton Cordova, Nicolas Stigler


#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Node {
public:
    vector<int> keys;         // Claves en el nodo
    vector<Node*> children;   // Punteros a hijos
    bool isLeaf;
    Node* next;

    Node(bool leaf) : isLeaf(leaf), next(nullptr) {}
};

class BPlusTree {
private:
    Node* root;
    int degree; // Grado del arbol

public:
    BPlusTree(int degree) : degree(degree), root(nullptr) {}

    // Función de búsqueda
    Node* search(int key) {
        return searchRecursive(root, key);
    }

    // Función de inserción
    void insert(int key) {
        if (root == nullptr) {
            root = new Node(true);
            root->keys.push_back(key);
        } else {
            if (root->keys.size() == 2 * degree - 1) {
                Node* newRoot = new Node(false);
                newRoot->children.push_back(root);
                splitChild(newRoot, 0, root);
                root = newRoot;
            }
            insertNonFull(root, key);
        }
    }

    // Función de eliminación
    void remove(int key) {
        if (root == nullptr) {
            return;
        }
        removeRecursive(root, key);
        if (root->keys.empty()) {
            Node* oldRoot = root;
            if (!root->isLeaf) {
                root = root->children[0];
            } else {
                root = nullptr;
            }
            delete oldRoot;
        }
    }

private:
    // Búsqueda recursiva
    Node* searchRecursive(Node* node, int key) {
        if (node == nullptr) return nullptr;

        int i = 0;
        while (i < node->keys.size() && key > node->keys[i]) {
            i++;
        }

        if (i < node->keys.size() && key == node->keys[i]) {
            if (node->isLeaf) {
                return node; // Clave encontrada en hoja
            } else {
                return searchRecursive(node->children[i + 1], key); // Clave en nodo interno
            }
        }

        if (node->isLeaf) {
            return nullptr; // No encontrada
        } else {
            return searchRecursive(node->children[i], key); // Buscar en subárbol
        }
    }

    // División de un hijo cuando está lleno
    void splitChild(Node* parent, int index, Node* child) {
        Node* newChild = new Node(child->isLeaf);
        int t = degree;
        newChild->keys.assign(child->keys.begin() + t, child->keys.end());
        child->keys.resize(t - 1);

        if (!child->isLeaf) {
            newChild->children.assign(child->children.begin() + t, child->children.end());
            child->children.resize(t);
        } else {
            newChild->next = child->next;
            child->next = newChild;
        }

        parent->children.insert(parent->children.begin() + index + 1, newChild);
        parent->keys.insert(parent->keys.begin() + index, newChild->keys[0]);
    }

    // Inserción en un nodo no lleno
    void insertNonFull(Node* node, int key) {
        int i = node->keys.size() - 1;

        if (node->isLeaf) {
            while (i >= 0 && key < node->keys[i]) {
                i--;
            }
            node->keys.insert(node->keys.begin() + i + 1, key);
        } else {
            while (i >= 0 && key < node->keys[i]) {
                i--;
            }
            i++;

            if (node->children[i]->keys.size() == 2 * degree - 1) {
                splitChild(node, i, node->children[i]);
                if (key > node->keys[i]) {
                    i++;
                }
            }
            insertNonFull(node->children[i], key);
        }
    }

    // Eliminación recursiva
    void removeRecursive(Node* node, int key) {
        int idx = findKey(node, key);

        if (idx < node->keys.size() && node->keys[idx] == key) {
            if (node->isLeaf) {
                node->keys.erase(node->keys.begin() + idx);
            } else {
                removeFromNonLeaf(node, idx);
            }
        } else {
            if (node->isLeaf) {
                // La clave no está en el árbol
                return;
            }

            bool flag = ((idx == node->keys.size()) ? true : false);

            if (node->children[idx]->keys.size() < degree) {
                fill(node, idx);
            }

            if (flag && idx > node->keys.size()) {
                removeRecursive(node->children[idx - 1], key);
            } else {
                removeRecursive(node->children[idx], key);
            }
        }
    }

    // Encuentra el índice de la clave
    int findKey(Node* node, int key) {
        int idx = 0;
        while (idx < node->keys.size() && node->keys[idx] < key) {
            ++idx;
        }
        return idx;
    }

    // Elimina de un nodo no hoja
    void removeFromNonLeaf(Node* node, int idx) {
        int key = node->keys[idx];

        if (node->children[idx]->keys.size() >= degree) {
            int pred = getPredecessor(node, idx);
            node->keys[idx] = pred;
            removeRecursive(node->children[idx], pred);
        } else if (node->children[idx + 1]->keys.size() >= degree) {
            int succ = getSuccessor(node, idx);
            node->keys[idx] = succ;
            removeRecursive(node->children[idx + 1], succ);
        } else {
            merge(node, idx);
            removeRecursive(node->children[idx], key);
        }
    }

    // Obtener el predecesor
    int getPredecessor(Node* node, int idx) {
        Node* cur = node->children[idx];
        while (!cur->isLeaf) {
            cur = cur->children[cur->keys.size()];
        }
        return cur->keys.back();
    }

    // Obtener el sucesor
    int getSuccessor(Node* node, int idx) {
        Node* cur = node->children[idx + 1];
        while (!cur->isLeaf) {
            cur = cur->children[0];
        }
        return cur->keys[0];
    }

    // Llena el hijo que tiene menos claves de las mínimas permitidas
    void fill(Node* node, int idx) {
        if (idx != 0 && node->children[idx - 1]->keys.size() >= degree) {
            borrowFromPrev(node, idx);
        } else if (idx != node->keys.size() && node->children[idx + 1]->keys.size() >= degree) {
            borrowFromNext(node, idx);
        } else {
            if (idx != node->keys.size()) {
                merge(node, idx);
            } else {
                merge(node, idx - 1);
            }
        }
    }

    // Toma prestada una clave del hijo anterior
    void borrowFromPrev(Node* node, int idx) {
        Node* child = node->children[idx];
        Node* sibling = node->children[idx - 1];

        child->keys.insert(child->keys.begin(), node->keys[idx - 1]);

        if (!child->isLeaf) {
            child->children.insert(child->children.begin(), sibling->children.back());
            sibling->children.pop_back();
        }

        node->keys[idx - 1] = sibling->keys.back();
        sibling->keys.pop_back();
    }

    // Toma prestada una clave del siguiente hijo
    void borrowFromNext(Node* node, int idx) {
        Node* child = node->children[idx];
        Node* sibling = node->children[idx + 1];

        child->keys.push_back(node->keys[idx]);

        if (!child->isLeaf) {
            child->children.push_back(sibling->children[0]);
            sibling->children.erase(sibling->children.begin());
        }

        node->keys[idx] = sibling->keys[0];
        sibling->keys.erase(sibling->keys.begin());
    }

    // Fusiona dos hijos
    void merge(Node* node, int idx) {
        Node* child = node->children[idx];
        Node* sibling = node->children[idx + 1];

        if (!child->isLeaf) {
            child->keys.push_back(node->keys[idx]);
            child->keys.insert(child->keys.end(), sibling->keys.begin(), sibling->keys.end());
            child->children.insert(child->children.end(), sibling->children.begin(), sibling->children.end());
        } else {
            child->keys.insert(child->keys.end(), sibling->keys.begin(), sibling->keys.end());
            child->next = sibling->next;
        }

        node->keys.erase(node->keys.begin() + idx);
        node->children.erase(node->children.begin() + idx + 1);

        delete sibling;
    }
};

int main() {
    BPlusTree arbol(3);

    // Inserción de claves en el árbol B+
    arbol.insert(10);
    arbol.insert(20);
    arbol.insert(5);
    arbol.insert(6);
    arbol.insert(12);
    arbol.insert(30);
    arbol.insert(7);
    arbol.insert(17);

    // Búsqueda de una clave en el árbol B+
    int claveBuscar = 20;
    Node* resultado = arbol.search(claveBuscar);
    if (resultado) {
        cout << "Clave " << claveBuscar << " encontrada en el arbol." << endl;
    } else {
        cout << "Clave " << claveBuscar << " no encontrada en el arbol." << endl;
    }

    // Búsqueda de una clave en el árbol B+
    claveBuscar = 5;
    resultado = arbol.search(claveBuscar);
    if (resultado) {
        cout << "Clave " << claveBuscar << " encontrada en el arbol." << endl;
    } else {
        cout << "Clave " << claveBuscar << " no encontrada en el arbol." << endl;
    }

    // Búsqueda de una clave en el árbol B+
    claveBuscar = 6;
    resultado = arbol.search(claveBuscar);
    if (resultado) {
        cout << "Clave " << claveBuscar << " encontrada en el arbol." << endl;
    } else {
        cout << "Clave " << claveBuscar << " no encontrada en el arbol." << endl;
    }

    // Búsqueda de una clave en el árbol B+
    claveBuscar = 30;
    resultado = arbol.search(claveBuscar);
    if (resultado) {
        cout << "Clave " << claveBuscar << " encontrada en el arbol." << endl;
    } else {
        cout << "Clave " << claveBuscar << " no encontrada en el arbol." << endl;
    }

    // Búsqueda de una clave que no esta en el arbol B+
    claveBuscar = 123;
    resultado = arbol.search(claveBuscar);
    if (resultado) {
        cout << "Clave " << claveBuscar << " encontrada en el arbol." << endl;
    } else {
        cout << "Clave " << claveBuscar << " no encontrada en el arbol." << endl;
    }

    // Eliminación de una clave
    claveBuscar = 6;
    arbol.remove(6);
    resultado = arbol.search(claveBuscar);
    if (resultado) {
        cout << "Clave " << claveBuscar << " aun se encuentra en el arbol despues de eliminarla." << endl; // no deberia pasar
    } else {    // si ya no esta despues de eliminarla
        cout << "Clave " << claveBuscar << " eliminada correctamente del arbol." << endl;
    }

    return 0;
}
