#include "lab14.h"
#include <iostream>

int main() {
    std::cout << "=== Тестування класу Employer ===" << std::endl;
    
    // Створюємо роботодавця з 3 позиціями
    Employer company(3);
    
    // Найм працівників
    company.hire("Іван Петренко");
    company.hire("Марія Коваль");
    company.hire("Олексій Сидоренко");
    
    company.showEmployees();
    
    // Спроба найняти ще одного (немає місць)
    std::cout << "\nСпроба найняти четвертого працівника:" << std::endl;
    company.hire("Анна Мельник");
    
    // Звільнення працівника
    std::cout << "\nЗвільнення працівника з індексом 1:" << std::endl;
    company.fire(1);
    
    company.showEmployees();
    
    // Тепер можна найняти нового
    std::cout << "\nТепер є вакансія, наймаємо нового працівника:" << std::endl;
    company.hire("Анна Мельник");
    
    company.showEmployees();
    
    std::cout << "\n=== Тестування калькулятора з акумулятором ===" << std::endl;
    
    Calculator calc;
    
    // Приклад операцій додавання
    std::cout << "\nОперації додавання:" << std::endl;
    calc.exe('=', 10);  // Встановити акумулятор = 10
    calc.show();
    
    calc.exe('+', 5);   // 10 + 5 = 15
    calc.show();
    
    calc.exe('+', 3);   // 15 + 3 = 18
    calc.show();
    
    // Приклад операцій з різними операторами
    std::cout << "\nРізні операції:" << std::endl;
    calc.exe('=', 100); // Встановити = 100
    calc.show();
    
    calc.exe('-', 20);  // 100 - 20 = 80
    calc.show();
    
    calc.exe('*', 2);   // 80 * 2 = 160
    calc.show();
    
    calc.exe('/', 4);   // 160 / 4 = 40
    calc.show();
    
    // Скидання акумулятора
    std::cout << "\nСкидання акумулятора:" << std::endl;
    calc.exe('c');
    calc.show();
    
    // Приклад послідовних обчислень
    std::cout << "\nПослідовне обчислення: (5 + 3) * 2 - 4 =" << std::endl;
    calc.exe('=', 5);
    std::cout << "Встановлено 5: ";
    calc.show();
    
    calc.exe('+', 3);
    std::cout << "Додано 3: ";
    calc.show();
    
    calc.exe('*', 2);
    std::cout << "Помножено на 2: ";
    calc.show();
    
    calc.exe('-', 4);
    std::cout << "Віднято 4: ";
    calc.show();
    
    std::cout << "\nРезультат: " << calc.getAccumulator() << std::endl;
    
    return 0;
}
