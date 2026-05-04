#include "shapes.h"
#include <iostream>
#include <string>
using namespace std;

int main() {
    const Point pt1(3, 4);
    Circle circ(pt1, 4);
    circ.name();
    cout << "Площадь: " << circ.calc_area() << endl;
    cout << "Периметр: " << circ.calc_perimetr() << endl;

    cout << "" << endl;

    Ellipse ellipse(pt1, 5, 4);
    ellipse.name();
    cout << "Площадь: " << ellipse.calc_area() << endl;
    cout << "Периметр: " << ellipse.calc_perimetr() << endl;

    cout << "" << endl;

    const Point pt2(5, 1);
    Rectangle rect(pt1, pt2);
    rect.name();
    cout << "Площадь: " << rect.calc_area() << endl;
    cout << "Периметр: " << rect.calc_perimetr() << endl;

    cout << "" << endl;

    const Point pt3(6, 8);
    Triangle trian(pt1, pt2, pt3);
    trian.name();
    cout << "Площадь: " << trian.calc_area() << endl;
    cout << "Периметр: " << trian.calc_perimetr() << endl;

    cout << "" << endl;

    string filename = "granitsy-uchastka2.txt";
    Polygon poly(filename);
    poly.name();
    cout << "Площадь: " << poly.calc_area() << endl;
    cout << "Периметр: " << poly.calc_perimetr() << endl;

    cout << "" << endl;
}