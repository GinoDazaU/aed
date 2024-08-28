#include <iostream>
#include "../ForwardList.cpp"

using namespace std;

int main() {
    ForwardList<int> list;

    // Probando push_back y push_front
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    list.push_front(5);
    list.push_front(1);

    cout << "Lista despues de push_back y push_front: ";
    list.print(); // Deberia imprimir: 1 5 10 20 30

    // Probando front y back
    cout << "Primer elemento (front): " << list.front() << endl; // Deberia imprimir: 1
    cout << "Ultimo elemento (back): " << list.back() << endl;  // Deberia imprimir: 30

    // Probando pop_front y pop_back
    list.pop_front();
    list.pop_back();
    cout << "Lista despues de pop_front y pop_back: ";
    list.print(); // Deberia imprimir: 5 10 20

    // Probando reverse
    list.reverse();
    cout << "Lista despues de reverse: ";
    list.print(); // Deberia imprimir: 20 10 5

    // Probando el operador []
    cout << "Elemento en la posicion 1: " << list[1] << endl; // Deberia imprimir: 10

    // Probando empty
    cout << "La lista esta vacia?: " << (list.empty() ? "Si" : "No") << endl; // Deberia imprimir: No

    // Probando size
    cout << "Tamano de la lista: " << list.size() << endl; // Deberia imprimir: 3

    // Probando mergeSort
    list.push_back(15);
    list.push_back(25);
    cout << "Lista antes de ordenar: ";
    list.print(); // Deberia imprimir: 20 10 5 15 25

    list.mergeSort();
    cout << "Lista despues de mergeSort: ";
    list.print(); // Deberia imprimir: 5 10 15 20 25

    // Probando clear
    list.clear();
    cout << "La lista esta vacia despues de clear?: " << (list.empty() ? "Si" : "No") << endl; // Deberia imprimir: Si

    return 0;
}
