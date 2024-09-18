#include <vector>
#include <set>
#include <string>
#include <iostream>

using namespace std;

int MorseProblem(vector<string> words) {

    vector<string> morse = {".-", "-...", "-.-.", "-..", ".", "..-.", "--.", "....", "..", ".---", 
                                    "-.-", ".-..", "--", "-.", "---", ".--.", "--.-", ".-.", "...", "-", 
                                    "..-", "...-", ".--", "-..-", "-.--", "--.."};

    set<string> palabras_unicas;
    
    for (string word : words) {
        string morse_word;
        for (char c : word) {
            morse_word += morse[c - 'a'];
        }
        palabras_unicas.insert(morse_word);
    }

    for (auto it = palabras_unicas.begin(); it != palabras_unicas.end(); ++it){
        cout << *it << " ";
    }
    
    return palabras_unicas.size();
}

int main(){

    cout << int('a') << endl;

    cout << int('z') - int('a') << endl;

    vector<string> palabras = {"gin","zen","gig","msg"};

    cout << MorseProblem(palabras);
}
