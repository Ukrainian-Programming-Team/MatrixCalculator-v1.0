#include "library.h"
#include "Result.h"

class ChangeOper
{
private:
    int r, c;
    int r2, c2;
    double** temp1;
    double** temp2;
    int choose;
public:

    void HeadChangeSol(int choose_user_op) {
        choose = choose_user_op;
        cout << "Enter size matrix" << endl;
        cout << "Input numbers rows - "; cin >> r;
        cout << "Input numbers cols - "; cin >> c;
        Matrix mat1(r, c);
        mat1.inputElements();
        mat1.print();

        Res R;
        if (choose == 1) {
            Transpon matrixt(mat1);
            R.getres(&matrixt);
        }
        else if (choose == 2) {
            Vizna4nik detm(mat1);
            R.getres(&detm);
        }
        else if (choose == 3) {
            Rang rm(mat1);
            R.getres(&rm);
        }
        else if (choose == 4) {
            MatrixInverse invm(mat1);
            R.getres(&invm);
        }

    }

    void HeadChangeDuo(int choose_user_op) {
        choose = choose_user_op;

        while (true) {
            cout << "Enter size matrix A" << endl;
            cout << "Input number of rows for matrix A: ";
            cin >> r;
            cout << "Input number of columns for matrix A: ";
            cin >> c;
            Matrix mat1(r, c);
            mat1.inputElements();

            cout << "Enter size matrix B" << endl;
            cout << "Input number of rows for matrix B: ";
            cin >> r2;
            cout << "Input number of columns for matrix B: ";
            cin >> c2;
            Matrix mat2(r2, c2);
            mat2.inputElements();

            cout << "Your matrix A:" << endl;
            mat1.print();
            cout << "Your matrix B:" << endl;
            mat2.print();

            Res R;
            if (choose == 5) {
                if (r == r2 && c == c2) {
                    Summa smat12(mat1, mat2);
                    R.getres(&smat12);
                    break;
                }
                else {
                    cout << "Error - number of rows or columns in matrix A is not equal to number of rows or columns in matrix B" << endl;
                    cout << "Please try again." << endl;
                }
            }
            else if (choose == 6) {
                if (c == r2) {
                    Multip mt12(mat1, mat2);
                    R.getres(&mt12);
                    break;
                }
                else {
                    cout << "Error - number of columns in matrix A is not equal to number of rows in matrix B" << endl;
                    cout << "Please try again." << endl;
                }
            }
        }
    }

};