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

// Реализация свободной функции abs
Rational abs(const Rational& r) {
    return Rational(std::abs(r.numer), r.denom);
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

Rational Rational::operator -(const Rational &other) const {
  Rational res(*this);
  return res += (-other);
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

bool Rational::operator >(const Rational &other) const {
  return (numer * other.denom) > (other.numer * denom);
}

bool Rational::operator <(const Rational &other) const {
  return (numer * other.denom) < (other.numer * denom);
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

Rational operator *(int n, const Rational& r) {
  return Rational(n) * r;
}

Rational Rational::sqrt(const Rational& S) {
    // Проверка на отрицательное число
    if (S.numer < 0) return Rational(-1, 1);
    if (S.numer == 0) return Rational(0, 1);

    // Преобразуем Rational в long double
    long double value = (long double)S.numer / (long double)S.denom;

    // Получаем мантиссу и экспоненту
    int exp;
    long double mantissa = frexp(value, &exp);

    // Корректируем экспоненту для извлечения корня
    if (exp % 2 != 0) {
        exp--;
        mantissa *= 2;
    }

    // Вавилонский метод для извлечения корня из мантиссы
    long double sqrt_mantissa = mantissa;  // начальное приближение
    for (int i = 0; i < 30; i++) {
        sqrt_mantissa = (sqrt_mantissa + mantissa / sqrt_mantissa) / 2.0;
    }

    // Собираем результат
    long double result = ldexp(sqrt_mantissa, exp / 2);

    // Преобразуем обратно в Rational
    const long long PRECISION = 1000000000;  // 10^9
    long long result_num = std::llround(result * PRECISION);
    long long result_den = PRECISION;

    Rational res(result_num, result_den);
    res.simplify();

    return res;
}