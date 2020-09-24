#ifndef USER_H
#define USER_H

#include <QString>

class User
{
public:
    User();

    QString getUsername() const;
    void setUsername(const QString &value);

    QString getEmail() const;
    void setEmail(const QString &value);

    QString getPassword() const;
    void setPassword(const QString &value);

private:
    QString username;
    QString email;
    QString password;
};

#endif // USER_H
