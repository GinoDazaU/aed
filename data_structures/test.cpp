
#include <iostream>
#include "ForwardList.cpp"

using namespace std;

int main(){
    srand(time(NULL));

    cout << "Hola" << endl;

    ForwardList<int> forwardList1;
    for (int i = 0; i < 10; i++){
        forwardList1.push_front(rand() % 50 + 1);
    }
    
    forwardList1.print();

    forwardList1.push_front(11);
    forwardList1.push_back(0);

    forwardList1.print();
    cout << forwardList1[0] << endl;

    forwardList1.reverse();
    forwardList1.print();

    forwardList1.mergeSort();
    forwardList1.print();

    return 0;
}