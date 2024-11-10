#include "commandsn.h"

#include <QProcess>
#include <QString>
#include <QTextStream>
#include <QDateTime>
#include <QRegularExpression>

commandsn::commandsn(QObject *parent)
    : QObject{parent}
{}

void commandsn::scanSingleIP(const QString &ip) {
    QTextStream out(stdout);
    out << "Starting scan at " << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss") << "\n\n";

    QString baseIP = ip;

    if (baseIP.endsWith('.')) {
        for (int i = 1; i <= 254; ++i) {
            QString fullIP = QString("%1%2").arg(baseIP).arg(i);
            scanIP(fullIP);
        }
    } else if (baseIP.count('.') == 3) {
        scanIP(baseIP);
    } else {
        out << "Invalid IP format. Please provide a valid IP or the first three parts of an IP.\n";
    }

    out << "\nScan complete at " << QDateTime::currentDateTime().toString("yyyy-MM-dd HH:mm:ss") << "\n";
}

void commandsn::scanIP(const QString &ip) {
    QTextStream out(stdout);

    QProcess pingProcess;
#ifdef Q_OS_WIN
    pingProcess.start("ping", QStringList() << "-n" << "1" << ip);//windows
#else
    pingProcess.start("ping", QStringList() << "-c" << "1" << ip); //linux or mac
#endif
    pingProcess.waitForFinished();

    QString output = pingProcess.readAllStandardOutput();


    out << "Ping Output: " << output << "\n";

    QRegularExpression regex("time<([0-9.]+)ms");
    QRegularExpressionMatch match = regex.match(output);

    if (match.hasMatch()) {
        QString responseTime = match.captured(1);
        out << QString("Host %1 is UP (%2 ms)\n").arg(ip).arg(responseTime);
    } else {
        out << QString("Host %1 is DOWN or not responding to ping.\n").arg(ip);
    }
}
