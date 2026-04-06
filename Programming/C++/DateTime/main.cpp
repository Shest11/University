#include "moon.h"
#include <fstream>
#include <sstream>
#include "datetime.h"
#include <iostream>
#include <string>
using namespace std;

int main() {
    string input, obj, line;
    bool flag = true;
    int day, month, year;

    // cout << "Ведите дату в формате дд.мм.гггг: ";
    // cin >> input;
    //
    // for (int i = 0; i < input.length(); i++) {
    //     obj += input[i];
    //     if ((input[i] == '.') and (flag)) {
    //         day = stoi(obj);
    //         flag = false;
    //         obj = "";
    //     }
    //     else if ((input[i] == '.') and (!flag)) {
    //         month = stoi(obj);
    //         flag = true;
    //         obj = "";
    //     }
    //     else if (i == 9)
    //         year = stoi(obj);
    // }
    //
    // Moon dt(year, month, day);
    // cout << dt;

    ifstream file("Moon/moon1998.dat");

    string ymd, hms;
    double el;
    getline(file, line);

    while (getline(file, line)) {

        stringstream ss(line);

        ss >> ymd >> hms >> el;

        cout << "Дата: " << ymd << endl;
        cout << "Время: " << hms << endl;
        cout << "Градус:" << el << endl;
    }

}