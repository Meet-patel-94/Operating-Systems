/**
 *
 * COE 628 - Operating Systems
 * © Ebrahim Bagheri
 * Lab 6
 *
 **/
#include <stdlib.h>     /* NULL */
#include  <stdio.h>	/* printf */
#include  <sys/types.h>	/* pid_t */
#include <unistd.h>	/* get_pid */
#include <stdlib.h>     /* exit, EXIT_FAILURE */
#include <sys/wait.h> 	/* wait */
#include <pthread.h>

#define PRODUCER_NO 5	//Number of producers
#define NUM_PRODUCED 2000 //Number of items to be produced

void *generator_function(void *args);
void *print_function(void *a);
long sum; /* Sum of generated values*/
long finished_producers; /* number of the producer that finished producing */

//C: Mutex declaration and initialization
pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
//F: Condition variable declaration and initialization
pthread_cond_t cond1 = PTHREAD_COND_INITIALIZER;

int main(void) {
    /* initialize random seed: */
    srand(time(NULL));
    sum = 0;
    int i;
    pthread_t counterThread[5], print_thread;
    
    //A: Creates five generator thread
    for (i = 0; i < 5; i++) {
        pthread_create(&counterThread[i], (void *) 0,generator_function, NULL);
    }
    
    //D: Creates print thread
    pthread_create(&print_thread, (void *) 0,print_function, NULL);    

    //B: Makes sure that all generator threads has finished before proceeding
    for(i=0; i < 5; i++){
      pthread_join(counterThread[i], NULL); 
    }
    
    //E: Makes sure that print thread has finished before proceeding
    pthread_join(print_thread, NULL);

    return (0);

}

void *generator_function(void *args) {

    long counter = 0;
    long sum_this_generator = 0;

    pthread_mutex_lock( &mutex1 );
    while (counter < 2000L) {

        long tmpNumber = sum;
        long rnd_number = rand() % 10;
        printf("current sum of the generated number up to now is %ld going to add %ld to it.\n", tmpNumber, rnd_number);
        sum = tmpNumber + rnd_number;
        counter++;
        sum_this_generator += rnd_number;
        usleep(1000);
    }
    printf("--+---+----+----------+---------+---+--+---+------+----\n");
    printf("The sum of produced items for this number generator at the end is: %ld \n", sum_this_generator);
    printf("--+---+----+----------+---------+---+--+---+------+----\n");
    finished_producers++;
    //H: If all generator has finished fire signal for condition variable
    pthread_mutex_unlock( &mutex1 );
    if(finished_producers == PRODUCER_NO)
    	pthread_cond_signal(&cond1);
    return (0);
}

void *print_function(void *a) {
    //G: Wait until all generator has finished
    pthread_mutex_lock( &mutex1 );
    while (finished_producers != PRODUCER_NO){
    	pthread_cond_wait(&cond1,&mutex1);
    }
    
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    printf("The value of counter at the end is: %ld \n", sum);
    printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n");
    pthread_mutex_unlock( &mutex1 );
    
}
