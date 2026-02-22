/*
 * Завдання 13
 * Абстрактний клас ФІГУРИ НА ЕКРАНІ.
 * Захищені дані: координати центра, кут повороту, масштаб.
 * Методи: зобразити, сховати, повернути, перемістити.
 * Похідні класи: ТРИКУТНИК, ЧОТИРИКУТНИК, БАГАТОКУТНИК.
 */

#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <iomanip>
using namespace std;

// ─── Абстрактний клас ────────────────────────────────────────────────────────
class ScreenFigure {
protected:
    double cx, cy;     // координати центра
    double angle;      // кут повороту (градуси)
    double scale;      // масштабний фактор
    bool   visible;

public:
    ScreenFigure(double cx, double cy, double angle = 0, double scale = 1.0)
        : cx(cx), cy(cy), angle(angle), scale(scale), visible(false) {}

    virtual void draw()   = 0;   // зобразити
    virtual void hide()   = 0;   // сховати
    virtual string name() const = 0;
    virtual ~ScreenFigure() {}

    void rotate(double deg) {
        angle += deg;
        if (angle >= 360) angle -= 360;
        if (angle < 0)    angle += 360;
        cout << name() << ": повернуто на " << deg << "°. Поточний кут: " << angle << "°" << endl;
    }

    void move(double dx, double dy) {
        cx += dx; cy += dy;
        cout << name() << ": переміщено на вектор ("
             << dx << ", " << dy << "). Центр: ("
             << fixed << setprecision(1) << cx << ", " << cy << ")" << endl;
    }

    void status() const {
        cout << "  Центр:   (" << cx << ", " << cy << ")" << endl;
        cout << "  Кут:     " << angle << "°" << endl;
        cout << "  Масштаб: " << scale << endl;
        cout << "  Видимий: " << (visible ? "так" : "ні") << endl;
    }
};

// ─── Трикутник ───────────────────────────────────────────────────────────────
class Triangle : public ScreenFigure {
    double sideA, sideB, sideC;
public:
    Triangle(double cx, double cy, double a, double b, double c, double sc = 1.0)
        : ScreenFigure(cx, cy, 0, sc), sideA(a), sideB(b), sideC(c) {}

    void draw() override {
        visible = true;
        cout << "[" << name() << "] ЗОБРАЖЕНО" << endl;
        cout << "  Сторони: a=" << sideA*scale << " b=" << sideB*scale << " c=" << sideC*scale << endl;
        status();
    }
    void hide() override {
        visible = false;
        cout << "[" << name() << "] ПРИХОВАНО" << endl;
    }
    string name() const override { return "Трикутник"; }
};

// ─── Чотирикутник ────────────────────────────────────────────────────────────
class Quadrilateral : public ScreenFigure {
    double width, height;
public:
    Quadrilateral(double cx, double cy, double w, double h, double sc = 1.0)
        : ScreenFigure(cx, cy, 0, sc), width(w), height(h) {}

    void draw() override {
        visible = true;
        cout << "[" << name() << "] ЗОБРАЖЕНО" << endl;
        cout << "  Розміри: " << width*scale << " x " << height*scale << endl;
        status();
    }
    void hide() override {
        visible = false;
        cout << "[" << name() << "] ПРИХОВАНО" << endl;
    }
    string name() const override { return "Чотирикутник"; }
};

// ─── Багатокутник ────────────────────────────────────────────────────────────
class Polygon : public ScreenFigure {
    int    sides;
    double radius; // радіус описаного кола
public:
    Polygon(double cx, double cy, int sides, double radius, double sc = 1.0)
        : ScreenFigure(cx, cy, 0, sc), sides(sides), radius(radius) {}

    void draw() override {
        visible = true;
        cout << "[" << name() << "] ЗОБРАЖЕНО" << endl;
        cout << "  Кількість сторін: " << sides
             << "  Радіус: " << radius*scale << endl;
        // Виводимо координати вершин
        cout << "  Вершини: ";
        for (int i = 0; i < sides; ++i) {
            double theta = 2 * M_PI * i / sides + angle * M_PI / 180.0;
            double vx = cx + radius * scale * cos(theta);
            double vy = cy + radius * scale * sin(theta);
            cout << "(" << fixed << setprecision(1) << vx << "," << vy << ") ";
        }
        cout << endl;
        status();
    }
    void hide() override {
        visible = false;
        cout << "[" << name() << "] ПРИХОВАНО" << endl;
    }
    string name() const override { return to_string(sides) + "-кутник"; }
};

int main() {
    cout << "=== Завдання 13: Геометричні фігури на екрані ===" << endl << endl;

    const int N = 3;
    ScreenFigure* figures[N] = {
        new Triangle(0, 0, 3, 4, 5),
        new Quadrilateral(10, 5, 6, 4),
        new Polygon(20, 20, 6, 5)     // шестикутник
    };

    for (int i = 0; i < N; ++i) {
        figures[i]->draw();
        cout << endl;
    }

    cout << "--- Операції ---" << endl;
    figures[0]->rotate(45);
    figures[0]->move(3, -2);
    cout << endl;

    figures[2]->rotate(30);
    figures[2]->draw();
    cout << endl;

    cout << "--- Приховуємо фігури ---" << endl;
    for (int i = 0; i < N; ++i)
        figures[i]->hide();

    for (int i = 0; i < N; ++i)
        delete figures[i];

    return 0;
}
