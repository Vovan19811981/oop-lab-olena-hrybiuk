#ifndef DIGITALDEVICE_H
#define DIGITALDEVICE_H

#include <string>
#include <iostream>

/**
 * Базовий клас "Цифровий пристрій"
 * Представляє загальну інформацію про будь-який цифровий пристрій
 */
class DigitalDevice {
protected:
    std::string brand;      // Бренд
    std::string model;      // Модель
    double price;          // Ціна в грн
    int yearOfManufacture; // Рік випуску

public:
    // Конструктор
    DigitalDevice(std::string br = "", std::string mod = "", 
                  double pr = 0.0, int year = 2024);
    
    // Віртуальний деструктор
    virtual ~DigitalDevice();
    
    // Віртуальні методи
    virtual void display() const;
    virtual std::string getType() const;
    
    // Геттери
    std::string getBrand() const { return brand; }
    std::string getModel() const { return model; }
    double getPrice() const { return price; }
    int getYearOfManufacture() const { return yearOfManufacture; }
};

#endif // DIGITALDEVICE_H
