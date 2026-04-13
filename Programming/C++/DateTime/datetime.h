#pragma once
#include <iostream>
using namespace std;

class DateTime {
    int year, month, day, hour, minute, second, totalDays, secondsDay;

public:
    DateTime();
    DateTime(int year, int month, int day, int hour = 0, int minute = 0, int second = 0);

    bool isLeap() const;
    bool isValid() const;

    void printDays() const;

    int operator -(const DateTime& other);
    void operator +(int days);

    bool operator ==(const DateTime& other) const;
    bool operator >(const DateTime& other) const;
    bool operator <(const DateTime& other) const;
    bool operator >=(const DateTime& other) const;
    bool operator <=(const DateTime& other) const;

    void dayOfWeek() const;

    friend istream& operator >> (istream& is, DateTime& dt);
    friend ostream& operator << (ostream& os, const DateTime& dt);
    friend class Moon;
};