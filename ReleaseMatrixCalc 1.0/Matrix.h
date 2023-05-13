#include "library.h"

class Matrix
{
private:
    int rows;
    int cols;
    double** data;


public:
    Matrix(int r, int c) {
        rows = r;
        cols = c;
        data = new double* [rows];
        for (int i = 0; i < rows; i++) {
            data[i] = new double[cols];
        }
    }

    ~Matrix() {
        for (int i = 0; i < rows; i++) {
            delete[] data[i];
        }
        delete[] data;
    }

    void set(int r, int c, double value) {
        data[r][c] = value;
    }

    int getRows() { return rows; }
    int getCols() { return cols; }

    double get(int r, int c) {
        return data[r][c];
    }

    void print() {
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << "[" << data[i][j] << "]" << " ";
            }
            cout << endl;
        }
    }
    double** getData() {
        double** data = new double* [this->rows];
        for (int i = 0; i < this->rows; i++) {
            data[i] = new double[this->cols];
            for (int j = 0; j < this->cols; j++) {
                data[i][j] = this->data[i][j];
            }
        }
        return data;
    }


    void inputElements() {
        system("cls");
        cout << "Enter elements of matrix:" << endl;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                float value;
                cin >> value;
                stringstream ss;
                ss << value;
                string str_num = ss.str();

                int len = str_num.length();

                int total_len = (j + 1) * (len + 4);

                cout << "\t\033[" << i + 2 << ";" << total_len + 2 << "f";
                set(i, j, value);
            }
            cout << endl;
        }
        system("cls");
    }

};


