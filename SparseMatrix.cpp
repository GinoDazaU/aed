
// Gino Daza, Nicolas Stigler, Milton Cordova

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

    // Suma de matrices
    SparseMatrix<T> operator+(const SparseMatrix<T>& other) const {
        if (n_rows != other.n_rows || n_cols != other.n_cols)
            throw invalid_argument("Matrix dimensions must match");

        SparseMatrix<T> result(n_rows, n_cols);

        for (int i = 0; i < n_rows; ++i) {
            for (int j = 0; j < n_cols; ++j) {
                result.insert(i, j,this->get(i, j) + other.get(i,j));
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
            this->insert(coords_row[i] - 1, coords_column[i] - 1, cords_value[i]);
        }
    }

};


int main() {

    // problema 2

    // Matriz 1

    int n1 = 9;
    int m1 = 7;

    vector<int> row1 = {2, 5, 5, 7, 8, 8, 9};
    vector<int> column1 = {3, 1, 4, 4, 1, 6, 3};
    vector<int> value1 = {3, 3, 1, 5, 1, 4, 2};

    SparseMatrix<int> mat1(n1, m1);

    mat1.coords_to_list(row1,column1, value1);

    mat1.display();

    // Matriz 2

    int n2 = 9;
    int m2 = 7;

    vector<int> row2 = {2, 5, 5, 7, 8, 8, 9};
    vector<int> column2 = {3, 1, 4, 4, 1, 6, 3};
    vector<int> value2 = {4, 2, 1, 4, 3, 2, 1};

    SparseMatrix<int> mat2(n2, m2);

    mat2.coords_to_list(row2, column2, value2);

    mat2.display();

    // Matriz 1 + Matriz 2

    SparseMatrix<int> mat3(n2, m2);
    mat3 = mat1 + mat2;

    mat3.display();

    return 0;
}
