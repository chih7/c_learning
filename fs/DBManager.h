#ifndef DBMANAGER_H
#define DBMANAGER_H
#include<cstdlib>
#include <string>
#include "User.h"

using namespace std;

class DBManager
{
public:
    static void fresh();                                    //界面头
    static void Login();									//登录界面
    void start();											//初始化数据（从文件中读入）显示首界面
    static void User_Write();								//保存用户数据
    static bool Judge_Password(string);						//读密码
    static void resetPassword();							//设置密码
    static void ui_AddUser();                               //增加用户
    static void ui_DelUser();                               //删除用户
    static string isExisted_User(string);					//判断用户是否存在并返回密码
    static string name_User(string);						//判断用户是否存在并返回密码
    static void Login_User();								//登录界面
    static void Home_User();								//登录后界面
    static User Find_User(string);							//找到用户
    static void Delete_User(string);						//删除用户
    static void Add_User(User user);						//增加用户
    static void Resetpassword_User();				       	//改密码
};
#endif // DBMANAGER_H
