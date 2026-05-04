#pragma once
#include <vector>
#include <string>
using namespace std;

class Shape {
public:
    virtual double calc_area() = 0;
    virtual double calc_perimetr() = 0;
    virtual void name() = 0;
    virtual ~Shape();
};

class Point {
public:
    int x, y;
    Point() : x(0), y(0) {}
    Point(int x, int y) : x(x), y(y) {}
};

class Circle : public Shape{
    Point center;
    double radius;
public:
    Circle(const Point& coord, double radius) : center(coord), radius(radius) {}
    double calc_area() override;
    double calc_perimetr() override;
    void name() override;
};

class Ellipse : public Shape {
    Point center;
    double big_radius;
    double small_radius;
public:
    Ellipse(const Point& coord, double big_radius, double small_radius) : center(coord), big_radius(big_radius), small_radius(small_radius) {}
    double calc_area() override;
    double calc_perimetr() override;
    void name() override;
};

class Rectangle : public Shape {
    const Point upper_left, lower_right;
public:
    Rectangle(const Point& upper_left, const Point& lower_right) : upper_left(upper_left), lower_right(lower_right) {}
    double calc_area() override;
    double calc_perimetr() override;
    void name() override;
};

class Triangle : public Shape {
    const Point A, B, C;
public:
    Triangle(const Point& A, const Point& B, const Point& C) : A(A), B(B), C(C) {}
    double calc_area() override;
    double calc_perimetr() override;
    void name() override;
};

class Polygon : public Shape {
    vector<Point> coords;
public:
    Polygon(const string& filename);
    double calc_area() override;
    double calc_perimetr() override;
    void name() override;
};

