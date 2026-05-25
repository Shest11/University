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

    Rational operator -(const Rational& other) const;
    Rational& operator *=(const Rational& other);
    Rational operator *(const Rational& other) const;
    Rational operator /(const Rational& other) const;

    Rational& operator ++();
    Rational operator ++(int);

    bool operator ==(const Rational& r) const;
    bool operator !=(const Rational& r) const;

    bool operator >(const Rational& other) const;
    bool operator <(const Rational& other) const;

    friend istream& operator >>(istream& in, Rational& r);
    friend ostream& operator <<(ostream& out, const Rational& r);

    void simplify();

    Rational operator *(long long n) const;
    friend Rational operator *(long long n, const Rational& r);
    friend Rational operator *(int n, const Rational& r);

    friend Rational abs(const Rational& r);

    static Rational sqrt(const Rational& S);
};