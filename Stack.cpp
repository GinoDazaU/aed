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
class Stack {
private:
    Node<T>* top;
    int size;

public:
    // Constructor
    Stack() : top(nullptr), size(0) {}

    // Destructor
    ~Stack() {
        while (!isEmpty()) {
            pop();
        }
    }

    // Insertar elemento en la pila
    void push(T value) {
        Node<T>* new_node = new Node<T>(value);
        new_node->next = top;
        top = new_node;
        size++;
    }

    // Eliminar el elemento superior de la pila
    void pop() {
        if (isEmpty()) {
            throw underflow_error("Stack underflow: No elements to pop.");
        }
        Node<T>* temp = top;
        top = top->next;
        delete temp;
        size--;
    }

    // Obtener el elemento superior de la pila sin eliminarlo
    T peek() const {
        if (isEmpty()) {
            throw underflow_error("Stack underflow: No elements in stack.");
        }
        return top->data;
    }

    // Verificar si la pila está vacía
    bool isEmpty() const {
        return top == nullptr;
    }

    // Obtener el tamaño de la pila
    int getSize() const {
        return size;
    }

    // Imprimir el contenido de la pila
    void print() const {
        Node<T>* current = top;
        cout << "Pila: ";
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }
};

int main() {
    // Crear una pila de enteros
    Stack<int> stack;

    // Insertar elementos
    stack.push(10);
    stack.push(20);
    stack.push(30);
    cout << "Contenido después de agregar elementos:" << endl;
    stack.print();

    // Obtener el elemento superior
    cout << "Elemento en la cima: " << stack.peek() << endl;

    // Eliminar un elemento
    stack.pop();
    cout << "Contenido después de hacer pop:" << endl;
    stack.print();

    // Verificar el tamaño
    cout << "Tamaño de la pila: " << stack.getSize() << endl;

    // Verificar si está vacía
    if (stack.isEmpty()) {
        cout << "La pila está vacía." << endl;
    } else {
        cout << "La pila no está vacía." << endl;
    }

    // Vaciar la pila completamente
    while (!stack.isEmpty()) {
        stack.pop();
    }
    cout << "Contenido después de vaciar la pila:" << endl;
    stack.print();

    return 0;
}
