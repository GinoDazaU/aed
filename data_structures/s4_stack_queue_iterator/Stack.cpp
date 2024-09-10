
#include <iostream>

using namespace std;

template <typename T>
class Stack {
private:
    struct Node {
        T data;
        Node* next;
        Node(T d) : data(d), next(nullptr) {}
    };

    Node* topNode;

public:
    Stack() : topNode(nullptr) {}

    ~Stack() {
        while (!empty()) {
            pop();
        }
    }

    void push(T data) {
        Node* newNode = new Node(data);
        newNode->next = topNode;
        topNode = newNode;
    }

    T pop() {
        if (empty()) {
            throw runtime_error("Stack is empty");
        }
        Node* temp = topNode;
        T data = temp->data;
        topNode = topNode->next;
        delete temp;
        return data;
    }

    T top() const {
        if (empty()) {
            throw runtime_error("Stack is empty");
        }
        return topNode->data;
    }

    bool empty() const {
        return topNode == nullptr;
    }

    int size() const {
        int count = 0;
        Node* current = topNode;
        while (current != nullptr) {
            count++;
            current = current->next;
        }
        return count;
    }
};
