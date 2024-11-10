#ifndef CLIENTHANDLER_H
#define CLIENTHANDLER_H

#include <QObject>
#include <QTcpSocket>
#include <QThread>

class ClientHandler : public QObject {
    Q_OBJECT
public:
    explicit ClientHandler(QTcpSocket *socket, QObject *parent = nullptr);

signals:
    void finished();

public slots:
    void process();

private:
    QTcpSocket *clientSocket;

    QString handleGetRequest(const QString &request);
    QString handlePostRequest(const QString &request);
};

#endif // CLIENTHANDLER_H
