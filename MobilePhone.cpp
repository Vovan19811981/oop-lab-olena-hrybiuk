#include "MobilePhone.h"

// Конструктор
MobilePhone::MobilePhone(std::string br, std::string mod, double pr, int year,
                         std::string os, int battery, double screen, int camera)
    : DigitalDevice(br, mod, pr, year),
      operatingSystem(os),
      batteryCapacity(battery),
      screenSize(screen),
      cameraMP(camera) {
}

// Деструктор
MobilePhone::~MobilePhone() {
}

// Виведення інформації про мобільний телефон
void MobilePhone::display() const {
    std::cout << "\n=== " << getType() << " ===" << std::endl;
    DigitalDevice::display();
    std::cout << "Операційна система: " << operatingSystem << std::endl;
    std::cout << "Батарея: " << batteryCapacity << " мАг" << std::endl;
    std::cout << "Екран: " << screenSize << " дюймів" << std::endl;
    std::cout << "Камера: " << cameraMP << " МП" << std::endl;
}

// Отримання типу об'єкта
std::string MobilePhone::getType() const {
    return "Мобільний телефон";
}
