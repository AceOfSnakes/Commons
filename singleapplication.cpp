#include "singleapplication.h"
#include <QLocalSocket>
#ifdef Q_OS_WIN
#include <windows.h>
#endif

SingleApplication::SingleApplication(const QString &uniqueKey, QObject *parent):
    QObject(parent), serverName(uniqueKey) {}

bool SingleApplication::checkInstance() {
    QLocalSocket socket;
    socket.connectToServer(serverName);

    if (socket.waitForConnected(500)) {
        // 1. Tell primary instance to wake up
        socket.write("WAKE_UP");
        socket.waitForBytesWritten(500);

        // 2. Wait for the primary instance to send its Process ID (PID)
        if (socket.waitForReadyRead(500)) {
            QByteArray reply = socket.readAll();
            reply.toLongLong();
        }

        return false; // Secondary copy exits cleanly
    }

    // No existing instance found. Start the server...
    server = new QLocalServer(this);
    connect(server, &QLocalServer::newConnection, this, &SingleApplication::handleNewConnection);

    QLocalServer::removeServer(serverName);
    server->listen(serverName);
    return true;
}

void SingleApplication::handleNewConnection() {
    QLocalSocket *socket = server->nextPendingConnection();
    connect(socket, &QLocalSocket::readyRead, this, [this, socket]() {
        if (socket->readAll() == "WAKE_UP") {
            emit wakeUpRequested(); // Notify MainWindow to show up
        }
        socket->disconnectFromServer();
        socket->deleteLater();
    });
}