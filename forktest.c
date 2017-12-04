#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main()
{
    pid_t pid;
    pid_t wait_pid;
    int status;
    int retval;

    pid = fork();
    if(pid == 0)
    {
        printf("this is a child process with pid is:%d\n",getpid());
        if(execlp("firefox","firefox","www.baidu.com",NULL) == -1)
        {
            perror("execlp failed!");
        }
        //system("firefox www.baidu.com");

        exit(1); //设置子进程的退出码为1
    }
    else if(pid > 0)
    {
        //        printf("input 'q' if you want to quit!\n");
        //        wait_pid = wait(&status); //将退出码保存在status中，返回等待退出的子进程的pid
        //        printf("i catch a child process with pid is:%d,and exit number is:%d\n",wait_pid,WEXITSTATUS(status));
        if ( 0 == (waitpid( pid, &status, WNOHANG )))
        {
            sleep(10);
            printf("wait some second to quit!\n");

            retval = kill(pid, SIGKILL);
            if (retval)
            {
                perror("kill failed!");
                waitpid( pid, &status, 0 );
            }
            else
                printf( "%d killed\n", pid );
        }
    }
    else
    {
        fprintf(stderr,"error");
    }

    return 0;
}
