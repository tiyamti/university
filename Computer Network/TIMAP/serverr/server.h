#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>


class Server : public QObject {
    Q_OBJECT

public:
    Server(QObject *parent = nullptr);
    void startServer();

private slots:
    void onNewConnection();

private:
    QTcpServer *server;
};

#endif // SERVER_H
