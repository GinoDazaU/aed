
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
    public:
        T front(){
            if (head == nullptr){
                throw runtime_error("List is empty");
            }
            return head->data;
        }

        T back(){
            if(head == nullptr){
                throw runtime_error("List is empty");
            }
            Node<T>* temp = head;
            T data;
            while(temp != nullptr){
                data = temp->data;
                temp = temp->next;
            } return data;
        }

        void push_front(T data){
            Node<T>* node = new Node<T>();
            node->data = data;
            node->next = head;
            head = node;
        }

        void push_back(T data){
            Node<T>* node = new Node<T>();
            node->data = data;
            if(head == nullptr){
                head = node;
                return;
            }
            Node<T>* temp = head;
            while(temp->next != nullptr){
                temp = temp->next;
            }
            temp->next = node;
        }

        void print(){
            Node<T>* temp = head;
            while(temp != nullptr){
                cout << temp->data << " ";
                temp = temp->next;
            } cout << endl;
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

        T pop_back(){
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
            while(temp->next->next != nullptr){
                temp = temp->next;
            }
            T data = temp->next->data;
            delete temp->next;
            temp->next = nullptr;
            return data;
        }

        T operator[](int pos){
            if (pos < 0) {
                throw runtime_error("Negative index");
            }
            if (head == nullptr) {
                throw runtime_error("List is empty");
            }
            Node<T>* temp = head;
            for (int i = 0; i < pos; i++){
                if(temp->next == nullptr){
                    throw runtime_error("Out of range");
                }
                temp = temp->next;
            } return temp->data;
        }

        bool empty(){
            return head == nullptr;
        }

};