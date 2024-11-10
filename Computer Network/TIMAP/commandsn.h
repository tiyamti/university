#ifndef COMMANDSN_H
#define COMMANDSN_H

#include <QObject>
#include <QString>

class commandsn : public QObject {
    Q_OBJECT
public:
    explicit commandsn(QObject *parent = nullptr);
    void scanSingleIP(const QString &ip);
    void scanIP(const QString &ip);
};

#endif // COMMANDSN_H
