/*
 * Завдання 2
 * Абстрактний клас НОРМА.
 * Похідні класи: КОМПЛЕКСНІ ЧИСЛА, ВЕКТОР, МАТРИЦЯ.
 * Норма: |z| для комплексного, sqrt(sum x_i^2) для вектора, max|a_ij| для матриці.
 */

#include <iostream>
#include <cmath>
#include <iomanip>
#include <string>
#include <vector>
using namespace std;

// ─── Абстрактний базовий клас ───────────────────────────────────────────────
class Norm {
public:
    virtual double norm() const = 0;
    virtual string name() const = 0;
    virtual ~Norm() {}

    void print() const {
        cout << name() << "  ||норма|| = " << fixed << setprecision(4) << norm() << endl;
    }
};

// ─── Комплексне число ────────────────────────────────────────────────────────
class Complex : public Norm {
    double re, im;
public:
    Complex(double re, double im) : re(re), im(im) {}
    double norm() const override { return sqrt(re * re + im * im); }
    string name() const override {
        return "Комплексне число (" + to_string(re) + " + " + to_string(im) + "i)";
    }
};

// ─── Вектор ──────────────────────────────────────────────────────────────────
class Vector : public Norm {
    vector<double> elems;
public:
    Vector(initializer_list<double> lst) : elems(lst) {}
    double norm() const override {
        double s = 0;
        for (double x : elems) s += x * x;
        return sqrt(s);
    }
    string name() const override {
        string s = "Вектор [";
        for (size_t i = 0; i < elems.size(); ++i) {
            s += to_string(elems[i]);
            if (i + 1 < elems.size()) s += ", ";
        }
        return s + "]";
    }
};

// ─── Матриця ─────────────────────────────────────────────────────────────────
class Matrix : public Norm {
    vector<vector<double>> data;
    int rows, cols;
public:
    Matrix(initializer_list<initializer_list<double>> lst) {
        rows = 0; cols = 0;
        for (auto& row : lst) {
            data.push_back(vector<double>(row));
            rows++;
            cols = max(cols, (int)row.size());
        }
    }
    double norm() const override {
        double maxVal = 0;
        for (auto& row : data)
            for (double x : row)
                maxVal = max(maxVal, fabs(x));
        return maxVal;
    }
    string name() const override {
        return "Матриця " + to_string(rows) + "x" + to_string(cols);
    }
};

int main() {
    cout << "=== Завдання 2: Норма об'єктів ===" << endl << endl;

    const int N = 3;
    Norm* objects[N] = {
        new Complex(3, 4),
        new Vector({1, 2, 3, 4}),
        new Matrix({{1, -5, 3}, {2, 8, -1}, {-4, 0, 7}})
    };

    cout << "Пізнє зв'язування через масив вказівників:" << endl;
    cout << string(60, '-') << endl;
    for (int i = 0; i < N; ++i)
        objects[i]->print();

    for (int i = 0; i < N; ++i)
        delete objects[i];

    return 0;
}
