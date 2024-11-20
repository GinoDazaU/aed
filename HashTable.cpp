#include <iostream>
#include <vector>
#include <list>
#include <stdexcept>
using namespace std;

template <class K, class V>
class HashTable {
private:
    vector<list<pair<K, V>>> table; // Tabla hash: vector de listas enlazadas
    int numBuckets;                // Número de buckets
    int size;                      // Número de elementos actuales

    // Función hash
    int hashFunction(const K& key) const {
        return static_cast<int>(key) % numBuckets;
    }

    // Redimensionar la tabla cuando sea necesario
    void resize() {
        int oldBuckets = numBuckets;
        numBuckets *= 2;
        vector<list<pair<K, V>>> newTable(numBuckets);

        // Reinsertar los elementos en la nueva tabla
        for (const auto& bucket : table) {
            for (const auto& pair : bucket) {
                int newIndex = hashFunction(pair.first);
                newTable[newIndex].push_back(pair);
            }
        }

        table = move(newTable);
    }

public:
    HashTable(int buckets = 10) : numBuckets(buckets), size(0) {
        table.resize(numBuckets);
    }

    // Insertar o actualizar un valor
    void insert(const K& key, const V& value) {
        int index = hashFunction(key);

        // Buscar si la clave ya existe
        for (auto& pair : table[index]) {
            if (pair.first == key) {
                pair.second = value; // Actualizar el valor
                return;
            }
        }

        // Insertar nuevo par clave-valor
        table[index].push_back({key, value});
        size++;

        // Redimensionar si la carga supera el límite (factor de carga > 0.75)
        if (size > 0.75 * numBuckets) {
            resize();
        }
    }

    // Eliminar un valor
    void erase(const K& key) {
        int index = hashFunction(key);

        for (auto it = table[index].begin(); it != table[index].end(); ++it) {
            if (it->first == key) {
                table[index].erase(it);
                size--;
                return;
            }
        }

        throw invalid_argument("Key not found");
    }

    // Buscar un valor
    V get(const K& key) const {
        int index = hashFunction(key);

        for (const auto& pair : table[index]) {
            if (pair.first == key) {
                return pair.second;
            }
        }

        throw invalid_argument("Key not found");
    }

    // Sobrecarga del operador [] para acceso o modificación
    V& operator[](const K& key) {
        int index = hashFunction(key);

        // Buscar si la clave ya existe
        for (auto& pair : table[index]) {
            if (pair.first == key) {
                return pair.second;
            }
        }

        // Si la clave no existe, insertar un valor por defecto
        table[index].push_back({key, V()});
        size++;
        return table[index].back().second;
    }

    // Imprimir la tabla hash
    void print() const {
        for (int i = 0; i < numBuckets; ++i) {
            cout << "Bucket " << i << ": ";
            for (const auto& pair : table[i]) {
                cout << "(" << pair.first << ", " << pair.second << ") ";
            }
            cout << endl;
        }
    }

    int getSize() const {
        return size;
    }
};

int main() {
    HashTable<int, int> table;

    // Insertar valores
    table.insert(1, 100);
    table.insert(11, 200);
    table.insert(21, 300);

    // Imprimir la tabla
    cout << "Tabla inicial:" << endl;
    table.print();

    // Modificar un valor usando []
    table[11] = 250;
    cout << "Después de modificar el valor en la clave 11:" << endl;
    table.print();

    // Agregar un nuevo elemento con []
    table[31] = 400;
    cout << "Después de agregar un nuevo elemento con clave 31:" << endl;
    table.print();

    // Eliminar un elemento
    table.erase(21);
    cout << "Después de eliminar la clave 21:" << endl;
    table.print();

    // Buscar un valor
    cout << "Valor asociado a la clave 1: " << table.get(1) << endl;

    // Manejar una clave no encontrada
    try {
        cout << "Valor asociado a la clave 99: " << table.get(99) << endl;
    } catch (const invalid_argument& e) {
        cout << "Error: " << e.what() << endl;
    }

    return 0;
}
