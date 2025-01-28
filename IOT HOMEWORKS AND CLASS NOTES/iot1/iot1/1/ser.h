#ifndef SER_H
#define SER_H

#include <QObject>

class ser : public QObject
{
    Q_OBJECT
public:
    explicit ser(QObject *parent = nullptr);

signals:
};

#endif // SER_H
