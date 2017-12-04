#include<stdio.h>

#define N 10

///数据结构
int Available[N];        //可使用资源向量
int Max[N][N];           //最大需求矩阵
int Allocation[N][N] = { 0 };   //分配矩阵
int Need[N][N] = { 0 };  //需求矩阵

///银行家算法
int Work[N];              //工作向量
int Finish[N];            //状态标志
int Request[N][N];        //进程申请资源向量
int Pause[N];


int n;                //系统资源总数
int m;                //总的进程数
int a;                //当前申请的进程号
int l, e;             //计数器
int b = 0, c = 0, f = 0, g;    //计数器

void input()          //主要的输入部分代码
{
    int i,j;
    printf("请输入系统总共有的资源数：");
    scanf("%d", &n);
    printf("请输入总共有多少个进程：");
    scanf("%d", &m);
    for (i = 1; i <= n; i++) {
        printf("第%d类资源有的资源实例：", i);
        scanf("%d", &Available[i]);
    }
    for (i = 1; i <= m; i++) {
        for (j = 1; j <= n; j++) {
            printf("进程P[%d]对第%d类资源的最大需求量：", i, j);
            scanf("%d", &Max[i][j]);
            Need[i][j] = Max[i][j];
        }
    }
}

void inputrequest()        //进程提出新申请的代码部分
{
    int i,j;
    printf("请输入申请资源的进程：");
    scanf("%d", &a);
    for (i = 1; i <= n; i++) {
        printf("请输入进程P[%d]对%d类资源的申请量：", a, i);
        scanf("%d", &Request[a][i]);
        if (Request[a][i] > Need[a][i])
            printf("\n出错！进程申请的资源数多于它自己申报的最大量\n");
        if (Request[a][i] > Available[i])
            printf("\n P[%d]必须等待\n", a);

        //以下是试探性分配
        Available[i] = Available[i] - Request[a][i];
        Allocation[a][i] = Allocation[a][i] + Request[a][i];
        Need[a][i] = Need[a][i] - Request[a][i];
        Work[i] = Available[i];
    }
    for (i = 1; i <= n; i++) {
        Pause[i] = Available[i];//Pause[i]只是一个暂时寄存的中间变量，为防止在下面
        //安全性检查时修改到Available[i]而代替的一维数组
        Finish[i] = false;
    }
    for (g = 1; g <= m; g++) {     //m个进程分别要求申请资源
        for (i = 1; i <= m; i++) {//每个进程要求分配资源检查是否安全
            b = 0;    //计数器初始化
            for (j = 1; j <= n; j++) {
                if (Need[i][j] <= Pause[j]) {
                    b = b + 1;
                }
                if (Finish[i] == false && b == n) {
                    for (l = 1; l <= n; l++) {
                        Pause[l] = Pause[l] + Allocation[i][l];
                    }
                    Finish[i] = true;
                    printf("$$ %d ", i);    //依次输出进程安全序列之一中每个元素
                }
            }
        }
    }
    printf("\n");
    for (i = 1; i <= m; i++) {
        if (Finish[i] == true)
            f = f + 1;    //统计Finish[i]＝＝true的个数
    }
    if (f == m) {
        printf("safe static");
        f = 0;        //将计数器f重新初始化，为下一次提出新的进程申请做准备
    } else {
        printf(" unsafe static ");    //以下代码为当系统被判定为不安全状态时
        //返回提出申请前的状态
        for (i = 1; i <= n; i++) {
            Available[i] = Available[i] + Request[a][i];
            Allocation[a][i] = Allocation[a][i] - Request[a][i];
            Need[a][i] = Need[a][i] + Request[a][i];
        }
    }
}

void display()
{
    int i,j;
    printf("当前的系统状态\n");
    printf(" 目前占有量 最大需求量 尚需要量 \n进程");
    for (i = 1; i <= n; i++)
        for (j = 1; j <= n; j++) {
            printf(" %d类", j);
        }
    for (i = 1; i <= m; i++) {
        printf("\nP[%d]", i);
        for (j = 1; j <= n; j++) {
            printf(" %d ", Allocation[i][j]);
        }
        for (j = 1; j <= n; j++) {
            printf(" %d ", Max[i][j]);
        }
        for (j = 1; j <= n; j++) {
            printf(" %d ", Need[i][j]);
        }
    }
    printf("\n\n系统剩余资源量： ");
    for (i = 1; i <= n; i++) {
        printf(" %d ", Available[i]);
    }
    printf("\n");
}

int  main()
{

    input();
    inputrequest();
    display();
    return 0;
}
