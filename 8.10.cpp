/*
 * Завдання 10
 * Базовий клас БАТЬКО з іменем і віртуальною функцією виведення імені.
 * Похідний клас ДИТИНА — має ім'я та успадковане поле по батькові.
 */

#include <iostream>
#include <string>
using namespace std;

// ─── Базовий клас БАТЬКО ─────────────────────────────────────────────────────
class Father {
protected:
    string name;
public:
    Father(const string& name) : name(name) {}

    virtual void displayName() const {
        cout << "Батько:  " << name << endl;
    }
    virtual string getPatronymic() const {
        // Проста генерація по батькові для демонстрації
        // Якщо ім'я закінчується на голосну — додаємо "йович", інакше "ович"
        if (!name.empty()) {
            char last = name.back();
            if (last == 'a' || last == 'о' || last == 'о')
                return name + "йович";
        }
        return name + "ович";
    }
    virtual ~Father() {}
};

// ─── Похідний клас ДИТИНА ────────────────────────────────────────────────────
class Child : public Father {
    string childName;
    // поле по батькові успадковується (береться з батька)
public:
    // Конструктор приймає ім'я дитини і вказівник на батька
    Child(const string& childName, const Father& father)
        : Father(father.getPatronymic()), childName(childName) {}

    void displayName() const override {
        cout << "Дитина:  " << childName << " " << name << endl;
    }
};

int main() {
    cout << "=== Завдання 10: Батько і Дитина ===" << endl << endl;

    Father* father1 = new Father("Іван");
    Father* father2 = new Father("Микола");

    Father* child1 = new Child("Олег", *father1);
    Father* child2 = new Child("Ганна", *father2);
    Father* child3 = new Child("Марія", *father1);

    const int N = 5;
    Father* people[N] = {father1, father2, child1, child2, child3};

    cout << "Пізнє зв'язування через масив вказівників:" << endl;
    cout << string(40, '-') << endl;
    for (int i = 0; i < N; ++i)
        people[i]->displayName();

    for (int i = 0; i < N; ++i)
        delete people[i];

    return 0;
}
