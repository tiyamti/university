#include "server.h"
#include "clienthandler.h"
#include <QTcpSocket>
#include <QDebug>
#include <QThread>
Server::Server(QObject *parent) : QObject(parent) {
    server = new QTcpServer(this);
}

void Server::startServer() {
    if (!server->listen(QHostAddress::Any, 8080)) {
        qCritical() << "Server could not start!";
    } else {
        qDebug() << "Server is listening on port 8080";
        connect(server, &QTcpServer::newConnection, this, &Server::onNewConnection);
    }
}

void Server::onNewConnection() {
    QTcpSocket *clientSocket = server->nextPendingConnection();
    ClientHandler *clientHandler = new ClientHandler(clientSocket);

    QThread *thread = new QThread;
    clientHandler->moveToThread(thread);

    connect(thread, &QThread::started, clientHandler, &ClientHandler::process);
    connect(clientHandler, &ClientHandler::finished, thread, &QThread::quit);
    connect(clientHandler, &ClientHandler::finished, clientHandler, &ClientHandler::deleteLater);
    connect(thread, &QThread::finished, thread, &QThread::deleteLater);

    thread->start();
}
