#ifndef FS_H
#define FS_H
#include<iostream>
#include<string>
#include<stack>
#include<time.h>

using namespace std;

struct inode
{
    int uid;  //使用者id
    int gid;  //使用组id
    time_t i_atime;  //最后访问时间
    time_t i_mtime;  //最后修改时间
    time_t i_ctime;  //最后改变时间
    int i_file;  //文件id
    string fileName;  //文件名
    int size;         //文件大小
    string content;   //文件内容
    inode * nextInode=NULL;  //同一目录下的下一个文件

    inode(string filename){
        this->fileName = filename;
        size = 0;
        nextInode = NULL;
    }

    inode(string filename, string content){
        this->fileName = filename;
        this->content = content;
        this->size = content.length();
        nextInode = NULL;
    }

    inode(inode * file){
        fileName = file->fileName;
        content = file->content;
        size = file->size;
        nextInode = NULL;
    }
};

struct dentry
{
    int uid;  //使用者id
    int gid;  //使用组id
    time_t i_atime;  //最后访问时间
    time_t i_mtime;  //最后修改时间
    time_t i_ctime;  //最后改变时间
    int i_dir;  //目录id
    string dirName;  //目录名
    dentry * nextDir = NULL;   //同一父目录下的下一个目录
    dentry * dirList;    //该目录下的目录
    inode * inodeList;  //该目录下的文件
    dentry(string dirName){
        this->dirName = dirName;
        nextDir = NULL;
        dirList = NULL;
        inodeList = NULL;
    }
};
class files{

public:
    files()                  //构造函数
    {
        root = new dentry("root");
        curDir = root;
        tmpFile = NULL;
        tmpDir = NULL;
    }
    ~files()                  //析构函数
    {
        _reDeleteDir(root);
    }
    void man();                    //查看帮助列表
    void pwd();                    //显示当前路径
    void ls();                     //打印当前目录的清单
    void touch(string filename);   //创建文件
    void mkdir(string dirname);    //创建目录
    void cd(string dirname);  //打开目录
    void retPreDir();              //返回上级目录
    void rm(string filename); //删除文件
    void renameFile(string oldname, string newname);  //重命名文件
    void cat(string filename);   //打开文件
    void vi(string filename);     //编辑文件
    void vim(string filename);     //编辑文件
    void cp(string filename);     //复制文件
    void pasteFile();             //粘贴文件
    void rmdir(string dirname);   //删除目录
    void comHelp(string command); //查看帮助信息
    void renameDir(string oldname, string newname);  //重命名目录
    void cpDir(string dirname);    //复制目录
    void pasteDir();               //粘贴目录

private:
    dentry * root;      //根目录
    dentry * curDir;    //当前目录
    inode * tmpFile;    //用于拷贝文件时的临时文件
    dentry * tmpDir;    //用于拷贝目录时的临时目录
    stack<dentry*> dirStack;  //用于存放上级路径的栈

private:
    void _reDeleteDir(dentry * dir);     //递归删除目录
    dentry* _reCopyDir(dentry * dir);       //递归复制目录
};

#endif // FS_H
