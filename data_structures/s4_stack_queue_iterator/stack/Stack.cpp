
#include <iostream>

using namespace std;

template<typename T>
class Stack{
private:
    int top_index = -1;
    T elements[100];
public:
 
    Stack(){}

    void push(T element){
        if(isfull()){
            cout << "stack is full" << endl;
            return;
        }
        elements[++top_index] = element; 
    }

    T pop(){
        if(isempty()){
            throw runtime_error("Stack is empty");
        }
        T element = elements[top_index--];
        return element;
    }

    T top(){
        if(isempty()){
            throw runtime_error("Stack is empty");
        }
        return elements[top_index];
    }

    bool isempty(){
        return (top_index == -1);
    }
    
    bool isfull(){
        return (top_index == 100 - 1); 
    }

    int size(){
        return top_index + 1;
    }

};
