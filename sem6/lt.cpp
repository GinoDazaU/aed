






#include <iostream>
#include <vector>

using namespace std;

int main(){

    vector<int> vector1 = {324, 235, 98, 700, 701, 450, 108, 653, 230, 538, 110, 1038, 222, 144, 145, 94, 515, 105, 106};

    cout << "hola" << endl;


}
































"""

1. Convert Sorted Array to Binary Search Tree
Descripción: Dado un array ordenado en orden ascendente, conviértelo en un árbol binario de búsqueda balanceado.
Solución: Utiliza la técnica de dividir y conquistar (Divide and Conquer). Toma el elemento medio como la raíz y recursivamente construye el subárbol izquierdo y derecho usando las mitades izquierda y derecha del array.

2. Binary Search Tree Iterator
Descripción: Diseña un iterador para un BST que debe iterar sobre los nodos en orden ascendente.
Solución: Realiza un recorrido inorden. Almacena los nodos en una pila y ve devolviendo uno a uno, simulando el recorrido inorden con espacio adicional.

3. Validate Binary Search Tree
Descripción: Determina si un árbol dado es un árbol binario de búsqueda válido.
Solución: Haz una función recursiva que verifique si todos los nodos en el subárbol izquierdo son menores que el nodo actual y si todos los nodos en el subárbol derecho son mayores, utilizando límites mínimo y máximo.

4. Lowest Common Ancestor of a Binary Search Tree
Descripción: Encuentra el ancestro común más bajo (Lowest Common Ancestor) de dos nodos en un BST.
Solución: Si ambos nodos son menores que el nodo actual, ve hacia la izquierda; si ambos son mayores, ve hacia la derecha. Si están en lados opuestos, has encontrado el ancestro común más bajo.

5. Kth Smallest Element in a BST
Descripción: Encuentra el k-ésimo elemento más pequeño en un BST.
Solución: Realiza un recorrido inorden y cuenta los nodos visitados hasta llegar al k-ésimo nodo.

6. Delete Node in a BST
Descripción: Dado un valor, elimina el nodo con ese valor de un BST.
Solución: Primero, encuentra el nodo a eliminar. Si tiene dos hijos, reemplázalo con su sucesor en inorden. Luego, elimina el sucesor recursivamente.

7. Insert into a Binary Search Tree
Descripción: Dado un valor, inserta un nodo con ese valor en un BST.
Solución: Recursivamente, encuentra la posición adecuada para insertar el nuevo valor respetando las propiedades del BST.

8. Range Sum of BST
Descripción: Dado un rango [L, R], devuelve la suma de todos los valores de los nodos dentro de ese rango.
Solución: Realiza un recorrido DFS y suma los valores que estén dentro del rango dado.

9. Closest Binary Search Tree Value
Descripción: Dado un valor objetivo, encuentra el valor en el BST que esté más cerca al valor dado.
Solución: Realiza una búsqueda binaria en el BST y actualiza el valor más cercano mientras navegas hacia la izquierda o derecha.

10. Binary Tree to BST
Descripción: Convierte un árbol binario cualquiera en un BST, manteniendo la estructura del árbol original.
Solución: Recoge todos los valores en el árbol en una lista, ordena la lista y luego reasigna los valores a los nodos utilizando un recorrido inorden.

11. Recover Binary Search Tree
Descripción: En un BST, dos nodos han sido intercambiados por error. Recupera el BST sin cambiar la estructura.
Solución: Realiza un recorrido inorden para identificar los dos nodos fuera de orden y luego intercambia sus valores.

12. Convert BST to Greater Tree
Descripción: Convierte un BST en un árbol donde cada nodo contiene la suma de los valores de todos los nodos mayores o iguales a él.
Solución: Realiza un recorrido inverso (derecha -> nodo -> izquierda) mientras acumulas las sumas.

13. Trim a Binary Search Tree
Descripción: Recorta un BST para que solo contenga nodos con valores dentro de un rango dado.
Solución: Recursivamente, ajusta el subárbol izquierdo o derecho dependiendo del valor del nodo actual con respecto al rango.

14. Inorder Successor in BST
Descripción: Encuentra el sucesor inorden de un nodo en un BST.
Solución: Si el nodo tiene subárbol derecho, encuentra el mínimo en el subárbol derecho. Si no, rastrea hacia arriba hasta encontrar un nodo que sea el hijo izquierdo de su padre.

15. Inorder Predecessor in BST
Descripción: Encuentra el predecesor inorden de un nodo en un BST.
Solución: Si el nodo tiene subárbol izquierdo, encuentra el máximo en el subárbol izquierdo. Si no, rastrea hacia arriba hasta encontrar un nodo que sea el hijo derecho de su padre.

16. Increasing Order Search Tree
Descripción: Dado un BST, reorganízalo en un árbol que siga el orden creciente de los nodos, de modo que todos los nodos tengan solo un hijo derecho.
Solución: Realiza un recorrido inorden y reconstruye el árbol con solo nodos a la derecha.

17. All Elements in Two Binary Search Trees
Descripción: Dado dos BST, devuelve todos los elementos en orden ascendente.
Solución: Realiza un recorrido inorden en ambos árboles y luego fusiona las dos listas ordenadas.

18. Find Mode in Binary Search Tree
Descripción: Encuentra el valor (o valores) que aparecen más frecuentemente en el BST.
Solución: Utiliza un recorrido inorden para contar las frecuencias de los valores y luego encuentra el valor más frecuente.

19. Largest BST Subtree
Descripción: Dado un árbol binario, encuentra el tamaño del subárbol más grande que también sea un BST.
Solución: Utiliza una función recursiva que verifica para cada nodo si su subárbol es un BST y calcula su tamaño.

20. Construct Binary Search Tree from Preorder Traversal
Descripción: Dado un recorrido en preorden de un BST, construye el árbol original.
Solución: Usa el primer valor como la raíz, y luego divide los valores restantes en subárboles izquierdo y derecho según el valor de la raíz. Inserta los nodos en el BST recursivamente.
"""