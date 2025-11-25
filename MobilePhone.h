#ifndef MOBILEPHONE_H
#define MOBILEPHONE_H

#include "DigitalDevice.h"

/**
 * Похідний клас "Мобільний телефон"
 * Розширює клас DigitalDevice специфічними властивостями смартфона
 */
class MobilePhone : public DigitalDevice {
private:
    std::string operatingSystem;  // Операційна система
    int batteryCapacity;         // Ємність батареї (мАг)
    double screenSize;           // Розмір екрану (дюйми)
    int cameraMP;               // Камера (мегапікселі)

public:
    // Конструктор
    MobilePhone(std::string br = "", std::string mod = "", 
                double pr = 0.0, int year = 2024,
                std::string os = "", int battery = 0, 
                double screen = 0.0, int camera = 0);
    
    // Деструктор
    ~MobilePhone();
    
    // Перевизначені методи
    void display() const override;
    std::string getType() const override;
    
    // Геттери
    std::string getOperatingSystem() const { return operatingSystem; }
    int getBatteryCapacity() const { return batteryCapacity; }
    double getScreenSize() const { return screenSize; }
    int getCameraMP() const { return cameraMP; }
};

#endif // MOBILEPHONE_H
