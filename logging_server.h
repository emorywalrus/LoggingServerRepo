#include <iostream>
#include <QtCore>
#include <QtNetwork>
#include <QSocketNotifier>
#include <unistd.h>

class LoggingServer : public QObject {
    Q_OBJECT
    public:
    QTcpServer server;
    LoggingServer() {
        int port = 5005;
        if (server.listen(QHostAddress::Any, port)) {
            std::cout << "listening on port ";
            std::cout << port;
            std::cout << "\n";
        } else {
            std::cout << "listen failed\n";
        }
        connect(&server, &QTcpServer::newConnection, this, &LoggingServer::new_connection);
    }

    private slots:
    void new_connection() {
        QTcpSocket *socket = server.nextPendingConnection();
        std::cout << "Connection from: " + socket->peerAddress().toString().toStdString() + "\n";
        connect(socket, &QTcpSocket::disconnected, socket, &QTcpSocket::deleteLater);
        connect(socket, &QTcpSocket::readyRead, this, &LoggingServer::read_ready);
    }
    void read_ready() {
        QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
        std::cout << socket->readAll().toStdString();
    }
};

