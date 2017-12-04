#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<netdb.h>
#include<errno.h>
#include<sys/types.h>
#include<netinet/tcp.h>
#include<unistd.h>

int port = 12345;
int key  = 123456;

#define TCP_ULP  31
#define TCP_NONE 100

int main(){

    int sockfd;
    int i = 0;
    int ret;
    struct sockaddr_in serveraddr;
    char *buf = "abcdefg";

    bzero(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port   = htons(port);
    serveraddr.sin_addr.s_addr = inet_addr("127.0.0.1");

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd == -1){
        perror("socket error");
        return 1;
    }
    setsockopt(sockfd, SOL_TCP, TCP_ULP, "Caesar cipher", sizeof(("Caesar cipher")));
    perror("ulp init");
    setsockopt(sockfd, SOL_TCP, TCP_NONE, &key, sizeof(int));
    perror("cipher init");

    ret = connect(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    if(ret < 0){
        perror("connect error");
        close(sockfd);
        return 1;
    }
    ret = send(sockfd, buf, sizeof(buf), 0);
    if(ret < 0){
        perror("recvfrom error");
        perror("connect error");
        return 1;
    }
    close(sockfd);
    return 0;
}
