#include "rational.h"
#include <iostream>
#include <cmath>

using namespace std;

Rational::Rational()
{
  numer = 0;
  denom = 1;
}

Rational::Rational(long long n)
{
  numer = n;
  denom = 1;
}

Rational::Rational(long long n, long long d)
{
  numer = n;
  denom = d;
}

Rational& Rational::operator +=(const Rational& r) {
  numer = (numer * r.denom + denom * r.numer);
  denom *= r.denom;
  simplify();
  return *this;
}

void Rational::simplify() {
  if (denom == 0) return;
  if (denom < 0) {
    numer = -numer;
    denom = -denom;
  }

  long long a = llabs(numer);
  long long b = denom;
  while (b != 0) {
    long long temp = b;
    b = a % b;
    a = temp;
  }
  long long nod = a;
  if (nod != 0) {
    numer /= nod;
    denom /= nod;
  }
}

Rational Rational::operator +(const Rational &other) const {
  Rational res(*this);
  return res += other;
}

Rational Rational::operator -() const {
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

bool Rational::operator ==(const Rational &other) const {
  return (numer == other.numer) and (denom == other.denom);
}

bool Rational::operator !=(const Rational &other) const {
  return !(*this == other);
}

istream& operator >>(istream& in, Rational& r) {
  in >> r.numer >> r.denom;
  return in;
}

ostream& operator <<(ostream& out, const Rational& r) {
  out << r.numer << "/" << r.denom;
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

Rational Rational::operator /(const Rational& other) const {
  Rational res(*this);
  res.numer *= other.denom;
  res.denom *= other.numer;
  res.simplify();
  return res;
}

Rational Rational::operator *(long long n) const {
  Rational res(*this);
  res.numer *= n;
  res.simplify();
  return res;
}

Rational operator *(long long n, const Rational& r) {
  return r * n;
}

Rational Rational::sqrt(Rational r) {
  long long s_num = std::llround(std::sqrt((long double)r.numer));
  long long s_den = std::llround(std::sqrt((long double)r.denom));

  if (s_num * s_num == r.numer && s_den * s_den == r.denom) {
    return Rational(s_num, s_den);
  }

  // Возвращаем 0/1, если точный корень не найден
  return Rational(0, 1);
}