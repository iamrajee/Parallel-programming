#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include<time.h>
#include<unistd.h>
#include <iostream>
#include <string>
#include <errno.h>

using namespace std;


clock_t tStart = clock(); //starting clock

double sum = 0;
long long iters = 0;
long long NUM_THREADS = 0;
long long counter = 0;
void *compute(void *rank);

pthread_cond_t cond = PTHREAD_COND_INITIALIZER; 
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;

int main(int argc, char* argv[]) 
{
    long thread;
    if (argc == 1) {
        fprintf(stderr, "Insufficient arguments.Need number of iters\n");
        exit(1);
    }
    iters = strtoll(argv[1], NULL, 10);
    NUM_THREADS = strtoll(argv[2], NULL, 10);
    pthread_t *handles;
    double val = 0.0;
    
    handles = (pthread_t*) malloc(NUM_THREADS * sizeof(pthread_t));
    
    for(thread = 0; thread < NUM_THREADS; thread++)  {
        pthread_create(&handles[thread], NULL, compute, (void*) thread);
    }
    
    for(thread = 0; thread < NUM_THREADS; thread++)  {
        pthread_join(handles[thread], NULL);
    }
    free(handles);
    
    val = 4.0 * sum;
	cout << ", "<< val << ", " << (double)(clock() - tStart)/CLOCKS_PER_SEC;
    return 0;
}

void *compute(void *rank) 
{
    long my_rank = (long) rank;
    double factor;
    long long i;
    long long my_n = iters/NUM_THREADS;
    long long my_first_i = my_n * my_rank;
    long long my_last_i = my_first_i + my_n;
    double my_sum;
    if (my_first_i % 2 == 0) {
        factor = 1.0;
    }
    else {
        factor = -1.0;
    }
    for (i = my_first_i; i < my_last_i; i++) {
        my_sum += factor/(double) (2*i+1);
        factor = -1.0 * factor;
    }
    
    pthread_mutex_lock(&mutex);
    sum += my_sum;
    counter++;
    if(counter < NUM_THREADS){
            pthread_cond_wait(&cond, &mutex); 
    }
    else{
        pthread_cond_broadcast(&cond);
    }
    pthread_mutex_unlock(&mutex);
    return NULL;
}
