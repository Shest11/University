#pragma once
#include "datetime.h"
#include <iostream>
using namespace std;

class Moon {
    DateTime date;

public:
    Moon();
    Moon(int day, int month, int year);

    friend ostream& operator<<(ostream& os, const Moon& moon);
    friend istream& operator>>(istream& is, Moon& moon);

    void moonrise();
    void culmination();
    void moonset();
};