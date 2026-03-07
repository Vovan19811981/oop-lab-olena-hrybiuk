/*
 * Лабораторна робота № 9. Бібліотека стандартних шаблонів (STL)
 * Всі 13 завдань в одному файлі
 * Компіляція: g++ -std=c++11 -o lab9 9_stl.cpp
 */

#include <iostream>
#include <vector>
#include <list>
#include <map>
#include <stack>
#include <queue>
#include <set>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>
using namespace std;

// ============================================================
// ЗАВДАННЯ 1
// Шаблонна функція створення, заповнення, сортування і
// виведення динамічного вектора
// ============================================================

template<typename T>
void processVector(int n) {
    vector<T> v;
    cout << "Заповнення вектора (" << n << " елементів):" << endl;
    for (int i = 0; i < n; ++i) {
        T val;
        cout << "  [" << i << "]: ";
        cin >> val;
        v.push_back(val);
    }
    sort(v.begin(), v.end());
    cout << "Відсортований вектор: ";
    for (auto& x : v) cout << x << " ";
    cout << endl;
}

// ============================================================
// ЗАВДАННЯ 2
// Шаблонна функція читання текстового файлу і вставки
// елементів у список
// ============================================================

template<typename T>
list<T> readFileToList(const string& filename) {
    list<T> lst;
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "  (файл не знайдено, демонстрація з тестових даних)" << endl;
        // Демо: додаємо тестові дані
        for (int i = 1; i <= 5; ++i) lst.push_back((T)i * 10);
        return lst;
    }
    T val;
    while (file >> val)
        lst.push_back(val);
    file.close();
    return lst;
}

// ============================================================
// ЗАВДАННЯ 3
// Пари номер місяця – назва місяця в map,
// пошук назви за номером
// ============================================================

void task3() {
    map<int, string> months;
    months[1]  = "Січень";
    months[2]  = "Лютий";
    months[3]  = "Березень";
    months[4]  = "Квітень";
    months[5]  = "Травень";
    months[6]  = "Червень";
    months[7]  = "Липень";
    months[8]  = "Серпень";
    months[9]  = "Вересень";
    months[10] = "Жовтень";
    months[11] = "Листопад";
    months[12] = "Грудень";

    int num;
    cout << "Введіть номер місяця (1-12): ";
    cin >> num;

    auto it = months.find(num);
    if (it != months.end())
        cout << "Місяць: " << it->second << endl;
    else
        cout << "Невірний номер місяця!" << endl;
}

// ============================================================
// ЗАВДАННЯ 4
// Шаблонна функція послідовного пошуку в масиві за ключем.
// Повертає перший знайдений елемент або повідомлення.
// ============================================================

template<typename T>
int sequentialSearch(const vector<T>& arr, const T& key) {
    for (int i = 0; i < (int)arr.size(); ++i) {
        if (arr[i] == key)
            return i;
    }
    return -1;
}

// ============================================================
// ЗАВДАННЯ 5
// Шаблонна функція сортування одновимірного масиву методом
// бульбашки за зростанням
// ============================================================

template<typename T>
void bubbleSort(vector<T>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i)
        for (int j = 0; j < n - i - 1; ++j)
            if (arr[j] > arr[j + 1])
                swap(arr[j], arr[j + 1]);
}

// ============================================================
// ЗАВДАННЯ 6
// Шаблонна функція перевірки впорядкованості масиву
// за зростанням або спаданням
// ============================================================

template<typename T>
string checkOrder(const vector<T>& arr) {
    if (arr.size() < 2) return "Один елемент";

    bool asc  = true; // зростання
    bool desc = true; // спадання

    for (int i = 0; i < (int)arr.size() - 1; ++i) {
        if (arr[i] > arr[i + 1]) asc  = false;
        if (arr[i] < arr[i + 1]) desc = false;
    }

    if (asc  && desc) return "Всі елементи рівні";
    if (asc)          return "Впорядкований за зростанням";
    if (desc)         return "Впорядкований за спаданням";
    return "Не впорядкований";
}

// ============================================================
// ЗАВДАННЯ 7
// Шаблонна функція формування файлу числових даних
// у текстовому форматі
// ============================================================

template<typename T>
void writeToFile(const string& filename, const vector<T>& data) {
    ofstream file(filename);
    if (!file.is_open()) {
        cout << "  Помилка відкриття файлу!" << endl;
        return;
    }
    for (const T& val : data)
        file << val << "\n";
    file.close();
    cout << "  Записано " << data.size() << " елементів у файл: " << filename << endl;
}

// ============================================================
// ЗАВДАННЯ 8
// Шаблонний клас КВАДРАТНА МАТРИЦЯ.
// Контрольна сума = сума всіх елементів mod 2.
// ============================================================

template<typename T>
class SquareMatrix {
    int n;
    vector<vector<T>> data;

public:
    SquareMatrix(int size) : n(size), data(size, vector<T>(size, T())) {}

    T& at(int i, int j) { return data[i][j]; }

    void fill() {
        cout << "  Введіть елементи матриці " << n << "x" << n << ":" << endl;
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < n; ++j) {
                cout << "  [" << i << "][" << j << "]: ";
                cin >> data[i][j];
            }
    }

    void print() const {
        for (int i = 0; i < n; ++i) {
            cout << "  ";
            for (int j = 0; j < n; ++j)
                cout << data[i][j] << "\t";
            cout << endl;
        }
    }

    // Контрольна сума = сума всіх елементів mod 2
    long long checksum() const {
        long long sum = 0;
        for (auto& row : data)
            for (auto& val : row)
                sum += (long long)val;
        return sum % 2;
    }
};

// ============================================================
// ЗАВДАННЯ 9
// Шаблонний клас СТЕК.
// Параметризований рядками string, знайти найдовший рядок.
// ============================================================

template<typename T>
class MyStack {
    vector<T> data;

public:
    void push(const T& val) { data.push_back(val); }

    T pop() {
        if (data.empty()) throw runtime_error("Стек порожній!");
        T val = data.back();
        data.pop_back();
        return val;
    }

    T top() const {
        if (data.empty()) throw runtime_error("Стек порожній!");
        return data.back();
    }

    bool empty() const { return data.empty(); }
    int  size()  const { return data.size(); }

    // Знайти найдовший рядок (для T = string)
    T findLongest() const {
        if (data.empty()) throw runtime_error("Стек порожній!");
        T longest = data[0];
        for (const T& s : data)
            if (s.size() > longest.size())
                longest = s;
        return longest;
    }
};

// ============================================================
// ЗАВДАННЯ 10
// Шаблонний клас однонапрямленого лінійного списку.
// Сортування за зростанням.
// ============================================================

template<typename T>
class SinglyLinkedList {
    struct Node {
        T     val;
        Node* next;
        Node(T v) : val(v), next(nullptr) {}
    };
    Node* head;

public:
    SinglyLinkedList() : head(nullptr) {}

    ~SinglyLinkedList() {
        while (head) {
            Node* tmp = head;
            head = head->next;
            delete tmp;
        }
    }

    void pushBack(T val) {
        Node* newNode = new Node(val);
        if (!head) { head = newNode; return; }
        Node* cur = head;
        while (cur->next) cur = cur->next;
        cur->next = newNode;
    }

    // Сортування вибіркою
    void sort() {
        for (Node* i = head; i; i = i->next)
            for (Node* j = i->next; j; j = j->next)
                if (i->val > j->val)
                    swap(i->val, j->val);
    }

    void print() const {
        Node* cur = head;
        while (cur) {
            cout << cur->val;
            if (cur->next) cout << " -> ";
            cur = cur->next;
        }
        cout << endl;
    }
};

// ============================================================
// ЗАВДАННЯ 11
// Шаблонний клас списку з подвійними зв'язками.
// Вставка на початок, вилучення з кінця.
// ============================================================

template<typename T>
class DoublyLinkedList {
    struct Node {
        T     val;
        Node* prev;
        Node* next;
        Node(T v) : val(v), prev(nullptr), next(nullptr) {}
    };
    Node* head;
    Node* tail;
    int   sz;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), sz(0) {}

    ~DoublyLinkedList() {
        while (head) {
            Node* tmp = head;
            head = head->next;
            delete tmp;
        }
    }

    // Вставка на початок
    void pushFront(T val) {
        Node* newNode = new Node(val);
        if (!head) {
            head = tail = newNode;
        } else {
            newNode->next = head;
            head->prev    = newNode;
            head          = newNode;
        }
        ++sz;
    }

    void pushBack(T val) {
        Node* newNode = new Node(val);
        if (!tail) {
            head = tail = newNode;
        } else {
            newNode->prev = tail;
            tail->next    = newNode;
            tail          = newNode;
        }
        ++sz;
    }

    // Вилучення з кінця
    T popBack() {
        if (!tail) throw runtime_error("Список порожній!");
        T val = tail->val;
        Node* tmp = tail;
        tail = tail->prev;
        if (tail) tail->next = nullptr;
        else      head = nullptr;
        delete tmp;
        --sz;
        return val;
    }

    int  size()  const { return sz; }
    bool empty() const { return sz == 0; }

    void print() const {
        Node* cur = head;
        while (cur) {
            cout << cur->val;
            if (cur->next) cout << " <-> ";
            cur = cur->next;
        }
        cout << endl;
    }
};

// ============================================================
// ЗАВДАННЯ 12
// Шаблонний клас МНОЖИНА.
// Операції: об'єднання, перетин, різниця.
// ============================================================

template<typename T>
class MySet {
    set<T> data;

public:
    MySet() {}
    MySet(initializer_list<T> lst) : data(lst) {}

    void insert(const T& val) { data.insert(val); }

    // Об'єднання
    MySet<T> unionWith(const MySet<T>& other) const {
        MySet<T> result;
        for (auto& x : data)       result.insert(x);
        for (auto& x : other.data) result.insert(x);
        return result;
    }

    // Перетин
    MySet<T> intersectWith(const MySet<T>& other) const {
        MySet<T> result;
        for (auto& x : data)
            if (other.data.count(x)) result.insert(x);
        return result;
    }

    // Різниця (this - other)
    MySet<T> differenceWith(const MySet<T>& other) const {
        MySet<T> result;
        for (auto& x : data)
            if (!other.data.count(x)) result.insert(x);
        return result;
    }

    void print() const {
        cout << "{ ";
        for (auto& x : data) cout << x << " ";
        cout << "}";
    }
};

// ============================================================
// ЗАВДАННЯ 13
// Шаблонний клас ЧЕРГА З ПРІОРИТЕТАМИ.
// Вставка, вилучення з найвищим та найнижчим пріоритетами.
// ============================================================

template<typename T>
class PriorityQueue {
    // max-heap для найвищого пріоритету
    priority_queue<T>             maxQ;
    // min-heap для найнижчого пріоритету
    priority_queue<T, vector<T>, greater<T>> minQ;

public:
    void push(const T& val) {
        maxQ.push(val);
        minQ.push(val);
    }

    // Вилучити елемент з найвищим пріоритетом
    T popMax() {
        if (maxQ.empty()) throw runtime_error("Черга порожня!");
        T val = maxQ.top();
        maxQ.pop();
        return val;
    }

    // Вилучити елемент з найнижчим пріоритетом
    T popMin() {
        if (minQ.empty()) throw runtime_error("Черга порожня!");
        T val = minQ.top();
        minQ.pop();
        return val;
    }

    T peekMax() const { return maxQ.top(); }
    T peekMin() const { return minQ.top(); }

    bool empty() const { return maxQ.empty(); }
    int  size()  const { return maxQ.size(); }
};

// ============================================================
// ГОЛОВНА ПРОГРАМА — демонстрація всіх завдань
// ============================================================

int main() {
    cout << "╔══════════════════════════════════════════════════╗" << endl;
    cout << "║   Лабораторна робота №9 — STL                    ║" << endl;
    cout << "╚══════════════════════════════════════════════════╝" << endl;

    // ── Завдання 1 ──────────────────────────────────────────
    cout << "\n=== Завдання 1: Шаблонний вектор ===" << endl;
    cout << "Демонстрація з фіксованими даними:" << endl;
    {
        vector<int> v = {5, 2, 8, 1, 9, 3};
        cout << "До сортування:     ";
        for (auto x : v) cout << x << " ";
        cout << endl;
        sort(v.begin(), v.end());
        cout << "Після сортування:  ";
        for (auto x : v) cout << x << " ";
        cout << endl;
    }

    // ── Завдання 2 ──────────────────────────────────────────
    cout << "\n=== Завдання 2: Читання файлу у список ===" << endl;
    {
        // Спочатку запишемо тестовий файл
        ofstream f("test_input.txt");
        f << "10\n20\n30\n40\n50\n";
        f.close();

        list<int> lst = readFileToList<int>("test_input.txt");
        cout << "Список з файлу: ";
        for (auto x : lst) cout << x << " ";
        cout << endl;
    }

    // ── Завдання 3 ──────────────────────────────────────────
    cout << "\n=== Завдання 3: Місяці (map) ===" << endl;
    {
        map<int, string> months = {
            {1,"Січень"},{2,"Лютий"},{3,"Березень"},
            {4,"Квітень"},{5,"Травень"},{6,"Червень"},
            {7,"Липень"},{8,"Серпень"},{9,"Вересень"},
            {10,"Жовтень"},{11,"Листопад"},{12,"Грудень"}
        };
        // Демо без вводу
        for (int num : {3, 7, 12}) {
            auto it = months.find(num);
            cout << "Місяць " << num << ": " << it->second << endl;
        }
    }

    // ── Завдання 4 ──────────────────────────────────────────
    cout << "\n=== Завдання 4: Послідовний пошук ===" << endl;
    {
        vector<int> arr = {15, 3, 42, 7, 99, 18, 6};
        cout << "Масив: ";
        for (auto x : arr) cout << x << " ";
        cout << endl;

        int key = 42;
        int idx = sequentialSearch(arr, key);
        if (idx >= 0)
            cout << "Знайдено " << key << " на позиції " << idx << endl;
        else
            cout << "Елемент " << key << " не знайдено" << endl;

        key = 100;
        idx = sequentialSearch(arr, key);
        if (idx >= 0)
            cout << "Знайдено " << key << " на позиції " << idx << endl;
        else
            cout << "Елемент " << key << " не знайдено" << endl;
    }

    // ── Завдання 5 ──────────────────────────────────────────
    cout << "\n=== Завдання 5: Сортування бульбашкою ===" << endl;
    {
        vector<double> arr = {3.5, 1.2, 8.9, 2.4, 6.1};
        cout << "До:    ";
        for (auto x : arr) cout << x << " ";
        cout << endl;
        bubbleSort(arr);
        cout << "Після: ";
        for (auto x : arr) cout << x << " ";
        cout << endl;
    }

    // ── Завдання 6 ──────────────────────────────────────────
    cout << "\n=== Завдання 6: Перевірка впорядкованості ===" << endl;
    {
        vector<int> a1 = {1, 2, 3, 4, 5};
        vector<int> a2 = {5, 4, 3, 2, 1};
        vector<int> a3 = {3, 1, 4, 1, 5};
        vector<int> a4 = {7, 7, 7};

        cout << "{1,2,3,4,5}: " << checkOrder(a1) << endl;
        cout << "{5,4,3,2,1}: " << checkOrder(a2) << endl;
        cout << "{3,1,4,1,5}: " << checkOrder(a3) << endl;
        cout << "{7,7,7}:     " << checkOrder(a4) << endl;
    }

    // ── Завдання 7 ──────────────────────────────────────────
    cout << "\n=== Завдання 7: Запис числових даних у файл ===" << endl;
    {
        vector<double> data = {1.1, 2.2, 3.3, 4.4, 5.5};
        writeToFile<double>("output_data.txt", data);

        // Читаємо назад для перевірки
        ifstream f("output_data.txt");
        cout << "  Вміст файлу: ";
        double v;
        while (f >> v) cout << v << " ";
        cout << endl;
        f.close();
    }

    // ── Завдання 8 ──────────────────────────────────────────
    cout << "\n=== Завдання 8: Квадратна матриця ===" << endl;
    {
        SquareMatrix<int> m(3);
        // Заповнюємо вручну для демо
        int vals[3][3] = {{1,2,3},{4,5,6},{7,8,9}};
        for (int i = 0; i < 3; ++i)
            for (int j = 0; j < 3; ++j)
                m.at(i, j) = vals[i][j];

        cout << "Матриця:" << endl;
        m.print();
        // Сума = 1+2+...+9 = 45, 45 mod 2 = 1
        cout << "Контрольна сума (сума mod 2) = " << m.checksum() << endl;
    }

    // ── Завдання 9 ──────────────────────────────────────────
    cout << "\n=== Завдання 9: Стек рядків ===" << endl;
    {
        MyStack<string> st;
        st.push("Hello");
        st.push("Бібліотека");
        st.push("STL");
        st.push("Програмування");
        st.push("C++");

        cout << "Елементи у стеку (знизу вгору): Hello, Бібліотека, STL, Програмування, C++" << endl;
        cout << "Найдовший рядок: \"" << st.findLongest() << "\"" << endl;
        cout << "Top (останній): " << st.top() << endl;
        cout << "Pop: " << st.pop() << endl;
        cout << "Розмір після pop: " << st.size() << endl;
    }

    // ── Завдання 10 ──────────────────────────────────────────
    cout << "\n=== Завдання 10: Однонапрямлений список ===" << endl;
    {
        SinglyLinkedList<int> lst;
        lst.pushBack(5);
        lst.pushBack(2);
        lst.pushBack(8);
        lst.pushBack(1);
        lst.pushBack(9);

        cout << "До сортування:    ";
        lst.print();
        lst.sort();
        cout << "Після сортування: ";
        lst.print();
    }

    // ── Завдання 11 ──────────────────────────────────────────
    cout << "\n=== Завдання 11: Двонаправлений список ===" << endl;
    {
        DoublyLinkedList<int> lst;
        lst.pushBack(10);
        lst.pushBack(20);
        lst.pushBack(30);

        cout << "Початковий список: ";
        lst.print();

        lst.pushFront(5);
        cout << "Після вставки 5 на початок: ";
        lst.print();

        int removed = lst.popBack();
        cout << "Вилучено з кінця: " << removed << endl;
        cout << "Список після вилучення: ";
        lst.print();
    }

    // ── Завдання 12 ──────────────────────────────────────────
    cout << "\n=== Завдання 12: Множина ===" << endl;
    {
        MySet<int> A = {1, 2, 3, 4, 5};
        MySet<int> B = {3, 4, 5, 6, 7};

        cout << "A = "; A.print(); cout << endl;
        cout << "B = "; B.print(); cout << endl;

        cout << "A ∪ B = "; A.unionWith(B).print();      cout << endl;
        cout << "A ∩ B = "; A.intersectWith(B).print();  cout << endl;
        cout << "A \\ B = "; A.differenceWith(B).print(); cout << endl;
    }

    // ── Завдання 13 ──────────────────────────────────────────
    cout << "\n=== Завдання 13: Черга з пріоритетами ===" << endl;
    {
        PriorityQueue<int> pq;
        pq.push(15);
        pq.push(3);
        pq.push(42);
        pq.push(7);
        pq.push(99);

        cout << "Елементи: 15, 3, 42, 7, 99" << endl;
        cout << "Найвищий пріоритет (max): " << pq.peekMax() << endl;
        cout << "Найнижчий пріоритет (min): " << pq.peekMin() << endl;
        cout << "Вилучено з найвищим: " << pq.popMax() << endl;
        cout << "Вилучено з найнижчим: " << pq.popMin() << endl;
        cout << "Залишилось елементів: " << pq.size() << endl;
    }

    cout << "\n=== Всі завдання виконано ===" << endl;
    return 0;
}
