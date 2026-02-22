/*
 * Завдання 5
 * Базовий клас СПИСОК.
 * Похідні класи: СТЕК і ЧЕРГА з віртуальними функціями включення і вилучення.
 */

#include <iostream>
#include <deque>
#include <string>
using namespace std;

// ─── Базовий клас СПИСОК ─────────────────────────────────────────────────────
class List {
protected:
    deque<int> data;
public:
    virtual void push(int val) = 0;
    virtual int  pop()         = 0;
    virtual bool empty() const { return data.empty(); }
    virtual string name() const = 0;
    virtual ~List() {}

    void printAll() {
        cout << name() << ": ";
        if (data.empty()) { cout << "(порожній)" << endl; return; }
        deque<int> tmp = data;
        // Виводимо в порядку черги/стеку
        while (!tmp.empty()) {
            cout << tmp.front() << " ";
            tmp.pop_front();
        }
        cout << endl;
    }
};

// ─── СТЕК (LIFO) ──────────────────────────────────────────────────────────────
class Stack : public List {
public:
    void push(int val) override { data.push_back(val); }
    int  pop()         override {
        if (empty()) throw runtime_error("Стек порожній!");
        int val = data.back();
        data.pop_back();
        return val;
    }
    string name() const override { return "Стек (LIFO)"; }
};

// ─── ЧЕРГА (FIFO) ────────────────────────────────────────────────────────────
class Queue : public List {
public:
    void push(int val) override { data.push_back(val); }
    int  pop()         override {
        if (empty()) throw runtime_error("Черга порожня!");
        int val = data.front();
        data.pop_front();
        return val;
    }
    string name() const override { return "Черга (FIFO)"; }
};

void demo(List* lst) {
    cout << "--- " << lst->name() << " ---" << endl;
    cout << "Додаємо: 10, 20, 30, 40" << endl;
    lst->push(10); lst->push(20); lst->push(30); lst->push(40);
    lst->printAll();
    cout << "Вилучаємо: " << lst->pop() << endl;
    cout << "Вилучаємо: " << lst->pop() << endl;
    lst->printAll();
    cout << endl;
}

int main() {
    cout << "=== Завдання 5: Стек і Черга ===" << endl << endl;

    const int N = 2;
    List* containers[N] = {
        new Stack(),
        new Queue()
    };

    for (int i = 0; i < N; ++i)
        demo(containers[i]);

    for (int i = 0; i < N; ++i)
        delete containers[i];

    return 0;
}
