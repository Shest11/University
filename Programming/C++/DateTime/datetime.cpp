#include "datetime.h"
#include <iostream>
using namespace std;


DateTime::DateTime() {
    year = 1900;
    month = 1;
    day = 1;
    hour = 0;
    minute = 0;
    second = 0;
    totalDays = 0;
    secondsDay = 0;
}

DateTime::DateTime(int y, int m, int d, int h, int min, int sec)
    : year(y), month(m), day(d), hour(h), minute(min), second(sec) {
    if (!isValid())
        throw invalid_argument("Некорректная дата или время");
    recomputeTotalDays();
}

bool DateTime::isLeap(int y) const {
    return (y % 400 == 0) or (y % 4 == 0 and y % 100 != 0);
}

int DateTime::daysInMonth(int y, int m) const {
    if (m == 2) return isLeap(y) ? 29 : 28;
    if (m == 4 || m == 6 || m == 9 || m == 11) return 30;
    return 31;
}

void DateTime::recomputeTotalDays() {
    totalDays = 0;
    for (int y = 1900; y < year; ++y)
        totalDays += isLeap(y) ? 366 : 365;
    for (int m = 1; m < month; ++m)
        totalDays += daysInMonth(year, m);
    totalDays += day - 1;
    secondsDay = hour * 3600 + minute * 60 + second;
}

void DateTime::printDays() const {
    cout << totalDays;
}

bool DateTime::isLeap() const {
    return isLeap(year);
}

bool DateTime::isValid() const {
    if (year < 1900) return false;
    if (month < 1 || month > 12) return false;
    if (day < 1 || day > daysInMonth(year, month)) return false;
    if (hour < 0 || hour > 23) return false;
    if (minute < 0 || minute > 59) return false;
    if (second < 0 || second > 59) return false;
    return true;
}

int DateTime::operator-(const DateTime &other){
    return totalDays - other.totalDays;
}

DateTime& DateTime::operator+(int days) {
    for (int d = 0; d < days; d++) {
        if ((month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12) && ((day + 1) > 31)) {
            month++;
            day = 0;
            if (month == 13) {
                month = 1;
                year++;
            }
        }
        else if ((month == 4 || month == 6 || month == 9 || month == 11) && ((day + 1) > 30)) {
            month++;
            day = 0;
        }
        else if (month == 2) {
            if (isLeap(year) && ((day + 1) > 29)) {
                month++;
                day = 0;
            } else if (!isLeap(year) && ((day + 1) > 28)) {
                month++;
                day = 0;
            }
        }
        day += 1;
    }
    totalDays += days;
    return *this;
}

bool DateTime::operator==(const DateTime &other) const {
    if (totalDays == other.totalDays)
        return secondsDay == other.secondsDay;
    else
        return false;
}

bool DateTime::operator>(const DateTime &other) const {
    if (totalDays == other.totalDays)
        return secondsDay > other.secondsDay;
    else
        return totalDays > other.totalDays;
}

bool DateTime::operator<(const DateTime &other) const {
    return other > *this;
}

bool DateTime::operator>=(const DateTime &other) const {
    return !(*this < other);
}

bool DateTime::operator<=(const DateTime &other) const {
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

istream& operator>>(istream& is, DateTime& dt) {
    string input, obj;
    bool flag = true;
    cout << endl << "Введите дату в формате (yyyy-MM-ddThh:mm:ss или yyyy-MM-dd):" << endl;
    is >> input;

    if (input.length() == 19) {
        for (size_t i = 0; i < input.length(); i++) {
            obj += input[i];
            if ((input[i] == '-') && (flag)) {
                dt.year = stoi(obj);
                flag = false;
                obj = "";
            }
            else if ((input[i] == '-') && (!flag)) {
                dt.month = stoi(obj);
                flag = true;
                obj = "";
            }
            else if ((input[i] == 'T') && (flag)) {
                dt.day = stoi(obj);
                flag = false;
                obj = "";
            }
            else if ((input[i] == ':') && (!flag)) {
                dt.hour = stoi(obj);
                flag = true;
                obj = "";
            }
            else if ((input[i] == ':') && (flag)) {
                dt.minute = stoi(obj);
                obj = "";
            }
            else if (i == 18)
                dt.second = stoi(obj);
        }
    }
    else {
        for (size_t i = 0; i < input.length(); i++) {
            obj += input[i];
            if ((input[i] == '-') && (flag)) {
                dt.year = stoi(obj);
                flag = false;
                obj = "";
            }
            else if ((input[i] == '-') && (!flag)) {
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

    if (!dt.isValid())
        throw invalid_argument("Введена несуществующая дата");

    dt.recomputeTotalDays();
    return is;
}

ostream& operator<<(ostream& os, const DateTime& dt) {
    os << dt.year << '-' << dt.month << '-' << dt.day << 'T' << dt.hour << ':' << dt.minute << ':' << dt.second;
    return os;
}