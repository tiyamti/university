#ifndef COMMANDSS_H
#define COMMANDSS_H
#include <QTcpSocket>
#include <QObject>
#include <QDebug>
#include <QElapsedTimer>
using namespace std;
class commandsS: public QObject
{
    Q_OBJECT
public:
    explicit commandsS( QObject *parent = nullptr);
    void statechecker(const QString &ip, int port);
    void checkPort(const QString &ip, quint16 port,const QElapsedTimer &overallTimer);
signals:

private:
    QTcpSocket *socket;
};


#endif // COMMANDSS_H
