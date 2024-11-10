#ifndef COMMANDR_H
#define COMMANDR_H
#include <QObject>
#include <QCoreApplication>
#include <QTcpSocket>
#include <QElapsedTimer>
#include <QMap>
#include <QDebug>
#include <QString>
class commandr : public QObject
{
    Q_OBJECT
public:
    explicit commandr(QObject *parent = nullptr);
    void scanPorts(const QString &ip);
    QMap<int, QString> getServiceNames();
signals:
private:
    QTcpSocket *socket;
};

#endif // COMMANDR_H
