#include "datetime.h"
#include <iostream>
using namespace std;

int main() {
  DateTime dt(2007, 2, 20, 15, 30, 12);
  cout << dt << endl;
  cout << "Високосный: " << (dt.isLeap() ? "Да" : "Нет");
}
