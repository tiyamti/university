#include "userdatabase.h"

UserDatabase::UserDatabase() {
    users.insert("user1", QJsonObject{{"name", "Alice"}, {"age", 30}});
    users.insert("user2", QJsonObject{{"name", "Bob"}, {"age", 25}});
    users.insert("user3", QJsonObject{{"name", "Charlie"}, {"age", 35}});
}

UserDatabase &UserDatabase::getInstance() {
    static UserDatabase instance;
    return instance;
}

QJsonObject UserDatabase::getUser(const QString &userId) {
    return users.value(userId, QJsonObject());
}

void UserDatabase::addUser(const QString &name, int age) {
    QString newUserId = QString("user%1").arg(users.size() + 1);
    users[newUserId] = QJsonObject{{"name", name}, {"age", age}};
}
