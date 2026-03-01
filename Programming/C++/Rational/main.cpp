#include "rational.h"
#include <string>
#include <iostream>
#include <cmath>
using namespace std;

int main() {
  string a, b, c;
  int index_, xa, ya, xb, yb, xc, yc;

  cout << "Введите a (в формате x/y): ";
  cin >> a;
  for (int i = 0; i < a.length(); i++) {
    if (a[i] == '/')
      index_ = i;
  }
  xa = stoi(a.substr(0, index_));
  ya = stoi(a.substr(index_+1));

  cout << "Введите b (в формате x/y): ";
  cin >> b;
  for (int i = 0; i < b.length(); i++) {
    if (b[i] == '/')
      index_ = i;
  }
  xb = stoi(b.substr(0, index_));
  yb = stoi(b.substr(index_+1));

  cout << "Введите c (в формате x/y): ";
  cin >> c;
  for (int i = 0; i < c.length(); i++) {
    if (c[i] == '/')
      index_ = i;
  }
  xc = stoi(c.substr(0, index_));
  yc = stoi(c.substr(index_+1));

  Rational ra(xa, ya);
  Rational rb(xb, yb);
  Rational rc(xc, yc);
  Rational four(4);
  Rational two(2);
  Rational D(0);
  Rational x1(1);
  Rational x2(1);

  D = rb * rb + (-(four * ra * rc));
  D.simplify();

  Rational Dn(int(sqrt(D.numer)));
  Rational Dd(1, int(sqrt(D.denom)));
  Rational a2(1, two * ra);

  x1 = ((-rb) + Dn * Dd) * a2;
  x2 = ( (-rb) + (-(Dn * Dd)) ) * a2;

  cout << "x1: " << x1.numer << " / " << x1.denom << endl;
  cout << "x2: " << x2.numer << " / " << x2.denom << endl;

  return 0;
}