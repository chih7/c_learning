#include<stdio.h>
#include<fstream>
#include<iostream>
#include<string>

#include"btree.h"

int main()
{

    CBPlusTree* pTree = new CBPlusTree;

    student stu;
    int x=1;int y = 1;

    while (0 != x)
    {

        printf("\n\n");
        printf("* 1从文本建立一棵B+树；          \n");
        printf("* 2在B+树中查找；               \n");
        printf("* 3在B+树中插入；               \n");
        printf("* 4从B+树中删除；               \n");
        printf("* 5显示整个B+树；               \n");
        printf("* 6范围查找；                  \n");
        printf("* 0退出程序；                  \n");
        printf("\n  您的选择是：");


        scanf("%d", &x);
        switch (x)
        {
        case 1:{
            pTree->clear();
            ifstream infile("datafile.txt");
            student stu;
            if(infile){
                while(!infile.eof()){

                    infile >> stu.num;
                    infile >> stu.name;
                    infile >> stu.grade;
                    infile >> stu.department;
                    infile >> stu.mailbox;
                    pTree->insert(stu.num,stu);
                }

                printf("\n successed! \n");
            }
            infile.close();
            break;
        }

        case 2:{
            printf("请输入要查找的数值：");
            scanf("%d", &y);
            cout<<y<<endl;
            bool found = pTree->search(y);
            if(found == false)
                cout<<"此节点不存在"<<endl;
            else
                cout<<"有此节点。"<<endl;
            break;
        }

        case 3:{
            printf("请输入要插入的学生的学号，姓名，年级，专业，和邮箱（如：201289 zhouXiaolong 2 CS xiaolong@zjut.edu.cn ）：");

            cin>>stu.num>>stu.name>>stu.grade>>stu.department>>stu.mailbox;

            bool success = pTree->insert(stu.num,stu);
            if (true == success)
            {
                printf("\nsuccessed!\n");
            }
            else
            {
                printf("\nfailed!\n");
            }
            break;
        }

        case 4:{
            printf("请输入要删除的数值：");
            scanf("%d", &y);
            bool success = pTree->remove(y);
            if (true == success)
            {
                printf("\nsuccessed!\n");
            }
            else
            {
                printf("\nfailed!\n");
            }
            break;
        }

        case 5:{
            pTree->print();
            break;
        }

        case 6:{
            cout<<"进行范围查找，请起始学号小于结束学号"<<endl;
            cout<<"请输入起始学号：";
            int first;
            cin>>first;
            cout<<"请输入结束学号:";
            int last;
            cin>>last;
            vector<student> find = pTree->select(first,last);
            if(find.empty() == true)
                cout<<"没有节点"<<endl;
            else
                cout<<"有"<<find.size()<<"个节点"<<endl;
            break;
        }

        case 0:{
            delete pTree;
            return 0;
            break;
        }

        default:
            break;
        }
    }

    delete pTree;
    return 0;
}
