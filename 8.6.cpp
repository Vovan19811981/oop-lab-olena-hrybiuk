/*
 * Завдання 6
 * Базовий клас ФІГУРА з віртуальними функціями: площа, периметр, виведення.
 * Похідні класи: КОЛО, ПРЯМОКУТНИК, ТРАПЕЦІЯ.
 * Площа: S_кола=πr², S_прямокутника=ab, S_трапеції=(a+b)h/2
 * Периметр: L_кола=2πr, L_прямокутника=2(a+b), L_трапеції=a+b+c+d
 */

#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>
using namespace std;

// ─── Базовий клас ────────────────────────────────────────────────────────────
class Figure {
public:
    virtual double area()      const = 0;
    virtual double perimeter() const = 0;
    virtual string name()      const = 0;
    virtual void   display()   const {
        cout << "┌─ " << name() << endl;
        cout << "│  Площа:     " << fixed << setprecision(4) << area() << endl;
        cout << "│  Периметр:  " << perimeter() << endl;
        cout << "+" << string(40, '-') << endl;
    }
    virtual ~Figure() {}
};

// ─── Коло ────────────────────────────────────────────────────────────────────
class Circle : public Figure {
    double r;
public:
    Circle(double r) : r(r) {}
    double area()      const override { return M_PI * r * r; }
    double perimeter() const override { return 2 * M_PI * r; }
    string name()      const override { return "Коло (r=" + to_string(r) + ")"; }
};

// ─── Прямокутник ─────────────────────────────────────────────────────────────
class Rectangle : public Figure {
    double a, b;
public:
    Rectangle(double a, double b) : a(a), b(b) {}
    double area()      const override { return a * b; }
    double perimeter() const override { return 2 * (a + b); }
    string name()      const override {
        return "Прямокутник (a=" + to_string(a) + ", b=" + to_string(b) + ")";
    }
};

// ─── Трапеція ─────────────────────────────────────────────────────────────────
class Trapezoid : public Figure {
    double a, b, c, d, h; // основи a,b; бічні сторони c,d; висота h
public:
    Trapezoid(double a, double b, double c, double d, double h)
        : a(a), b(b), c(c), d(d), h(h) {}
    double area()      const override { return 0.5 * (a + b) * h; }
    double perimeter() const override { return a + b + c + d; }
    string name()      const override {
        return "Трапеція (a=" + to_string(a) + ", b=" + to_string(b) + ")";
    }
};

int main() {
    cout << "=== Завдання 6: Площа і периметр фігур ===" << endl << endl;

    const int N = 3;
    Figure* figures[N] = {
        new Circle(5),
        new Rectangle(4, 7),
        new Trapezoid(6, 4, 3, 3, 4)
    };

    for (int i = 0; i < N; ++i)
        figures[i]->display();

    for (int i = 0; i < N; ++i)
        delete figures[i];

    return 0;
}
