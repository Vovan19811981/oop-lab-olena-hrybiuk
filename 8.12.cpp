/*
 * Завдання 12
 * Абстрактний клас з віртуальною функцією КОРЕНІ РІВНЯННЯ.
 * Похідні класи: ЛІНІЙНЕ РІВНЯННЯ, КВАДРАТНЕ РІВНЯННЯ.
 */

#include <iostream>
#include <cmath>
#include <string>
#include <vector>
using namespace std;

// ─── Абстрактний базовий клас ───────────────────────────────────────────────
class Equation {
public:
    virtual vector<double> roots() const = 0;
    virtual string         name()  const = 0;
    virtual ~Equation() {}

    void print() const {
        cout << name() << endl;
        vector<double> r = roots();
        if (r.empty()) {
            cout << "  Коренів немає (або нескінченно багато)." << endl;
        } else {
            cout << "  Корені: ";
            for (size_t i = 0; i < r.size(); ++i)
                cout << "x" << (i+1) << "=" << r[i] << "  ";
            cout << endl;
        }
        cout << string(50, '-') << endl;
    }
};

// ─── Лінійне рівняння: ax + b = 0 ───────────────────────────────────────────
class LinearEquation : public Equation {
    double a, b;
public:
    LinearEquation(double a, double b) : a(a), b(b) {}

    vector<double> roots() const override {
        if (fabs(a) < 1e-12) return {}; // 0 = b — немає або нескінченно
        return { -b / a };
    }
    string name() const override {
        return "Лінійне рівняння: " + to_string(a) + "x + " + to_string(b) + " = 0";
    }
};

// ─── Квадратне рівняння: ax² + bx + c = 0 ───────────────────────────────────
class QuadraticEquation : public Equation {
    double a, b, c;
public:
    QuadraticEquation(double a, double b, double c) : a(a), b(b), c(c) {}

    vector<double> roots() const override {
        if (fabs(a) < 1e-12) {
            // вироджується в лінійне
            LinearEquation lin(b, c);
            return lin.roots();
        }
        double D = b * b - 4 * a * c;
        if (D < 0)  return {};
        if (D == 0) return { -b / (2 * a) };
        double sqrtD = sqrt(D);
        return { (-b - sqrtD) / (2 * a), (-b + sqrtD) / (2 * a) };
    }
    string name() const override {
        return "Квадратне рівняння: " + to_string(a) + "x^2 + "
               + to_string(b) + "x + " + to_string(c) + " = 0";
    }
};

int main() {
    cout << "=== Завдання 12: Корені рівнянь ===" << endl << endl;

    const int N = 5;
    Equation* equations[N] = {
        new LinearEquation(2, -6),           // x = 3
        new LinearEquation(0, 5),            // немає коренів
        new QuadraticEquation(1, -5, 6),     // x1=2, x2=3
        new QuadraticEquation(1, -2, 1),     // x=1 (один корінь)
        new QuadraticEquation(1, 0, 4)       // немає дійсних коренів
    };

    for (int i = 0; i < N; ++i)
        equations[i]->print();

    for (int i = 0; i < N; ++i)
        delete equations[i];

    return 0;
}
