
#include <iostream>

using namespace std;

void print_array(int* array, int size){
    for (int i = 0; i < size; ++i){
        cout << *(array + i) << " ";
    } cout << endl;
}

int* create_array(int size){
    int* array = new int[size];
    for (int i = 0; i < size; ++i){
        array[i] = rand() % size + 1;
    }

    return array;
}

// No tiene nombre, es muy simple

void my_sort(int* array, int size){

    for (int i = 0; i < size; ++i){
        for (int j = 0; j < size; ++j){
            if(array[j] > array[i]){
                int temp = array[j];
                array[j] = array[i];
                array[i] = temp;
                print_array(array, size);
            }
        }
    }
}

int main(){

    srand(time(NULL));

    int* array1 = new int[10];
    for(int i = 0; i < 10; ++i){ array1[i] = i + 1;}
    int* array2 = create_array(15);
    int* array3 = create_array(20);

    print_array(array1, 10);
    print_array(array2, 15);
    print_array(array3, 20);

    my_sort(array1, 10);
    my_sort(array2, 15);
    my_sort(array3, 20);

    cout << endl;
    print_array(array1, 10);
    print_array(array2, 15);
    print_array(array3, 20);

    return 0;
}