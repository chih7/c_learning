#include "DBManager.h"
#include <fstream>
#include <iostream>
#include <unistd.h>
using namespace std;

User curUser;

AVLTree<User> user_Tree;										//用户树
AVLTree<User>::iterator iter_Tree;								//迭代器

void DBManager::start()											//初始化
{
    ifstream IOFile_User("USER.db",ios::in);					//打开文件输入流
    if (!IOFile_User.is_open())
    {
        cerr<< "Cannot open USER.db. \n";
        system("clear");
        exit(1);
    }
    while(IOFile_User.peek() != EOF){							//直到文件结束
        User user;												//用户节点
        IOFile_User>>user.uid>>user.rname>>user.password;		//文件读入
        user_Tree.insert(user);									//插入用户树
    }
    IOFile_User.close();

    Login();													//显示首届面
}

void DBManager::User_Write()									//刷新db，重新把树全部写入；
{
    ofstream iofileUser("USER.db",ios::out);					//打开文件写入流
    if (!iofileUser.is_open())
    {
        cerr<< "Cannot open USER.db. \n";
        system("clear");
        exit(1);
    }
    for(iter_Tree = user_Tree.begin(); iter_Tree != user_Tree.end(); iter_Tree++)
    {															//写入到文件
        iofileUser<<iter_Tree->uid<<" "<<iter_Tree->rname<<" "<<iter_Tree->password<<"\n";
    }
    iofileUser.close();
}

void DBManager::fresh()											//界面头
{
    char s[] = "               ";
    system("clear");
    cout << s << "-----------------------------------------------" << endl;
    cout << s << "-----------------  用户登录系统  -----------------" << endl;
    cout << s << "--------------  （C）2013. Chih ----------------" << endl;
    cout << s << "-----------------------------------------------" << endl;
    cout << endl << endl;
}

void DBManager::Login(){

AAA:
    fresh();
    cout<<"--------------------------------------\n";
    cout<<"                                       \n";
    cout<<"         欢迎使用用户登录系统             \n";
    cout<<"                                       \n";
    cout<<"--------------------------------------\n";
    cout<<"                                      \n";
    cout<<"            1:用户登录                 \n";
    cout<<"                                      \n";
    cout<<"            2:绘制树                   \n";
    cout<<"                                      \n";
    cout<<"            3:退出系统                 \n";
    cout<<"                                      \n";
    cout<<"--------------------------------------\n";
    cout<<"\n";
    cout<<"请输入1~3进行操作:\n";
    cout<<endl;
    string choice;
    do
    {
        cin>>choice;										//输入控制
        if (choice != "1" && choice != "2" && choice != "3")
        {
            cout<<"输入有误, 请重新输入!\n";
            sleep(1000);
        }
        else
            break;
    } while (1);
    if (choice == "1")
    {
        Login_User();
    }
    if (choice == "2")
    {
        system("clear");
        user_Tree.graph(cout);
        system("PAUSE"); // 按任意键结束
        goto AAA;

    }
    else
    {
        exit(0);
    }
}
void DBManager::Login_User()
{
    fresh();
    string rno_in;
    cout<<"请输入你的账号:\n";
    cin>>rno_in;
    string password = isExisted_User(rno_in);//验证用户并得到密码
    if(password == "None")
    {
        cout<<"不存在该账号!\n";
        sleep(1000);
        Login();
    }
    else if(Judge_Password(password)){
        curUser.uid=rno_in;//从AVL树的节点写入临时User节点
        curUser.password=password;
        curUser.rname=name_User(rno_in);
        Home_User();
    }
}

bool DBManager::Judge_Password(string password)
{
    cout<<endl;
    int degree = 0;
    string keypassword;
    do
    {
        degree++;
        cout<<"请输入密码:";
        cin>>keypassword;
        if( password == keypassword ) return true;
        else
        {
            if(degree <= 2)
            {
                cout<<"密码错误，请重新输入:\n";
                sleep(1000);
                continue;
            }
            else
            {
                cout<<"您已经输入错误超过3次!\n";
                sleep(1000);
                return false;
            }
        }
    }while(1);
}

string DBManager::isExisted_User(string rno)
{
    for (iter_Tree = user_Tree.begin(); iter_Tree != user_Tree.end(); iter_Tree++)
    {
        if (iter_Tree->uid == rno)          //找到AVL树上的节点
        {
            return iter_Tree->password;     //返回密码
        }
    }
    return "None";							//如果用户不存在，返回密码为“None”
}

string DBManager::name_User(string rno)
{
    for (iter_Tree = user_Tree.begin(); iter_Tree != user_Tree.end(); iter_Tree++)
    {
        if (iter_Tree->uid == rno)
        {
            return iter_Tree->rname;
        }
    }
    return "None";
}


User DBManager::Find_User(string rno)//找到用户并返回User对象
{
    for(iter_Tree = user_Tree.begin(); iter_Tree != user_Tree.end(); iter_Tree++)
    {
        if(iter_Tree->uid == rno){
            return *(iter_Tree);
        }
        exit(1);
    }
}
void DBManager::Add_User(User user)
{
    user_Tree.insert(user);//插入AVL树
    User_Write();//写入文件
}

void DBManager::Delete_User(string name)
{
    for(iter_Tree = user_Tree.begin(); iter_Tree != user_Tree.end(); iter_Tree++)
    {
        if(iter_Tree->uid == name){
            user_Tree.remove(*(iter_Tree));////从AVL书中移除节点
            User_Write();//把改变写入文件
            return ;
        }
    }
}
void DBManager::resetPassword()//重置密码界面
{
    fresh();
    string new1,new2;
    cout<<"请输入您的新密码:"<<"\n";
    cin>>new1;
    cout<<"请确认您的新密码:"<<"\n";
    cin>>new2;
    if(new1 != new2)
    {
        cout<<"两次输入不同!"<<"\n";
        Sleep(1000);
    }
    else
    {
        curUser.password = new1;//把新密码输入当前用户curUser
        cout<<"更改密码成功!"<<"\n";
        Sleep(1000);
    }
}
void DBManager::ui_AddUser()//增加用户界面
{
    fresh();
    User tmp;//新建一个临时User
    string newUid;
    string newName;
    cout<<"请输入新用户的用户名:\n";
    cin>>newName;
    tmp.rname=newName;
    cout<<"请输入新用户的用户id:\n";
    cin>>newUid;
    for (iter_Tree = user_Tree.begin(); iter_Tree != user_Tree.end(); iter_Tree++)//判断用户id是否已存在
    {
        if (newUid == iter_Tree->uid)
        {
            cout<<"与已有id重复："<<tmp.uid<<endl;
            cout<<"请重新输入您的id:\n";
            cin>>newUid;
        }
    }
    tmp.uid=newUid;
    string new1Pass,new2Pass;
    cout<<"请输入新用户的新密码:"<<"\n";
    cin>>new1Pass;
    cout<<"请确认新用户的新密码:"<<"\n";
    cin>>new2Pass;
    if(new1Pass != new2Pass)
    {
        cout<<"两次输入不同!"<<"\n";
        Sleep(1000);
    }
    else
    {
        tmp.password = new1Pass;
        cout<<"设置密码成功!"<<"\n";
    }
    Add_User(tmp);
    system("cls");
    user_Tree.graph(cout);
    system("PAUSE"); // 按任意键结束
    Home_User();
}
void DBManager::ui_DelUser()//删除用户界面
{
    fresh();

    string newUid;
    cout<<"请输入待删除用户的id:\n";
    cin>>newUid;
    string password = isExisted_User(newUid);//验证用户并得到密码
    if(password == "None")
    {
        cout<<"不存在该账号!\n";
        Sleep(1000);
        Home_User();
    }
    Delete_User(newUid);				//删除旧节点
    system("cls");
    user_Tree.graph(cout);
    system("PAUSE"); // 按任意键结束
    Home_User();
}

void DBManager::Resetpassword_User()       //重置密码
{
    resetPassword();
    Delete_User(curUser.uid);				//删除旧节点
    Add_User(curUser);						//重新插入密码改过的节点
    Home_User();
}

void DBManager::Home_User()
{
    DBManager::fresh();
    cout<<"--------------------------------------\n";
    cout<<"                                      \n";
    cout<<"    "<<curUser.rname<<"用户";
    cout<<"您好，请进行您的操作            \n";
    cout<<"                                      \n";
    cout<<"--------------------------------------\n";
    cout<<"                                      \n";
    cout<<"            1:增加用户  				 \n";
    cout<<"                                      \n";
    cout<<"            2:删除用户  				 \n";
    cout<<"                                      \n";
    cout<<"            3:修改个人密码              \n";
    cout<<"                                      \n";
    cout<<"            4:返回                     \n";
    cout<<"                                      \n";
    cout<<"--------------------------------------\n";
    cout<<endl;
    cout<<"请输入1~4进行操作:\n";
    cout<<endl;
    string choice;
    do
    {
        cin>>choice;
        if (choice != "1" && choice != "2" && choice != "3" && choice != "4")
        {
            cout<<"输入有误, 请重新输入!\n";
            sleep(1000);
        }
        else
        {
            break;
        }
    } while (1);
    if(choice == "1"){
        ui_AddUser();
    }
    else if(choice == "3"){
        Resetpassword_User();
    }
    else if(choice == "2"){
        ui_DelUser();
    }
    else{
        Login();
    }
}
