/*
 * Практична робота № 9 — Мережевий чат
 * Файл: 9_server_gui.cpp
 * Серверний додаток з графічним інтерфейсом (Qt5)
 *
 * Компіляція:
 *   g++ -o server_gui 9_server_gui.cpp \
 *       $(pkg-config --cflags --libs Qt5Widgets Qt5Network) \
 *       -fPIC -std=c++11
 */

#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QGridLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QListWidget>
#include <QTimer>
#include <QTime>
#include <QGroupBox>
#include <QStatusBar>
#include <QTcpServer>
#include <QTcpSocket>
#include <QHostAddress>
#include <QNetworkInterface>
#include <QMessageBox>

// ─── Головне вікно сервера ───────────────────────────────────────────────────
class ServerWindow : public QMainWindow {
    Q_OBJECT

    QTcpServer*  tcpServer;
    QList<QTcpSocket*> clients;
    QMap<QTcpSocket*, QString> nicknames;

    // UI елементи
    QLineEdit*   edIP;
    QLineEdit*   edPort;
    QPushButton* btnSwitch;
    QTextEdit*   mLog;
    QListWidget* lbUsers;
    QLabel*      lblTime;
    QLabel*      lblStatus;
    QTimer*      timerClock;

public:
    ServerWindow(QWidget* parent = nullptr) : QMainWindow(parent) {
        setWindowTitle("Серверне застосування — Чат");
        setMinimumSize(700, 500);

        tcpServer = new QTcpServer(this);
        connect(tcpServer, &QTcpServer::newConnection,
                this, &ServerWindow::onNewConnection);

        buildUI();

        // Таймер для годинника
        timerClock = new QTimer(this);
        connect(timerClock, &QTimer::timeout, this, &ServerWindow::updateClock);
        timerClock->start(1000);
        updateClock();

        // Отримати локальний IP
        for (auto& addr : QNetworkInterface::allAddresses()) {
            if (addr.protocol() == QAbstractSocket::IPv4Protocol &&
                addr != QHostAddress::LocalHost) {
                edIP->setText(addr.toString());
                break;
            }
        }
        if (edIP->text().isEmpty())
            edIP->setText("127.0.0.1");

        edPort->setText("8888");
    }

private:
    void buildUI() {
        QWidget* central = new QWidget(this);
        setCentralWidget(central);
        QVBoxLayout* mainLayout = new QVBoxLayout(central);

        // ── Верхня панель (IP, Port, кнопка, час) ──
        QGroupBox* topGroup = new QGroupBox("Налаштування сервера");
        QHBoxLayout* topLayout = new QHBoxLayout(topGroup);

        topLayout->addWidget(new QLabel("IP:"));
        edIP = new QLineEdit();
        edIP->setMaximumWidth(150);
        topLayout->addWidget(edIP);

        topLayout->addWidget(new QLabel("Порт:"));
        edPort = new QLineEdit("8888");
        edPort->setMaximumWidth(80);
        topLayout->addWidget(edPort);

        btnSwitch = new QPushButton("Start!");
        btnSwitch->setMinimumWidth(100);
        btnSwitch->setStyleSheet("QPushButton { background: #4CAF50; color: white; "
                                 "font-weight: bold; padding: 5px; border-radius: 4px; }"
                                 "QPushButton:hover { background: #45a049; }");
        connect(btnSwitch, &QPushButton::clicked, this, &ServerWindow::onToggleServer);
        topLayout->addWidget(btnSwitch);

        topLayout->addStretch();
        lblTime = new QLabel("00:00:00");
        lblTime->setStyleSheet("font-size: 18px; font-weight: bold; color: #333;");
        topLayout->addWidget(lblTime);

        mainLayout->addWidget(topGroup);

        // ── Центральна частина (лог + список юзерів) ──
        QHBoxLayout* centerLayout = new QHBoxLayout();

        // Лог сесії
        QGroupBox* logGroup = new QGroupBox("Лог сесії");
        QVBoxLayout* logLayout = new QVBoxLayout(logGroup);
        mLog = new QTextEdit();
        mLog->setReadOnly(true);
        mLog->setStyleSheet("font-family: monospace; font-size: 12px;");
        logLayout->addWidget(mLog);
        centerLayout->addWidget(logGroup, 3);

        // Список користувачів
        QGroupBox* usersGroup = new QGroupBox("Користувачі онлайн");
        QVBoxLayout* usersLayout = new QVBoxLayout(usersGroup);
        lbUsers = new QListWidget();
        lbUsers->setStyleSheet("font-size: 13px;");
        usersLayout->addWidget(lbUsers);
        centerLayout->addWidget(usersGroup, 1);

        mainLayout->addLayout(centerLayout);

        // ── Статусний рядок ──
        lblStatus = new QLabel("Сервер зупинено");
        statusBar()->addWidget(lblStatus);
    }

    void addLog(const QString& msg) {
        mLog->append("[" + QTime::currentTime().toString("hh:mm:ss") + "] " + msg);
    }

    QString getUserList() {
        QString list = "#";
        for (int i = 0; i < lbUsers->count(); ++i)
            list += lbUsers->item(i)->text() + "\n";
        return list;
    }

    void broadcast(const QString& msg, QTcpSocket* except = nullptr) {
        for (auto* c : clients) {
            if (c != except)
                c->write(msg.toUtf8());
        }
    }

private slots:
    void updateClock() {
        lblTime->setText(QTime::currentTime().toString("hh:mm:ss"));
    }

    void onToggleServer() {
        if (!tcpServer->isListening()) {
            // Запуск
            int port = edPort->text().toInt();
            if (!tcpServer->listen(QHostAddress::Any, port)) {
                QMessageBox::critical(this, "Помилка",
                    "Не вдалося запустити сервер!\n" + tcpServer->errorString());
                return;
            }
            addLog("Сервер запущено на порту " + edPort->text());
            btnSwitch->setText("Shutdown!");
            btnSwitch->setStyleSheet("QPushButton { background: #f44336; color: white; "
                                     "font-weight: bold; padding: 5px; border-radius: 4px; }"
                                     "QPushButton:hover { background: #da190b; }");
            edIP->setEnabled(false);
            edPort->setEnabled(false);
            lblStatus->setText("Сервер працює на порту " + edPort->text());
        } else {
            // Зупинка
            tcpServer->close();
            for (auto* c : clients) c->disconnectFromHost();
            clients.clear();
            nicknames.clear();
            lbUsers->clear();
            addLog("Сервер зупинено.");
            btnSwitch->setText("Start!");
            btnSwitch->setStyleSheet("QPushButton { background: #4CAF50; color: white; "
                                     "font-weight: bold; padding: 5px; border-radius: 4px; }");
            edIP->setEnabled(true);
            edPort->setEnabled(true);
            lblStatus->setText("Сервер зупинено");
        }
    }

    void onNewConnection() {
        while (tcpServer->hasPendingConnections()) {
            QTcpSocket* socket = tcpServer->nextPendingConnection();
            clients.append(socket);
            nicknames[socket] = "Guest";

            connect(socket, &QTcpSocket::readyRead,
                    this, &ServerWindow::onClientRead);
            connect(socket, &QTcpSocket::disconnected,
                    this, &ServerWindow::onClientDisconnect);

            addLog("Нове підключення з " + socket->peerAddress().toString());
            lblStatus->setText("Сервер працює | Клієнтів: " +
                               QString::number(clients.size()));
        }
    }

    void onClientRead() {
        QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
        if (!socket) return;

        QString msg = QString::fromUtf8(socket->readAll()).trimmed();
        if (msg.isEmpty()) return;

        // Реєстрація
        if (msg.startsWith("#")) {
            QString nick = msg.mid(1);
            nicknames[socket] = nick;
            lbUsers->addItem(nick);
            addLog("Підключився: " + nick +
                   " (" + socket->peerAddress().toString() + ")");
            broadcast(getUserList());
            broadcast("SERVER~" + nick + " приєднався до чату.");
        }
        else {
            // FROM#TO~TEXT або All#FROM~TEXT
            int hashPos  = msg.indexOf('#');
            int tildePos = msg.indexOf('~');
            if (hashPos < 0 || tildePos < 0) return;

            QString from = msg.left(hashPos);
            QString to   = msg.mid(hashPos + 1, tildePos - hashPos - 1);
            QString text = msg.mid(tildePos + 1);

            addLog("<" + from + "> -> <" + to + ">: " + text);

            if (to == "All") {
                broadcast(from + "~" + text);
            } else {
                // Приватне
                for (auto* c : clients) {
                    if (nicknames[c] == to || nicknames[c] == from)
                        c->write((from + "~[PM] " + text).toUtf8());
                }
            }
        }
    }

    void onClientDisconnect() {
        QTcpSocket* socket = qobject_cast<QTcpSocket*>(sender());
        if (!socket) return;

        QString nick = nicknames.value(socket, "Guest");
        addLog("Відключився: " + nick);

        // Видалити зі списку
        for (int i = 0; i < lbUsers->count(); ++i) {
            if (lbUsers->item(i)->text() == nick) {
                delete lbUsers->takeItem(i);
                break;
            }
        }
        clients.removeAll(socket);
        nicknames.remove(socket);
        socket->deleteLater();

        broadcast(getUserList());
        broadcast("SERVER~" + nick + " покинув чат.");
        lblStatus->setText("Сервер працює | Клієнтів: " +
                           QString::number(clients.size()));
    }
};

#include "9_server_gui.moc"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    app.setStyle("Fusion");
    ServerWindow win;
    win.show();
    return app.exec();
}
