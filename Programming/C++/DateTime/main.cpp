#include "datetime.h"
#include <iostream>
using namespace std;

int main() {
    DateTime dt1, dt2;
    int days;
    cin >> dt1;
    cout << "Вы ввели дату: " << dt1 << endl;
    cout << "Её день недели: ";
    dt1.dayOfWeek();

    cin >> dt2;
    cout << "Вы ввели дату: " << dt1 << endl;
    cout << "Её день недели: ";
    dt2.dayOfWeek();

    cout << endl;
    cout << endl << "Разница между ними: " << abs(dt2 - dt1) << endl;

    cout << "Насколько увеличить первую дату: ";
    cin >> days;
    dt1 + days;
    cout << "Теперь первая дата: " << dt1;

    cout << endl;
    cout << "Даты равны: " << (dt1 == dt2 ? "Да" : "Нет") << endl;
    cout << "Первая больше: " << (dt1 > dt2 ? "Да" : "Нет") << endl;
    cout << "Первая меньше: " << (dt1 < dt2 ? "Да" : "Нет") << endl;
    cout << "Первая больше или равна: " << (dt1 >= dt2 ? "Да" : "Нет") << endl;
    cout << "Первая меньше или равна: " << (dt1 <= dt2 ? "Да" : "Нет") << endl;
}
