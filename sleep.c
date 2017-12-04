#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

void wakeup(){

    printf("wakeup\n");
}

int main(void) {

    printf("sleep 5s\n");
    signal(SIGALRM, wakeup);
    alarm(5);
    pause();
    printf("end\n");
    
    return EXIT_SUCCESS;
}
