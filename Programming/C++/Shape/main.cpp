#include "shapes.h"
#include <iostream>
#include <string>
#include <vector>
using namespace std;

int main() {
    const Point pt1(3, 4);
    const Point pt2(5, 1);
    const Point pt3(6, 8);
    double general_area = 0;
    double general_perimetr = 0;

    vector<Shape*> shapes;

    shapes.push_back(new Circle(pt1, 4));
    shapes.push_back(new Ellipse(pt1, 5, 4));
    shapes.push_back(new Rectangle(pt1, pt2));
    shapes.push_back(new Triangle(pt1, pt2, pt3));
    shapes.push_back(new Polygon("granitsy-uchastka2.txt"));

    for (size_t i = 0; i < shapes.size(); ++i) {
        shapes[i]->name();
        cout << "Площадь: " << shapes[i]->calc_area() << endl;
        cout << "Периметр: " << shapes[i]->calc_perimetr() << endl;
        cout << "" << endl;
        general_area += shapes[i]->calc_area();
        general_perimetr += shapes[i]->calc_perimetr();
    }

    cout << "Общая площадь: " << general_area << endl;
    cout << "Общий периметр: " << general_perimetr << endl;

    for (size_t i = 0; i < shapes.size(); ++i) {
        delete shapes[i];
    }
    shapes.clear();
}