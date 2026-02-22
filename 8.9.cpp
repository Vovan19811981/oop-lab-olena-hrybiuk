/*
 * Завдання 9
 * Абстрактний клас ССАВЦІ.
 * Похідні класи: ТВАРИНИ та ЛЮДИ.
 * У тварин: КОНІ та КОРОВИ.
 * Віртуальні функції опису кожного класу.
 */

#include <iostream>
#include <string>
using namespace std;

// ─── Абстрактний клас ССАВЦІ ─────────────────────────────────────────────────
class Mammal {
public:
    virtual void describe() const = 0;
    virtual string category() const = 0;
    virtual ~Mammal() {}
};

// ─── ЛЮДИ ────────────────────────────────────────────────────────────────────
class Human : public Mammal {
    string fullName;
    int    age;
    string profession;
public:
    Human(const string& name, int age, const string& prof)
        : fullName(name), age(age), profession(prof) {}

    void describe() const override {
        cout << "[" << category() << "]" << endl;
        cout << "  Ім'я:     " << fullName << endl;
        cout << "  Вік:      " << age << " р." << endl;
        cout << "  Професія: " << profession << endl;
    }
    string category() const override { return "ЛЮДИНА"; }
};

// ─── Базовий клас ТВАРИНА ────────────────────────────────────────────────────
class Animal : public Mammal {
protected:
    string animalName;
    double weight; // кг
public:
    Animal(const string& name, double weight)
        : animalName(name), weight(weight) {}
};

// ─── КІНЬ ────────────────────────────────────────────────────────────────────
class Horse : public Animal {
    string breed;
public:
    Horse(const string& name, double weight, const string& breed)
        : Animal(name, weight), breed(breed) {}

    void describe() const override {
        cout << "[" << category() << "]" << endl;
        cout << "  Кличка: " << animalName << endl;
        cout << "  Порода: " << breed << endl;
        cout << "  Вага:   " << weight << " кг" << endl;
    }
    string category() const override { return "КІНЬ"; }
};

// ─── КОРОВА ──────────────────────────────────────────────────────────────────
class Cow : public Animal {
    double milkPerDay; // літрів на день
public:
    Cow(const string& name, double weight, double milk)
        : Animal(name, weight), milkPerDay(milk) {}

    void describe() const override {
        cout << "[" << category() << "]" << endl;
        cout << "  Кличка:    " << animalName << endl;
        cout << "  Вага:      " << weight << " кг" << endl;
        cout << "  Надій/день:" << milkPerDay << " л" << endl;
    }
    string category() const override { return "КОРОВА"; }
};

int main() {
    cout << "=== Завдання 9: Ссавці ===" << endl << endl;

    const int N = 4;
    Mammal* mammals[N] = {
        new Human("Іван Петрович Коваль", 35, "Програміст"),
        new Human("Марія Іванівна Лисенко", 28, "Лікар"),
        new Horse("Зефір", 520, "Арабська чистокровна"),
        new Cow("Ромашка", 450, 18.5)
    };

    for (int i = 0; i < N; ++i) {
        mammals[i]->describe();
        cout << string(35, '-') << endl;
    }

    for (int i = 0; i < N; ++i)
        delete mammals[i];

    return 0;
}
