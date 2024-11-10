#ifndef COMMANDP_H
#define COMMANDP_H

#include <QObject>

class commandp : public QObject
{
    Q_OBJECT
public:
    explicit commandp(QObject *parent = nullptr);
    void scanPorts (const QString &ip, const QList<int> &ports) ;
    QMap<int, QString> getServiceNames();
signals:
};

#endif // COMMANDP_H
