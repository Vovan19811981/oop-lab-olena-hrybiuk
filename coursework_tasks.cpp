/*
 * Курсова робота з ООП
 * Додаткові завдання до курсової роботи
 *
 * Завдання 1: Функція power() — піднесення числа в степінь
 * Завдання 2: Функція zeroSmaller() — обнулення меншого аргументу
 * Завдання 3: Функція maxDistance() — найбільша відстань типу Distance
 *
 * Компіляція: g++ -std=c++11 -o tasks tasks.cpp
 */

#include <iostream>
#include <cmath>
using namespace std;

// ============================================================
// ЗАВДАННЯ 1
// Функція power() — піднесення числа n у степінь p.
// Параметр p має значення за замовчуванням = 2 (квадрат).
// ============================================================

double power(double n, int p = 2) {
    if (p == 0) return 1.0;

    double result = 1.0;

    if (p > 0) {
        for (int i = 0; i < p; ++i)
            result *= n;
    } else {
        // від'ємний степінь: n^(-p) = 1 / n^p
        for (int i = 0; i < -p; ++i)
            result *= n;
        result = 1.0 / result;
    }

    return result;
}

// ============================================================
// ЗАВДАННЯ 2
// Функція zeroSmaller() — присвоює меншому з двох аргументів 0.
// Аргументи передаються за посиланням.
// ============================================================

void zeroSmaller(int& a, int& b) {
    if (a < b)
        a = 0;
    else if (b < a)
        b = 0;
    else {
        // рівні — обнуляємо обидва
        a = 0;
        b = 0;
    }
}

// ============================================================
// ЗАВДАННЯ 3
// Клас Distance — зберігає відстань у футах та дюймах.
// Функція maxDistance() — повертає більшу з двох відстаней.
// ============================================================

struct Distance {
    int    feet;    // фути
    double inches;  // дюйми (0..11.99)

    Distance(int f = 0, double i = 0.0) : feet(f), inches(i) {}

    // Конвертація в дюйми для порівняння
    double toInches() const {
        return feet * 12.0 + inches;
    }

    void display() const {
        cout << feet << " фут(и) " << inches << " дюйм(и)";
    }
};

Distance maxDistance(Distance d1, Distance d2) {
    return (d1.toInches() >= d2.toInches()) ? d1 : d2;
}

// ============================================================
// ГОЛОВНА ПРОГРАМА
// ============================================================

int main() {
    cout << "╔══════════════════════════════════════════════╗" << endl;
    cout << "║   Курсова робота з ООП — Додаткові завдання  ║" << endl;
    cout << "╚══════════════════════════════════════════════╝" << endl;

    // ── Завдання 1: power() ────────────────────────────────
    cout << "\n=== Завдання 1: Функція power() ===" << endl;

    double n;
    int    p;

    cout << "Введіть число n: ";
    cin >> n;
    cout << "Введіть степінь p (Enter = піднести в квадрат, введіть 0 щоб пропустити): ";

    // Перевіряємо чи є ввід (демонстрація значення за замовчуванням)
    char choice;
    cout << "Використати значення p за замовчуванням (2)? (y/n): ";
    cin >> choice;

    double result;
    if (choice == 'y' || choice == 'Y') {
        result = power(n);   // p = 2 за замовчуванням
        cout << n << " ^ 2 (за замовчуванням) = " << result << endl;
    } else {
        cout << "Введіть p: ";
        cin >> p;
        result = power(n, p);
        cout << n << " ^ " << p << " = " << result << endl;
    }

    // Демонстрація різних викликів
    cout << "\nДемонстрація power():" << endl;
    cout << "  power(3.0)      = " << power(3.0)       << "  (3^2, p за замовч.)" << endl;
    cout << "  power(2.0, 10)  = " << power(2.0, 10)   << "  (2^10)" << endl;
    cout << "  power(5.0, 3)   = " << power(5.0, 3)    << "  (5^3)" << endl;
    cout << "  power(2.0, -3)  = " << power(2.0, -3)   << "  (2^-3 = 1/8)" << endl;
    cout << "  power(7.0, 0)   = " << power(7.0, 0)    << "  (будь-яке число^0 = 1)" << endl;

    // ── Завдання 2: zeroSmaller() ──────────────────────────
    cout << "\n=== Завдання 2: Функція zeroSmaller() ===" << endl;

    int a, b;
    cout << "Введіть перше ціле число a: ";
    cin >> a;
    cout << "Введіть друге ціле число b: ";
    cin >> b;

    cout << "До виклику:  a = " << a << ", b = " << b << endl;
    zeroSmaller(a, b);
    cout << "Після виклику: a = " << a << ", b = " << b << endl;

    // Демонстрація різних випадків
    cout << "\nДемонстрація zeroSmaller():" << endl;

    int x1 = 5, y1 = 10;
    cout << "  До:    a=" << x1 << ", b=" << y1;
    zeroSmaller(x1, y1);
    cout << "  ->  Після: a=" << x1 << ", b=" << y1 << "  (менший a=5 -> 0)" << endl;

    int x2 = 8, y2 = 3;
    cout << "  До:    a=" << x2 << ", b=" << y2;
    zeroSmaller(x2, y2);
    cout << "  ->  Після: a=" << x2 << ", b=" << y2 << "  (менший b=3 -> 0)" << endl;

    int x3 = 7, y3 = 7;
    cout << "  До:    a=" << x3 << ", b=" << y3;
    zeroSmaller(x3, y3);
    cout << "  ->  Після: a=" << x3 << ", b=" << y3 << "  (рівні -> обидва 0)" << endl;

    // ── Завдання 3: maxDistance() ──────────────────────────
    cout << "\n=== Завдання 3: Функція maxDistance() ===" << endl;

    int    f1, f2;
    double i1, i2;

    cout << "Введіть першу відстань:" << endl;
    cout << "  Фути: ";   cin >> f1;
    cout << "  Дюйми: ";  cin >> i1;

    cout << "Введіть другу відстань:" << endl;
    cout << "  Фути: ";   cin >> f2;
    cout << "  Дюйми: ";  cin >> i2;

    Distance d1(f1, i1);
    Distance d2(f2, i2);
    Distance dMax = maxDistance(d1, d2);

    cout << "Перша відстань:  "; d1.display(); cout << endl;
    cout << "Друга відстань:  "; d2.display(); cout << endl;
    cout << "Найбільша:       "; dMax.display(); cout << endl;

    // Демонстрація різних випадків
    cout << "\nДемонстрація maxDistance():" << endl;

    Distance da(5, 6.5), db(3, 11.9);
    Distance dm = maxDistance(da, db);
    cout << "  d1 = "; da.display();
    cout << "  |  d2 = "; db.display();
    cout << "  ->  max = "; dm.display(); cout << endl;

    Distance dc(2, 0.0), dd(2, 0.0);
    Distance dm2 = maxDistance(dc, dd);
    cout << "  d1 = "; dc.display();
    cout << "  |  d2 = "; dd.display();
    cout << "  ->  max = "; dm2.display(); cout << " (рівні)" << endl;

    cout << "\n=== Завершено ===" << endl;
    return 0;
}
