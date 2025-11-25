#include "DigitalDevice.h"

// Конструктор
DigitalDevice::DigitalDevice(std::string br, std::string mod, double pr, int year)
    : brand(br), model(mod), price(pr), yearOfManufacture(year) {
}

// Деструктор
DigitalDevice::~DigitalDevice() {
}

// Виведення інформації про пристрій
void DigitalDevice::display() const {
    std::cout << "=== " << getType() << " ===" << std::endl;
    std::cout << "Бренд: " << brand << std::endl;
    std::cout << "Модель: " << model << std::endl;
    std::cout << "Ціна: " << price << " грн" << std::endl;
    std::cout << "Рік випуску: " << yearOfManufacture << std::endl;
}

// Отримання типу об'єкта
std::string DigitalDevice::getType() const {
    return "Цифровий пристрій";
}
