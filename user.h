#ifndef USER_H
#define USER_H
#include <QString>
#include <vector>

class User {
private:
    QString username;
    QString password;
    QString role;


public:
    User(const QString& username, const QString& password, const QString& role);
    QString getUsername() const;
    QString getPassword() const;
    QString getRole() const;
    void setUsername(const QString& uname);
    void setPassword(const QString& pword);
    void setRole(const QString& r);
    QString toString() const;
};


#endif // USER_H
