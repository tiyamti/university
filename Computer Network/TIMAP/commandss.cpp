#include "commandss.h"
#include <QTcpSocket>
#include <QObject>
#include <QDebug>
#include <QString>
#include <QThread>
#include <QElapsedTimer>
#include <QTimer>
using namespace std;
commandsS::commandsS(QObject *parent)
    : QObject{parent}
 {
}
 void commandsS::checkPort(const QString &ip, quint16 port,const QElapsedTimer &overallTimer) {
     QElapsedTimer timer;
     timer.start();

     QTcpSocket *socket = new QTcpSocket(this);

     connect(socket, &QTcpSocket::connected, [this, socket, ip, port, timer, overallTimer]() {
         qint64 elapsed = timer.elapsed(); // Get the elapsed time for this port check
         qDebug() << "Host is" << ip << "tcp" << port << "open (" << elapsed << "ms)";
         socket->disconnectFromHost();
         socket->deleteLater();
     });

     connect(socket, &QTcpSocket::errorOccurred, [this, socket, ip, port, timer, overallTimer](QTcpSocket::SocketError socketError) {
         qint64 elapsed = timer.elapsed(); // Get the elapsed time for this port check
         if (socketError == QTcpSocket::ConnectionRefusedError) {
             qDebug() << "Host is" << ip << "tcp" << port << "closed (" << elapsed << "ms)";
         } else {
             qDebug() << "Host is" << ip << "tcp" << port << "filtered (" << elapsed << "ms)" << ":" << socket->errorString();
         }
         socket->deleteLater();
     });

     socket->connectToHost(ip, port);


     if (!socket->waitForConnected(3000)) {
         qint64 elapsed = timer.elapsed();
         qDebug() << "Host is" << ip << "tcp" << port << "closed (timeout after" << elapsed << "ms)";
         socket->deleteLater();
     }
 }

 void commandsS::statechecker(const QString &ip, int port = 0) {
     qDebug() << "Starting.............";
     QElapsedTimer overallTimer;
     overallTimer.start();

     if (port > 0) {

         checkPort(ip, port, overallTimer);
     } else {

         for (quint16 p = 1; p <= 1024; ++p) {
             QTimer::singleShot(p * 1000, this, [this, ip, p, overallTimer]() {
                 checkPort(ip, p, overallTimer);
                  QThread::sleep(1);
             });
         }
     }

     QTimer::singleShot(1025 * 1000, this, [overallTimer, ip]() {
         qDebug() << "timap reports for" << ip;
         qDebug() << "timap is done: time:" << overallTimer.elapsed() / 1000.0 << "seconds";
     });
 }
