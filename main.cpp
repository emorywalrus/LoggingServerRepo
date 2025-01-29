#include <iostream>
#include <QCoreApplication>
#include "logging_server.h"



int main(int argc, char** argv) {
    QCoreApplication app(argc, argv);
    LoggingServer server;
    return app.exec();
}
