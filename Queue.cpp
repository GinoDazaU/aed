#include <iostream>
using namespace std;

template <class T>
class Node {
public:
    T data;
    Node<T>* next;

    Node(T value) : data(value), next(nullptr) {}
};

template <class T>
class Queue {
private:
    Node<T>* front; // Primer elemento de la cola
    Node<T>* rear;  // Último elemento de la cola
    int size;       // Tamaño actual de la cola

public:
    Queue() : front(nullptr), rear(nullptr), size(0) {}

    ~Queue() {
        while (!isEmpty()) {
            dequeue();
        }
    }

    // Agrega un elemento al final de la cola
    void enqueue(T value) {
        Node<T>* new_node = new Node<T>(value);
        if (isEmpty()) {
            front = rear = new_node;
        } else {
            rear->next = new_node;
            rear = new_node;
        }
        size++;
    }

    // Elimina el elemento al frente de la cola
    void dequeue() {
        if (isEmpty()) {
            throw underflow_error("Queue underflow: No elements to dequeue.");
        }
        Node<T>* temp = front;
        front = front->next;
        if (!front) {
            rear = nullptr;
        }
        delete temp;
        size--;
    }

    // Devuelve el elemento al frente de la cola sin eliminarlo
    T peek() const {
        if (isEmpty()) {
            throw underflow_error("Queue underflow: No elements in queue.");
        }
        return front->data;
    }

    bool isEmpty() const {
        return front == nullptr;
    }

    int getSize() const {
        return size;
    }

    void print() const {
        Node<T>* current = front;
        cout << "Cola (front -> rear): ";
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
};

int main() {
    Queue<int> queue;

    queue.enqueue(10);
    queue.enqueue(20);
    queue.enqueue(30);
    cout << "Contenido de la cola después de encolar elementos:" << endl;
    queue.print();

    cout << "Elemento al frente: " << queue.peek() << endl;

    queue.dequeue();
    cout << "Contenido de la cola después de hacer dequeue:" << endl;
    queue.print();

    queue.enqueue(40);
    queue.enqueue(50);
    cout << "Contenido de la cola después de encolar 40 y 50:" << endl;
    queue.print();

    cout << "Tamaño de la cola: " << queue.getSize() << endl;

    while (!queue.isEmpty()) {
        cout << "Eliminando: " << queue.peek() << endl;
        queue.dequeue();
    }
    cout << "Contenido después de vaciar la cola:" << endl;
    queue.print();

    return 0;
}
