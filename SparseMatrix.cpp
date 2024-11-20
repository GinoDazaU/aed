#include <iostream>
#include <vector>

using namespace std;

template <class T>
class Node {
public:
    T data;
    int pos_row, pos_col;
    Node<T>* next_row;
    Node<T>* next_col;

    Node(int r, int c, T value) : pos_row(r), pos_col(c), data(value), next_row(nullptr), next_col(nullptr) {}
};

template <class T>
class SparseMatrix {
private:
    vector<Node<T>*> rows;
    vector<Node<T>*> cols;
    int n_rows, n_cols;

public:
    // Constructor
    SparseMatrix(int rows, int cols) : n_rows(rows), n_cols(cols) {
        this->rows.resize(rows, nullptr);
        this->cols.resize(cols, nullptr);
    }

    // Destructor
    ~SparseMatrix() {
        for (int i = 0; i < n_rows; ++i) {
            Node<T>* current = rows[i];
            while (current) {
                Node<T>* temp = current;
                current = current->next_row;
                delete temp;
            }
        }
    }

    // Insertar un valor en (i, j)
    void insert(int i, int j, T value) {
        if (i >= n_rows || j >= n_cols || i < 0 || j < 0)
            throw out_of_range("Invalid index");

        Node<T>* new_node = new Node<T>(i, j, value);

        // Insertar en fila
        if (!rows[i] || rows[i]->pos_col > j) {
            new_node->next_row = rows[i];
            rows[i] = new_node;
        } else {
            Node<T>* current = rows[i];
            while (current->next_row && current->next_row->pos_col < j)
                current = current->next_row;
            new_node->next_row = current->next_row;
            current->next_row = new_node;
        }

        // Insertar en columna
        if (!cols[j] || cols[j]->pos_row > i) {
            new_node->next_col = cols[j];
            cols[j] = new_node;
        } else {
            Node<T>* current = cols[j];
            while (current->next_col && current->next_col->pos_row < i)
                current = current->next_col;
            new_node->next_col = current->next_col;
            current->next_col = new_node;
        }
    }

    // Buscar un valor en (i, j)
    T get(int i, int j) const {
        if (i >= n_rows || j >= n_cols || i < 0 || j < 0)
            throw out_of_range("Invalid index");

        Node<T>* current = rows[i];
        while (current) {
            if (current->pos_col == j)
                return current->data;
            current = current->next_row;
        }
        return T(); // Retorna valor por defecto si no existe
    }

    // Obtener valor con sobrecarga de operador
    T operator()(int i, int j) const {
        return get(i, j);
    }

    // Transpuesta de la matriz
    SparseMatrix<T> transpose() const {
        SparseMatrix<T> result(n_cols, n_rows);
        for (int i = 0; i < n_rows; ++i) {
            Node<T>* current = rows[i];
            while (current) {
                result.insert(current->pos_col, current->pos_row, current->data);
                current = current->next_row;
            }
        }
        return result;
    }

    void display(){
        for (int i = 0; i < n_rows; ++i) {
            for (int j = 0; j < n_cols; ++j) {
                cout << this->get(i,j) << " ";
            }
            cout << endl;
        }
        cout << endl;
    }

    void coords_to_list(vector<int> coords_row, vector<int> coords_column, vector<T> cords_value){
        int n = coords_row.size();
        for (int i = 0; i < n; ++i) {
            this->insert(coords_row[i], coords_column[i], cords_value[i]);
        }
    }

};

int main() {
    SparseMatrix<int> mat(5, 5);

    // Insertar elementos en la matriz
    mat.insert(0, 0, 5);
    mat.insert(1, 2, 8);
    mat.insert(3, 4, 10);

    // Caso de prueba: Obtener elementos
    cout << "Elemento en (0,0): " << mat(0, 0) << endl;
    cout << "Elemento en (1,2): " << mat(1, 2) << endl;
    cout << "Elemento en (3,4): " << mat(3, 4) << endl;
    cout << "Elemento en (2,2): " << mat(2, 2) << " (esperado 0, ya que no está definido)" << endl;

    // Transponer la matriz
    auto transpuesta = mat.transpose();
    cout << "Transpuesta - Elemento en (0,0): " << transpuesta(0, 0) << endl;
    cout << "Transpuesta - Elemento en (2,1): " << transpuesta(2, 1) << endl;
    cout << "Transpuesta - Elemento en (4,3): " << transpuesta(4, 3) << endl;

    // Matriz vacía
    SparseMatrix<int> empty_mat(5, 5);
    cout << "Elemento en matriz vacía (0,0): " << empty_mat(0, 0) << " (esperado 0)" << endl;

    return 0;
}
