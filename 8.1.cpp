/*
 * Завдання 1
 * Абстрактний клас ФІГУРА з віртуальною функцією площа.
 * Похідні класи: ПРЯМОКУТНИК, КОЛО, ПРЯМОКУТНИЙ ТРИКУТНИК, ТРАПЕЦІЯ.
 */

#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>
using namespace std;

// ─── Абстрактний базовий клас ───────────────────────────────────────────────
class Figure {
public:
    virtual double area()  const = 0;
    virtual string name()  const = 0;
    virtual ~Figure() {}

    void print() const {
        cout << left << setw(40) << name()
             << "S = " << fixed << setprecision(4) << area() << endl;
    }
};

// ─── Прямокутник ────────────────────────────────────────────────────────────
class Rectangle : public Figure {
    double a, b;
public:
    Rectangle(double a, double b) : a(a), b(b) {}
    double area() const override { return a * b; }
    string name() const override { return "Прямокутник (a=" + to_string(a) + ", b=" + to_string(b) + ")"; }
};

// ─── Коло ────────────────────────────────────────────────────────────────────
class Circle : public Figure {
    double r;
public:
    Circle(double r) : r(r) {}
    double area() const override { return M_PI * r * r; }
    string name() const override { return "Коло (r=" + to_string(r) + ")"; }
};

// ─── Прямокутний трикутник ──────────────────────────────────────────────────
class RightTriangle : public Figure {
    double a, b; // катети
public:
    RightTriangle(double a, double b) : a(a), b(b) {}
    double area() const override { return 0.5 * a * b; }
    string name() const override { return "Прямокутний трикутник (a=" + to_string(a) + ", b=" + to_string(b) + ")"; }
};

// ─── Трапеція ────────────────────────────────────────────────────────────────
class Trapezoid : public Figure {
    double a, b, h; // основи і висота
public:
    Trapezoid(double a, double b, double h) : a(a), b(b), h(h) {}
    double area() const override { return 0.5 * (a + b) * h; }
    string name() const override { return "Трапеція (a=" + to_string(a) + ", b=" + to_string(b) + ", h=" + to_string(h) + ")"; }
};

// ─── Функція виклику через вказівник ────────────────────────────────────────
void printFigure(Figure* f) { f->print(); }

int main() {
    cout << "=== Завдання 1: Площа геометричних фігур ===" << endl << endl;

    // Масив вказівників на абстрактний клас
    const int N = 4;
    Figure* figures[N] = {
        new Rectangle(5, 8),
        new Circle(4),
        new RightTriangle(3, 6),
        new Trapezoid(4, 8, 5)
    };

    cout << "Пізнє зв'язування через масив вказівників:" << endl;
    cout << string(60, '-') << endl;
    for (int i = 0; i < N; ++i)
        printFigure(figures[i]);

    for (int i = 0; i < N; ++i)
        delete figures[i];

    return 0;
}
