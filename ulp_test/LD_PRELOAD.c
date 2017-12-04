#define _GNU_SOURCE
#include <stdio.h>  
#include <dlfcn.h> 
#include<errno.h>
#include <netinet/tcp.h>

#define TCP_ULP         31
#define TCP_NONE        100

int key = 12354;

int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen)
{
    int clisd;
    typeof(accept) *_accept;  

    _accept = dlsym(RTLD_NEXT, "accept");
    clisd = (*_accept)(sockfd, addr, addrlen);
    setsockopt(clisd, SOL_TCP, TCP_ULP, "Caesar cipher", sizeof("Caesar cipher"));
    perror("client ulp init");
    setsockopt(clisd, SOL_TCP, TCP_NONE, &key, sizeof(int));
    perror("client cipher init");

    return clisd;
}
