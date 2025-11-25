#ifndef BUILDING_H
#define BUILDING_H

#include <string>
#include <iostream>

/**
 * Базовий клас "Будинок"
 * Представляє загальну інформацію про будь-який будинок
 */
class Building {
protected:
    std::string address;    // Адреса будинку
    int floors;            // Кількість поверхів
    double area;           // Загальна площа (кв.м)

public:
    // Конструктор
    Building(std::string addr = "", int fl = 0, double ar = 0.0);
    
    // Віртуальний деструктор для правильного видалення похідних класів
    virtual ~Building();
    
    // Віртуальний метод для виведення інформації
    virtual void display() const;
    
    // Віртуальний метод для отримання типу об'єкта
    virtual std::string getType() const;
    
    // Геттери
    std::string getAddress() const { return address; }
    int getFloors() const { return floors; }
    double getArea() const { return area; }
    
    // Сеттери
    void setAddress(const std::string& addr) { address = addr; }
    void setFloors(int fl) { floors = fl; }
    void setArea(double ar) { area = ar; }
};

#endif // BUILDING_H
