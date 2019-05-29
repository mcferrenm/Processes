// Write a program that calls `fork()` and then calls some form of `exec()`
// to run the program `/bin/ls`. Try a few variants of `exec()`, such as 
// `execl()`, `execle()`, `execv()`, and others. Why do you think there 
// are so many variants of the same basic call?

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(void)
{
    int rc = fork();

    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
    } else if (rc == 0) {
        printf("Child process: Hello\n");
        
        char *myargs[2];
        myargs[0] = "ls";
        myargs[1] = NULL;
        execvp(myargs[0], myargs);
    } else {
        int wc = waitpid(rc, NULL, 0);
        printf("Parent process: Goodbye\n");
    }

    return 0;
}
