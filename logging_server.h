#include <iostream>
#include <QtCore>
#include <QtNetwork>
#include <QSocketNotifier>
#include <unistd.h>

class LoggingServer : public QObject {
    Q_OBJECT
    public:
    QTcpServer *server;
    QSocketNotifier *notifier;
    LoggingServer() {
        server = new QTcpServer();
        if (server->listen(QHostAddress::LocalHost, 5678)) {
            std::cout << "listening\n";
        }
        connect(server, &QTcpServer::newConnection, this, &LoggingServer::new_connection);
        notifier = new QSocketNotifier(STDIN_FILENO, QSocketNotifier::Read);
        connect(notifier, &QSocketNotifier::activated, this, &LoggingServer::new_input);
    }
    void shutdown() {
        server->close();
        delete server;
        delete notifier;
        QCoreApplication::quit();
    }
    private slots:
    void new_connection() {
        QTcpSocket *socket = server->nextPendingConnection();
        std::cout << "Connection from: " + socket->peerAddress().toString().toStdString() + "\n";
        connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
    }
    void new_input() {
        std::string input;
        std::getline(std::cin, input);
        if (input == "quit") {
            shutdown();
        }
    }
};