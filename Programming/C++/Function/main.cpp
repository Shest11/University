#include "func.h"
#include <iostream>
using namespace std;

int main() {
    Hyperbola hyp(1, 2);
    cout << "Гипербола" << endl;
    hyp.func_calc();
    hyp.get_max_min(2, 6);
    hyp.differentiation();
    hyp.integration();

    cout << endl;

    Parabola par(3, -5, 8, 2);
    cout << "Парабола" << endl;
    par.func_calc();
    par.get_max_min(2, 6);
    par.differentiation();
    par.integration();

    cout << endl;

    Exponent expo(2, 0.5, 2);
    cout << "Экспонента" << endl;
    expo.func_calc();
    expo.get_max_min(2, 6);
    expo.differentiation();
    expo.integration();
}