#include"fs.h"
#include<sstream>

files fs;

void init()
{
    const int SIZE_CHAR = 8;  //生成32 + 1位C Style字符串
    const char CCH[] = "0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char ch[SIZE_CHAR + 1] = {0};
    srand((unsigned)time(0));
    for(int j =0; j<20; j++){
        for (int i = 0; i < SIZE_CHAR; ++i)
        {
            int x = rand() % (sizeof(CCH) - 1);

            ch[i] = CCH[x];
        }
        string name(ch);
        fs.touch(name);
    }
    for(int j =0; j<8; j++){
        for (int i = 0; i < SIZE_CHAR; ++i)
        {
            int x = rand() % (sizeof(CCH) - 1);

            ch[i] = CCH[x];
        }
        string name(ch);
        fs.mkdir(name);
    }
    ////////////////////////////////
    /// \ for linux  \\\////////////
    ////////////////////////////////
    system("clear");
}

int main()
{

//    cout<<"请输入用户ID:\n";
//    cin>>user.uid;
//    cout<<"请输入用户名:\n";
//    cin>>user.rname;
    init();
    string line;
    printf("输入\"help\"获得帮助\n");
    fs.pwd();

    while (getline(cin, line)){
        istringstream sin(line);//分离空格
        string com, arg1, arg2;
        sin >> com >> arg1;
        if (arg1 == "help")
            fs.comHelp(com);
        else{

            if (com == "ls"){
                fs.ls();
            }
            else if (com == "cd"){
                if (arg1 == "")
                    cout << "目录名不能为空。\n\n";
                else
                    fs.cd(arg1);
            }
            else if (com == "cd.."){
                fs.retPreDir();
            }
            else if (com == "touch"){
                if (arg1 == "")
                    cout << "文件名不能为空。\n\n";
                else
                    fs.touch(arg1);
            }
            else if (com == "rm"){
                if (arg1 == "")
                    cout << "文件名不能为空。\n\n";
                else
                    fs.rm(arg1);
            }
            else if (com == "re"){
                sin >> arg2;
                if (arg1 == "" || arg2 == "")
                    cout << "文件名不能为空。\n\n";
                else
                    fs.renameFile(arg1, arg2);
            }
            else if (com == "cat"){
                if (arg1 == "")
                    cout << "文件名不能为空。\n\n";
                else
                    fs.cat(arg1);
            }
            else if (com == "vi"){
                if (arg1 == "")
                    cout << "文件名不能为空。\n\n";
                else
                    fs.vi(arg1);
            }
            else if (com == "vim"){
                if (arg1 == "")
                    cout << "文件名不能为空。\n\n";
                else
                    fs.vim(arg1);
            }
            else if (com == "cp"){
                if (arg1 == "")
                    cout << "文件名不能为空。\n\n";
                else
                    fs.cp(arg1);
            }
            else if (com == "paste"){
                fs.pasteFile();
            }
            else if (com == "mkdir"){
                if (arg1 == "")
                    cout << "目录名不能为空。\n\n";
                else
                    fs.mkdir(arg1);
            }
            else if (com == "rmdir"){
                if (arg1 == "")
                    cout << "目录名不能为空。\n\n";
                else
                    fs.rmdir(arg1);
            }
            else if (com == "redir"){
                sin >> arg2;
                if (arg1 == "" || arg2 == "")
                    cout << "目录名不能为空。\n\n";
                else
                    fs.renameDir(arg1, arg2);
            }
            else if (com == "cpdir"){
                if (arg1 == "")
                    cout << "目录名不能为空。\n\n";
                else
                    fs.cpDir(arg1);
            }
            else if (com == "pastedir"){
                fs.pasteDir();
            }
            else if (com == "exit"){
                break;
            }
            else if (com == "help"){
                fs.man();
            }
            else{
                cout << "命令无效。\n\n";
            }
        }
        fs.pwd();
    }
    return 0;
}

