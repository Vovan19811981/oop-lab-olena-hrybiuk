#ifndef PAIRTEMPLATE_H
#define PAIRTEMPLATE_H

#include <iostream>

/**
 * Шаблон класу для зберігання пари чисел різних типів
 * 
 * @tparam T1 - тип першого числа
 * @tparam T2 - тип другого числа
 */
template <typename T1, typename T2>
class NumberPair {
private:
    T1 first;   // Перше число
    T2 second;  // Друге число

public:
    // Конструктор за замовчуванням
    NumberPair() : first(T1()), second(T2()) {}
    
    // Конструктор з параметрами
    NumberPair(T1 f, T2 s) : first(f), second(s) {}
    
    // Сеттери
    void setFirst(T1 f) { first = f; }
    void setSecond(T2 s) { second = s; }
    
    // Геттери
    T1 getFirst() const { return first; }
    T2 getSecond() const { return second; }
    
    // Виведення пари
    void display() const {
        std::cout << "(" << first << ", " << second << ")";
    }
    
    // Перевантаження оператора + для додавання пар
    NumberPair operator+(const NumberPair& other) const {
        return NumberPair(first + other.first, second + other.second);
    }
    
    // Перевантаження оператора - для віднімання пар
    NumberPair operator-(const NumberPair& other) const {
        return NumberPair(first - other.first, second - other.second);
    }
    
    // Перевантаження оператора * для множення пар
    NumberPair operator*(const NumberPair& other) const {
        return NumberPair(first * other.first, second * other.second);
    }
    
    // Порівняння пар (за сумою елементів)
    bool operator==(const NumberPair& other) const {
        return (first + second) == (other.first + other.second);
    }
    
    bool operator<(const NumberPair& other) const {
        return (first + second) < (other.first + other.second);
    }
    
    // Обчислення суми елементів пари
    auto sum() const -> decltype(first + second) {
        return first + second;
    }
};

#endif // PAIRTEMPLATE_H
