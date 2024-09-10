
#include "Stack.cpp"
#include <iostream>

int main() {
    Stack<int> stack;

    // Probar push
    stack.push(10);
    stack.push(20);
    stack.push(30);
    std::cout << "Top after pushing 10, 20, 30: " << stack.top() << std::endl;  // Deberia imprimir 30

    // Probar pop
    std::cout << "Popped: " << stack.pop() << std::endl;  // Deberia imprimir 30
    std::cout << "Top after pop: " << stack.top() << std::endl;  // Deberia imprimir 20

    // Probar isempty
    if (!stack.isempty()) {
        std::cout << "Stack is not empty." << std::endl;  // Deberia imprimir esto
    }

    // Probar isfull llenando el stack
    for (int i = 0; i < 98; i++) {
        stack.push(i);
    }

    std::cout << "Stack is full: " << (stack.isfull() ? "Yes" : "No") << std::endl;  // Deberia imprimir "Yes"

    // Intentar hacer push cuando el stack esta lleno
    try {
        stack.push(100);
    } catch (const std::exception& e) {
        std::cout << e.what() << std::endl;  // Deberia imprimir "Stack is full"
    }

    // Vaciar el stack usando pop y mostrar los valores
    while (!stack.isempty()) {
        std::cout << "Popped: " << stack.pop() << std::endl;
    }

    // Probar empty después de vaciar el stack
    std::cout << "Stack is empty: " << (stack.isempty() ? "Yes" : "No") << std::endl;  // Deberia imprimir "Yes"

    return 0;
}

