# Лабораторна робота №14

## Опис завдання

### 1. Клас Employer
- Доповнено функцію `hire()` реакцією на відсутність вакантних посад
- Реалізовано метод `fire(const size_t i)` для звільнення робочого місця

### 2. Утиліта калькулятора exe()
- Виконує операції простого арифметичного калькулятора
- Підтримує регістр-акумулятор
- Операції: `+`, `-`, `*`, `/`, `=` (встановлення), `c` (скидання)

## Структура проекту

```
lab14/
├── lab14.h       # Заголовний файл з класами
├── main.cpp      # Приклади використання
└── README.md     # Документація
```

## Інструкції для Git

### 1. Ініціалізація репозиторію

```bash
# Створити директорію проекту
mkdir lab14
cd lab14

# Ініціалізувати Git репозиторій
git init

# Скопіювати файли в директорію
# (lab14.h, main.cpp, README.md)

# Додати файли до staging
git add .

# Створити перший коміт
git commit -m "Initial commit: Lab 14 - Employer class and Calculator utility"
```

### 2. Створення віддаленого репозиторію

#### На GitHub:
1. Зайдіть на https://github.com
2. Натисніть "New repository"
3. Назвіть репозиторій "lab14" або "cpp-lab14"
4. НЕ створюйте README (він вже є)
5. Створіть репозиторій

```bash
# Підключити віддалений репозиторій
git remote add origin https://github.com/YOUR_USERNAME/lab14.git

# Відправити код на GitHub
git branch -M main
git push -u origin main
```

### 3. Компіляція та запуск

```bash
# Компіляція
g++ -std=c++11 -o lab14 main.cpp

# Запуск
./lab14
```

## Приклади використання

### Employer (Роботодавець)

```cpp
Employer company(3);  // Створити з 3 позиціями

company.hire("Іван Петренко");      // Найняти
company.hire("Марія Коваль");
company.hire("Олексій Сидоренко");

company.hire("Анна Мельник");       // Виведе помилку - немає місць

company.fire(1);                     // Звільнити працівника з індексом 1

company.hire("Анна Мельник");       // Тепер можна найняти
```

### Calculator (Калькулятор)

```cpp
Calculator calc;

calc.exe('=', 10);   // Акумулятор = 10
calc.exe('+', 5);    // Акумулятор = 15
calc.exe('*', 2);    // Акумулятор = 30
calc.exe('-', 5);    // Акумулятор = 25
calc.exe('/', 5);    // Акумулятор = 5

calc.show();         // Вивести значення
calc.exe('c');       // Скинути акумулятор
```

## Основні команди Git

```bash
# Перевірити статус
git status

# Додати зміни
git add .

# Створити коміт
git commit -m "Опис змін"

# Відправити на сервер
git push

# Отримати зміни
git pull

# Переглянути історію
git log

# Створити нову гілку
git branch feature-name
git checkout feature-name
# або
git checkout -b feature-name

# Об'єднати гілки
git checkout main
git merge feature-name
```

## Можливі розширення

1. Додати методи:
   - `Employer::getEmployee(size_t i)` - отримати ім'я працівника
   - `Employer::findEmployee(const string& name)` - знайти індекс

2. Розширити Calculator:
   - Додати операції: `^` (степінь), `%` (остача)
   - Додати історію операцій
   - Додати можливість скасування (undo)

## Автор

[Ваше ім'я]
[Група]
[Дата]
