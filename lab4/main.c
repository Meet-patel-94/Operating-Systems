/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */

/* 
 * File:   main.c
 * Author: Meet Patel
 *
 * Created on February 18, 2016, 6:36 PM
 */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>

char cmd[100];
char cmd1[100];
char cmd2[100];

int main(int argc, char** argv) 
{
    printf("Please enter your pipe command:\n");
    fgets(cmd, 100, stdin);
    int i,j=0,k=0;
    int flags = 0;
    int length;
    length = strlen(cmd) - 1;
    for (i=0;i<length;i++){                  // This is for parsing the string
        if (cmd[i] != '|' && flags == 0){
            cmd1[j] = cmd[i];
            j++;
        }
        else if(cmd[i] == '|') {
            flags = 1;
            i++;
        }
        else{
            cmd2[k] = cmd[i];
            k++;
        }          
    } // This is when the parsing is done
    
    int fd[2], pid;
    pipe(fd);
    switch(pid = fork()){
      case 0:
            dup2(fd[1],1);
            close(fd[0]);
            system(cmd1);
            exit(0);
            
        default:
            dup2(fd[0],0);
            close(fd[1]);
            system(cmd2);
    }

    return (EXIT_SUCCESS);
}


