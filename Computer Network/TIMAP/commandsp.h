#ifndef COMMANDSP_H
#define COMMANDSP_H

#include <QObject>
#include <QTcpSocket>
class commandsp : public QObject
{
    Q_OBJECT
public:
    explicit commandsp(QObject *parent = nullptr);
    void formRequest(const QString &command, const QString &param1 = "", const QString &param2 = "");
signals:
    void onReadyRead();
private:
    QTcpSocket *socket;
};

#endif // COMMANDSP_H
