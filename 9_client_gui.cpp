/*
 * Практична робота № 9 — Мережевий чат
 * Файл: 9_client_gui.cpp
 * Клієнтський додаток з графічним інтерфейсом (Qt5)
 *
 * Компіляція:
 *   g++ -o client_gui 9_client_gui.cpp \
 *       $(pkg-config --cflags --libs Qt5Widgets Qt5Network) \
 *       -fPIC -std=c++11
 */

#include <QApplication>
#include <QMainWindow>
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>
#include <QTextEdit>
#include <QListWidget>
#include <QTimer>
#include <QTime>
#include <QGroupBox>
#include <QStatusBar>
#include <QTcpSocket>
#include <QHostAddress>
#include <QMessageBox>
#include <QKeyEvent>
#include <QScrollBar>

// ─── Поле вводу з обробкою Enter ─────────────────────────────────────────────
class ChatInput : public QLineEdit {
    Q_OBJECT
signals:
    void enterPressed();
protected:
    void keyPressEvent(QKeyEvent* e) override {
        if (e->key() == Qt::Key_Return || e->key() == Qt::Key_Enter)
            emit enterPressed();
        else
            QLineEdit::keyPressEvent(e);
    }
};

// ─── Головне вікно клієнта ───────────────────────────────────────────────────
class ClientWindow : public QMainWindow {
    Q_OBJECT

    QTcpSocket* socket;

    // UI
    QLineEdit*   edNickname;
    QLineEdit*   edAddress;
    QLineEdit*   edPort;
    QPushButton* btnConnect;
    QTextEdit*   mLog;
    QListWidget* lbUsers;
    ChatInput*   edMessage;
    QPushButton* btnSend;
    QLabel*      lblTime;
    QLabel*      lblStatus;
    QTimer*      timerClock;

    QString myNick;

public:
    ClientWindow(QWidget* parent = nullptr) : QMainWindow(parent) {
        setWindowTitle("Клієнтське застосування — Чат");
        setMinimumSize(750, 550);

        socket = new QTcpSocket(this);
        connect(socket, &QTcpSocket::connected,    this, &ClientWindow::onConnected);
        connect(socket, &QTcpSocket::disconnected, this, &ClientWindow::onDisconnected);
        connect(socket, &QTcpSocket::readyRead,    this, &ClientWindow::onDataReceived);
        connect(socket, QOverload<QAbstractSocket::SocketError>::of(&QTcpSocket::errorOccurred),
                this, &ClientWindow::onError);

        buildUI();

        timerClock = new QTimer(this);
        connect(timerClock, &QTimer::timeout, this, &ClientWindow::updateClock);
        timerClock->start(1000);
        updateClock();

        setInputEnabled(false);
    }

private:
    void buildUI() {
        QWidget* central = new QWidget(this);
        setCentralWidget(central);
        QVBoxLayout* mainLayout = new QVBoxLayout(central);

        // ── Панель підключення ──
        QGroupBox* connGroup = new QGroupBox("Налаштування підключення");
        QHBoxLayout* connLayout = new QHBoxLayout(connGroup);

        connLayout->addWidget(new QLabel("Нікнейм:"));
        edNickname = new QLineEdit("User1");
        edNickname->setMaximumWidth(120);
        connLayout->addWidget(edNickname);

        connLayout->addWidget(new QLabel("Адреса сервера:"));
        edAddress = new QLineEdit("127.0.0.1");
        edAddress->setMaximumWidth(140);
        connLayout->addWidget(edAddress);

        connLayout->addWidget(new QLabel("Порт:"));
        edPort = new QLineEdit("8888");
        edPort->setMaximumWidth(70);
        connLayout->addWidget(edPort);

        btnConnect = new QPushButton("Connect!");
        btnConnect->setMinimumWidth(110);
        btnConnect->setStyleSheet("QPushButton { background: #2196F3; color: white; "
                                  "font-weight: bold; padding: 5px; border-radius: 4px; }"
                                  "QPushButton:hover { background: #1976D2; }");
        connect(btnConnect, &QPushButton::clicked, this, &ClientWindow::onToggleConnect);
        connLayout->addWidget(btnConnect);

        connLayout->addStretch();
        lblTime = new QLabel("00:00:00");
        lblTime->setStyleSheet("font-size: 18px; font-weight: bold; color: #333;");
        connLayout->addWidget(lblTime);

        mainLayout->addWidget(connGroup);

        // ── Центр (чат + список юзерів) ──
        QHBoxLayout* centerLayout = new QHBoxLayout();

        // Лог чату
        QGroupBox* chatGroup = new QGroupBox("Лог сесії");
        QVBoxLayout* chatLayout = new QVBoxLayout(chatGroup);
        mLog = new QTextEdit();
        mLog->setReadOnly(true);
        mLog->setStyleSheet("font-family: monospace; font-size: 12px; "
                            "background: #fafafa;");
        chatLayout->addWidget(mLog);
        centerLayout->addWidget(chatGroup, 3);

        // Список юзерів
        QGroupBox* usersGroup = new QGroupBox("Список користувачів");
        QVBoxLayout* usersLayout = new QVBoxLayout(usersGroup);
        lbUsers = new QListWidget();
        lbUsers->setStyleSheet("font-size: 13px;");
        usersLayout->addWidget(new QLabel("Онлайн:"));
        usersLayout->addWidget(lbUsers);
        centerLayout->addWidget(usersGroup, 1);

        mainLayout->addLayout(centerLayout);

        // ── Панель відправки ──
        QGroupBox* sendGroup = new QGroupBox();
        QHBoxLayout* sendLayout = new QHBoxLayout(sendGroup);

        edMessage = new ChatInput();
        edMessage->setPlaceholderText("Введіть повідомлення... (Enter — відправити всім, "
                                       "виберіть користувача для приватного)");
        edMessage->setEnabled(false);
        connect(edMessage, &ChatInput::enterPressed, this, &ClientWindow::onSendMessage);
        sendLayout->addWidget(edMessage);

        btnSend = new QPushButton("Надіслати");
        btnSend->setMinimumWidth(100);
        btnSend->setEnabled(false);
        btnSend->setStyleSheet("QPushButton { background: #4CAF50; color: white; "
                               "font-weight: bold; padding: 5px; border-radius: 4px; }"
                               "QPushButton:hover { background: #45a049; }"
                               "QPushButton:disabled { background: #aaa; }");
        connect(btnSend, &QPushButton::clicked, this, &ClientWindow::onSendMessage);
        sendLayout->addWidget(btnSend);

        mainLayout->addWidget(sendGroup);

        // Статусний рядок
        lblStatus = new QLabel("Не підключено");
        statusBar()->addWidget(lblStatus);
    }

    void addLog(const QString& msg, const QString& color = "#333") {
        QString time = QTime::currentTime().toString("hh:mm:ss");
        mLog->append(QString("<span style='color:#888'>[%1]</span> "
                             "<span style='color:%2'>%3</span>")
                     .arg(time).arg(color).arg(msg));
        mLog->verticalScrollBar()->setValue(mLog->verticalScrollBar()->maximum());
    }

    void setInputEnabled(bool en) {
        edMessage->setEnabled(en);
        btnSend->setEnabled(en);
    }

private slots:
    void updateClock() {
        lblTime->setText(QTime::currentTime().toString("hh:mm:ss"));
    }

    void onToggleConnect() {
        if (socket->state() == QAbstractSocket::UnconnectedState) {
            // Підключення
            myNick = edNickname->text().trimmed();
            if (myNick.isEmpty()) myNick = "Guest";
            QString host = edAddress->text().trimmed();
            int port = edPort->text().toInt();

            socket->connectToHost(host, port);
            addLog("Підключаємося до " + host + ":" + QString::number(port) + "...", "#2196F3");
            btnConnect->setEnabled(false);
        } else {
            // Відключення
            socket->disconnectFromHost();
        }
    }

    void onConnected() {
        addLog("З'єднання встановлено! Вітаємо, " + myNick + "!", "#4CAF50");
        socket->write(("#" + myNick).toUtf8());

        btnConnect->setText("Disconnect!");
        btnConnect->setEnabled(true);
        btnConnect->setStyleSheet("QPushButton { background: #f44336; color: white; "
                                  "font-weight: bold; padding: 5px; border-radius: 4px; }");
        edNickname->setEnabled(false);
        edAddress->setEnabled(false);
        edPort->setEnabled(false);
        setInputEnabled(true);
        lblStatus->setText("Підключено як: " + myNick);
    }

    void onDisconnected() {
        addLog("Відключено від сервера.", "#f44336");
        lbUsers->clear();
        btnConnect->setText("Connect!");
        btnConnect->setEnabled(true);
        btnConnect->setStyleSheet("QPushButton { background: #2196F3; color: white; "
                                  "font-weight: bold; padding: 5px; border-radius: 4px; }");
        edNickname->setEnabled(true);
        edAddress->setEnabled(true);
        edPort->setEnabled(true);
        setInputEnabled(false);
        lblStatus->setText("Не підключено");
    }

    void onDataReceived() {
        QString msg = QString::fromUtf8(socket->readAll()).trimmed();
        if (msg.isEmpty()) return;

        // Список користувачів
        if (msg.startsWith("#")) {
            lbUsers->clear();
            QStringList users = msg.mid(1).split("\n", Qt::SkipEmptyParts);
            for (auto& u : users)
                if (!u.trimmed().isEmpty())
                    lbUsers->addItem(u.trimmed());
            return;
        }

        // FROM~TEXT
        int tildePos = msg.indexOf('~');
        if (tildePos < 0) return;
        QString from = msg.left(tildePos);
        QString text = msg.mid(tildePos + 1);

        if (from == "SERVER") {
            addLog("*** " + text + " ***", "#FF9800");
        } else if (from == myNick) {
            addLog("<b>" + from + "</b>: " + text, "#1976D2");
        } else {
            addLog("<b>" + from + "</b>: " + text, "#333");
        }
    }

    void onSendMessage() {
        QString text = edMessage->text().trimmed();
        if (text.isEmpty()) return;

        // Якщо вибрано юзера — приватне, інакше всім
        QString to = "All";
        if (lbUsers->currentItem() && lbUsers->currentItem()->text() != myNick)
            to = lbUsers->currentItem()->text();

        QString msg = myNick + "#" + to + "~" + text;
        socket->write(msg.toUtf8());

        if (to != "All")
            addLog("<b>[PM → " + to + "]</b> " + text, "#9C27B0");

        edMessage->clear();
        lbUsers->clearSelection();
    }

    void onError(QAbstractSocket::SocketError) {
        addLog("Помилка: " + socket->errorString(), "#f44336");
        btnConnect->setEnabled(true);
        lblStatus->setText("Помилка з'єднання");
    }
};

#include "9_client_gui.moc"

int main(int argc, char* argv[]) {
    QApplication app(argc, argv);
    app.setStyle("Fusion");
    ClientWindow win;
    win.show();
    return app.exec();
}
