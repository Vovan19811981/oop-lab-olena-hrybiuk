#ifndef LAB14_H
#define LAB14_H

#include <iostream>
#include <vector>
#include <string>
#include <stdexcept>

// Клас для роботодавця
class Employer {
private:
    std::vector<std::string> employees;
    size_t maxPositions;

public:
    Employer(size_t maxPos) : maxPositions(maxPos) {
        employees.reserve(maxPositions);
    }

    // Метод найму працівника
    void hire(const std::string& name) {
        if (employees.size() >= maxPositions) {
            std::cout << "Помилка: немає вакантних посад!" << std::endl;
            return;
        }
        employees.push_back(name);
        std::cout << "Найнято: " << name << std::endl;
    }

    // Метод звільнення працівника за індексом
    void fire(const size_t i) {
        if (i >= employees.size()) {
            std::cout << "Помилка: неправильний індекс працівника!" << std::endl;
            return;
        }
        std::cout << "Звільнено: " << employees[i] << std::endl;
        employees.erase(employees.begin() + i);
    }

    // Метод для виведення списку працівників
    void showEmployees() const {
        std::cout << "Список працівників (" << employees.size() << "/" << maxPositions << "):" << std::endl;
        for (size_t i = 0; i < employees.size(); ++i) {
            std::cout << "  [" << i << "] " << employees[i] << std::endl;
        }
    }

    size_t getEmployeeCount() const {
        return employees.size();
    }
};

// Утиліта калькулятора з акумулятором
class Calculator {
private:
    double accumulator;

public:
    Calculator() : accumulator(0.0) {}

    // Функція exe для виконання операцій
    double exe(char operation, double operand = 0.0) {
        switch (operation) {
            case '+':
                accumulator += operand;
                break;
            case '-':
                accumulator -= operand;
                break;
            case '*':
                accumulator *= operand;
                break;
            case '/':
                if (operand == 0) {
                    std::cout << "Помилка: ділення на нуль!" << std::endl;
                    return accumulator;
                }
                accumulator /= operand;
                break;
            case '=':
                accumulator = operand;
                break;
            case 'c':
            case 'C':
                accumulator = 0.0;
                std::cout << "Акумулятор скинуто" << std::endl;
                break;
            default:
                std::cout << "Помилка: невідома операція '" << operation << "'" << std::endl;
                break;
        }
        return accumulator;
    }

    // Отримати поточне значення акумулятора
    double getAccumulator() const {
        return accumulator;
    }

    // Вивести поточне значення
    void show() const {
        std::cout << "Акумулятор: " << accumulator << std::endl;
    }
};

#endif // LAB14_H
