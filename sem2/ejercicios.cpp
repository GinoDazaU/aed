
#include <iostream>
#include "ForwardList.cpp"

using namespace std;

void ejercicio1(){
    ForwardList<int> list1;
    list1.push_back(1);
    list1.push_back(0);
    list1.push_back(1);
    list1.push_back(1);
    list1.print();
    cout << list1.convertNodestoBinary() << endl;
}

int main(){
    ejercicio1();
}