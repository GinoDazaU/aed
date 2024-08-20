
/*
- Solicita al usuario el tamaño de un arreglo de enteros y lo crea dinámicamente.
- Llena el arreglo con números enteros consecutivos del 1 al tamaño especificado.
- Muestra el arreglo antes del intercambio.
- Solicita al usuario dos posiciones en el arreglo para intercambiar sus valores.
- Realiza el intercambio de los valores en las posiciones especificadas.
- Muestra el arreglo después del intercambio.
- Verifica que las entradas del usuario sean válidas y dentro del rango permitido.
- Libera la memoria asignada al arreglo dinámico al final del programa.
*/

#include <iostream>
#include <string>

using namespace std;

int getPositiveNumber(const string& prompt, int a, int b){
    string input;
    int number;

    do{
        if(number == -1){cout << "Enter a valid number" << endl; cin.clear();}
        cout << prompt;
        cin >> input;
        try{
            number = stoi(input);
            } catch(...){
                number = -1;
            }
    } while( number <= b || number >= a);

    return number;
}

void swapPosition(int* e1, int* e2){
    int temp = *e2;
    *e2 = *e1;
    *e1 = temp;
}

void printArray(int size, int arr[]){
    for (int i = 0; i < size; i++){
        cout << arr[i] << " ";
    }
}

int main(){

    int size = getPositiveNumber("Enter the size of the array: ", 101, 0);

    int* arr = new int[size];
    
    for (int i = 0; i < size; i++){
        arr[i] = i + 1;
    }

    cout << "Array before swap: ";
    printArray(size, arr);
    cout << endl;


    int e1 = getPositiveNumber("Enter the first position to swap: ", size, -1);
    int e2 = getPositiveNumber("Enter the second position to swap: ", size, -1);
    
    swapPosition((arr + e1), (arr + e2));

    cout << "Array after swap: ";
    printArray(size, arr);

    delete[] arr;

    return 0;
}