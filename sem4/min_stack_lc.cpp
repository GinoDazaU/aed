
class MinStack {
private:
    int elements[300000];
    int min_stack[300000];
    int top_index = -1;
    int min_top_index = -1;

public:
    MinStack() {}

    void push(int val) {
        elements[++top_index] = val;

        // Si es el primer valor o es menor o igual al mínimo actual, lo añadimos a la pila de mínimos
        if (min_top_index == -1 || val <= min_stack[min_top_index]) {
            min_stack[++min_top_index] = val;
        }
    }

    void pop() {
        if (top_index == -1) return;
        
        // Si el valor a eliminar es igual al mínimo actual, lo eliminamos también de la pila de mínimos
        if (elements[top_index] == min_stack[min_top_index]) {
            --min_top_index;
        }
        
        elements[top_index--] = 0;
        }

    int top() {
        return elements[top_index];
    }

    int getMin() {
        return min_stack[min_top_index];
    }
};

