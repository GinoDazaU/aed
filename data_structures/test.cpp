
#include <iostream>
#include "ForwardList.cpp"

using namespace std;

int main(){

    cout << "Hola" << endl;

    ForwardList<int> forwardList1;
    for (int i = 0; i < 10; i++){
        forwardList1.push_front(i + 1);
    }
    
    forwardList1.print();

    forwardList1.push_front(11);
    forwardList1.push_back(0);

    forwardList1.print();

    return 0;
}