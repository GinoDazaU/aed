
#include <iostream>
#include "BST.cpp"

using namespace std;

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
