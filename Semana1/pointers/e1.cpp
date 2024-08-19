
#include <iostream>
#include <string>

using namespace std;

int getPositiveNumber(const string& prompt){
    string input;
    int number;

    do{
        if(number == -1){cout << "Enter a valid number" << endl;}
        cout << prompt;
        cin >> input;
        try{
            number = stoi(input);
            } catch(...){
                number = -1;
            }
    } while(number <= 0);

    return number;
}

int main(){

    int* size = new int(getPositiveNumber("Enter the size of the array: "));

    cout << *size;

    return 0;
}