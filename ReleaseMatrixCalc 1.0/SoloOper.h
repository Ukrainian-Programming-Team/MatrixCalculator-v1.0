#include "library.h"
#include "Result.h"

class Transpon : public Oper, public Matrix {
private:
    double** matrix;
    int rows, cols;
public:

public:
    Transpon(Matrix& mat) : Matrix(mat.getRows(), mat.getCols()) {
        rows = mat.getRows();
        cols = mat.getCols();
        matrix = mat.getData();
    }

    ~Transpon() {
        for (int i = 0; i < rows; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
    }

    void getres() override {
        double** newMatrix = new double* [cols];
        for (int i = 0; i < cols; i++) {
            newMatrix[i] = new double[rows];
        }
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                newMatrix[j][i] = matrix[i][j];
            }
        }
        for (int i = 0; i < rows; i++) {
            delete[] matrix[i];
        }
        delete[] matrix;
        matrix = newMatrix;
        int temp = rows;
        rows = cols;
        cols = temp;
        cout << "Transpon matrix is: " << endl;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                cout << "[" << matrix[i][j] << "]" << " ";
            }
            cout << endl;
        }
    }
};

class Vizna4nik : public Oper, public Matrix
{
private:
    int row, col;
    double result = 0.0;
    double** mas;
    double Second3X3(double mas[3][3]) {
        double res;
        res = mas[0][0] * mas[1][1] * mas[2][2] + mas[0][1] * mas[2][0] * mas[1][2] + mas[1][0] * mas[2][1] * mas[0][2]
            - mas[0][2] * mas[1][1] * mas[2][0] - mas[0][0] * mas[2][1] * mas[1][2] - mas[2][2] * mas[1][0] * mas[0][1];
        return res;
    }

public:
    Vizna4nik(Matrix& mat) : Matrix(mat.getRows(), mat.getCols()) {
        row = mat.getRows(); col = mat.getCols(); this->mas = mat.getData();
    }
    void getres() override {
        if (row == 2 and col == 2) {
            cout << "You matrix determinant - " << DetTwoXTwoMatr(mas) << endl;
        }
        else if (row == 3 and col == 3) {
            cout << "You matrix determinant - " << DetThreeXThreeMatr(mas) << endl;
        }
        else if (row == 4 and col == 4) {
            cout << "You matrix determinant - " << DetFourXFourMatr(mas) << endl;
        }
        else {
            cout << "This version calc not supported big size matrix for operation - Find Determinant" << endl;
            cout << "Enter size matrix from 2x2 to 4x4. Restart Program" << endl;
        };
        cout << result << endl;
    }

    double DetTwoXTwoMatr(double** mas) {
        result = mas[0][0] * mas[1][1] - mas[0][1] * mas[1][0];
        return result;
    }
    double DetThreeXThreeMatr(double** mas) {
        result = mas[0][0] * mas[1][1] * mas[2][2] + mas[0][1] * mas[2][0] * mas[1][2] + mas[1][0] * mas[2][1] * mas[0][2]
            - mas[0][2] * mas[1][1] * mas[2][0] - mas[0][0] * mas[2][1] * mas[1][2] - mas[2][2] * mas[1][0] * mas[0][1];
        return result;
    }
    double DetFourXFourMatr(double** mas) {
        double submatrix[3][3];
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 3; j++) {
                for (int k = 0; k < 3; k++) {
                    submatrix[j][k] = mas[j + 1][(k >= i) ? k + 1 : k];
                }
            }
            int sign = (i % 2 == 0) ? 1 : -1;
            result += sign * mas[0][i] * Second3X3(submatrix);
        }
        return result;
    }

    double GetResult() {
        return result;
    }

    ~Vizna4nik() {
        for (int i = 0; i < row; i++)
            delete[] mas[i];
        delete[] mas;
    }
};

static const double EPS = 1E-9;
class Rang : public Oper, public Matrix
{
    double** mas;
    int row, col;
public:
    Rang(Matrix& mat) : Matrix(mat.getRows(), mat.getCols()) {
        mas = mat.getData(); row = mat.getRows(); col = mat.getCols();
    }
    void getres() override {
        int rank = min(row, col);
        bool* line_used = new bool[row]();

        for (int i = 0; i < col; ++i) {
            int j;
            for (j = 0; j < row; ++j) {
                if (!line_used[j] && abs(mas[j][i]) > EPS) {
                    break;
                }
            }
            if (j == row) {
                --rank;
            }
            else {
                line_used[j] = true;
                for (int p = i + 1; p < col; ++p) {
                    mas[j][p] /= mas[j][i];
                }
                for (int k = 0; k < row; ++k) {
                    if (k != j && abs(mas[k][i]) > EPS) {
                        for (int p = i + 1; p < col; ++p) {
                            mas[k][p] -= mas[j][p] * mas[k][i];
                        }
                    }
                }
            }
        }
        if (rank > 0) {
            cout << "Rank = " << rank << std::endl;
            delete[] line_used;
        }
        else { cout << "Error - Rank < 0" << endl; }
    }

};

class MatrixInverse : public Oper, public Matrix {
private:
    double** matrix;
    double** inverse;
    int rows, cols;
public:
    MatrixInverse(Matrix& mat) : Matrix(mat.getRows(), mat.getCols()) {
        rows = mat.getRows();
        cols = mat.getCols();
        matrix = mat.getData();
        inverse = new double* [rows];
        for (int i = 0; i < rows; i++) {
            inverse[i] = new double[cols];
        }
    }

    void getres() override {
        // Create an identity matrix
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (i == j) {
                    inverse[i][j] = 1;
                }
                else {
                    inverse[i][j] = 0;
                }
            }
        }

        // Perform elementary row operations
        for (int i = 0; i < rows; i++) {
            double factor = matrix[i][i];
            for (int j = 0; j < cols; j++) {
                matrix[i][j] /= factor;
                inverse[i][j] /= factor;
            }
            for (int k = 0; k < rows; k++) {
                if (k != i) {
                    factor = matrix[k][i];
                    for (int j = 0; j < cols; j++) {
                        matrix[k][j] -= factor * matrix[i][j];
                        inverse[k][j] -= factor * inverse[i][j];
                    }
                }
            }
        }
        cout << "Inverse Matrix:" << endl;
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                if (isnan(inverse[i][j]) || isinf(inverse[i][j]))
                    inverse[i][j] = 0;
                cout << inverse[i][j] << " ";
            }
            cout << endl;
        }
    }

    ~MatrixInverse() {
        for (int i = 0; i < rows; i++) {
            delete[] matrix[i];
            delete[] inverse[i];
        }
        delete[] matrix;
        delete[] inverse;
    }
};
