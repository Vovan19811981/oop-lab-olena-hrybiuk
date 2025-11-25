#ifndef SEARCHTEMPLATE_H
#define SEARCHTEMPLATE_H

#include <iostream>

/**
 * Шаблонна функція для пошуку елемента в масиві в заданому діапазоні
 * 
 * @param array - масив для пошуку
 * @param size - розмір масиву
 * @param searchValue - значення для пошуку
 * @param startIndex - початковий індекс діапазону
 * @param endIndex - кінцевий індекс діапазону
 * @return індекс знайденого елемента або -1, якщо не знайдено
 */
template <typename T>
int searchInRange(T* array, int size, T searchValue, int startIndex, int endIndex) {
    // Перевірка коректності діапазону
    if (startIndex < 0 || endIndex >= size || startIndex > endIndex) {
        std::cout << "Помилка: неправильний діапазон пошуку!" << std::endl;
        return -1;
    }
    
    // Пошук елемента
    for (int i = startIndex; i <= endIndex; i++) {
        if (array[i] == searchValue) {
            return i;  // Елемент знайдено
        }
    }
    
    return -1;  // Елемент не знайдено
}

/**
 * Допоміжна функція для виведення результату пошуку
 */
template <typename T>
void printSearchResult(int result, T searchValue, int startIndex, int endIndex) {
    if (result != -1) {
        std::cout << "Елемент " << searchValue 
                  << " знайдено на індексі: " << result << std::endl;
    } else {
        std::cout << "Елемент " << searchValue 
                  << " не знайдено в діапазоні [" << startIndex 
                  << ", " << endIndex << "]" << std::endl;
    }
}

#endif // SEARCHTEMPLATE_H
