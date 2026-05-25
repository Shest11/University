#include "func.h"
#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    vector<Function*> functions;

    functions.push_back(new Hyperbola(1, 2));
    functions.push_back(new Parabola(3, -5, 8, 2));
    functions.push_back(new Exponent(2, 0.5, 2));

    vector<string> names = {"Гипербола", "Парабола", "Экспонента"};

    for (size_t i = 0; i < functions.size(); ++i) {
        cout << names[i] << endl;
        functions[i]->func_calc();
        functions[i]->get_max_min(2, 6);
        functions[i]->differentiation();
        functions[i]->integration();
        cout << endl;
    }

    for (size_t i = 0; i < functions.size(); ++i) {
        delete functions[i];
    }

}