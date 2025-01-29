#include <iostream>
#include <QtCore>
#include <QtNetwork>
#include <QSocketNotifier>
#include <unistd.h>

class LoggingServer : public QObject {
    Q_OBJECT
    public:
    QTcpServer *server;
    LoggingServer() {
        server = new QTcpServer();
        if (server->listen(QHostAddress::LocalHost, 5002)) {
            std::cout << "listening\n";
        } else {
            std::cout << "listen failed\n";
        }
        connect(server, &QTcpServer::newConnection, this, &LoggingServer::new_connection);
    }

    void shutdown() {
        server->close();
        delete server;
        QCoreApplication::quit();
    }
    private slots:
    void new_connection() {
        QTcpSocket *socket = server->nextPendingConnection();
        std::cout << "Connection from: " + socket->peerAddress().toString().toStdString() + "\n";
        connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
        connect(socket, &QTcpSocket::readyRead, this, &LoggingServer::read_ready);
    }
    void read_ready() {
        QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
        std::cout << socket->readAll().toStdString();
    }
};
