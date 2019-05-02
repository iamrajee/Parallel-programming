#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include<time.h>
#include<unistd.h>


int turtle=0;
int hare=0;
int finish=20;
char *winner[20];

int hare_steped = 0;
int turtle_steped = 0;
int reporter_signal = 0;

void *god_function(void*);
void *hare_function(void*);
void *turtle_function(void*);
void *reporter_function(void*);
void printerrormsg(int);

pthread_mutex_t lock;
pthread_mutex_t lock_hare;
pthread_mutex_t lock_turtle;

int main()
{
     pthread_t hare_thread, turtle_thread, god_thread, reporter_thread;
     int  ret;

     srand(time(NULL));
     int rando= rand() % finish +1;

     ret = pthread_create( &god_thread, NULL, god_function, NULL);
     if(ret) printerrormsg(ret);
     printf("god_thread created!\n");

     ret = pthread_create( &hare_thread, NULL, hare_function, NULL);
     if(ret) printerrormsg(ret);
     printf("hare_thread created!\n");

     ret = pthread_create( &turtle_thread, NULL, turtle_function, NULL);
     if(ret) printerrormsg(ret);
     printf("turtle_thread created!\n");

     ret = pthread_create( &reporter_thread, NULL, reporter_function, NULL);
     if(ret) printerrormsg(ret);
     printf("reporter_thread created!\n");




    
     pthread_join( god_thread, NULL);
     pthread_join( turtle_thread, NULL);
     pthread_join( hare_thread, NULL);
     pthread_join( reporter_thread, NULL); 
     pthread_mutex_destroy(&lock);

    if (hare>turtle){
        printf("Hare Wins!!!\n");
    }
    else if (turtle>hare){
        printf("Turtle Wins!!!\n");
    }
    else{
        printf("Race Ties!!!\n");
    }

     exit(EXIT_SUCCESS);
}


void *god_function(void* argv)
{
    while(hare < finish && turtle < finish){
        //pthread_mutex_lock(&lock); 
        hare = rand()%finish + 1;
        turtle = rand()%finish + 1;
        printf("god_called\n");
        while (reporter_signal==0);
        //pthread_mutex_unlock(&lock);
    }
    return NULL;
}

void *hare_function(void* argv)
{
    
    while(hare < finish){
        //pthread_mutex_lock(&lock); 
        reporter_signal = 0;

        hare+=3;
        hare_steped = 1;
        printf("hare_called\n");
        while (reporter_signal==0);

        //pthread_mutex_unlock(&lock);
    }
    return NULL;
}

void *turtle_function(void* argv)
{
    while(turtle < finish){
        //pthread_mutex_lock(&lock); 
        reporter_signal = 0;
        turtle+=3;
        turtle_steped = 1;
        printf("turtle_called\n");
        while (reporter_signal==0);

        //pthread_mutex_unlock(&lock);
    }
    return NULL;
}

void *reporter_function(void* argv)
{
    while(hare < finish || turtle < finish){
        //pthread_mutex_lock(&lock); 
        while (hare_steped==0 || turtle_steped==0);
        printf("reporter_called => Hare: %d, Turtle: %d\n\n", hare,turtle);
        hare_steped=0;
        turtle_steped==0;
        reporter_signal = 1;
        //pthread_mutex_unlock(&lock);
    }
    return NULL;
    

}

void printerrormsg(int ret){
    fprintf(stderr,"Error - pthread_create() return code: %d\n",ret);
    exit(EXIT_FAILURE);
}