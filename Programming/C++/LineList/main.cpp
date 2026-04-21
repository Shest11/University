#include "linelist.h"
#include <iostream>
using namespace std;

int main() {
    // LineList<int> list;
    // list.insertFirst(1);
    // list.insertFirst(2);
    // list.insertFirst(3);
    //
    // list.deleteFirst();
    // cout << list;

    LineList<int> list;
    int N;
    cout << "Введите N: " << endl;
    cin >> N;

    list.iosif(N);
    cout << list;

}
