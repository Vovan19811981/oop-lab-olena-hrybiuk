#ifndef ACADEMICBUILDING_H
#define ACADEMICBUILDING_H

#include "Building.h"

/**
 * Похідний клас "Навчальний корпус"
 * Розширює клас Building додатковими властивостями навчального закладу
 */
class AcademicBuilding : public Building {
private:
    int numberOfClassrooms;      // Кількість аудиторій
    std::string facultyName;     // Назва факультету
    bool hasLibrary;            // Чи є бібліотека
    int numberOfLaboratories;   // Кількість лабораторій

public:
    // Конструктор
    AcademicBuilding(std::string addr = "", int fl = 0, double ar = 0.0,
                     int classrooms = 0, std::string faculty = "", 
                     bool lib = false, int labs = 0);
    
    // Деструктор
    ~AcademicBuilding();
    
    // Перевизначені методи
    void display() const override;
    std::string getType() const override;
    
    // Геттери
    int getNumberOfClassrooms() const { return numberOfClassrooms; }
    std::string getFacultyName() const { return facultyName; }
    bool getHasLibrary() const { return hasLibrary; }
    int getNumberOfLaboratories() const { return numberOfLaboratories; }
};

#endif // ACADEMICBUILDING_H
