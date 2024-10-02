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
#include <vector>

using namespace std;

int main(){

    vector<int> vector1 = {324, 235, 98, 700, 701, 450, 108, 653, 230, 538, 110, 1038, 222, 144, 145, 94, 515, 105, 106};

    cout << "hola" << endl;


}
































"""

1. Convert Sorted Array to Binary Search Tree
Descripción: Dado un array ordenado en orden ascendente, conviértelo en un árbol binario de búsqueda balanceado.
Solución: Utiliza la técnica de dividir y conquistar (Divide and Conquer). Toma el elemento medio como la raíz y recursivamente construye el subárbol izquierdo y derecho usando las mitades izquierda y derecha del array.

2. Binary Search Tree Iterator
Descripción: Diseña un iterador para un BST que debe iterar sobre los nodos en orden ascendente.
Solución: Realiza un recorrido inorden. Almacena los nodos en una pila y ve devolviendo uno a uno, simulando el recorrido inorden con espacio adicional.

3. Validate Binary Search Tree
Descripción: Determina si un árbol dado es un árbol binario de búsqueda válido.
Solución: Haz una función recursiva que verifique si todos los nodos en el subárbol izquierdo son menores que el nodo actual y si todos los nodos en el subárbol derecho son mayores, utilizando límites mínimo y máximo.

4. Lowest Common Ancestor of a Binary Search Tree
Descripción: Encuentra el ancestro común más bajo (Lowest Common Ancestor) de dos nodos en un BST.
Solución: Si ambos nodos son menores que el nodo actual, ve hacia la izquierda; si ambos son mayores, ve hacia la derecha. Si están en lados opuestos, has encontrado el ancestro común más bajo.

5. Kth Smallest Element in a BST
Descripción: Encuentra el k-ésimo elemento más pequeño en un BST.
Solución: Realiza un recorrido inorden y cuenta los nodos visitados hasta llegar al k-ésimo nodo.

6. Delete Node in a BST
Descripción: Dado un valor, elimina el nodo con ese valor de un BST.
Solución: Primero, encuentra el nodo a eliminar. Si tiene dos hijos, reemplázalo con su sucesor en inorden. Luego, elimina el sucesor recursivamente.

7. Insert into a Binary Search Tree
Descripción: Dado un valor, inserta un nodo con ese valor en un BST.
Solución: Recursivamente, encuentra la posición adecuada para insertar el nuevo valor respetando las propiedades del BST.

8. Range Sum of BST
Descripción: Dado un rango [L, R], devuelve la suma de todos los valores de los nodos dentro de ese rango.
Solución: Realiza un recorrido DFS y suma los valores que estén dentro del rango dado.

9. Closest Binary Search Tree Value
Descripción: Dado un valor objetivo, encuentra el valor en el BST que esté más cerca al valor dado.
Solución: Realiza una búsqueda binaria en el BST y actualiza el valor más cercano mientras navegas hacia la izquierda o derecha.

10. Binary Tree to BST
Descripción: Convierte un árbol binario cualquiera en un BST, manteniendo la estructura del árbol original.
Solución: Recoge todos los valores en el árbol en una lista, ordena la lista y luego reasigna los valores a los nodos utilizando un recorrido inorden.

11. Recover Binary Search Tree
Descripción: En un BST, dos nodos han sido intercambiados por error. Recupera el BST sin cambiar la estructura.
Solución: Realiza un recorrido inorden para identificar los dos nodos fuera de orden y luego intercambia sus valores.

12. Convert BST to Greater Tree
Descripción: Convierte un BST en un árbol donde cada nodo contiene la suma de los valores de todos los nodos mayores o iguales a él.
Solución: Realiza un recorrido inverso (derecha -> nodo -> izquierda) mientras acumulas las sumas.

13. Trim a Binary Search Tree
Descripción: Recorta un BST para que solo contenga nodos con valores dentro de un rango dado.
Solución: Recursivamente, ajusta el subárbol izquierdo o derecho dependiendo del valor del nodo actual con respecto al rango.

14. Inorder Successor in BST
Descripción: Encuentra el sucesor inorden de un nodo en un BST.
Solución: Si el nodo tiene subárbol derecho, encuentra el mínimo en el subárbol derecho. Si no, rastrea hacia arriba hasta encontrar un nodo que sea el hijo izquierdo de su padre.

15. Inorder Predecessor in BST
Descripción: Encuentra el predecesor inorden de un nodo en un BST.
Solución: Si el nodo tiene subárbol izquierdo, encuentra el máximo en el subárbol izquierdo. Si no, rastrea hacia arriba hasta encontrar un nodo que sea el hijo derecho de su padre.

16. Increasing Order Search Tree
Descripción: Dado un BST, reorganízalo en un árbol que siga el orden creciente de los nodos, de modo que todos los nodos tengan solo un hijo derecho.
Solución: Realiza un recorrido inorden y reconstruye el árbol con solo nodos a la derecha.

17. All Elements in Two Binary Search Trees
Descripción: Dado dos BST, devuelve todos los elementos en orden ascendente.
Solución: Realiza un recorrido inorden en ambos árboles y luego fusiona las dos listas ordenadas.

18. Find Mode in Binary Search Tree
Descripción: Encuentra el valor (o valores) que aparecen más frecuentemente en el BST.
Solución: Utiliza un recorrido inorden para contar las frecuencias de los valores y luego encuentra el valor más frecuente.

19. Largest BST Subtree
Descripción: Dado un árbol binario, encuentra el tamaño del subárbol más grande que también sea un BST.
Solución: Utiliza una función recursiva que verifica para cada nodo si su subárbol es un BST y calcula su tamaño.

20. Construct Binary Search Tree from Preorder Traversal
Descripción: Dado un recorrido en preorden de un BST, construye el árbol original.
Solución: Usa el primer valor como la raíz, y luego divide los valores restantes en subárboles izquierdo y derecho según el valor de la raíz. Inserta los nodos en el BST recursivamente.
"""
