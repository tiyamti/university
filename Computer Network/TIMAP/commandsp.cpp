#include "commandsp.h"
#include <QTcpSocket>
#include <QDebug>
#include <QElapsedTimer>
#include <QString>
using namespace std;
commandsp::commandsp(QObject *parent)
    : QObject{parent}
{

}

void commandsp::formRequest(const QString &command, const QString &param1, const QString &param2) {
    QTcpSocket socket;
    socket.connectToHost("127.0.0.1", 8080);

    if (!socket.waitForConnected()) {
        qDebug() << "Connection failed:" << socket.errorString();
        return;
    }
    qDebug() << "Connected to server.\n";

    QString request;
    if (command == "GET") {
        request = "GET "+ param1 + "\r\n";
    } else if (command == "POST") {
        request = "POST " + param1 + " " + param2 + "\r\n";
    } else {
        qDebug() << "Invalid command.\n";
        socket.close();
        return;
    }

    QElapsedTimer timer;
    timer.start();

    qint64 bytesWritten = socket.write(request.toLatin1());
    if (bytesWritten == -1 || bytesWritten != request.size()) {
        qDebug() << "Failed to send request completely. Bytes written:" << bytesWritten << "Expected:" << request.size();
        socket.close();
        return;
    }

    socket.flush();
    QByteArray responseBuffer;
    while (socket.waitForReadyRead(3000)) {
        responseBuffer.append(socket.readAll());
    }

    if (responseBuffer.isEmpty()) {
        qDebug() << "No response from server.";
    } else {
        qDebug() << "Server Response:\n" << QString(responseBuffer) << "\n";
    }

    socket.close();
}

