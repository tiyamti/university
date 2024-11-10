#ifndef USERTABLE_H
#define USERTABLE_H

#include <QObject>
#include <QDebug>

class usertable : public QObject
{
    Q_OBJECT
public:
    explicit usertable(QObject *parent = nullptr);
    void menu();
signals:
};

#endif // USERTABLE_H
