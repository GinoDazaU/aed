
#include <iostream>

using namespace std;

template <typename T>
class Queue {
private:
    struct Node {
        T data;
        Node* next;
        Node(T d) : data(d), next(nullptr) {}
    };

    Node* frontNode;
    Node* backNode;
    int length;

public:
    Queue() : frontNode(nullptr), backNode(nullptr), length(0) {}

    ~Queue() {
        while (!empty()) {
            dequeue();
        }
    }

    void enqueue(T data) {
        Node* newNode = new Node(data);
        if (backNode == nullptr) {
            frontNode = backNode = newNode;
        } else {
            backNode->next = newNode;
            backNode = newNode;
        }
        length++;
    }

    T dequeue() {
        if (empty()) {
            throw runtime_error("Queue is empty");
        }
        Node* temp = frontNode;
        T data = temp->data;
        frontNode = frontNode->next;
        if (frontNode == nullptr) {
            backNode = nullptr;
        }
        delete temp;
        length--;
        return data;
    }

    T front() const {
        if (empty()) {
            throw runtime_error("Queue is empty");
        }
        return frontNode->data;
    }

    bool empty() const {
        return frontNode == nullptr;
    }

    int size() const {
        return length;
    }
};
