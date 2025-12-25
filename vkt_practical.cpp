#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <typeinfo>
using namespace std;

const double PI = 3.14159265358979323846;

// ==================== ЗАВДАННЯ 1: ІЄРАРХІЯ КЛАСІВ УНІВЕРСИТЕТ ====================

class University {
protected:
    string name;
    int foundedYear;
    
public:
    University(string n, int year) : name(n), foundedYear(year) {}
    
    virtual void displayInfo() {
        cout << "=== Університет ===" << endl;
        cout << "Назва: " << name << endl;
        cout << "Рік заснування: " << foundedYear << endl;
    }
    
    virtual ~University() {}
};

class Faculty : public University {
protected:
    string facultyName;
    int studentsCount;
    
public:
    Faculty(string n, int year, string fName, int students) 
        : University(n, year), facultyName(fName), studentsCount(students) {}
    
    void displayInfo() override {
        cout << "=== Факультет ===" << endl;
        cout << "Університет: " << name << endl;
        cout << "Факультет: " << facultyName << endl;
        cout << "Кількість студентів: " << studentsCount << endl;
    }
};

class Department : public Faculty {
private:
    string departmentName;
    int professorsCount;
    
public:
    Department(string n, int year, string fName, int students, 
               string dName, int professors)
        : Faculty(n, year, fName, students), 
          departmentName(dName), professorsCount(professors) {}
    
    void displayInfo() override {
        cout << "=== Кафедра ===" << endl;
        cout << "Університет: " << name << endl;
        cout << "Факультет: " << facultyName << endl;
        cout << "Кафедра: " << departmentName << endl;
        cout << "Кількість студентів на факультеті: " << studentsCount << endl;
        cout << "Кількість викладачів на кафедрі: " << professorsCount << endl;
    }
};

void demonstrateUniversityHierarchy() {
    cout << "\n========== ЗАВДАННЯ 1: ІЄРАРХІЯ УНІВЕРСИТЕТ ===========\n" << endl;
    
    University* objects[4];
    
    objects[0] = new University("КНУ ім. Тараса Шевченка", 1834);
    objects[1] = new Faculty("КНУ ім. Тараса Шевченка", 1834, 
                             "Факультет інформаційних технологій", 1200);
    objects[2] = new Department("КНУ ім. Тараса Шевченка", 1834,
                                "Факультет інформаційних технологій", 1200,
                                "Кафедра системного аналізу", 15);
    objects[3] = new Department("НТУ України", 1898,
                                "Факультет прикладної математики", 800,
                                "Кафедра математичного моделювання", 12);
    
    for(int i = 0; i < 4; i++) {
        objects[i]->displayInfo();
        cout << endl;
    }
    
    for(int i = 0; i < 4; i++) {
        delete objects[i];
    }
}

// ==================== ЗАВДАННЯ 2: ФІГУРИ ОБЕРТАННЯ ====================

class RotationFigure {
protected:
    double radius;
    string figureName;
    
public:
    RotationFigure(double r, string name) : radius(r), figureName(name) {}
    
    virtual double getVolume() = 0;
    virtual double getSurfaceArea() = 0;
    
    virtual void displayInfo() {
        cout << "=== Фігура обертання ===" << endl;
        cout << "Тип: " << figureName << endl;
        cout << "Радіус основи: " << radius << endl;
    }
    
    virtual ~RotationFigure() {}
};

class Cylinder : public RotationFigure {
protected:
    double height;
    
public:
    Cylinder(double r, double h) 
        : RotationFigure(r, "Циліндр"), height(h) {}
    
    double getVolume() override {
        return PI * radius * radius * height;
    }
    
    double getSurfaceArea() override {
        return 2 * PI * radius * (radius + height);
    }
    
    void displayInfo() override {
        cout << "=== Циліндр ===" << endl;
        cout << "Радіус основи: " << radius << endl;
        cout << "Висота: " << height << endl;
        cout << "Об'єм: " << getVolume() << endl;
        cout << "Площа поверхні: " << getSurfaceArea() << endl;
    }
};

class Cone : public RotationFigure {
protected:
    double height;
    double slantHeight;
    
public:
    Cone(double r, double h) 
        : RotationFigure(r, "Конус"), height(h) {
        slantHeight = sqrt(radius * radius + height * height);
    }
    
    double getVolume() override {
        return (PI * radius * radius * height) / 3.0;
    }
    
    double getSurfaceArea() override {
        return PI * radius * (radius + slantHeight);
    }
    
    void displayInfo() override {
        cout << "=== Конус ===" << endl;
        cout << "Радіус основи: " << radius << endl;
        cout << "Висота: " << height << endl;
        cout << "Твірна: " << slantHeight << endl;
        cout << "Об'єм: " << getVolume() << endl;
        cout << "Площа поверхні: " << getSurfaceArea() << endl;
    }
};

class Sphere : public RotationFigure {
public:
    Sphere(double r) : RotationFigure(r, "Сфера") {}
    
    double getVolume() override {
        return (4.0 / 3.0) * PI * radius * radius * radius;
    }
    
    double getSurfaceArea() override {
        return 4 * PI * radius * radius;
    }
    
    void displayInfo() override {
        cout << "=== Сфера ===" << endl;
        cout << "Радіус: " << radius << endl;
        cout << "Об'єм: " << getVolume() << endl;
        cout << "Площа поверхні: " << getSurfaceArea() << endl;
    }
};

void demonstrateRotationFigures() {
    cout << "\n========== ЗАВДАННЯ 2: ФІГУРИ ОБЕРТАННЯ ===========\n" << endl;
    
    RotationFigure* figures[4];
    
    figures[0] = new Cylinder(5.0, 10.0);
    figures[1] = new Cone(4.0, 8.0);
    figures[2] = new Cone(3.0, 6.0);
    figures[3] = new Sphere(7.0);
    
    for(int i = 0; i < 4; i++) {
        figures[i]->displayInfo();
        cout << endl;
    }
    
    for(int i = 0; i < 4; i++) {
        delete figures[i];
    }
}

// ==================== ЗАВДАННЯ 3: ШАБЛОННА ФУНКЦІЯ ПОШУКУ ====================

template <typename T>
vector<T> findInRange(T* array, int size, T minValue, T maxValue) {
    vector<T> result;
    
    for(int i = 0; i < size; i++) {
        if(array[i] >= minValue && array[i] <= maxValue) {
            result.push_back(array[i]);
        }
    }
    
    return result;
}

template <typename T>
void displaySearchResults(const vector<T>& results, T minValue, T maxValue) {
    cout << "Пошук елементів в діапазоні [" << minValue << ", " << maxValue << "]" << endl;
    
    if(results.empty()) {
        cout << "Елементів не знайдено" << endl;
    } else {
        cout << "Знайдено елементів: " << results.size() << endl;
        cout << "Елементи: ";
        for(const T& val : results) {
            cout << val << " ";
        }
        cout << endl;
    }
}

void demonstrateTemplateSearch() {
    cout << "\n========== ЗАВДАННЯ 3: ШАБЛОННА ФУНКЦІЯ ПОШУКУ ===========\n" << endl;
    
    cout << "--- Тест 1: Цілі числа ---" << endl;
    int intArray[] = {5, 12, 3, 18, 7, 25, 9, 14, 2, 20};
    int intSize = sizeof(intArray) / sizeof(intArray[0]);
    
    cout << "Масив: ";
    for(int i = 0; i < intSize; i++) {
        cout << intArray[i] << " ";
    }
    cout << endl;
    
    vector<int> intResults1 = findInRange(intArray, intSize, 10, 20);
    displaySearchResults(intResults1, 10, 20);
    cout << endl;
    
    vector<int> intResults2 = findInRange(intArray, intSize, 1, 5);
    displaySearchResults(intResults2, 1, 5);
    cout << endl;
    
    cout << "--- Тест 2: Дійсні числа ---" << endl;
    double doubleArray[] = {3.14, 2.71, 1.41, 5.67, 8.23, 4.89, 6.28};
    int doubleSize = sizeof(doubleArray) / sizeof(doubleArray[0]);
    
    cout << "Масив: ";
    for(int i = 0; i < doubleSize; i++) {
        cout << doubleArray[i] << " ";
    }
    cout << endl;
    
    vector<double> doubleResults = findInRange(doubleArray, doubleSize, 3.0, 6.0);
    displaySearchResults(doubleResults, 3.0, 6.0);
    cout << endl;
    
    cout << "--- Тест 3: Символи ---" << endl;
    char charArray[] = {'a', 'z', 'm', 'c', 'x', 'f', 'k', 'p'};
    int charSize = sizeof(charArray) / sizeof(charArray[0]);
    
    cout << "Масив: ";
    for(int i = 0; i < charSize; i++) {
        cout << charArray[i] << " ";
    }
    cout << endl;
    
    vector<char> charResults = findInRange(charArray, charSize, 'f', 'p');
    displaySearchResults(charResults, 'f', 'p');
    cout << endl;
}

// ==================== ЗАВДАННЯ 4: ШАБЛОН КЛАСУ ДЛЯ ПАРИ ЧИСЕЛ ====================

template <typename T1, typename T2>
class NumberPair {
private:
    T1 first;
    T2 second;
    
public:
    NumberPair() : first(T1()), second(T2()) {}
    NumberPair(T1 f, T2 s) : first(f), second(s) {}
    
    T1 getFirst() const { return first; }
    T2 getSecond() const { return second; }
    
    void setFirst(T1 f) { first = f; }
    void setSecond(T2 s) { second = s; }
    
    void swap() {
        T1 temp = first;
        first = static_cast<T1>(second);
        second = static_cast<T2>(temp);
    }
    
    auto getSum() const -> decltype(first + second) {
        return first + second;
    }
    
    auto getProduct() const -> decltype(first * second) {
        return first * second;
    }
    
    bool isFirstGreater() const { return first > second; }
    bool isSecondGreater() const { return second > first; }
    bool areEqual() const { return first == second; }
    
    void display() const {
        cout << "Пара: (" << first << ", " << second << ")" << endl;
        cout << "Тип першого: " << typeid(T1).name() << endl;
        cout << "Тип другого: " << typeid(T2).name() << endl;
    }
    
    void displayDetailed() const {
        display();
        cout << "Сума: " << getSum() << endl;
        cout << "Добуток: " << getProduct() << endl;
        
        if(isFirstGreater()) {
            cout << "Перше число більше" << endl;
        } else if(isSecondGreater()) {
            cout << "Друге число більше" << endl;
        } else {
            cout << "Числа рівні" << endl;
        }
    }
};

void demonstrateNumberPair() {
    cout << "\n========== ЗАВДАННЯ 4: ШАБЛОН КЛАСУ ДЛЯ ПАРИ ЧИСЕЛ ===========\n" << endl;
    
    cout << "--- Тест 1: int і int ---" << endl;
    NumberPair<int, int> pair1(10, 20);
    pair1.displayDetailed();
    cout << endl;
    
    cout << "--- Тест 2: int і double ---" << endl;
    NumberPair<int, double> pair2(15, 7.5);
    pair2.displayDetailed();
    cout << endl;
    
    cout << "--- Тест 3: double і double ---" << endl;
    NumberPair<double, double> pair3(3.14, 2.71);
    pair3.displayDetailed();
    cout << endl;
    
    cout << "--- Тест 4: float і int ---" << endl;
    NumberPair<float, int> pair4(5.5f, 11);
    pair4.displayDetailed();
    cout << endl;
    
    cout << "--- Тест 5: Модифікація значень ---" << endl;
    NumberPair<int, int> pair5(100, 200);
    cout << "До модифікації:" << endl;
    pair5.display();
    
    pair5.setFirst(300);
    pair5.setSecond(150);
    cout << "\nПісля модифікації:" << endl;
    pair5.displayDetailed();
    cout << endl;
    
    cout << "--- Тест 6: Обмін значень ---" << endl;
    NumberPair<int, int> pair6(50, 75);
    cout << "До обміну:" << endl;
    pair6.display();
    
    pair6.swap();
    cout << "\nПісля обміну:" << endl;
    pair6.display();
    cout << endl;
}

// ==================== ГОЛОВНА ФУНКЦІЯ ====================

int main() {
    cout << "╔════════════════════════════════════════════════════════╗" << endl;
    cout << "║     ПРАКТИЧНА ЧАСТИНА ВКТ - РІШЕННЯ ВСІХ ЗАВДАНЬ      ║" << endl;
    cout << "║              (Максимальна складність - 4 бали)         ║" << endl;
    cout << "╚════════════════════════════════════════════════════════╝" << endl;
    
    demonstrateUniversityHierarchy();
    demonstrateRotationFigures();
    demonstrateTemplateSearch();
    demonstrateNumberPair();
    
    cout << "\n╔════════════════════════════════════════════════════════╗" << endl;
    cout << "║           ВСІ ЗАВДАННЯ ВИКОНАНО УСПІШНО!              ║" << endl;
    cout << "╚════════════════════════════════════════════════════════╝" << endl;
    
    return 0;
}
