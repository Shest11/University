#include "linelist.h"
#include <iostream>
using namespace std;

void iosif(LineList<int>& list, int N, int k) {
    for (int data = N; data > 0; --data)
        list.insertFirst(data);

    if (k == 1) {
        for (int i = 0; i < N - 1; ++i)
            list.deleteFirst();
        return;
    }

    list.makeCircular();

    auto prev = list.getStart();

    for (int i = 0; i < N - 1; ++i) {
        for (int step = 0; step < k - 2; ++step) {
            prev = prev->getNext();
        }
        list.deleteAfter(prev);
        prev = prev->getNext();
    }

    list.breakCircular(prev);
    list.setStart(prev);
}

int main() {
    LineList<int> list;
    int N, k;
    cout << "Введите N: ";
    cin >> N;
    cout << "Введите k: ";
    cin >> k;

    iosif(list, N, k);
    cout << list << endl;

}