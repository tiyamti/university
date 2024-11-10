#ifndef USERDATABASE_H
#define USERDATABASE_H

#include <QHash>
#include <QJsonObject>
#include <QString>

class UserDatabase {
public:
    static UserDatabase &getInstance();

    QJsonObject getUser(const QString &userId);
    void addUser(const QString &name, int age);

private:
    UserDatabase();
    QHash<QString, QJsonObject> users;
};

#endif // USERDATABASE_H
