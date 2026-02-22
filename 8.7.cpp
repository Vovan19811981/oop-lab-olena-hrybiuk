/*
 * Завдання 7
 * Базовий клас ПРАЦІВНИК.
 * Похідні класи: СЛУЖБОВЕЦЬ З ПОГОДИННОЮ ОПЛАТОЮ, СЛУЖБОВЕЦЬ З ОКЛАДОМ.
 * Віртуальна функція: нарахування зарплати.
 */

#include <iostream>
#include <iomanip>
#include <string>
using namespace std;

// ─── Базовий клас ПРАЦІВНИК ──────────────────────────────────────────────────
class Employee {
protected:
    string firstName;
    string lastName;
public:
    Employee(const string& first, const string& last)
        : firstName(first), lastName(last) {}

    virtual double calculatePay() const = 0;
    virtual string type()         const = 0;
    virtual ~Employee() {}

    void display() const {
        cout << "┌─ " << type() << endl;
        cout << "│  Ім'я:        " << firstName << " " << lastName << endl;
        cout << "│  Зарплата:    " << fixed << setprecision(2)
             << calculatePay() << " грн." << endl;
        cout << "+" << string(45, '-') << endl;
    }
};

// ─── Погодинна оплата ─────────────────────────────────────────────────────────
class HourlyEmployee : public Employee {
    double hourlyRate;
    double hoursWorked;
public:
    HourlyEmployee(const string& first, const string& last,
                   double rate, double hours)
        : Employee(first, last), hourlyRate(rate), hoursWorked(hours) {}

    double calculatePay() const override {
        // Понаднормові (більше 40 год) оплачуються в 1.5 рази
        if (hoursWorked <= 40)
            return hourlyRate * hoursWorked;
        return hourlyRate * 40 + hourlyRate * 1.5 * (hoursWorked - 40);
    }
    string type() const override {
        return "Погодинний працівник (" + to_string(hourlyRate) +
               " грн/год, " + to_string((int)hoursWorked) + " год)";
    }
};

// ─── Фіксований оклад ─────────────────────────────────────────────────────────
class SalariedEmployee : public Employee {
    double monthlySalary;
public:
    SalariedEmployee(const string& first, const string& last, double salary)
        : Employee(first, last), monthlySalary(salary) {}

    double calculatePay() const override { return monthlySalary; }
    string type() const override {
        return "Окладний працівник (оклад " + to_string(monthlySalary) + " грн)";
    }
};

int main() {
    cout << "=== Завдання 7: Нарахування зарплати ===" << endl << endl;

    const int N = 3;
    Employee* staff[N] = {
        new HourlyEmployee("Іван", "Коваль", 150.0, 45),
        new HourlyEmployee("Ольга", "Петренко", 120.0, 40),
        new SalariedEmployee("Микола", "Шевченко", 25000.0)
    };

    for (int i = 0; i < N; ++i)
        staff[i]->display();

    for (int i = 0; i < N; ++i)
        delete staff[i];

    return 0;
}
