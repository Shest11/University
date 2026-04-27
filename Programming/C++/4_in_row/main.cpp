#include "4_in_row.h"
#include <iostream>
using namespace std;

int main () {

    bool redFirst = true;
    Field field(redFirst);

    while (!field.isOver()) {
        field.print();

        cout << "Ходит " << (field.isRedTurnNow() ? "КРАСНЫЙ" : "ЖËЛТЫЙ") << " игрок, введите ход (1-7): ";

        int column;
        cin >> column;

        field.makeTurn(column);
    }
    field.printResult();
}