
#include <iostream>

using namespace std;

class MyCircularDeque {
private:
    int elements[2001];
    int top = 1000;
    int rear = 1000;
    int max_size;
    int size;

public:
    MyCircularDeque(int k) {
        max_size = k;
        size = 0;
    }
    
    bool insertFront(int value) {
        if (isFull()) {
            return false; 
        }
        if (isEmpty()) {
            elements[top] = value;
            elements[rear] = value;
            size++;
        }
        else {
            elements[--top] = value;
            size++;
        }
        return true;
    }
    
    bool insertLast(int value) {
        if (isFull()) {
            return false; 
        }
        if (isEmpty()) {
            elements[top] = value;
            elements[rear] = value;
            size++;
        }
        else {
            elements[++rear] = value;
            size++;
        } 
    }
    
    bool deleteFront() {
        if (isEmpty()) {
            return false;
        }
        else {
            top++;
            size--;
        }   
        if (isEmpty()){
            top = 1500;
            rear = 1500;
        }
        return true;
    }
    
    bool deleteLast() {
        if (isEmpty()) {
            return false;
        }
        else {
            rear--;
            size--;
        } 
        if (isEmpty()) {
            top = 1500;
            rear = 1500;
        }
        return true;
    }
    
    int getFront() {
        return elements[top];
    }
    
    int getRear() {
        return elements[rear];
    }
    
    bool isEmpty() {
        return (size == 0);
    }
    
    bool isFull() {
        return !(size < max_size);
    }
};
