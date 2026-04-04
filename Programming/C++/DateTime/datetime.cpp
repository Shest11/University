#include "datetime.h"
#include <iostream>
using namespace std;


DateTime::DateTime() {
    year = 0;
    month = 0;
    day = 0;
    hour = 0;
    minute = 0;
    second = 0;
}

DateTime::DateTime(int year, int month, int day, int hour, int minute, int second) : year(year), month(month), day(day), hour(hour), minute(minute), second(second) {
    int daysInYears = 0, daysInMonth = 0;

    for (int i = 1900; i < year; i++) {

        if ((i % 400 == 0) or (i % 4 == 0 and i % 100 != 0))
            daysInYears += 366;
        else
            daysInYears += 365;
    }

    for (int m = 1; m < month; m++) {

        if (m == 1 or m == 3 or m == 5 or m == 8 or m == 7 or m == 10 or m == 12)
            daysInMonth += 31;
        else if (m == 4 or m == 6 or m == 9 or m == 11)
            daysInMonth += 30;
        else if ((year % 400 == 0) or (year % 4 == 0 and year % 100 != 0))
            daysInMonth += 29;
        else
            daysInMonth += 28;
    }

    totalDays = daysInYears + daysInMonth + day - 1;
    secondsDay = hour * 3600 + minute * 60 + second;
}

void DateTime::printDays() const {
    cout << totalDays;
}

bool DateTime::isLeap() const {
    return (year % 400 == 0) or (year % 4 == 0 and year % 100 != 0);
}

bool DateTime::isValid() const {
    return (year >= 1900) and (0 < month and month < 13)
    and (0 < day and day < 32) and (0 <= hour and hour < 25)
    and (0 <= minute and minute < 61) and (0 <= second and second < 61);
}



int DateTime::operator-(const DateTime &other) {
    return totalDays - other.totalDays;
}

void DateTime::operator+(int days) {
    for (int d = 0; d < days; d++) {

        if ((month == 1 or month == 3 or month == 5 or month == 8 or month == 7 or month == 10 or month == 12) and ((day + 1) > 31)) {
            month++;
            day = 0;
            if (month == 13) {
                month = 1;
                year++;
            }
        }
        else if ((month == 4 or month == 6 or month == 9 or month == 11) and ((day + 1) > 30)) {
            month++;
            day = 0;
        }
        else if (month == 2) {
            if (((year % 400 == 0) or (year % 4 == 0 and year % 100 != 0)) and ((day + 1) > 29)) {
                month++;
                day = 0;
            } else {
                month++;
                day = 0;
            }
        }
        day += 1;
    }
    totalDays += days;
}

bool DateTime::operator==(const DateTime &other) const{

    if (totalDays == other.totalDays)
        return secondsDay == other.secondsDay;
    else
        return false;
}

bool DateTime::operator >(const DateTime &other) const{

    if (totalDays == other.totalDays)
        return secondsDay > other.secondsDay;
    else
        return totalDays > other.totalDays;
}

bool DateTime::operator<(const DateTime &other) const{
    return other > *this;
}

bool DateTime::operator>=(const DateTime &other) const {
    return !(*this < other);
}

bool DateTime::operator<=(const DateTime &other) const{
    return !(*this > other);
}

void DateTime::dayOfWeek() const {
    if (totalDays % 7 == 0) {
        cout << "Понедельник";
    }
    else if (totalDays % 7 == 1) {
        cout << "Вторник";
    }
    else if (totalDays % 7 == 2) {
        cout << "Среда";
    }
    else if (totalDays % 7 == 3) {
        cout << "Четверг";
    }
    else if (totalDays % 7 == 4) {
        cout << "Пятница";
    }
    else if (totalDays % 7 == 5) {
        cout << "Суббота";
    }
    else if (totalDays % 7 == 6) {
        cout << "Воскресенье";
    }
}

istream& operator >> (istream& is, DateTime& dt) {
    string input, obj;
    bool flag = true;
    cout << endl << "Введите дату в формате (yyyy-MM-ddThh:mm:ss или yyyy-MM-dd):" << endl;
    is >> input;

    if (input.length() == 19) {
        for (int i = 0; i < input.length(); i++) {
            obj += input[i];
            if ((input[i] == '-') and (flag)) {
                dt.year = stoi(obj);
                flag = false;
                obj = "";
            }
            else if ((input[i] == '-') and (!flag)) {
                dt.month = stoi(obj);
                flag = true;
                obj = "";
            }
            else if ((input[i] == 'T') and (flag)) {
                dt.day = stoi(obj);
                flag = false;
                obj = "";
            }
            else if ((input[i] == ':') and (!flag)) {
                dt.hour = stoi(obj);
                flag = true;
                obj = "";
            }
            else if ((input[i] == ':') and (flag)) {
                dt.minute = stoi(obj);
                obj = "";
            }
            else if (i == 18)
                dt.second = stoi(obj);
        }
    }
    else {
        for (int i = 0; i < input.length(); i++) {
            obj += input[i];
            if ((input[i] == '-') and (flag)) {
                dt.year = stoi(obj);
                flag = false;
                obj = "";
            }
            else if ((input[i] == '-') and (!flag)) {
                dt.month = stoi(obj);
                flag = true;
                obj = "";
            }
            else if (i == 9) {
                dt.day = stoi(obj);
                obj = "";
            }
        }
    }
    int daysInYears = 0, daysInMonth = 0;

    for (int i = 1900; i < dt.year; i++) {

        if ((i % 400 == 0) or (i % 4 == 0 and i % 100 != 0))
            daysInYears += 366;
        else
            daysInYears += 365;
    }

    for (int m = 1; m < dt.month; m++) {

        if (m == 1 or m == 3 or m == 5 or m == 8 or m == 7 or m == 10 or m == 12)
            daysInMonth += 31;
        else if (m == 4 or m == 6 or m == 9 or m == 11)
            daysInMonth += 30;
        else if ((dt.year % 400 == 0) or (dt.year % 4 == 0 and dt.year % 100 != 0))
            daysInMonth += 29;
        else
            daysInMonth += 28;
    }

    dt.totalDays = daysInYears + daysInMonth + dt.day - 1;
    dt.secondsDay = dt.hour * 3600 + dt.minute * 60 + dt.second;

    return is;
}

ostream& operator << (ostream& os, const DateTime& dt) {
    os << dt.year << '-' << dt.month << '-' << dt.day << 'T' << dt.hour << ':' << dt.minute << ':' << dt.second;
    return os;
}
