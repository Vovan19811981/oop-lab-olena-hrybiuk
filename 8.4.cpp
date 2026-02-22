/*
 * Завдання 4
 * Абстрактний клас ПРОГРЕСІЯ з віртуальною функцією суми.
 * Похідні класи: АРИФМЕТИЧНА ПРОГРЕСІЯ, ГЕОМЕТРИЧНА ПРОГРЕСІЯ.
 * Арифметична: a_j = a0 + j*d,  S_n = (n+1)*(a0+a_n)/2
 * Геометрична:  a_j = a0 * r^j, S_n = (a0 - a_n*r)/(1 - r)
 */

#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>
using namespace std;

// ─── Абстрактний базовий клас ───────────────────────────────────────────────
class Progression {
public:
    virtual double sum(int n)  const = 0;  // сума n+1 елементів (від 0 до n)
    virtual double element(int j) const = 0;
    virtual string name()      const = 0;
    virtual ~Progression() {}

    void print(int n) const {
        cout << name() << endl;
        cout << "  Елементи: ";
        for (int j = 0; j <= n; ++j)
            cout << fixed << setprecision(2) << element(j) << " ";
        cout << endl;
        cout << "  Сума (" << n+1 << " елементів) = " << sum(n) << endl << endl;
    }
};

// ─── Арифметична прогресія ───────────────────────────────────────────────────
class ArithmeticProgression : public Progression {
    double a0, d; // перший елемент і різниця
public:
    ArithmeticProgression(double a0, double d) : a0(a0), d(d) {}
    double element(int j) const override { return a0 + j * d; }
    double sum(int n) const override {
        double an = element(n);
        return (n + 1) * (a0 + an) / 2.0;
    }
    string name() const override {
        return "Арифметична прогресія (a0=" + to_string(a0) + ", d=" + to_string(d) + ")";
    }
};

// ─── Геометрична прогресія ───────────────────────────────────────────────────
class GeometricProgression : public Progression {
    double a0, r; // перший елемент і знаменник
public:
    GeometricProgression(double a0, double r) : a0(a0), r(r) {}
    double element(int j) const override { return a0 * pow(r, j); }
    double sum(int n) const override {
        if (fabs(r - 1.0) < 1e-9)
            return a0 * (n + 1);
        double an = element(n);
        return (a0 - an * r) / (1.0 - r);
    }
    string name() const override {
        return "Геометрична прогресія (a0=" + to_string(a0) + ", r=" + to_string(r) + ")";
    }
};

int main() {
    cout << "=== Завдання 4: Сума прогресій ===" << endl << endl;

    const int N = 2;
    Progression* progs[N] = {
        new ArithmeticProgression(2, 3),   // 2, 5, 8, 11, 14
        new GeometricProgression(1, 2)     // 1, 2, 4, 8, 16
    };

    cout << "Пізнє зв'язування через масив вказівників:" << endl;
    cout << string(60, '-') << endl;
    for (int i = 0; i < N; ++i)
        progs[i]->print(4); // 5 елементів (від 0 до 4)

    for (int i = 0; i < N; ++i)
        delete progs[i];

    return 0;
}
