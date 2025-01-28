#ifndef SERIALCOMMUNICATION_H
#define SERIALCOMMUNICATION_H

#include <QObject>

class serialCommunication : public QObject
{
    Q_OBJECT
public:
    explicit serialCommunication(QObject *parent = nullptr);

signals:
};

#endif // SERIALCOMMUNICATION_H
