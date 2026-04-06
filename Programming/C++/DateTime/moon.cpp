#include "moon.h"

Moon::Moon(int day, int month, int year) : date(year, month, day) {}

ostream& operator<<(ostream& os, const Moon& moon) {
    os << moon.date;
    return os;
}
