#include "datetime.h"
#include <iostream>
using namespace std;

DateTime::DateTime(int year, int month, int day, int hour, int minute , int second) : year(year), month(month), day(day), hour(hour), minute(minute), second(second) {}

bool DateTime::isLeap() {
  return (year % 400 == 0) or (year % 4 == 0 && year % 100 != 0);
}

ostream& operator<<(ostream& os, const DateTime& dt) {
  os << dt.year << "-" << dt.month << "-" << dt.day << "T"
     << dt.hour << ":" << dt.minute << ":" << dt.second;
  return os;
}

istream& operator>>(istream& is, DateTime& dt) {
  char dash1, dash2, T, colon1, colon2;

  is >> dt.year >> dash1 >> dt.month >> dash2 >> dt.day >> T
     >> dt.hour >> colon1 >> dt.minute >> colon2 >> dt.second;

  return is;
}


