#include "clienthandler.h"
#include "userdatabase.h"
#include <QJsonObject>
#include <QJsonDocument>
#include <QStringList>
#include <QDebug>

ClientHandler::ClientHandler(QTcpSocket *socket, QObject *parent)
    : QObject(parent), clientSocket(socket) {}

void ClientHandler::process() {
    connect(clientSocket, &QTcpSocket::readyRead, this, [this]() {
        QString request = QString::fromUtf8(clientSocket->readAll());
        QString response;

        if (request.startsWith("GET")) {
            response = handleGetRequest(request);
        } else if (request.startsWith("POST")) {
            response = handlePostRequest(request);
        } else {
            response = "HTTP/1.1 400 Bad Request\r\n\r\nInvalid request";
        }

        clientSocket->write(response.toUtf8());
        clientSocket->flush();
        clientSocket->disconnectFromHost();

        // Signal the thread to quit when done
        emit finished();
    });
}

QString ClientHandler::handleGetRequest(const QString &request) {
    QStringList requestParts = request.split(" ");
    if (requestParts.size() >= 2 && requestParts[0] == "GET") {
        QString userId = requestParts[1].trimmed();

        QJsonObject user = UserDatabase::getInstance().getUser(userId);
        if (!user.isEmpty()) {
            QJsonDocument doc(user);
            QString userInfo = doc.toJson(QJsonDocument::Compact);
            return QString("HTTP/1.1 200 OK\r\nContent-Type: application/json\r\n\r\n%1").arg(userInfo);
        } else {
            return "HTTP/1.1 404 Not Found\r\n\r\nUser not found";
        }
    }
    return "HTTP/1.1 400 Bad Request\r\n\r\nInvalid request";
}

QString ClientHandler::handlePostRequest(const QString &request) {
    QStringList requestParts = request.split(" ");
    if (requestParts.size() >= 3) {
        QString name = requestParts[1];
        int age = requestParts[2].toInt();
        UserDatabase::getInstance().addUser(name, age);
        return "HTTP/1.1 200 OK\r\n\r\nUser data updated";
    }
    return "HTTP/1.1 400 Bad Request\r\n\r\nInvalid request";
}
