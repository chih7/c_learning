#include"fs.h"

void files::cd(string dirname)
{
    dentry * pDir = curDir->dirList;
    while (pDir != NULL)
    {
        if (pDir->dirName == dirname){
            dirStack.push(curDir);
            curDir = pDir;
            cout << endl;
            return;
        }
        else
        {
            pDir = pDir->nextDir;
        }
    }
    cout << "无效路径。\n\n";
}

void files::ls()
{
    dentry * pDir = curDir->dirList;
    inode * pFile = curDir->inodeList;
    while (pDir != NULL)
    {
        cout << "-dir-    " << pDir->dirName+"   "<<ctime(&(pDir->i_mtime));
        pDir = pDir->nextDir;
    }
    while (pFile != NULL)
    {
        cout << "-file-   " << pFile->fileName+"   "<< ctime(&(pFile->i_mtime));
        pFile = pFile->nextInode;
    }
    cout << "\n";
}

void files::touch(string filename)
{
    inode * pFile = curDir->inodeList;
    if (pFile == NULL)
    {
        inode * f1 = new inode(filename);
        f1->i_ctime = time(0);
        f1->i_mtime = f1->i_ctime;
        f1->i_atime = f1->i_ctime;
        curDir->inodeList = f1;//插入
        cout << "创建成功。\n\n";
        return;
    }
    while (pFile != NULL)
    {
        if (pFile->nextInode == NULL && pFile->fileName != filename)
        {
            inode * f1 = new inode(filename);
            f1->i_ctime = time(0);
            f1->i_mtime = f1->i_ctime;
            f1->i_atime = f1->i_ctime;
            pFile->nextInode = f1;
            cout << "创建成功。\n\n";
            return;
        }
        else{
            if (pFile->fileName == filename)
            {
                cout << "文件 " + filename + " 已存在。\n\n";
                return;
            }
            else{
                pFile = pFile->nextInode;
            }
        }
    }
}

void files::pwd()
{
    stack<dentry*> tStack;
    while (!dirStack.empty())
    {
        tStack.push(dirStack.top());
        dirStack.pop();
    }
    while (!tStack.empty())
    {
        cout << tStack.top()->dirName + "/";
        dirStack.push(tStack.top());
        tStack.pop();
    }
    cout << curDir->dirName + "/";
}

void files::rm(string filename)
{
    inode * pFile = curDir->inodeList, *preFile = NULL;
    if (pFile == NULL || (pFile->fileName != filename && pFile->nextInode == NULL)){
        cout << "不存在文件 " + filename + " 。\n\n";
        return;
    }

    if (pFile->fileName == filename)
    {
        curDir->inodeList = pFile->nextInode;
        delete pFile;
        cout << "删除成功。\n\n";
        return;
    }
    else{
        preFile = pFile;
        pFile = pFile->nextInode;
        while (pFile != NULL)
        {
            if (pFile->fileName == filename)
            {
                preFile->nextInode = pFile->nextInode;
                delete pFile;
                cout << "删除成功。\n\n";
                return;
            }
            else
            {
                preFile = pFile;
                pFile = pFile->nextInode;
            }
        }
        cout << "不存在文件 " + filename + " 。\n\n";
    }
}

void files::renameFile(string oldname, string newname)
{
    inode * pFile = curDir->inodeList;
    bool isFind = false;
    while (pFile != NULL){
        if (pFile->fileName == oldname)
        {
            isFind = true;
            break;
        }
        pFile = pFile->nextInode;
    }

    if (!isFind){
        cout << "不存在文件 " + oldname + " 。\n\n";
        return;
    }
    else
    {
        inode * pFile2 = curDir->inodeList;
        while (pFile2 != NULL)
        {
            if (pFile2->fileName == newname && pFile2 != pFile)
            {
                cout << "已有同名文件。\n\n";
                return;
            }
            pFile2 = pFile2->nextInode;
        }

        pFile->fileName = newname;
        pFile->i_mtime = time(0);
        pFile->i_atime = pFile->i_mtime;
        cout << "重命名成功。\n\n";
    }
}

void files::cat(string filename)
{
    inode * pFile = curDir->inodeList;
    while (pFile != NULL)
    {
        if (pFile->fileName == filename)
        {
            pFile->i_atime = time(0);
            cout << pFile->content + "\n\n";
            return;
        }
        pFile = pFile->nextInode;
    }
    cout << "不存在文件 " + filename + " 。\n\n";
}

void files::vi(string filename)
{
    inode * pFile = curDir->inodeList;

    while (pFile != NULL){
        if (pFile->fileName == filename)
        {
            cout << "输入文件内容：";
            getline(cin, pFile->content);
            pFile->size = pFile->content.length();
            cout << "成功修改\n";
            pFile->i_mtime = time(0);
            pFile->i_atime = pFile->i_mtime;
            return;
        }
        pFile = pFile->nextInode;
    }
    cout << "不存在文件 " + filename + " 。\n\n";
}

void files::vim(string filename)
{
    inode * pFile = curDir->inodeList;

    while (pFile != NULL){
        if (pFile->fileName == filename)
        {
            cout <<"当前内容："<<pFile->content<<"\n"<< "请输入追加文件内容：";
            string content;
            getline(cin, content);
            pFile->content=pFile->content+content;
            pFile->size = pFile->content.length();
            cout << "成功修改\n";
            pFile->i_mtime = time(0);
            pFile->i_atime = pFile->i_mtime;
            return;
        }
        pFile = pFile->nextInode;
    }
    cout << "不存在文件 " + filename + " 。\n\n";
}

void files::cp(string filename)
{
    inode * pFile = curDir->inodeList;
    while (pFile != NULL)
    {
        if (pFile->fileName == filename)
        {
            tmpFile = new inode(pFile);

            cout << "复制成功。\n\n";
            return;
        }
        pFile = pFile->nextInode;
    }
    cout << "不存在文件 " + filename + " 。\n\n";
}

void files::pasteFile()
{
    if (tmpFile == NULL)
    {
        cout << "请先复制文件。\n\n";
        return;
    }
    inode * pFile = curDir->inodeList;
    if (pFile == NULL)
    {
        tmpFile->i_ctime = time(0);
        tmpFile->i_mtime = tmpFile->i_ctime;
        tmpFile->i_atime = tmpFile->i_ctime;
        curDir->inodeList = tmpFile;
        tmpFile = NULL;

        cout << "粘贴成功。\n\n";
        return;
    }
    while (pFile != NULL){
        if (pFile->nextInode == NULL && pFile->fileName != tmpFile->fileName)
        {
            tmpFile->i_ctime=time(0);
            tmpFile->i_mtime = tmpFile->i_ctime;
            tmpFile->i_atime = tmpFile->i_ctime;
            pFile->nextInode = tmpFile;
            tmpFile = NULL;
            cout << "粘贴成功。\n\n";
            return;
        }
        else{
            if (pFile->fileName == tmpFile->fileName)
            {
                cout << "文件 " + tmpFile->fileName + " 已存在。\n\n";
                return;
            }
            else{
                pFile = pFile->nextInode;
            }
        }
    }
}


void files::mkdir(string dirname)
{
    dentry * pDir = curDir->dirList;
    if (pDir == NULL)
    {
        dentry * d1 = new dentry(dirname);
        d1->i_ctime = time(0);
        d1->i_mtime = d1->i_ctime;
        d1->i_atime = d1->i_ctime;
        curDir->dirList = d1;

        cout << "创建成功。\n\n";
        return;
    }
    while (pDir != NULL){
        if (pDir->nextDir == NULL && pDir->dirName != dirname)
        {
            dentry * d1 = new dentry(dirname);
            d1->i_ctime = time(0);
            d1->i_mtime = d1->i_ctime;
            d1->i_atime = d1->i_ctime;
            pDir->nextDir = d1;
            cout << "创建成功。\n\n";
            return;
        }
        else{
            if (pDir->dirName == dirname){
                cout << "文件 " + dirname + " 已存在。\n\n";
                return;
            }
            else{
                pDir = pDir->nextDir;
            }
        }
    }
}

void files::rmdir(string dirname)
{
    dentry * pDir = curDir->dirList, *preDir = NULL;
    if (pDir == NULL || (pDir->dirName != dirname && pDir->nextDir == NULL))
    {
        cout << "不存在目录 " + dirname + " 。\n\n";
        return;
    }

    if (pDir->dirName == dirname)
    {
        curDir->dirList = pDir->nextDir;
        _reDeleteDir(pDir);
        cout << "删除成功。\n\n";
        return;
    }
    else{
        preDir = pDir;
        pDir = pDir->nextDir;
        while (pDir != NULL){
            if (pDir->dirName == dirname)
            {
                preDir->nextDir = pDir->nextDir;
                _reDeleteDir(pDir);
                cout << "删除成功。\n\n";
                return;
            }
            else{
                preDir = pDir;
                pDir = pDir->nextDir;
            }
        }
        cout << "不存在目录 " + dirname + " 。\n\n";
    }
}

void files::_reDeleteDir(dentry * dir)
{
    if (dir->inodeList != NULL)
    {
        inode * pFile = dir->inodeList;
        while (pFile != NULL)
        {
            inode * preFile = pFile;
            pFile = pFile->nextInode;
            cout << "删除文件 " + preFile->fileName + "\n";
            delete preFile;
        }
    }

    if (dir->dirList != NULL)
    {
        dentry * pDir = dir->dirList;
        while (pDir != NULL)
        {
            dentry * preDir = pDir;
            pDir = pDir->nextDir;
            _reDeleteDir(preDir);
        }
    }

    cout << "删除目录 " + dir->dirName + "\n";
    delete dir;
}

void files::renameDir(string oldname, string newname)
{
    dentry * pDir = curDir->dirList;
    bool isFind = false;
    while (pDir != NULL){
        if (pDir->dirName == oldname){
            isFind = true;
            break;
        }
        pDir = pDir->nextDir;
    }

    if (!isFind){
        cout << "不存在目录 " + oldname + " 。\n\n";
        return;
    }
    else
    {
        dentry * pDir2 = curDir->dirList;
        while (pDir2 != NULL){
            if (pDir2->dirName == newname && pDir2 != pDir){
                cout << "存在重名目录。\n\n";
                return;
            }
            pDir2 = pDir2->nextDir;
        }

        pDir->i_ctime = time(0);
        pDir->i_mtime = pDir->i_ctime;
        pDir->i_atime = pDir->i_ctime;
        pDir->dirName = newname;
        cout << "重命名成功。\n\n";
    }
}

void files::cpDir(string dirname)
{
    dentry * pDir = curDir->dirList;
    while (pDir != NULL){
        if (pDir->dirName == dirname)
        {
            tmpDir = _reCopyDir(pDir);
            cout << "复制成功。\n\n";
            return;
        }
        else
            pDir = pDir->nextDir;
    }
    cout << "不存在目录 " + dirname + " 。\n\n";
}


void files::retPreDir()
{
    if (!dirStack.empty())
    {
        curDir = dirStack.top();
        dirStack.pop();
    }
    cout << "\n";
}


dentry* files::_reCopyDir(dentry * dir)
{
    dentry * hcpDir = NULL;
    inode * hcpFile = NULL;
    if (dir->dirList != NULL)
    {
        dentry * pDir = dir->dirList, *cpDir = NULL;
        while (pDir != NULL){
            if (cpDir == NULL){
                cpDir = _reCopyDir(pDir);
                hcpDir = cpDir;
            }
            else{
                cpDir->nextDir = _reCopyDir(pDir);
                cpDir = cpDir->nextDir;
            }
            pDir = pDir->nextDir;
        }
    }
    if (dir->inodeList != NULL)
    {
        inode * pFile = dir->inodeList, *cpFile = NULL;
        while (pFile != NULL){
            if (cpFile == NULL){
                cpFile = new inode(pFile);
                hcpFile = cpFile;
            }
            else{
                cpFile->nextInode = new inode(pFile);
                cpFile = cpFile->nextInode;
            }
            pFile = pFile->nextInode;
        }
    }

    dentry * copydir = new dentry(dir->dirName);
    copydir->dirList = hcpDir;
    copydir->inodeList = hcpFile;

    return copydir;
}

void files::pasteDir()
{
    if (tmpDir == NULL){
        cout << "请先复制目录。\n\n";
        return;
    }
    dentry * pDir = curDir->dirList;
    if (pDir == NULL)
    {
        tmpDir->i_ctime = time(0);
        tmpDir->i_mtime = tmpDir->i_ctime;
        tmpDir->i_atime = tmpDir->i_ctime;
        curDir->dirList = tmpDir;
        tmpDir = NULL;
        cout << "粘贴成功。\n\n";
        return;
    }
    while (pDir != NULL)
    {
        if (pDir->nextDir == NULL && pDir->dirName != tmpDir->dirName){
            tmpDir->i_ctime = time(0);
            tmpDir->i_mtime = tmpDir->i_ctime;
            tmpDir->i_atime = tmpDir->i_ctime;
            pDir->nextDir = tmpDir;
            tmpDir = NULL;
            cout << "粘贴成功。\n\n";
            return;
        }
        else
        {
            if (pDir->dirName == tmpDir->dirName){
                cout << "目录 " + tmpDir->dirName + " 已存在。\n\n";
                return;
            }
            else{
                pDir = pDir->nextDir;
            }
        }
    }
}

void files::man()
{
    cout << "  输入命令help显示该条命令的使用说明\n"
         << "********************************\n"
         << "    touch    新建文件\n"
         << "    rm       删除文件\n"
         << "    re       重命名文件\n"
         << "    cp       复制文件\n"
         << "    paste    粘贴文件\n"
         << "    cat      打开文件\n"
         << "    vi       编辑文件\n"
         << "    vim      追加文件内容\n"
         << "    mkdir    新建目录\n"
         << "    rmdir    删除目录\n"
         << "    redir    重命名目录\n"
         << "    cpdir    复制目录\n"
         << "    pastedir 粘贴目录\n"
         << "    ls       打印当前目录的清单\n"
         << "    cd       进入子目录\n"
         << "    cd..     返回上一级目录\n"
         << "    exit     退出\n"
         << "********************************\n\n";
}

void files::comHelp(string command)
{
    if (command == "help")
        cout << "提供本文件系统命令的帮助信息。\n" << "命令格式：\n" << "    help\n\n";
    else if (command == "touch")
        cout << "创建文件。\n" << "命令格式：\n" << "    touch [filename]\n\n";
    else if (command == "rm")
        cout << "删除文件。\n" << "命令格式：\n" << "    rm [filename]\n\n";
    else if (command == "re")
        cout << "重命名文件。\n" << "命令格式：\n" << "    re [oldname] [newname]\n\n";
    else if (command == "cp")
        cout << "复制文件。\n" << "命令格式：\n" << "    cp [filename]\n\n";
    else if (command == "paste")
        cout << "粘贴文件。\n" << "命令格式：\n" << "    paste\n\n";
    else if (command == "cat")
        cout << "打开文件。\n" << "命令格式：\n" << "    cat [filename]\n\n";
    else if (command == "vi")
        cout << "编辑文件。\n" << "命令格式：\n" << "    vi [filename]\n\n";
    else if (command == "vim")
        cout << "追加文件内容。\n" << "命令格式：\n" << "    vim [filename]\n\n";
    else if (command == "mkdir")
        cout << "创建目录。\n" << "命令格式：\n" << "    mkdir [dirname]\n\n";
    else if (command == "rmdir")
        cout << "删除目录。\n" << "命令格式：\n" << "    rmdir [dirname]\n\n";
    else if (command == "redir")
        cout << "删除目录。\n" << "命令格式：\n" << "    redir [dirname]\n\n";
    else if (command == "cpdir")
        cout << "复制目录。\n" << "命令格式：\n" << "    cpdir [dirname]\n\n";
    else if (command == "pastedir")
        cout << "粘贴目录。\n" << "命令格式：\n" << "    pastedir\n\n";
    else if (command == "ls")
        cout << "显示目录中的文件和子目录列表。\n" << "命令格式：\n" << "    ls\n\n";
    else if (command == "cd")
        cout << "进入子目录。\n" << "命令格式：\n" << "    cd [dirname]\n\n";
    else if (command == "cd..")
        cout << "返回上一级目录。\n" << "命令格式：\n" << "    cd..\n\n";
    else if (command == "exit")
        cout << "退出。\n" << "命令格式：\n" << "   exit\n\n";
    else
        cout << "命令无效。\n\n";
}

