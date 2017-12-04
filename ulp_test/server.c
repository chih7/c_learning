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
    int ret;
    char buf[256];
    struct sockaddr_in serveraddr;
    struct sockaddr_in clientaddr;
    int addr_len = sizeof(clientaddr);
    int clientfd;

    bzero(&serveraddr, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_port   = htons(port);
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if(sockfd == -1){
        perror("socket error");
        return 1;
    }
    ret = bind(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    if(ret == -1){
        perror("bind error");
        return 1;
    }
    ret = listen(sockfd, 5);
    if(ret < 0){
        perror("listen error");
        close(sockfd);
        return 1;
    }
    while(1){
        clientfd = accept(sockfd, (struct sockaddr*)&clientaddr, (socklen_t*)&addr_len);
        if(clientfd < 0){
            perror("accept error");
            continue;
        }
        setsockopt(clientfd, SOL_TCP, TCP_ULP, "Caesear cipher", sizeof("Caeser cipher"));
        perror("ulp init");
        setsockopt(clientfd, SOL_TCP, TCP_NONE, &key, sizeof(int));
        perror("cipher init");

        ret = recv(clientfd, buf, sizeof(buf), 0);
        if(ret < 0){
            perror("recv error");
            close(clientfd);
            close(sockfd);
            return 1;
        }
        buf[ret] = 0;
        printf("%s\n", buf);
        close(clientfd);
    }
    close(sockfd);
    return 0;
}
