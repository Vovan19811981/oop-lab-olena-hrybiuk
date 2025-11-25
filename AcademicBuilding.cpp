#include "AcademicBuilding.h"

// Конструктор
AcademicBuilding::AcademicBuilding(std::string addr, int fl, double ar,
                                   int classrooms, std::string faculty, 
                                   bool lib, int labs)
    : Building(addr, fl, ar), 
      numberOfClassrooms(classrooms), 
      facultyName(faculty),
      hasLibrary(lib),
      numberOfLaboratories(labs) {
}

// Деструктор
AcademicBuilding::~AcademicBuilding() {
}

// Виведення інформації про навчальний корпус
void AcademicBuilding::display() const {
    std::cout << "\n=== " << getType() << " ===" << std::endl;
    Building::display();
    std::cout << "Факультет: " << facultyName << std::endl;
    std::cout << "Кількість аудиторій: " << numberOfClassrooms << std::endl;
    std::cout << "Кількість лабораторій: " << numberOfLaboratories << std::endl;
    std::cout << "Наявність бібліотеки: " << (hasLibrary ? "Так" : "Ні") << std::endl;
}

// Отримання типу об'єкта
std::string AcademicBuilding::getType() const {
    return "Навчальний корпус";
}
