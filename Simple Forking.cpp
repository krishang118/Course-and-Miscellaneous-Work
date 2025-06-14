#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main() {
    pid_t pid;
    const char *message;  
    int n;
    printf("Fork program starting\n");
    pid = fork();
    switch(pid) {
        case -1:
            perror("Fork failed");
            exit(1);
        case 0:
            message = "This is the child process";
            n = 5;
            break;
        default:
            message = "This is the parent process";
            n = 3;
            break;
    }
    for (; n > 0; n--) {
        puts(message);
        sleep(1);
    }
    exit(0);}