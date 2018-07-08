/*
 * Author: Meet Patel 500509440
 */

#include  <stdio.h> /* printf */
#include  <sys/types.h> /* pid_t */
#include <unistd.h> /* get_pid */
#include <stdlib.h>     /* exit, EXIT_FAILURE */
#include <sys/wait.h>  /* wait */
#include <pthread.h>
#include <sys/stat.h>



void * count(void *);
int globalNumber = 0;
//Create a mutex

pthread_mutex_t count_mutex = PTHREAD_MUTEX_INITIALIZER;

int main(void) {
    int i;
    pthread_t counterThread[5];


    //Create the 5 threads
    for (i = 0; i < 5; i++) {
        pthread_create(&counterThread[i], (void *) 0, count, NULL);
               
    }
    
    //Wait for all threads to finish
    
    //YOU NEED TO INSERT THIS CODE!
       for(i=0; i < 5; i++)
   {
      pthread_join(counterThread[i], NULL); 
   }
   

    printf("End globalNumber:: %d \n", globalNumber);
    return (0);
}

void * count(void * junk) {
    int loopCount = 0;

    while (loopCount < 10) {
      pthread_mutex_lock(&count_mutex);
        int tmpNumber = globalNumber;
        printf("counter: %d, Thread: %ld, PID: %d\n",
                tmpNumber, pthread_self(), getpid());
        tmpNumber = globalNumber;
        tmpNumber++;
        usleep(random() % 2);
        globalNumber = tmpNumber;
        loopCount++;
        pthread_mutex_unlock( &count_mutex );
    }
    return (0);
}