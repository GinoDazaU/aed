
/*Vimos una introduccion a notacion  asintotica:
    - BigO -BigOmega -Theta 
*/

#include <iostream>

using namespace std;

void time2(int& c){
    c = c * c;
}

int main(){

    int x = 5;

    int array[5] = {1, 2, 3, 4, 5};
    int* dynamic_array = new int(5);

    time2(x);
    cout << x << endl;

    for (int i = 0; i < 5; i++){
        cout << array[i] << ' ';
    }

    cout << endl << dynamic_array;


    return 0;
}