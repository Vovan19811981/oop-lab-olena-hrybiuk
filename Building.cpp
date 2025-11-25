#include "Building.h"

// Конструктор
Building::Building(std::string addr, int fl, double ar) 
    : address(addr), floors(fl), area(ar) {
}

// Деструктор
Building::~Building() {
}

// Виведення інформації про будинок
void Building::display() const {
    std::cout << "=== " << getType() << " ===" << std::endl;
    std::cout << "Адреса: " << address << std::endl;
    std::cout << "Кількість поверхів: " << floors << std::endl;
    std::cout << "Площа: " << area << " кв.м" << std::endl;
}

// Отримання типу об'єкта
std::string Building::getType() const {
    return "Будинок";
}
