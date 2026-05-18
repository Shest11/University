#include "func.h"
#include <iostream>
#include <cmath>
using namespace std;

void Hyperbola::func_calc() {
    cout << "y = " << k / x << endl;
}

void Hyperbola::get_max_min(double a, double b) {
    if (k > 0) {
        cout << "Максимум: " << k / a << endl;
        cout << "Минимум: " << k / b << endl;
    } else {
        cout << "Максимум: " << k / b << endl;
        cout << "Минимум: " << k / a << endl;
    }
}

void Hyperbola::differentiation() {
    cout << "Производная: " << -(k / x * x) << endl;
}

void Hyperbola::integration() {
    cout << "Интеграл: " << k * log(x) << " + C" << endl;
}

void Parabola::func_calc() {
    cout << "y = " << a * x*x + b * x + c << endl;
}

void Parabola::get_max_min(double l, double r) {
    double y_vertex;
    double x_vertex = - b / (2 * a);

    double y_l = a * l*l + b * l + c;
    double y_r = a * r*r + b * r + c;

    if (l < x_vertex and x_vertex < r) {
        y_vertex = a * x_vertex*x_vertex + b * x_vertex + c;
        if (y_vertex > y_r)
            cout << "Максимум: " << y_vertex << endl;
        else
            cout << "Максимум: " << y_r << endl;
        if (y_vertex < y_l)
            cout << "Минимум: " << y_vertex << endl;
        else
            cout << "Минимум: " << y_l << endl;
    } else {
        cout << "Максимум: " << y_r << endl;
        cout << "Минимум: " << y_l << endl;
    }
}

void Parabola::integration() {
    cout << "Интеграл: " << a * x*x*x / 3 + b * x*x / 2 + c * x << " + C" << endl;
}

void Parabola::differentiation() {
    cout << "Производная: " << 2 * a * x + b << endl;
}

void Exponent::func_calc() {
    cout << "y = " << A * exp(B * x) << endl;
}

void Exponent::get_max_min(double a, double b) {
    double y_left = A * exp(B * a);
    double y_right = A * exp(B * b);

    if (B > 0) {
        cout << "Минимум: " << y_left << endl;
        cout << "Максимум: " << y_right << endl;
    } else if (B < 0) {
        cout << "Максимум: " << y_left << endl;
        cout << "Минимум: " << y_right << endl;
    } else {
        cout << "Константа: " << A << " (нет максимума/минимума)" << endl;
    }
}

void Exponent::differentiation() {
    cout << "Производная: " << A * B * exp(B * x) << endl;
}

void Exponent::integration() {
    if (B != 0) {
        cout << "Интеграл: " << (A / B) * exp(B * x) << " + C" << endl;
    } else {
        cout << "Интеграл: " << A * x << " + C" << endl;
    }
}