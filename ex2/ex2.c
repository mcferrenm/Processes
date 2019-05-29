// Write a program that opens the text.txt file (with the `fopen()` library call) located in this directory 
// and then calls `fork()` to create a new process. Can both the child and parent access the file descriptor 
// returned by `fopen()`? What happens when they are written to the file concurrently?

#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main(void)
{
    FILE *fp;
    char c;

    fp = fopen("text.txt", "r+");
    
    int rc = fork();

    if (rc < 0) {
        fprintf(stderr, "fork failed\n");
        exit(1);
    } else if (rc == 0) {
        fprintf(fp, "%d", 100);

        while(1) {
            c = fgetc(fp);
            if ( feof(fp) ) {
                break;
            }
            printf("Child process: %c\n", c);
        }
    } else {
        fprintf(fp, "%d", 50);

         while(1) {
            c = fgetc(fp);
            if ( feof(fp) ) {
                break;
            }
            printf("Parent process: %c\n", c);
        }
    }

    fclose(fp);
    
    
    return 0;
}
