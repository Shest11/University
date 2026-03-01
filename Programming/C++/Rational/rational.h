#ifndef RATIONAL_H
#define RATIONAL_H
#include <iostream>
using namespace std;

class Rational {
public:
  int numer, denom;
  Rational();
  Rational(int n);
  Rational(int n, int d);

  Rational& operator +=(const Rational& r);
  Rational operator +(const Rational& other) const; // Первый const (const Rational& other) защищает аргумент other от изменения.
                                                    // Второй const защищает текущий объект (*this) от изменения.
  Rational operator -() const;
  Rational& operator -=(const Rational& r);

  Rational& operator ++(); // префикс
  Rational operator ++(int); // постфикс

  bool operator ==(const Rational& r) const;
  bool operator !=(const Rational& r) const;

  operator int() const;
  operator double() const;

  friend istream& operator >>(istream& in, Rational& r);
  friend ostream& operator <<(ostream& out, const Rational& r);

  void simplify();

  Rational operator *(const Rational& other) const;
  Rational& operator *=(const Rational& other);


};

#endif // RATIONAL_H
