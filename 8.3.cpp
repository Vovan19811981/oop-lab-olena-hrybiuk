/*
 * Завдання 3
 * Абстрактний клас КРИВІ — обчислення y від x.
 * Похідні класи: ПРЯМА (y=ax+b), ЕЛІПС (x²/a²+y²/b²=1), ГІПЕРБОЛА (x²/a²-y²/b²=1).
 */

#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>
#include <stdexcept>
using namespace std;

// ─── Абстрактний базовий клас ───────────────────────────────────────────────
class Curve {
public:
    // Повертає y для заданого x (може кидати виключення якщо x поза областю)
    virtual double compute(double x) const = 0;
    virtual string name()           const = 0;
    virtual ~Curve() {}

    void print(double x) const {
        try {
            double y = compute(x);
            cout << name() << "  при x=" << x
                 << "  ->  y = " << fixed << setprecision(4) << y << endl;
        } catch (const exception& e) {
            cout << name() << "  при x=" << x
                 << "  ->  [помилка: " << e.what() << "]" << endl;
        }
    }
};

// ─── Пряма: y = a*x + b ──────────────────────────────────────────────────────
class Line : public Curve {
    double a, b;
public:
    Line(double a, double b) : a(a), b(b) {}
    double compute(double x) const override { return a * x + b; }
    string name() const override {
        return "Пряма       (y=" + to_string(a) + "x+" + to_string(b) + ")";
    }
};

// ─── Еліпс: x²/a²+y²/b²=1  =>  y = b*sqrt(1 - x²/a²) ──────────────────────
class Ellipse : public Curve {
    double a, b; // піввісі
public:
    Ellipse(double a, double b) : a(a), b(b) {}
    double compute(double x) const override {
        double val = 1.0 - (x * x) / (a * a);
        if (val < 0)
            throw out_of_range("|x| > a, точка поза еліпсом");
        return b * sqrt(val);
    }
    string name() const override {
        return "Еліпс       (a=" + to_string(a) + ", b=" + to_string(b) + ")";
    }
};

// ─── Гіпербола: x²/a²-y²/b²=1  =>  y = b*sqrt(x²/a² - 1) ──────────────────
class Hyperbola : public Curve {
    double a, b; // піввісі
public:
    Hyperbola(double a, double b) : a(a), b(b) {}
    double compute(double x) const override {
        double val = (x * x) / (a * a) - 1.0;
        if (val < 0)
            throw out_of_range("|x| < a, точка поза гіперболою");
        return b * sqrt(val);
    }
    string name() const override {
        return "Гіпербола   (a=" + to_string(a) + ", b=" + to_string(b) + ")";
    }
};

int main() {
    cout << "=== Завдання 3: Криві — обчислення y(x) ===" << endl << endl;

    const int N = 3;
    Curve* curves[N] = {
        new Line(2, 3),
        new Ellipse(5, 3),
        new Hyperbola(3, 4)
    };

    double testX[] = {2.0, 3.0, 5.0};

    cout << "Пізнє зв'язування через масив вказівників:" << endl;
    cout << string(65, '-') << endl;
    for (int i = 0; i < N; ++i)
        curves[i]->print(testX[i]);

    cout << endl;
    // Додаткові тести
    cout << "Тест з некоректним x для еліпса (x=10):" << endl;
    curves[1]->print(10.0);

    for (int i = 0; i < N; ++i)
        delete curves[i];

    return 0;
}
