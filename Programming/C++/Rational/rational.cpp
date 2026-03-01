#include "rational.h"
#include <iostream>

using namespace std;

Rational::Rational()
{
  numer=0;
  denom=1;
}

Rational::Rational(int n)
{
  numer=n;
  denom=1;
}

Rational::Rational(int n, int d)
{
  numer=n;
  denom=d;
}

Rational& Rational::operator +=(const Rational& r) {
  numer = (numer*r.denom+denom*r.numer);
  denom *= r.denom;
  // this - указатель на себя
  // *this - ссылка на себя
  simplify();
  return *this;
}

void Rational::simplify() {
  if (denom == 0) return;

  if (denom < 0) {
    numer = -numer;
    denom = -denom;
  }

  int a = abs(numer);
  int b = denom;

  while (b != 0) {
    int temp = b;
    b = a % b;
    a = temp;
  }

  int nod = a;

  if (nod != 0) {
    numer /= nod;
    denom /= nod;
  }
}

Rational Rational::operator +(const Rational &other) const {
  Rational res(*this);
  return res += other;
}

Rational Rational::operator -() const
{
  Rational r(-numer, denom);
  return r;
}

Rational& Rational::operator -=(const Rational &other) {

  return (*this += (-other));
}

Rational& Rational::operator ++() {
  numer += denom;
  return *this;
}

Rational Rational::operator ++(int) {
  Rational r(*this);
  numer += denom;
  return r;
}

bool Rational::operator ==(const Rational &other) const{

  return (numer==other.numer) and (denom==other.denom);
}

bool Rational::operator !=(const Rational &other) const{

  return !(*this == other);
}

Rational::operator int() const {

  return numer / denom;
}

Rational::operator double() const {

  return (double(numer) / denom);
}

istream& operator >>(istream& in, Rational& r)
{
  in>>r.numer>>r.denom;
  return in;
}
ostream& operator <<(ostream& out, const Rational& r)
{
  out<<r.numer<<"/"<<r.denom;
  return out;
}

Rational& Rational::operator *=(const Rational& other) {
  numer *= other.numer;
  denom *= other.denom;
  simplify();
  return *this;
}

Rational Rational::operator *(const Rational& other) const {
  Rational res(*this);
  res *= other;
  return res;
}