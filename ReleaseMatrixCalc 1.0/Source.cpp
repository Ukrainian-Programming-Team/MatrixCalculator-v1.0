#include "library.h"     
#include "Matrix.h"       
#include "SoloOper.h"
#include "DuoOper.h"
#include "ChangeOper.h" 

int printchooses() {
    int chooses;
    cout << "Okay,this list operation. Change number needed operation: " << endl;
    cout << "1) Transponse matrix" << endl;
    cout << "2) Find Determinant" << endl;
    cout << "3) Find Rang Matrix" << endl;
    cout << "4) Find Inverse Matrix" << endl;
    cout << "5) Find Summ 2 Matrix" << endl;
    cout << "6) Find Multip 2 Matrix" << endl;
    cin >> chooses;
    return chooses;
}

void startprog() {
    while (true) {
        int choose = printchooses();
        if (choose > 0 && choose < 5) {
            ChangeOper A;
            A.HeadChangeSol(choose);
        }
        else if (choose > 4 && choose <= 6) {
            ChangeOper B;
            B.HeadChangeDuo(choose);
        }
        else {
            system("cls");
            continue;
        }

        int nextchoose;
        cout << "Thank you for using our Matrix Calc v1.0 beta." << endl;
        cout << "Do you want to continue using the calculator?" << endl;
        cout << "Enter 1 to restart the program or 0 to exit the calculator: ";
        cin >> nextchoose;

        if (nextchoose == 0) {
            cout << "Exiting the program." << endl;
            break;
        }
        else if (nextchoose == 1) {
            system("cls");
            continue;
        }
    }
}

int main() {
    cout << "Hi, I'm the Matrix Calculator v1.0 beta" << endl;
    startprog();
    return 0;
}
