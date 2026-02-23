#!/bin/bash
# Скрипт компіляції — Практична робота №9
# Запуск: chmod +x build.sh && ./build.sh

echo "=== Генерація MOC файлів ==="
moc 9_server_gui.cpp -o 9_server_gui.moc
moc 9_client_gui.cpp -o 9_client_gui.moc

echo "=== Компіляція сервера ==="
g++ -std=c++11 -fPIC -o server_gui 9_server_gui.cpp \
    $(pkg-config --cflags --libs Qt5Widgets Qt5Network)

echo "=== Компіляція клієнта ==="
g++ -std=c++11 -fPIC -o client_gui 9_client_gui.cpp \
    $(pkg-config --cflags --libs Qt5Widgets Qt5Network)

echo ""
echo "=== Готово! ==="
echo "Запуск сервера:  ./server_gui"
echo "Запуск клієнта:  ./client_gui"
