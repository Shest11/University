#pragma once
#include <iostream>
using namespace std;

class Rational {
public:
    long long numer, denom;
    Rational();
    Rational(long long n);
    Rational(long long n, long long d);

    Rational& operator +=(const Rational& r);
    Rational operator +(const Rational& other) const;
    Rational operator -() const;
    Rational& operator -=(const Rational& r);

    Rational& operator ++(); // префикс
    Rational operator ++(int); // постфикс

    bool operator ==(const Rational& r) const;
    bool operator !=(const Rational& r) const;

    friend istream& operator >>(istream& in, Rational& r);
    friend ostream& operator <<(ostream& out, const Rational& r);

    void simplify();

    Rational operator *(const Rational& other) const;
    Rational& operator *=(const Rational& other);

    Rational operator /(const Rational& other) const;

    // Операторы умножения с целыми числами
    Rational operator *(long long n) const;
    friend Rational operator *(long long n, const Rational& r);

    // Добавляем оператор умножения для int
    friend Rational operator *(int n, const Rational& r);

    // Оператор деления для целых чисел
    Rational operator /(long long n) const;

    static Rational sqrt(Rational r);
};