
#include <iostream>

using namespace std;

int main(){

    int rows = 12;
    int columns = 18;
    
    int** matrix = new int*[rows];
    for (int i = 0; i < rows; i++){
        matrix[i] = new int[columns];
    }

    for (int i = 0; i < rows; i++){
        for (int j = 0; j < columns; j++){
            matrix[i][j] = 1;
        }
    }

    for (int i = 0; i < rows; i++){
        for (int j = 0; j < columns; j++){
            cout << matrix[i][j] << " ";
        } cout << endl;
    }


    return 0;
}
