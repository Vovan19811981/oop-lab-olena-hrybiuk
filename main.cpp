#include <iostream>
#include <iomanip>
#include "Building.h"
#include "AcademicBuilding.h"
#include "DigitalDevice.h"
#include "MobilePhone.h"
#include "SearchTemplate.h"
#include "PairTemplate.h"

using namespace std;

void printSeparator() {
    cout << "\n" << string(70, '=') << "\n" << endl;
}

int main() {
    cout << "\n================================================" << endl;
    cout << "     ЛАБОРАТОРНА РОБОТА З ООП" << endl;
    cout << "     Студент: Олена Гриб'юк" << endl;
    cout << "     Група: aІк-43, aІк-44" << endl;
    cout << "================================================\n" << endl;
    
    // ============================================================
    // ЧАСТИНА 1: Ієрархія класів "Будинок" – "Навчальний корпус"
    // ============================================================
    
    cout << "\n--- ЧАСТИНА 1: Ієрархія класів 'Будинок' ---\n" << endl;
    
    const int BUILDING_COUNT = 5;
    Building* buildings[BUILDING_COUNT];
    
    // Створення масиву покажчиків на об'єкти різних типів
    buildings[0] = new Building("вул. Шевченка, 15", 5, 2500.0);
    buildings[1] = new AcademicBuilding("вул. Карпінського, 15", 4, 3200.0, 
                                        35, "Комп'ютерних наук", true, 12);
    buildings[2] = new Building("вул. Лесі Українки, 8", 3, 1800.0);
    buildings[3] = new AcademicBuilding("проспект Незалежності, 42", 5, 4500.0,
                                        50, "Інженерії та технологій", true, 18);
    buildings[4] = new AcademicBuilding("вул. Бандери, 28", 3, 2200.0,
                                        20, "Економіки та менеджменту", false, 5);
    
    cout << "Створено " << BUILDING_COUNT << " об'єктів:\n" << endl;
    
    // Виведення інформації про всі об'єкти через поліморфізм
    for (int i = 0; i < BUILDING_COUNT; i++) {
        cout << "Об'єкт #" << (i + 1) << ":" << endl;
        buildings[i]->display();
        cout << endl;
    }
    
    // ============================================================
    // ЧАСТИНА 2: Ієрархія класів "Цифровий пристрій"
    // ============================================================
    
    printSeparator();
    cout << "\n--- ЧАСТИНА 2: Ієрархія класів 'Цифровий пристрій' ---\n" << endl;
    
    const int DEVICE_COUNT = 6;
    DigitalDevice* devices[DEVICE_COUNT];
    
    // Створення масиву покажчиків на об'єкти різних типів
    devices[0] = new DigitalDevice("Dell", "Laptop-XPS15", 35000.0, 2023);
    devices[1] = new MobilePhone("Samsung", "Galaxy S23 Ultra", 32000.0, 2023,
                                 "Android 13", 5000, 6.8, 200);
    devices[2] = new MobilePhone("Apple", "iPhone 15 Pro", 42000.0, 2023,
                                 "iOS 17", 3274, 6.1, 48);
    devices[3] = new DigitalDevice("Sony", "PlayStation 5", 18000.0, 2022);
    devices[4] = new MobilePhone("Xiaomi", "Redmi Note 13 Pro", 12000.0, 2024,
                                 "Android 14", 5000, 6.67, 200);
    devices[5] = new MobilePhone("Google", "Pixel 8", 28000.0, 2023,
                                 "Android 14", 4575, 6.2, 50);
    
    cout << "Створено " << DEVICE_COUNT << " об'єктів:\n" << endl;
    
    // Виведення інформації про всі об'єкти через поліморфізм
    for (int i = 0; i < DEVICE_COUNT; i++) {
        cout << "Пристрій #" << (i + 1) << ":" << endl;
        devices[i]->display();
        cout << endl;
    }
    
    // ============================================================
    // ЧАСТИНА 3: Шаблонна функція пошуку в масиві
    // ============================================================
    
    printSeparator();
    cout << "\n--- ЧАСТИНА 3: Шаблонна функція пошуку ---\n" << endl;
    
    // Тест 1: Пошук цілих чисел
    cout << "Тест 1: Пошук цілих чисел" << endl;
    int numbers[] = {10, 25, 33, 42, 58, 67, 75, 89, 91, 100};
    int numbersSize = 10;
    
    cout << "Масив: ";
    for (int i = 0; i < numbersSize; i++) {
        cout << numbers[i];
        if (i < numbersSize - 1) cout << ", ";
    }
    cout << endl;
    
    cout << "\nПошук числа 58 в діапазоні [2, 7]:" << endl;
    int result1 = searchInRange(numbers, numbersSize, 58, 2, 7);
    printSearchResult(result1, 58, 2, 7);
    
    cout << "\nПошук числа 100 в діапазоні [0, 5]:" << endl;
    int result2 = searchInRange(numbers, numbersSize, 100, 0, 5);
    printSearchResult(result2, 100, 0, 5);
    
    // Тест 2: Пошук дробових чисел
    cout << "\n\nТест 2: Пошук дробових чисел" << endl;
    double decimals[] = {1.5, 2.7, 3.14, 4.8, 5.9, 6.2};
    int decimalsSize = 6;
    
    cout << "Масив: ";
    for (int i = 0; i < decimalsSize; i++) {
        cout << decimals[i];
        if (i < decimalsSize - 1) cout << ", ";
    }
    cout << endl;
    
    cout << "\nПошук числа 3.14 в діапазоні [1, 4]:" << endl;
    int result3 = searchInRange(decimals, decimalsSize, 3.14, 1, 4);
    printSearchResult(result3, 3.14, 1, 4);
    
    // ============================================================
    // ЧАСТИНА 4: Шаблон класу для пари чисел
    // ============================================================
    
    printSeparator();
    cout << "\n--- ЧАСТИНА 4: Шаблон класу для пари чисел ---\n" << endl;
    
    cout << "Створення пар різних типів:\n" << endl;
    
    // Пара int-int
    cout << "1. Пара цілих чисел: ";
    NumberPair<int, int> intPair(10, 20);
    intPair.display();
    cout << " | Сума: " << intPair.sum() << endl;
    
    // Пара double-float
    cout << "2. Пара дробових чисел: ";
    NumberPair<double, float> mixedPair(3.14, 2.71f);
    mixedPair.display();
    cout << " | Сума: " << mixedPair.sum() << endl;
    
    // Пара int-double
    cout << "3. Змішана пара: ";
    NumberPair<int, double> anotherPair(5, 7.5);
    anotherPair.display();
    cout << " | Сума: " << anotherPair.sum() << endl;
    
    // Операції з парами
    cout << "\n\nАрифметичні операції:\n" << endl;
    
    NumberPair<int, int> pair1(10, 20);
    NumberPair<int, int> pair2(5, 15);
    
    cout << "Пара 1: ";
    pair1.display();
    cout << endl;
    
    cout << "Пара 2: ";
    pair2.display();
    cout << endl;
    
    cout << "\nДодавання: ";
    pair1.display();
    cout << " + ";
    pair2.display();
    cout << " = ";
    NumberPair<int, int> sumPair = pair1 + pair2;
    sumPair.display();
    cout << endl;
    
    cout << "Віднімання: ";
    pair1.display();
    cout << " - ";
    pair2.display();
    cout << " = ";
    NumberPair<int, int> diffPair = pair1 - pair2;
    diffPair.display();
    cout << endl;
    
    cout << "Множення: ";
    pair1.display();
    cout << " * ";
    pair2.display();
    cout << " = ";
    NumberPair<int, int> multPair = pair1 * pair2;
    multPair.display();
    cout << endl;
    
    // ============================================================
    // Очищення пам'яті
    // ============================================================
    
    printSeparator();
    cout << "Очищення пам'яті...\n" << endl;
    
    for (int i = 0; i < BUILDING_COUNT; i++) {
        delete buildings[i];
    }
    
    for (int i = 0; i < DEVICE_COUNT; i++) {
        delete devices[i];
    }
    
    cout << "\n================================================" << endl;
    cout << "     ПРОГРАМА УСПІШНО ЗАВЕРШЕНА" << endl;
    cout << "     Всі завдання виконано!" << endl;
    cout << "================================================\n" << endl;
    
    return 0;
}
