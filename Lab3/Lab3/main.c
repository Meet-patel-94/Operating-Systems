/* 
 * File:   main.c
 * Author: m94patel
 *
 * Created on March 4, 2016, 3:57 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <ctype.h>

int main(int argc, char** argv) {
    pid_t pid;
    int status;
    int i = 0;
    int j = 0;
    char * line = malloc(100);
    char * start = line;
    char * my_argvs[10];
    int ch;
    int background = 0;

    for (;;) {
        i = 0;
        line = start;
        background = 0;
        fflush(stdin);
        
       printf(" Please insert Your command> ");
        my_argvs[i++] = line;
        while ((ch = getchar()) != '\n') {
            if (ch == EOF) {
                fprintf(stderr, "Goodbye!\n");
                exit(0);
            }
            if (isspace(ch)) {
                ch = 0;
                my_argvs[i++] = line + 1;
            }
            *line++ = ch;
        }
        
        *line = 0;
        my_argvs[i] = NULL;
        if (*(line - 1) == '&') {
            *(line - 1) = 0;
            fprintf(stderr, "Last char is &, so Parent won't wait for child's death\n");
            background = 1;
        }
        
        fprintf(stderr, "Number of words in command line: %d\n", i);
        for ( j = 0; j < i; j++) {
            fprintf(stderr, "my_argvs[%d]: %s\n", j, my_argvs[j]);
        }
        if ((pid = fork()) == 0) {
            //Child runs this
            fprintf(stderr, "Child (pid = %d) will now exec\n", getpid());
            execvp(my_argvs[0], my_argvs);
            fprintf(stderr, "Should NEVER get here!\n");
            exit(1);
        }
        //Parent continues here
        if (!background) {
            wait(&status);
        }
    }
    return(EXIT_SUCCESS);
}
