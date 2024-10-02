
#include <iostream>
#include "TreeNode.cpp"

using namespace std;

int main() {
    TreeNode root;

    // Insertar elementos
    root = *root.insert(10);
    root = *root.insert(20);
    root = *root.insert(5);
    root = *root.insert(4);
    root = *root.insert(6);
    root = *root.insert(15);
    root = *root.insert(30);

    cout << "Inorder traversal of the AVL tree: ";
    root.inorder();
    cout << endl;

    // Eliminar un elemento
    root = *root.remove(20);

    cout << "Inorder traversal after removing 20: ";
    root.inorder();
    cout << endl;

    return 0;
}