#include "moon.h"
#include <iostream>
using namespace std;

int main() {
    Moon dt;
    cin >> dt;
    dt.moonrise();
    dt.culmination();
    dt.moonset();
}