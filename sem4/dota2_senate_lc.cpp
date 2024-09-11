
// Gp implementation

#include <iostream>
#include <queue>
#include <string>

using namespace std;

/*
 En este problema, debemos simular el proceso de votación en el Senado de Dota2.
 Los senadores se representan por las letras 'R' (Radiant) y 'D' (Dire).
 Cada senador tiene la opción de "banear" a otro senador, lo que le quita el derecho de voto en rondas futuras.
 El juego continúa en rondas hasta que todos los senadores con derecho a votar pertenezcan a un solo partido.
 
 La idea de la solución es usar dos colas, una para almacenar los senadores de Radiant y otra para los de Dire.
 Usamos las posiciones de los senadores en el string de entrada para determinar quién vota primero en cada ronda.
 Cuando un senador vota, banea al próximo senador del partido opuesto en la próxima ronda. 
 El senador que vota se mueve al final de su cola para representar que puede votar en la siguiente ronda.
*/

string predictPartyVictory(string senate) {
    queue<int> radiant, dire;  // Usamos dos colas, una para los senadores de Radiant y otra para los de Dire
    
    // Recorremos el string para identificar las posiciones de los senadores de cada partido
    for (int i = 0; i < senate.size(); ++i) {
        if (senate[i] == 'R') radiant.push(i);  // Si es un senador de Radiant, lo añadimos a la cola radiant
        else dire.push(i);                      // Si es un senador de Dire, lo añadimos a la cola dire
    }
    
    // Continuamos el proceso hasta que uno de los partidos ya no tenga senadores
    while (!radiant.empty() && !dire.empty()) {
        // Tomamos el primer senador de cada cola (el primero en votar en esta ronda)
        int r_index = radiant.front();
        int d_index = dire.front();
        radiant.pop();  // Eliminamos al senador que va a votar de su cola
        dire.pop();
        
        // El senador que vota primero (el de menor índice) banea al otro
        // Si el senador de Radiant tiene un índice menor, banea al de Dire y sigue votando en la siguiente ronda
        if (r_index < d_index) {
            radiant.push(r_index + senate.size());  // Movemos al senador de Radiant al final para que vote de nuevo en la siguiente ronda
        } 
        // Si el senador de Dire tiene un índice menor, banea al de Radiant
        else {
            dire.push(d_index + senate.size());  // Movemos al senador de Dire al final para la siguiente ronda
        }
    }
    
    // Si quedan senadores de Radiant, significa que ganaron, y viceversa
    return radiant.empty() ? "Dire" : "Radiant";
}

int main() {
    string senate1 = "RD";
    string senate2 = "RDD";

    cout << "Resultado para RD: " << predictPartyVictory(senate1) << endl;  // Debe imprimir "Radiant"
    cout << "Resultado para RDD: " << predictPartyVictory(senate2) << endl;  // Debe imprimir "Dire"

    return 0;
}
