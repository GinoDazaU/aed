#include <iostream>
using namespace std;

template <class T>
class Node {
public:
    T data;
    Node<T>* next;

    // Constructor
    Node(T value) : data(value), next(nullptr) {}
};

template <class T>
class LinkedList {
private:
    Node<T>* head; // Puntero al primer nodo de la lista
    int size;      // Tamaño de la lista

public:
    // Constructor
    LinkedList() : head(nullptr), size(0) {}

    // Destructor
    ~LinkedList() {
        Node<T>* current = head;
        while (current) {
            Node<T>* temp = current;
            current = current->next;
            delete temp;
        }
    }

    // Insertar al inicio
    void insertFront(T value) {
        Node<T>* new_node = new Node<T>(value);
        new_node->next = head;
        head = new_node;
        size++;
    }

    // Insertar al final
    void insertBack(T value) {
        Node<T>* new_node = new Node<T>(value);
        if (!head) {
            head = new_node;
        } else {
            Node<T>* current = head;
            while (current->next) {
                current = current->next;
            }
            current->next = new_node;
        }
        size++;
    }

    // Eliminar un valor específico
    void remove(T value) {
        if (!head)
            return;

        // Si el valor está en el primer nodo
        if (head->data == value) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
            size--;
            return;
        }

        // Buscar el nodo a eliminar
        Node<T>* current = head;
        Node<T>* prev = nullptr;

        while (current && current->data != value) {
            prev = current;
            current = current->next;
        }

        // Si se encontró el valor
        if (current) {
            prev->next = current->next;
            delete current;
            size--;
        }
    }

    // Obtener un elemento por índice
    T get(int index) const {
        if (index < 0 || index >= size)
            throw out_of_range("Index out of bounds");

        Node<T>* current = head;
        for (int i = 0; i < index; ++i) {
            current = current->next;
        }
        return current->data;
    }

    // Sobrecarga del operador []
    T operator[](int index) const {
        return get(index);
    }

    // Imprimir la lista
    void print() const {
        Node<T>* current = head;
        while (current) {
            cout << current->data << " -> ";
            current = current->next;
        }
        cout << "nullptr" << endl;
    }

    // Obtener el tamaño de la lista
    int getSize() const {
        return size;
    }

    // Vaciar la lista
    void clear() {
        while (head) {
            Node<T>* temp = head;
            head = head->next;
            delete temp;
        }
        size = 0;
    }
};

int main() {
    LinkedList<int> list;

    // Insertar elementos
    list.insertFront(10);
    list.insertFront(20);
    list.insertBack(30);
    list.insertBack(40);

    // Imprimir la lista
    cout << "Lista inicial: ";
    list.print();

    // Obtener elementos por índice
    cout << "Elemento en índice 0: " << list[0] << endl;
    cout << "Elemento en índice 2: " << list[2] << endl;

    // Eliminar un elemento
    list.remove(20);
    cout << "Lista después de eliminar 20: ";
    list.print();

    // Tamaño de la lista
    cout << "Tamaño de la lista: " << list.getSize() << endl;

    // Vaciar la lista
    list.clear();
    cout << "Lista después de vaciarla: ";
    list.print();

    return 0;
}
