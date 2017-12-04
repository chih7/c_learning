#ifndef USER_H
#define USER_H
#include <string>
#include <iostream>
using namespace std;

class User
{
public:
    string uid;										//账号
    string rname;									//名字
    string password;								//密码
public:
    User() : uid(NULL),rname(NULL),password(NULL){} //构造函数
    ~User(){}										//析构函数
    bool operator<(const User & user) const;        //重载小于运算符
    bool operator>(const User & user) const;        //重载大于运算符
    bool operator==(const User & user) const;       //重载等于运算符
    friend ostream & operator<<(ostream & out, const User & t);//重载<<运算符
};
bool User::operator<(const User & user) const{
    return uid < user.uid ||
        (uid == user.uid && password < user.password);
}

bool User::operator>(const User & user) const{
    return uid > user.uid ||
        (uid == user.uid && password > user.password);
}

bool User::operator==(const User & user) const{
    return uid == user.uid ||
        (uid == user.uid && password == user.password);
}

ostream & operator<<(ostream & out, const User & t)
{
    out<<t.uid;
    return out;
}

#endif // USER_H
