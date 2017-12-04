#include<stdio.h>
#include<dlfcn.h>

int main(int argc, char *argv[]){
    void *handle;
    double (*func)(double);
    char *error;

    handle = dlopen("/lib/libm-2.26.so", RTLD_NOW);
    if (handle ==NULL) {
        printf("Open library %s error: %s.\n", "/lib/libm-2.26.so", dlerror());
        return -1;
    }

    func = dlsym(handle, "sin");
    if ( (error = dlerror()) != NULL ) {
        printf(" Symbol sin not found: %s.\n", error);
        goto exit_runso;
    }

    printf("print: %f\n", func(3.1415 / 2));
exit_runso:
    dlclose(handle);
}
