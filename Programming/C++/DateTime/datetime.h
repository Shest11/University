#pragma once
#include <iostream>

using namespace std;

class DateTime {
    int year, month, day, hour, minute, second;
    int totalDays;
    int secondsDay;

    bool isLeap(int y) const;
    int daysInMonth(int y, int m) const;
    void recomputeTotalDays();

public:
    DateTime();
    DateTime(int year, int month, int day,
             int hour = 0, int minute = 0, int second = 0);

    bool isValid() const;
    bool isLeap() const;

    void printDays() const;

    int operator-(const DateTime& other);
    DateTime& operator+(int days);

    bool operator==(const DateTime& other) const;
    bool operator>(const DateTime& other) const;
    bool operator<(const DateTime& other) const;
    bool operator>=(const DateTime& other) const;
    bool operator<=(const DateTime& other) const;

    void dayOfWeek() const;

    int getYear() const { return year; }
    int getMonth() const { return month; }
    int getDay() const { return day; }
    int getHour() const { return hour; }
    int getMinute() const { return minute; }
    int getSecond() const { return second; }

    friend istream& operator>>(istream& is, DateTime& dt);
    friend ostream& operator<<(ostream& os, const DateTime& dt);
    friend class Moon;
};