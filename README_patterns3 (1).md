# Патерни проєктування: Декоратор, Спостерігач, Відвідувач — Контрольні запитання

> Відповіді на контрольні завдання з теми **Decorator, Observer, Visitor**

---

## Зміст

1. [У чому рекурсивність декорування?](#1-у-чому-рекурсивність-декорування)
2. [Як реалізувати патерн Декоратор на C++?](#2-як-реалізувати-патерн-декоратор-на-c)
3. [Відмінності реалізації декораторів на Java від C++](#3-відмінності-реалізації-декораторів-на-java-від-c)
4. [Навіщо одній частині програми спостерігати за іншою?](#4-навіщо-одній-частині-програми-спостерігати-за-іншою)
5. [Як Observer забезпечує незалежність об'єкта від спостерігачів?](#5-як-observer-забезпечує-незалежність-обєкта-від-спостерігачів)
6. [Чи може конкретний спостерігач не залежати від конкретного об'єкта?](#6-чи-може-конкретний-спостерігач-не-залежати-від-конкретного-обєкта)
7. [Яку інформацію передавати через параметри методу Update?](#7-яку-інформацію-передавати-через-параметри-методу-update)
8. [Основна ідея патерну Visitor](#8-основна-ідея-патерну-visitor)
9. [Скільки методів має бути в інтерфейсі відвідувача?](#9-скільки-методів-має-бути-в-інтерфейсі-відвідувача)
10. [Наслідки появи нового конкретного класу елементів у Visitor](#10-наслідки-появи-нового-конкретного-класу-елементів-у-visitor)

---

## 1. У чому рекурсивність декорування?

**Декоратор (Decorator)** — структурний патерн, що дозволяє динамічно додавати об'єктам нову поведінку, загортаючи їх в об'єкти-обгортки.

Рекурсивність полягає в тому, що **декоратор сам реалізує той самий інтерфейс**, що й об'єкт, який він обгортає. Це дозволяє загортати декоратори один в одного на будь-яку глибину.

```
Клієнт → DecoratorC( DecoratorB( DecoratorA( BaseComponent ) ) )
```

```java
// Кожен виклик проходить через усі шари:
Coffee coffee = new SimpleCoffee();
coffee = new MilkDecorator(coffee);   // +молоко
coffee = new SugarDecorator(coffee);  // +цукор
coffee = new VanillaDecorator(coffee); // +ваніль

coffee.getCost(); // 3 + 2 + 1 + 0.5 = підсумовує всі шари
coffee.getDesc(); // "Simple coffee, milk, sugar, vanilla"
```

Кожен декоратор викликає метод внутрішнього об'єкта і **додає свою поведінку** до або після виклику. Ланцюжок може бути довільної довжини — звідси і рекурсивність.

```
getDesc() на VanillaDecorator
  → викликає getDesc() на SugarDecorator
    → викликає getDesc() на MilkDecorator
      → викликає getDesc() на SimpleCoffee
        ← повертає "Simple coffee"
      ← повертає "Simple coffee, milk"
    ← повертає "Simple coffee, milk, sugar"
  ← повертає "Simple coffee, milk, sugar, vanilla"
```

---

## 2. Як реалізувати патерн Декоратор на C++?

```cpp
#include <iostream>
#include <string>

// Базовий інтерфейс компонента
class Coffee {
public:
    virtual ~Coffee() = default;
    virtual double getCost() const = 0;
    virtual std::string getDescription() const = 0;
};

// Конкретний компонент
class SimpleCoffee : public Coffee {
public:
    double getCost() const override { return 3.0; }
    std::string getDescription() const override { return "Simple coffee"; }
};

// Базовий декоратор
class CoffeeDecorator : public Coffee {
protected:
    Coffee* wrappee; // вказівник на об'єкт, що декорується

public:
    explicit CoffeeDecorator(Coffee* c) : wrappee(c) {}

    double getCost() const override {
        return wrappee->getCost(); // делегує внутрішньому об'єкту
    }

    std::string getDescription() const override {
        return wrappee->getDescription();
    }
};

// Конкретний декоратор — молоко
class MilkDecorator : public CoffeeDecorator {
public:
    explicit MilkDecorator(Coffee* c) : CoffeeDecorator(c) {}

    double getCost() const override {
        return CoffeeDecorator::getCost() + 1.5;
    }

    std::string getDescription() const override {
        return CoffeeDecorator::getDescription() + ", milk";
    }
};

// Конкретний декоратор — цукор
class SugarDecorator : public CoffeeDecorator {
public:
    explicit SugarDecorator(Coffee* c) : CoffeeDecorator(c) {}

    double getCost() const override {
        return CoffeeDecorator::getCost() + 0.5;
    }

    std::string getDescription() const override {
        return CoffeeDecorator::getDescription() + ", sugar";
    }
};

// Використання
int main() {
    Coffee* coffee = new SimpleCoffee();
    coffee = new MilkDecorator(coffee);
    coffee = new SugarDecorator(coffee);

    std::cout << coffee->getDescription() << std::endl; // Simple coffee, milk, sugar
    std::cout << coffee->getCost() << std::endl;         // 5.0

    delete coffee; // важливо: управління пам'яттю вручну
    return 0;
}
```

> **Ключові моменти C++:** використовуються вказівники, деструктор має бути `virtual`, пам'ять звільняється вручну (або через `std::unique_ptr`).

---

## 3. Відмінності реалізації декораторів на Java від C++

| Аспект | C++ | Java |
|--------|-----|------|
| **Посилання на об'єкт** | Вказівник `Coffee*` | Посилання `Coffee` (reference) |
| **Управління пам'яттю** | Вручну (`delete`) або `unique_ptr` | Автоматично (Garbage Collector) |
| **Деструктор** | Потрібен `virtual ~Coffee()` | Не потрібен (є `finalize`, але не обов'язковий) |
| **Інтерфейс** | Абстрактний клас із чистими методами | Ключове слово `interface` |
| **Множинне спадкування** | Підтримується | Тільки через інтерфейси |
| **Анотації** | Відсутні | `@Override` для перевизначених методів |

```java
// Java — реалізація того ж патерну
interface Coffee {
    double getCost();
    String getDescription();
}

class SimpleCoffee implements Coffee {
    public double getCost() { return 3.0; }
    public String getDescription() { return "Simple coffee"; }
}

abstract class CoffeeDecorator implements Coffee {
    protected Coffee wrappee; // посилання, не вказівник

    public CoffeeDecorator(Coffee c) { this.wrappee = c; }

    public double getCost() { return wrappee.getCost(); }
    public String getDescription() { return wrappee.getDescription(); }
}

class MilkDecorator extends CoffeeDecorator {
    public MilkDecorator(Coffee c) { super(c); }

    @Override
    public double getCost() { return super.getCost() + 1.5; }

    @Override
    public String getDescription() { return super.getDescription() + ", milk"; }
}
```

Логіка однакова, але Java-код коротший і безпечніший завдяки автоматичному управлінню пам'яттю та чистому синтаксису інтерфейсів.

---

## 4. Навіщо одній частині програми спостерігати за іншою?

Спостереження потрібне, коли **зміна стану одного об'єкта має викликати реакцію інших**, але при цьому небажано створювати жорстку залежність між ними.

### Приклади:

**1. UI та дані (MVC)**
Модель (дані) змінилась → View (інтерфейс) автоматично оновлює відображення без прямого зв'язку.

**2. Система сповіщень**
Користувач підписався на товар → як тільки товар з'явився на складі, всі підписники отримують сповіщення.

**3. Логування та моніторинг**
Сервіс виконує дії → логер спостерігає і записує події, не впливаючи на логіку сервісу.

**4. Фінансові системи**
Змінився курс валюти → всі компоненти, що залежать від курсу (калькулятори, графіки, звіти), отримують оновлення.

**5. Ігри**
Стан гравця змінився (здоров'я впало до 0) → система досягнень, UI, звукові ефекти реагують одночасно.

> Спільне: **джерело події не знає і не повинно знати**, хто на неї реагує.

---

## 5. Як Observer забезпечує незалежність об'єкта від спостерігачів?

Патерн **Observer** забезпечує незалежність через **програмування на інтерфейс**: об'єкт спостереження (Subject) знає лише про абстрактний інтерфейс `Observer`, а не про конкретні класи.

```
Subject знає лише про: Observer (інтерфейс)
Subject НЕ знає про: EmailNotifier, SMSNotifier, LogObserver
```

```java
interface Observer {
    void update(String event);
}

class EventSource {
    private List<Observer> observers = new ArrayList<>();

    public void subscribe(Observer o) { observers.add(o); }
    public void unsubscribe(Observer o) { observers.remove(o); }

    private void notifyObservers(String event) {
        for (Observer o : observers) {
            o.update(event); // викликає через інтерфейс — не знає конкретного типу
        }
    }

    public void doSomething() {
        // ... логіка ...
        notifyObservers("something_happened");
    }
}
```

Завдяки цьому:
- Можна додавати нових спостерігачів без зміни `EventSource`.
- Можна видаляти спостерігачів під час виконання.
- `EventSource` не залежить від жодного конкретного спостерігача.

---

## 6. Чи може конкретний спостерігач не залежати від конкретного об'єкта?

**Так**, це можливо і є бажаною практикою. Конкретний спостерігач залежить лише від **інтерфейсу Subject** (або взагалі отримує всі дані через параметри методу `update`).

```java
// Спостерігач не знає про конкретний клас джерела
class LogObserver implements Observer {

    @Override
    public void update(String event) {
        // отримує тільки дані через параметр — не знає хто відправив
        System.out.println("Log: " + event);
    }
}
```

Якщо спостерігачу потрібно більше даних, йому можна передати посилання на загальний інтерфейс `Subject`:

```java
interface Observer {
    void update(Subject source, String event); // посилання на інтерфейс, не на конкретний клас
}
```

Таким чином обидва боки залежать лише від **абстракцій**, що відповідає принципу DIP (Dependency Inversion Principle).

---

## 7. Яку інформацію передавати через параметри методу Update?

Існують два підходи:

### Push-модель — Subject передає дані одразу
```java
interface Observer {
    void update(String eventType, Object newValue);
}

// Subject сам вирішує що передати
observer.update("price_changed", 42.5);
```

**Переваги:** спостерігач отримує все потрібне одразу, не робить зайвих запитів.  
**Недоліки:** Subject може передавати зайві дані деяким спостерігачам.

### Pull-модель — Subject передає посилання на себе
```java
interface Observer {
    void update(Subject source); // отримує посилання на джерело
}

// Спостерігач сам забирає потрібні дані
class PriceObserver implements Observer {
    public void update(Subject source) {
        double price = ((Shop) source).getPrice(); // сам запитує що потрібно
    }
}
```

**Переваги:** кожен спостерігач бере лише те, що йому потрібно.  
**Недоліки:** спостерігач може залежати від конкретного типу Subject.

### Рекомендований баланс
```java
interface Observer {
    void update(Subject source, String eventType, Object data);
    //          посилання     тип події           дані події
}
```

> Передавати варто: тип події, нові значення що змінились, посилання на джерело (через інтерфейс). Не варто передавати внутрішні деталі реалізації Subject.

---

## 8. Основна ідея патерну Visitor

**Відвідувач (Visitor)** — поведінковий патерн, що дозволяє **додавати нові операції до існуючих класів** без їх зміни, виносячи логіку операцій в окремі класи-відвідувачів.

```
Ідея: "розділити алгоритм і структуру даних, над якою він виконується"
```

```java
// Без Visitor — операції розкидані по класах елементів
class Circle { void draw() {...} void serialize() {...} void calcArea() {...} }
class Square { void draw() {...} void serialize() {...} void calcArea() {...} }

// З Visitor — кожна операція винесена в окремий клас
class DrawVisitor    { visit(Circle c) {...}  visit(Square s) {...}  }
class SerializeVisitor { visit(Circle c) {...}  visit(Square s) {...}  }
class AreaVisitor    { visit(Circle c) {...}  visit(Square s) {...}  }
```

Механізм **подвійної диспетчеризації (double dispatch)**:
```java
// Елемент приймає відвідувача
interface Shape {
    void accept(Visitor v);
}

class Circle implements Shape {
    public void accept(Visitor v) {
        v.visit(this); // передає себе відвідувачу — другий dispatch
    }
}

// Відвідувач знає що робити з кожним типом
interface Visitor {
    void visit(Circle c);
    void visit(Square s);
}
```

---

## 9. Скільки методів має бути в інтерфейсі відвідувача?

В інтерфейсі відвідувача має бути **по одному методу `visit` на кожен конкретний клас елементів** у ієрархії.

```java
// Якщо є 3 конкретні класи елементів — 3 методи у відвідувача
interface Visitor {
    void visit(Circle circle);
    void visit(Square square);
    void visit(Triangle triangle);
}
```

> **Правило:** кількість методів у `Visitor` = кількість конкретних класів елементів.

Якщо додати новий елемент `Pentagon`, потрібно додати метод `visit(Pentagon p)` до інтерфейсу — і **реалізувати його у всіх існуючих відвідувачах**. Це є відомим недоліком патерну.

```java
// При додаванні нового елемента:
interface Visitor {
    void visit(Circle circle);
    void visit(Square square);
    void visit(Triangle triangle);
    void visit(Pentagon pentagon); // ← новий метод — треба реалізувати скрізь
}
```

---

## 10. Наслідки появи нового конкретного класу елементів у Visitor

Поява нового конкретного класу елементів є **найбільшим недоліком** патерну Visitor:

### Що доведеться змінити:

1. **Інтерфейс `Visitor`** — додати новий метод `visit(NewElement e)`.
2. **Усі конкретні класи відвідувачів** — реалізувати новий метод у кожному.
3. **Новий клас елементу** — реалізувати метод `accept(Visitor v)`.

```java
// 1. Змінюємо інтерфейс
interface Visitor {
    void visit(Circle c);
    void visit(Square s);
    void visit(Pentagon p); // ← новий метод
}

// 2. Змінюємо КОЖЕН існуючий відвідувач
class DrawVisitor implements Visitor {
    public void visit(Circle c) { ... }
    public void visit(Square s) { ... }
    public void visit(Pentagon p) { ... } // ← треба додати
}

class AreaVisitor implements Visitor {
    public void visit(Circle c) { ... }
    public void visit(Square s) { ... }
    public void visit(Pentagon p) { ... } // ← і тут теж
}

// 3. Новий елемент реалізує accept
class Pentagon implements Shape {
    public void accept(Visitor v) { v.visit(this); }
}
```

### Висновок щодо гнучкості патерну:

| Зміна | Наслідок |
|-------|----------|
| Додати **нову операцію** (новий Visitor) | Легко — створити один новий клас |
| Додати **новий елемент** | Складно — змінити інтерфейс і всі існуючі відвідувачі |

> Visitor добре підходить для **стабільної ієрархії елементів** з великою кількістю різних операцій. Якщо ієрархія часто змінюється — варто розглянути інші патерни.

---

## Підсумок

| Патерн | Основна ідея |
|--------|-------------|
| **Декоратор** | Динамічно додає поведінку через рекурсивне загортання об'єктів |
| **Спостерігач** | Один об'єкт сповіщає інших про зміни через загальний інтерфейс |
| **Відвідувач** | Виносить операції над елементами в окремі класи без зміни елементів |
