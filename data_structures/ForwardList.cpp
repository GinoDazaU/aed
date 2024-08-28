#include <iostream>

using namespace std;

template <typename T>
struct Node {
    T data;
    Node* next = nullptr;
};

template <typename T>
class ForwardList {
private:
    Node<T>* head = nullptr;

     // Función para dividir la lista en dos mitades
    void split(Node<T>* source, Node<T>** front, Node<T>** back) {
        Node<T>* fast;
        Node<T>* slow;
        if (!source || !source->next) {
            *front = source;
            *back = nullptr;
        } else {
            slow = source;
            fast = source->next;
            while (fast) {
                fast = fast->next;
                if (fast) {
                    slow = slow->next;
                    fast = fast->next;
                }
            }
            *front = source;
            *back = slow->next;
            slow->next = nullptr;
        }
    }

    // Esto si lo hizo gpt
    // Función para combinar dos listas ordenadas
    Node<T>* merge(Node<T>* left, Node<T>* right) {
        if (!left) return right;
        if (!right) return left;

        if (left->data < right->data) {
            left->next = merge(left->next, right);
            return left;
        } else {
            right->next = merge(left, right->next);
            return right;
        }
    }

    // Función principal para ordenar la lista usando Merge Sort
    void mergeSort(Node<T>** headRef) {
        Node<T>* head = *headRef;
        Node<T>* left;
        Node<T>* right;

        if (!head || !head->next) return;

        split(head, &left, &right);
        mergeSort(&left);
        mergeSort(&right);
        *headRef = merge(left, right);
    }

public:

    ~ForwardList() {
        clear();
    }

    T front() {
        if (head == nullptr) {
            throw runtime_error("List is empty");
        }
        return head->data;
    }

    T back() {
        if (head == nullptr) {
            throw runtime_error("List is empty");
        }
        Node<T>* temp = head;
        T data;
        while (temp != nullptr) {
            data = temp->data;
            temp = temp->next;
        }
        return data;
    }

    void push_front(T data) {
        Node<T>* node = new Node<T>();
        node->data = data;
        node->next = head;
        head = node;
    }

    void push_back(T data) {
        Node<T>* node = new Node<T>();
        node->data = data;
        if (head == nullptr) {
            head = node;
            return;
        }
        Node<T>* temp = head;
        while (temp->next != nullptr) {
            temp = temp->next;
        }
        temp->next = node;
    }

    void print() {
        Node<T>* temp = head;
        while (temp != nullptr) {
            cout << temp->data << " ";
            temp = temp->next;
        }
        cout << endl;
    }

    T pop_front() {
        if (head == nullptr) {
            throw runtime_error("List is empty");
        }
        Node<T>* temp = head;
        T data = temp->data;
        head = head->next;
        delete temp;
        return data;
    }

    T pop_back() {
        if (head == nullptr) {
            throw runtime_error("List is empty");
        }
        if (head->next == nullptr) {
            T data = head->data;
            delete head;
            head = nullptr;
            return data;
        }
        Node<T>* temp = head;
        while (temp->next->next != nullptr) {
            temp = temp->next;
        }
        T data = temp->next->data;
        delete temp->next;
        temp->next = nullptr;
        return data;
    }

    T operator[](int pos) {
        if (pos < 0) {
            throw runtime_error("Negative index");
        }
        if (head == nullptr) {
            throw runtime_error("List is empty");
        }
        Node<T>* temp = head;
        for (int i = 0; i < pos; i++) {
            if (temp->next == nullptr) {
                throw runtime_error("Out of range");
            }
            temp = temp->next;
        }
        return temp->data;
    }

    bool empty() {
        return head == nullptr;
    }

    int size() {
        Node<T>* temp = head;
        int count = 0;
        while (temp != nullptr) {
            count++;
            temp = temp->next;
        }
        return count;
    }

    void clear() {
        Node<T>* temp = head;
        while (temp != nullptr) {
            Node<T>* next = temp->next;
            delete temp;
            temp = next;
        }
        head = nullptr;
    }

    void reverse(){
        ForwardList<T> forwardList;
        Node<T>* temp = head;
        while(temp != nullptr){
            forwardList.push_front(temp->data);
            temp = temp->next;
        }
        clear();
        head = forwardList.head;
        forwardList.head = nullptr;

    }

    void mergeSort(){
        mergeSort(&head);
    }

};