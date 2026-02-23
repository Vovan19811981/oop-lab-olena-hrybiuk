/*
 * Практична робота № 9 — Мережевий чат
 * Файл: 9_answers.cpp
 * Відповіді на контрольні питання
 */

/*
 * 1. Що таке сокети?
 *
 * Сокет (socket) — це програмний інтерфейс для організації мережевого
 * з'єднання між двома програмами. Сокет є кінцевою точкою з'єднання і
 * ідентифікується IP-адресою та номером порту. Розрізняють:
 *   - TCP-сокети (SOCK_STREAM) — надійна передача з гарантією доставки
 *   - UDP-сокети (SOCK_DGRAM)  — швидка передача без гарантії доставки
 *
 * Приклад створення сокету:
 */
#include <iostream>
#ifdef _WIN32
    #include <winsock2.h>
#else
    #include <sys/socket.h>
    #include <netinet/in.h>
    #define SOCKET int
#endif
using namespace std;

void answer1() {
    // Створення TCP-сокету
    SOCKET s = socket(AF_INET,      // сімейство адрес IPv4
                      SOCK_STREAM,  // тип: потоковий (TCP)
                      IPPROTO_TCP); // протокол
    cout << "Сокет створено, дескриптор: " << s << endl;
}

/*
 * 2. В чому полягає мережеве програмування з використанням бібліотеки winsock.h?
 *
 * WinSock (Windows Sockets API) — стандартний інтерфейс мережевого
 * програмування для Windows. Кроки роботи з WinSock:
 *
 *   1. WSAStartup()  — ініціалізація бібліотеки WinSock
 *   2. socket()      — створення сокету
 *   3. bind()        — прив'язка до IP і порту (для сервера)
 *   4. listen()      — очікування підключень (для сервера)
 *   5. accept()      — прийняття підключення (для сервера)
 *      connect()     — підключення до сервера (для клієнта)
 *   6. send()/recv() — відправка та отримання даних
 *   7. closesocket() — закриття сокету
 *   8. WSACleanup()  — завершення роботи з бібліотекою
 *
 * На Linux/macOS аналогічний функціонал реалізовано через POSIX sockets
 * (sys/socket.h) без потреби у WSAStartup/WSACleanup.
 */

void answer2() {
#ifdef _WIN32
    WSADATA wsaData;
    // Ініціалізація WinSock версії 2.2
    int result = WSAStartup(MAKEWORD(2, 2), &wsaData);
    if (result == 0)
        cout << "WinSock ініціалізовано успішно" << endl;
    WSACleanup();
#else
    cout << "Linux: POSIX sockets не потребують ініціалізації" << endl;
#endif
}

/*
 * 3. Які можливості надають компоненти Indy у програмуванні?
 *
 * Indy (Internet Direct) — бібліотека мережевих компонентів для
 * Borland/Embarcadero C++ Builder та Delphi. Надає:
 *
 *   - TIdTCPServer / TIdTCPClient — TCP з'єднання
 *   - TIdHTTP                    — HTTP запити
 *   - TIdFTP                     — FTP клієнт
 *   - TIdSMTP                    — відправка email
 *   - TIdPOP3                    — отримання email
 *   - TIdUDPServer/Client        — UDP з'єднання
 *   - TIdSSLIOHandlerSocketOpenSSL — захищені з'єднання SSL/TLS
 *
 * Головна перевага Indy — блокуючий (синхронний) режим роботи,
 * що спрощує написання коду порівняно з асинхронними підходами.
 */

void answer3() {
    cout << "Indy надає готові компоненти для роботи з TCP, HTTP, FTP, SMTP тощо" << endl;
}

/*
 * 4. Яку можливість надають компоненти ServerSocket, ClientSocket та Socket?
 *
 * ServerSocket — компонент Borland C++ Builder для створення TCP-сервера:
 *   - Властивість Port    — порт прослуховування
 *   - Метод Open()/Close()— запуск/зупинка сервера
 *   - Подія OnClientRead  — отримання даних від клієнта
 *   - Подія OnClientConnect/Disconnect — підключення/відключення клієнта
 *
 * ClientSocket — компонент для підключення до сервера:
 *   - Властивість Host/Address — адреса сервера
 *   - Властивість Port         — порт сервера
 *   - Метод Open()/Close()     — підключення/відключення
 *   - Подія OnRead             — отримання даних
 *   - Подія OnConnect/Disconnect — стан з'єднання
 *
 * Socket — базовий клас, що реалізує операції send/receive
 * безпосередньо через WinSock API.
 */

void answer4() {
    cout << "ServerSocket слухає порт, ClientSocket підключається до сервера" << endl;
}

/*
 * 5. Які події виконує клієнт і як на них реагує сервер?
 *
 * Клієнт                          Сервер
 * ──────────────────────────────────────────────────────
 * Open() / connect()    ──────►  OnClientConnect: додає клієнта до списку,
 *                                надсилає список користувачів
 *
 * SendText(#нікнейм)    ──────►  OnClientRead: реєструє нікнейм,
 *                                оновлює список у всіх клієнтів
 *
 * SendText(повідомлення) ─────►  OnClientRead: розбирає отримувача,
 *                                пересилає потрібному клієнту або всім
 *
 * Close() / disconnect  ──────►  OnClientDisconnect: видаляє зі списку,
 *                                повідомляє інших користувачів
 */

void answer5() {
    cout << "Клієнт: connect -> send -> disconnect" << endl;
    cout << "Сервер: OnConnect -> OnRead -> OnDisconnect" << endl;
}

/*
 * 6. З яких кроків складається мережеве програмування в winsock.h?
 *
 * СЕРВЕР:
 *   1. WSAStartup()           — ініціалізація WinSock
 *   2. socket()               — створення сокету
 *   3. bind()                 — прив'язка до адреси і порту
 *   4. listen()               — переведення у режим очікування
 *   5. accept()               — прийняття підключення (блокуючий виклик)
 *   6. recv() / send()        — обмін даними з клієнтом
 *   7. closesocket()          — закриття сокету клієнта
 *   8. closesocket()          — закриття серверного сокету
 *   9. WSACleanup()           — завершення роботи
 *
 * КЛІЄНТ:
 *   1. WSAStartup()           — ініціалізація WinSock
 *   2. socket()               — створення сокету
 *   3. connect()              — підключення до сервера
 *   4. send() / recv()        — обмін даними
 *   5. closesocket()          — закриття з'єднання
 *   6. WSACleanup()           — завершення роботи
 */

void answer6() {
    cout << "Сервер: WSAStartup -> socket -> bind -> listen -> accept -> recv/send -> closesocket -> WSACleanup" << endl;
    cout << "Клієнт: WSAStartup -> socket -> connect -> send/recv -> closesocket -> WSACleanup" << endl;
}

int main() {
    cout << "=== Практична робота №9 — Відповіді на контрольні питання ===" << endl;
    cout << endl;

    cout << "1. Сокет — кінцева точка мережевого з'єднання (IP + порт)." << endl;
    answer1();
    cout << endl;

    cout << "2. WinSock — API мережевого програмування для Windows." << endl;
    answer2();
    cout << endl;

    cout << "3. Indy — бібліотека готових мережевих компонентів для C++ Builder." << endl;
    answer3();
    cout << endl;

    cout << "4. ServerSocket/ClientSocket — компоненти C++ Builder для TCP." << endl;
    answer4();
    cout << endl;

    cout << "5. Події клієнта та реакція сервера:" << endl;
    answer5();
    cout << endl;

    cout << "6. Кроки мережевого програмування в WinSock:" << endl;
    answer6();
    cout << endl;

    return 0;
}
