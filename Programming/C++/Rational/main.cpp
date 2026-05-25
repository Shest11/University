#include "rational.h"
#include <iostream>
using namespace std;

int main() {

  // // Тестируем конструктор, +, -, *=, /, <<
  // Rational a(1,2), b(-1,6);
  // cout<<"a="<<a<<" b="<<b<<" a+b="<<a+b<<endl;
  // cout<<"a("<<a<<") *= b("<<b<<")"<<endl;
  // a *= b;
  // cout<<"a="<<a<<" b="<<b<<" a-b="<<a+(-b)<<endl;
  // Rational c=3;
  // cout<<"b="<<b<<" c="<<c<<" b/c="<<b/c<<endl;
  //
  // // Тестируем >>, !=
  // Rational e(7,8), f(5,12);
  // cout<<"e="<<e<<" f="<<f<<" e+f=?"<<endl;
  // cout<<"Введите результат g=m/n в формате: m n"<<endl;
  // Rational g;
  // cin>>g;
  // if (e+f!=g)
  //   cout<<"Неправильно! e+f="<<e+f<<endl;
  // else
  //   cout<<"Правильно!"<<endl;

  Rational ra;
  cout << "Введите a=x/y (в формате x y): ";
  cin >> ra;

  Rational rb;
  cout << "Введите b=x/y (в формате x y): ";
  cin >> rb;

  Rational rc;
  cout << "Введите с=x/y (в формате x y): ";
  cin >> rc;

  Rational D;
  Rational x1;
  Rational x2;

  D = rb * rb + (-(ra * rc * 4));
  D.simplify();

  x1 = ((-rb) + Rational::sqrt(D)) / (ra * 2);
  x2 = ((-rb) + (-(Rational::sqrt(D)))) / (ra * 2);
  x1.simplify();
  x2.simplify();
  cout << "x1: " << x1 << endl;
  cout << "x2: " << x2 << endl;
}