
#include <iostream>
#include <stdexcept>

template <typename T>
class Queue {
private:
    struct Node {
        Node* next;
        T data;
        Node(T d) : data(d), next(nullptr) {}
    };

    Node* frontNode;
    Node* backNode;
    int length;

public:
    Queue() : frontNode(nullptr), backNode(nullptr), length(0) {}

    void enqueue(T data) {
        Node* newNode = new Node(data);
        if (isempty()) {
            backNode = newNode;
            frontNode = newNode;
        } else {
            backNode->next = newNode;
            backNode = newNode;
        }
        length++;
    }

    void dequeue() {
        if (isempty()) {
            throw std::runtime_error("Queue is empty");
        }
        Node* temp = frontNode;
        frontNode = frontNode->next;
        delete temp;
        length--;

        if (isempty()) {
            backNode = nullptr;
        }
    }

    T front() {
        if (isempty()) {
            throw std::runtime_error("Queue is empty");
        }
        return frontNode->data;
    }

    int size() {
        return length;
    }

    bool isempty() {
        return frontNode == nullptr;
    }
};

