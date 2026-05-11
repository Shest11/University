#include "moon.h"
#include <fstream>
#include <sstream>

Moon::Moon() : date(1900, 1, 1) {}

Moon::Moon(int day, int month, int year) : date(year, month, day) {}

ostream& operator<<(ostream& os, const Moon& moon) {
    os << moon.date;
    return os;
}

istream& operator>>(istream& is, Moon& moon) {
    string input, obj, line;
    bool flag = true;
    int day, month, year;

    cout << "Ведите дату в формате дд.мм.гггг: ";
    cin >> input;

    for (int i = 0; i < input.length(); i++) {
        obj += input[i];
        if ((input[i] == '.') and (flag)) {
            day = stoi(obj);
            flag = false;
            obj = "";
        }
        else if ((input[i] == '.') and (!flag)) {
            month = stoi(obj);
            flag = true;
            obj = "";
        }
        else if (i == 9) {
            year = stoi(obj);
            obj = "";
        }

    }

    moon = Moon(day, month, year);
    return is;
}

void Moon::moonrise() {
    string ymd, hms, line, obj, hours, minutes, seconds;
    double el1, el2, skip;
    bool flag = true;
    int year, month, day;
    int day_from_dt = date.day;
    int month_from_dt = date.month;
    int year_from_dt = date.year;
    string filename = "Moon/moon" + to_string(year_from_dt) + ".dat";

    ifstream file(filename);
    getline(file, line);

    while (getline(file, line)) {

        stringstream ss(line);

        if (year_from_dt == 2007 or year_from_dt == 2008)
            ss >> ymd >> hms >> skip >> el2;
        else
            ss >> ymd >> hms >> skip >> skip >> el2;


        for (int i = 0; i < ymd.length(); i++) {
            obj += ymd[i];
            if (i == 3) {
                year = stoi(obj);
                obj = "";
            }
            else if (i == 5) {
                month = stoi(obj);
                obj = "";
            }
            else if (i == 7) {
                day = stoi(obj);
                obj = "";
            }
        }

        if (el2 > 0 and el1 < 0 and flag and day == day_from_dt and month == month_from_dt and year == year_from_dt ) {

            for (int i = 0; i < hms.length(); i++) {
                obj += hms[i];
                if (i == 1) {
                    hours = obj;
                    obj = "";
                }
                else if (i == 3) {
                    minutes = obj;
                    obj = "";
                }
                else if (i == 5) {
                    seconds = obj;
                    obj = "";
                }
            }

            cout << "Восход Луны: " << hours << ':' << minutes << ':' << seconds << endl;
            flag = false;
        }
        el1 = el2;
    }
}

void Moon::culmination() {
    string ymd, hms1, hms2, line, obj, hours, minutes, seconds;
    double el1 = -90, el2, skip;
    bool flag = true;
    int year, month, day;
    int day_from_dt = date.day;
    int month_from_dt = date.month;
    int year_from_dt = date.year;
    string filename = "Moon/moon" + to_string(year_from_dt) + ".dat";

    ifstream file(filename);
    getline(file, line);

    while (getline(file, line)) {

        stringstream ss(line);
        obj = "";

        if (year_from_dt == 2007 or year_from_dt == 2008)
            ss >> ymd >> hms2 >> skip >> el2;
        else
            ss >> ymd >> hms2 >> skip >> skip >> el2;


        for (int i = 0; i < ymd.length(); i++) {
            obj += ymd[i];
            if (i == 3) {
                year = stoi(obj);
                obj = "";
            }
            else if (i == 5) {
                month = stoi(obj);
                obj = "";
            }
            else if (i == 7) {
                day = stoi(obj);
                obj = "";
            }
        }

        if (el1 > el2 and flag and day == day_from_dt and month == month_from_dt and year == year_from_dt ) {
            obj = "";
            for (int i = 0; i < hms1.length(); i++) {
                obj += hms1[i];
                if (i == 1) {
                    hours = obj;
                    obj = "";
                }
                else if (i == 3) {
                    minutes = obj;
                    obj = "";
                }
                else if (i == 5) {
                    seconds = obj;
                    obj = "";
                }
            }

            cout << "Кульминация Луны: " << hours << ':' << minutes << ':' << seconds << endl;
            flag = false;
        }
        el1 = el2;
        hms1 = hms2;
    }

}

void Moon::moonset() {
    string ymd, hms, line, obj, hours, minutes, seconds;
    double el1 = -90, el2, skip;
    bool flag = true;
    int year, month, day;
    int day_from_dt = date.day;
    int month_from_dt = date.month;
    int year_from_dt = date.year;
    string filename = "Moon/moon" + to_string(year_from_dt) + ".dat";

    ifstream file(filename);
    getline(file, line);

    while (getline(file, line)) {

        stringstream ss(line);
        obj = "";

        if (year_from_dt == 2007 or year_from_dt == 2008)
            ss >> ymd >> hms >> skip >> el2;
        else
            ss >> ymd >> hms >> skip >> skip >> el2;

        for (int i = 0; i < ymd.length(); i++) {
            obj += ymd[i];
            if (i == 3) {
                year = stoi(obj);
                obj = "";
            }
            else if (i == 5) {
                month = stoi(obj);
                obj = "";
            }
            else if (i == 7) {
                day = stoi(obj);
                obj = "";
            }
        }

        if (el2 < 0 and el1 > 0 and flag and day == day_from_dt and month == month_from_dt and year == year_from_dt ) {
            obj = "";
            for (int i = 0; i < hms.length(); i++) {
                obj += hms[i];
                if (i == 1) {
                    hours = obj;
                    obj = "";
                }
                else if (i == 3) {
                    minutes = obj;
                    obj = "";
                }
                else if (i == 5) {
                    seconds = obj;
                    obj = "";
                }
            }

            cout << "Заход Луны: " << hours << ':' << minutes << ':' << seconds << endl;
            flag = false;
        }
        el1 = el2;
    }
}
