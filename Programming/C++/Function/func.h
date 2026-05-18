#pragma once

class Function {
public:
    virtual void func_calc() = 0;
    virtual void get_max_min(double a, double b) = 0;
    virtual void integration() = 0;
    virtual void differentiation() = 0;
    virtual ~Function() {}
};

class Hyperbola : public Function {
    double k, x;
public:
    Hyperbola(double k, double x) : k(k), x(x) {}
    void func_calc() override;
    void get_max_min(double a, double b) override;
    void integration() override;
    void differentiation() override;
};

class Parabola : public Function {
    double a, b, c, x;
public:
    Parabola(double a, double b, double c, double x) : a(a), b(b), c(c), x(x) {}
    void func_calc() override;
    void get_max_min(double l, double r) override;
    void integration() override;
    void differentiation() override;
};

class Exponent : public Function {
    double A, B, x;
public:
    Exponent(double A, double B, double x) : A(A), B(B), x(x) {}
    void func_calc() override;
    void get_max_min(double a, double b) override;
    void integration() override;
    void differentiation() override;
};