/////////////////////////////////////////////////////
///                 for linux
/////////////////////////////////////////////////////

#include<fstream>
#include<iostream>
#include<time.h>
#include<cstdlib>
#include<sstream>
#include<vector>
#include<algorithm>
#include<iterator>

using namespace std;

#define SUMOFLINE 1000
#define NUMOFSMALL  SUMOFLINE/20

string String[]={"0.txt","1.txt","2.txt","3.txt","4.txt",
                 "5.txt","6.txt","7.txt","8.txt","9.txt",
                 "10.txt","11.txt","12.txt","13.txt","14.txt",
                 "15.txt","16.txt","17.txt","18.txt","19.txt"};


const int Data_Legnth=20;
const int File_Num=20;

void createfile()
{
    //    cout<<NUMOFSMALL;
    ofstream mFile("test.txt");
    srand((int)time(0));
    int n = 0;
    while (n < SUMOFLINE)
    {
        for (int i = 0; i < 20; i++)
        {
            mFile <<rand()%10000000<<" ";
        }
        mFile << '\n';
        n++;
    }
    mFile.close();
}

void tofiles()
{
    // cout<<"test";

    ifstream inFile("test.txt");
    int win_size = NUMOFSMALL;
    if(inFile)
    {
        string line;

        int row_counter = 0;
        int i = 0;
        ofstream ofile(String[i].c_str());


        while(!inFile.eof())
        {
            getline(inFile,line);
            ofile<<line<<'\n';
            row_counter++;

            if(row_counter == win_size && i<19)
            {
                row_counter = 0;
                ofile.close();
                ++i;
                // generate new ofile_name
                //                cout<<String[i]<<endl;
                ofile.open(String[i].c_str()); // you might change the nMode parameter if necessary
            }
        }
        ofile.close();
        inFile.close();
    }
}

void fastSortEach()
{
    ifstream fin;
    ofstream fout;

    for(int i=0;i<20;i++)
    {
        fin.open(String[i].c_str());
        string s;
        s.clear();
        vector<string> v;
        v.clear();
        while(getline(fin,s,'\n'))
        {
            v.push_back(s.substr(0,s.find('\n')));
        }
        fin.close();
        fout.open(String[i].c_str());
        sort(v.begin(),v.end());
        //        vector<string>::iterator u=v.begin();
        copy(v.begin(),v.end(),ostream_iterator<string>(fout,"\n"));
        fout.close();
    }
}

void kway()
{
    int line_data[File_Num][Data_Legnth];
    int IO_Count[File_Num];
    bool IO_File[File_Num];
    ifstream infile[20];
    for(int a=0;a<File_Num;a++)
    {
        IO_Count[a]=0;
        IO_File[a]=true;
        infile[a].open(String[a].c_str());
        for(int b=0;b<Data_Legnth;b++)
            infile[a]>>line_data[a][b];
    }
    ofstream f_Result;
    int sign=0;
    string Result = "finish.txt";
    f_Result.open(Result.c_str());
    while(IO_File[0] || IO_File[1] || IO_File[2] || IO_File[3] || IO_File[4]
          || IO_File[5] || IO_File[6] || IO_File[7] || IO_File[8] || IO_File[9]
          || IO_File[10] || IO_File[11] || IO_File[12] || IO_File[13] || IO_File[14]
          || IO_File[15] || IO_File[16] || IO_File[17] || IO_File[18] || IO_File[19])
    {
        int temp=10000000;
        for(int a=0;a<File_Num;a++)
        {
            if(IO_File[a]==false)
                continue;
            if(line_data[a][0]<temp)
            {
                temp=line_data[a][0];
                sign=a;
            }
        }
        for(int b=0;b<Data_Legnth;b++)
            f_Result<<line_data[sign][b]<<' ';
        f_Result<<'\n';
        IO_Count[sign]++;
        if(IO_Count[sign]==NUMOFSMALL)
        {
            infile[sign].close();
            IO_File[sign]=false;
        }
        else
        {
            for(int b=0;b<Data_Legnth;b++)
                infile[sign]>>line_data[sign][b];
        }
    }
    f_Result.close();
}

void Deduplication(){

    int line_data[File_Num][Data_Legnth];
    int IO_Count[File_Num];
    bool IO_File[File_Num];
    ifstream infile[20];
    for(int a=0;a<File_Num;a++)
    {
        IO_Count[a]=0;
        IO_File[a]=true;
        infile[a].open(String[a].c_str());
        for(int b=0;b<Data_Legnth;b++)
            infile[a]>>line_data[a][b];
    }
    ofstream f_Result;
    int sign=0;
    string Result = "finish.txt";
    f_Result.open(Result.c_str());
    int temp2=0;
    while(IO_File[0] || IO_File[1] || IO_File[2] || IO_File[3] || IO_File[4]
          || IO_File[5] || IO_File[6] || IO_File[7] || IO_File[8] || IO_File[9]
          || IO_File[10] || IO_File[11] || IO_File[12] || IO_File[13] || IO_File[14]
          || IO_File[15] || IO_File[16] || IO_File[17] || IO_File[18] || IO_File[19])
    {
        int temp=10000000;
        for(int a=0;a<File_Num;a++)
        {
            if(IO_File[a]==false)
                continue;
            if(line_data[a][0]<temp)
            {
                temp=line_data[a][0];
                sign=a;
            }
        }


        if(temp != temp2){
            for(int b=0;b<Data_Legnth;b++)//写入一行
                f_Result<<line_data[sign][b]<<' ';
            f_Result<<'\n';
        }
        temp2 = temp;
        IO_Count[sign]++;

        if(IO_Count[sign]==NUMOFSMALL)
        {
            infile[sign].close();
            IO_File[sign]=false;
        }
        else
        {
            for(int b=0;b<Data_Legnth;b++)
                infile[sign]>>line_data[sign][b];
        }
    }
    f_Result.close();
}

void Group(){

    int line_data[File_Num][Data_Legnth];
    int IO_Count[File_Num];
    bool IO_File[File_Num];
    ifstream infile[20];
    for(int a=0;a<File_Num;a++)
    {
        IO_Count[a]=0;
        IO_File[a]=true;
        infile[a].open(String[a].c_str());
        for(int b=0;b<Data_Legnth;b++)
            infile[a]>>line_data[a][b];
    }
    ofstream f_Result;
    int sign=0;
    string Result = "finish.txt";
    f_Result.open(Result.c_str());
    int temp2=0;
    int i=1;
    while(IO_File[0] || IO_File[1] || IO_File[2] || IO_File[3] || IO_File[4]
          || IO_File[5] || IO_File[6] || IO_File[7] || IO_File[8] || IO_File[9]
          || IO_File[10] || IO_File[11] || IO_File[12] || IO_File[13] || IO_File[14]
          || IO_File[15] || IO_File[16] || IO_File[17] || IO_File[18] || IO_File[19])
    {
        int temp=10000000;
        for(int a=0;a<File_Num;a++)
        {
            if(IO_File[a]==false)
                continue;
            if(line_data[a][0]<temp)
            {
                temp=line_data[a][0];
                sign=a;
            }
        }


        if(temp != temp2){
            i=1;
            for(int b=0;b<Data_Legnth;b++)//写入一行
                f_Result<<i<<line_data[sign][b]<<' ';
            f_Result<<'\n';
        }
        else{
            i++;
            for(int b=0;b<Data_Legnth;b++)//写入一行
                f_Result<<i<<line_data[sign][b]<<' ';
            f_Result<<'\n';
        }
        temp2 = temp;
        IO_Count[sign]++;

        if(IO_Count[sign]==NUMOFSMALL)
        {
            infile[sign].close();
            IO_File[sign]=false;
        }
        else
        {
            for(int b=0;b<Data_Legnth;b++)
                infile[sign]>>line_data[sign][b];
        }
    }
    f_Result.close();
}


void And(){
    int line_data[File_Num][Data_Legnth];
    int IO_Count[File_Num];
    bool IO_File[File_Num];
    ifstream infile[20];
    for(int a=0;a<File_Num;a++)
    {
        IO_Count[a]=0;
        IO_File[a]=true;
        infile[a].open(String[a].c_str());
        for(int b=0;b<Data_Legnth;b++)
            infile[a]>>line_data[a][b];
    }
    ofstream f_Result;
    int sign=0;
    string Result = "finish.txt";
    f_Result.open(Result.c_str());
    int temp2=0;
    while(IO_File[0] || IO_File[1] || IO_File[2] || IO_File[3] || IO_File[4]
          || IO_File[5] || IO_File[6] || IO_File[7] || IO_File[8] || IO_File[9]
          || IO_File[10] || IO_File[11] || IO_File[12] || IO_File[13] || IO_File[14]
          || IO_File[15] || IO_File[16] || IO_File[17] || IO_File[18] || IO_File[19])
    {
        int temp=10000000;
        for(int a=0;a<File_Num;a++)
        {
            if(IO_File[a]==false)
                continue;
            if(line_data[a][0]<temp)
            {
                temp=line_data[a][0];
                sign=a;
            }
        }


        if(temp != temp2){
            for(int b=0;b<Data_Legnth;b++)//写入一行
                f_Result<<line_data[sign][b]<<' ';
            f_Result<<'\n';
        }
        temp2 = temp;
        IO_Count[sign]++;

        if(IO_Count[sign]==NUMOFSMALL)
        {
            infile[sign].close();
            IO_File[sign]=false;
        }
        else
        {
            for(int b=0;b<Data_Legnth;b++)
                infile[sign]>>line_data[sign][b];
        }
    }
    f_Result.close();
}

void Join(){

    vector< vector<int> > BufferA;
    vector< vector<int> > BufferB;
    vector<int> Sline;
    vector< vector<int> > Sublists;
    typedef vector< vector<int> > Delete_Sublists;
    vector< vector< vector<int> > > SublistsUnion;
    Delete_Sublists::iterator delete_sublists;
    int a=0,b=0,c=0;
    int tem;
    ofstream fout;
    fout.open("finish.txt");
    ifstream fin[File_Num];
    for(a=0;a<File_Num;a++)
    {
        fin[a].open(String[a].c_str());
        Sublists.clear();
        for(b=0;b<10;b++)
        {
            Sline.clear();
            for(c=0;c<Data_Legnth;c++)
            {
                fin[a]>>tem;
                Sline.push_back(tem);
            }
            Sublists.push_back(Sline);
        }
        SublistsUnion.push_back(Sublists);
    }
    bool flag=1;
    int temp=10;
    bool tem_flag=0;
    while(flag)
    {

        int tem_num=0;
        if(!tem_flag)
        {
            tem_flag=1;
            temp=10;
            for(a=0;a<File_Num;a++)//求出子列表中的最小值
            {
                if(SublistsUnion[a].empty())
                    continue;
                if(temp>SublistsUnion[a][0][0])
                {
                    temp=SublistsUnion[a][0][0];
                }
            }
        }
        for(a=0;a<File_Num;a++)//取出子列表中与最小值相等的元组
        {
            if(SublistsUnion[a].empty())
                continue;
            if(temp==SublistsUnion[a][0][0])
            {
                tem_num=a;
                break;
            }
        }
        bool tflag=0;///////////////////////////////
        bool boolflag=1;
        if(tem_num<10)
        {
            for(a=0;a<BufferA.size();a++)//与Buffer里的数据比较，若不重复则将其加入Buffer
            {
                tflag=0;
                boolflag=1;
                for(b=0;b<Data_Legnth;b++)
                {

                    if(BufferA[a][b]!=SublistsUnion[tem_num][0][b])
                    {
                        tflag=1;
                        break;
                    }
                }
                if(tflag==0)
                {
                    boolflag=0;
                    break;
                }
            }
            if(boolflag==1)
            {
                BufferA.push_back(SublistsUnion[tem_num][0]);
            }
        }
        else
        {
            for(a=0;a<BufferB.size();a++)//与Buffer里的数据比较，若不重复则将其加入Buffer
            {
                tflag=0;
                boolflag=1;
                for(b=0;b<Data_Legnth;b++)
                {

                    if(BufferB[a][b]!=SublistsUnion[tem_num][0][b])
                    {
                        tflag=1;
                        break;
                    }
                }
                if(tflag==0)
                {
                    boolflag=0;
                    break;
                }
            }
            if(boolflag==1)
            {
                BufferB.push_back(SublistsUnion[tem_num][0]);
            }
        }

        //删除对应子列表的值
        delete_sublists =SublistsUnion[tem_num].begin();
        SublistsUnion[tem_num].erase(delete_sublists);

        //若子列表数据为空则从文件中导入，直至文件为空
        bool t=0;
        for(a=0;a<File_Num;a++)
        {
            if(SublistsUnion[a].empty() && (fin[a].peek()!=EOF))
            {
                //fin[a].open(String[a]);
                Sublists.clear();
                //if()
                for(b=0;(b<10)&&(fin[a].peek()!=EOF);b++)
                {
                    Sline.clear();
                    for(c=0;(c<Data_Legnth)&&(fin[a].peek()!=EOF);c++)
                    {
                        fin[a]>>tem;
                        Sline.push_back(tem);
                    }
                    if(Sline.size()==Data_Legnth)//解决文件EOF问题
                    {
                        Sublists.push_back(Sline);
                        t=1;
                    }
                }
                SublistsUnion[a]=Sublists;
                break;
            }
        }
        if(t)//遇到文件EOF，再读一次
        {
            for(a=0;a<File_Num;a++)
            {
                if(SublistsUnion[a].empty() && (fin[a].peek()!=EOF))
                {
                    //fin[a].open(String[a]);
                    Sublists.clear();
                    //if()
                    for(b=0;(b<10)&&(fin[a].peek()!=EOF);b++)
                    {
                        Sline.clear();
                        for(c=0;(c<Data_Legnth)&&(fin[a].peek()!=EOF);c++)
                        {
                            fin[a]>>tem;
                            Sline.push_back(tem);
                        }
                        if(Sline.size()==Data_Legnth)//解决文件EOF问题
                        {
                            Sublists.push_back(Sline);
                            t=1;
                        }
                    }
                    SublistsUnion[a]=Sublists;
                    break;
                }
            }
        }

        if(	(fin[0].peek()==EOF)&&(fin[1].peek()==EOF)&&(fin[2].peek()==EOF)&&(fin[3].peek()==EOF)&&(fin[4].peek()==EOF)&&
                (fin[5].peek()==EOF)&&(fin[6].peek()==EOF)&&(fin[7].peek()==EOF)&&(fin[8].peek()==EOF)&&(fin[9].peek()==EOF)&&
                (fin[10].peek()==EOF)&&(fin[11].peek()==EOF)&&(fin[12].peek()==EOF)&&(fin[13].peek()==EOF)&&(fin[14].peek()==EOF)&&
                (fin[15].peek()==EOF)&&(fin[16].peek()==EOF)&&(fin[17].peek()==EOF)&&(fin[18].peek()==EOF)&&(fin[19].peek()==EOF)&&
                SublistsUnion[0].empty()&&SublistsUnion[1].empty()&&SublistsUnion[2].empty()&&
                SublistsUnion[3].empty()&&SublistsUnion[4].empty()&&SublistsUnion[5].empty()&&
                SublistsUnion[6].empty()&&SublistsUnion[7].empty()&&SublistsUnion[8].empty()&&
                SublistsUnion[9].empty()&&SublistsUnion[10].empty()&&SublistsUnion[11].empty()&&
                SublistsUnion[12].empty()&&SublistsUnion[13].empty()&&SublistsUnion[14].empty()&&
                SublistsUnion[15].empty()&&SublistsUnion[16].empty()&&SublistsUnion[17].empty()&&
                SublistsUnion[18].empty()&&SublistsUnion[19].empty())//循环结束判断
        {
            flag=0;
        }
        if(flag)
        {
            bool temp_flag=0;
            for(a=0;a<File_Num;a++)//判断子列表中的最小值是否改变
            {
                if(SublistsUnion[a].empty())
                    continue;
                if(temp==SublistsUnion[a][0][0])
                {
                    temp_flag=1;
                }
            }
            if(temp_flag==0)
            {
                tem_flag=0;
                //做连接操作

                for(a=0;a<BufferA.size();a++)
                {
                    for(b=0;b<BufferB.size();b++)
                    {
                        for(c=0;c<BufferA[a].size();c++)
                            fout<<BufferA[a][c]<<' ';
                        for(c=1;c<BufferB[b].size();c++)
                            fout<<BufferB[b][c]<<' ';
                        fout<<'\n';
                    }
                }
                BufferA.clear();
                BufferB.clear();
            }
        }

    }
}

void readcCom(){
    ifstream read_com("command.txt");
    string line;
    while(!read_com.eof()){
        getline(read_com,line);
        if(line=="duplicatate"){
            Deduplication();
        }
        if(line=="group"){
            Group();
        }
        if(line=="union"){
            And();
        }
        if(line=="join"){
            Join();
        }
        else{
            cout<<"错误!\n";
        }
    }
}


int main()
{
    createfile();
    tofiles();
    fastSortEach();
    readcCom();

    return 0;
}
