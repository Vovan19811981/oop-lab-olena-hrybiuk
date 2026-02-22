/*
 * Завдання 8
 * Абстрактний клас з віртуальною функцією ПЛОЩА ПОВЕРХНІ.
 * Похідні класи: ПАРАЛЕЛЕПІПЕД, ТЕТРАЕДР, КУЛЯ.
 * S_паралелепіпеда = 2(ab+bc+ca)
 * S_кулі = 4πr²
 * S_тетраедра = a²√3
 */

#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>
using namespace std;

// ─── Абстрактний базовий клас ───────────────────────────────────────────────
class Solid {
public:
    virtual double surfaceArea() const = 0;
    virtual string name()        const = 0;
    virtual ~Solid() {}

    void print() const {
        cout << left << setw(45) << name()
             << "S = " << fixed << setprecision(4) << surfaceArea() << endl;
    }
};

// ─── Прямокутний паралелепіпед ───────────────────────────────────────────────
class Parallelepiped : public Solid {
    double a, b, c;
public:
    Parallelepiped(double a, double b, double c) : a(a), b(b), c(c) {}
    double surfaceArea() const override { return 2 * (a*b + b*c + c*a); }
    string name() const override {
        return "Паралелепіпед (a=" + to_string(a) + ", b=" + to_string(b) + ", c=" + to_string(c) + ")";
    }
};

// ─── Правильний тетраедр ─────────────────────────────────────────────────────
class Tetrahedron : public Solid {
    double a; // ребро
public:
    Tetrahedron(double a) : a(a) {}
    double surfaceArea() const override { return a * a * sqrt(3.0); }
    string name() const override {
        return "Тетраедр    (a=" + to_string(a) + ")";
    }
};

// ─── Куля ────────────────────────────────────────────────────────────────────
class Sphere : public Solid {
    double r;
public:
    Sphere(double r) : r(r) {}
    double surfaceArea() const override { return 4 * M_PI * r * r; }
    string name() const override {
        return "Куля        (r=" + to_string(r) + ")";
    }
};

int main() {
    cout << "=== Завдання 8: Площа поверхні тіл ===" << endl << endl;

    const int N = 3;
    Solid* solids[N] = {
        new Parallelepiped(3, 4, 5),
        new Tetrahedron(6),
        new Sphere(4)
    };

    cout << "Пізнє зв'язування через масив вказівників:" << endl;
    cout << string(65, '-') << endl;
    for (int i = 0; i < N; ++i)
        solids[i]->print();

    for (int i = 0; i < N; ++i)
        delete solids[i];

    return 0;
}
