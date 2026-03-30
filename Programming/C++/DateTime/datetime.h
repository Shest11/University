#pragma once
#include <iostream>
using namespace std;

class DateTime {
  int year, month, day, hour, minute, second;

public:
  DateTime(int year, int month, int day, int hour = 0, int minute = 0, int second = 0);

  bool isLeap();

  friend ostream& operator<<(ostream& os, const DateTime& dt);
  friend istream& operator>>(istream& is, DateTime& dt);
};