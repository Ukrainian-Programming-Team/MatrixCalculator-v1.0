#include "library.h"
#include "Result.h"

class Summa : public Oper, public Matrix
{
private:
	int row, col;
	double** matr1;
	double** matr2;
	double** masOfres;
public:
	Summa(Matrix& mat1, Matrix& mat2) : Matrix(mat1.getRows(), mat1.getCols()) {
		row = mat1.getRows();
		col = mat1.getCols();
		matr1 = mat1.getData();
		matr2 = mat2.getData();
		masOfres = nullptr;
	}

	void getres() override {
		if (masOfres == nullptr) {
			masOfres = new double* [row];
			for (int i = 0; i < row; i++) {
				masOfres[i] = new double[col];
			}
		}
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				masOfres[i][j] = matr1[i][j] + matr2[i][j];
			}
		}
		cout << "Result summ matrix is: " << endl;
		for (int i = 0; i < row; i++) {
			for (int j = 0; j < col; j++) {
				cout << "[" << masOfres[i][j] << "]" << " ";
			}
			cout << endl;
		}
	}
	~Summa() {
		for (int i = 0; i < row; i++) {
			delete[] matr1[i];
			delete[] matr2[i];
			delete[] masOfres[i];
		}
		delete[] matr1;
		delete[] matr2;
		delete[] masOfres;
	}

};

class Multip : public Oper, public Matrix {
	int r1, c2, n;
	double** matr1;
	double** matr2;
	double** resOfMult;
public:
	Multip(Matrix& mat1, Matrix& mat2) : Matrix(mat1.getRows(), mat1.getCols()) {
		matr1 = mat1.getData();
		matr2 = mat2.getData();
		r1 = mat1.getRows(); c2 = mat2.getCols(); n = mat1.getCols();
		resOfMult = nullptr;
	}

	void getres() override {
		if (resOfMult == nullptr) {
			resOfMult = new double* [r1];
			for (int i = 0; i < r1; i++) {
				resOfMult[i] = new double[c2];
			}
		}
		for (int i = 0; i < r1; i++) {
			for (int j = 0; j < c2; j++) {
				resOfMult[i][j] = 0;
				for (int k = 0; k < n; k++) {
					resOfMult[i][j] += matr1[i][k] * matr2[k][j];
				}
			}
		}
		cout << "Result multip matrix A and B is: " << endl;
		for (int i = 0; i < r1; i++) {
			for (int j = 0; j < c2; j++) {
				cout << "[" << resOfMult[i][j] << "]" << " ";
			}
			cout << endl;
		}
	}
	~Multip() {
		for (int i = 0; i < r1; i++) {
			delete[] matr1[i];
			delete[] resOfMult[i];
		}
		delete[] matr1;
		delete[] resOfMult;
		for (int i = 0; i < n; i++)
			delete[] matr2[i];
		delete[] matr2;
	}
};
