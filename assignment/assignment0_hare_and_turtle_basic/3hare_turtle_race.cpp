/*============================================== INCLUDING LIBRARIES ====================================*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include<time.h>
#include<unistd.h>

/*============================================== GLOBAL VARIABLES =======================================*/
int turtle=0;                                             //variable to store distance covered by turtle
int hare=0;                                               //variable to store distance covered by hare
int finish=100;                                           //variable to store finish line distance
char *winner[20];                                         //variable to store winner name
int flag = 0;                                             //variable to maintain the order in which all function run
/*============================================== MUTEX VARIABLES =======================================*/
pthread_mutex_t lock_hare;                                //mutex lock for hare variable
pthread_mutex_t lock_turtle;                              //mutex lock for turtle variable
pthread_mutex_t lock_flag;                                //mutex lock for flag variable

/*============================================== FUNCTION DECLARATIONS =================================*/
void *god_function(void*);                                 //function to randomly chose hare and turtle position
void *hare_function(void*);                                //function to increment hare position
void *turtle_function(void*);                              //function to increment turtle position
void *reporter_function(void*);                            //function to print har and turtle position
void printerrormsg(int);                                   //function to print error messages

/*============================================== MAIN FUNCTION ========================================*/
int main()
{
     pthread_t hare_thread, turtle_thread, god_thread, reporter_thread;         //creating threads variable
     int  ret;                                                               //variable to store return value

    srand(time(NULL));

     ret = pthread_create( &god_thread, NULL, god_function, NULL);                   //creating god thread
     if(ret) printerrormsg(ret);                    //if return value equal to 1, then print error message
     printf("god_thread created!\n");

     ret = pthread_create( &hare_thread, NULL, hare_function, NULL);                 //creating hare thread
     if(ret) printerrormsg(ret);
     printf("hare_thread created!\n");

     ret = pthread_create( &turtle_thread, NULL, turtle_function, NULL);            //creating turtle thread
     if(ret) printerrormsg(ret);
     printf("turtle_thread created!\n");

     ret = pthread_create( &reporter_thread, NULL, reporter_function, NULL);        //creating reporter thread
     if(ret) printerrormsg(ret);
     printf("reporter_thread created!\n");




    /*Waiting for all thread to end*/
    pthread_join( god_thread, NULL); 
    pthread_join( turtle_thread, NULL);
    pthread_join( hare_thread, NULL);
    pthread_join( reporter_thread, NULL); 


    /*Printing Results*/
    printf("\n\n***************Race ends, Hare: %d, Turtle: %d**********\n\n", hare,turtle);
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

/*============================================== GOD FUNCTION DEFINATION ================================*/
void *god_function(void* argv)
{
    while(hare < finish && turtle < finish){            //condition of ending race, i.e one of them wins!
        
        if(flag !=0) continue;

        pthread_mutex_lock(&lock_hare);                 //lock hare variable
        hare = rand()%finish + 1;                       //randomly placing hare in (1,fininsh)
        pthread_mutex_unlock(&lock_hare);               //unlock hare variable

        pthread_mutex_lock(&lock_turtle);
        turtle = rand()%finish + 1;                       //randomly placing turtle in (1,fininsh)
        pthread_mutex_unlock(&lock_turtle);

        pthread_mutex_lock(&lock_flag);
        flag = 1;                                      //seting flag = 1, so that 
        pthread_mutex_unlock(&lock_flag);

        printf("god_called\n");
    }
    return NULL;
}

/*============================================== HARE FUNCTION DEFINATION ===============================*/
void *hare_function(void* argv)
{
    
    while(hare < finish  && turtle < finish){

        pthread_mutex_lock(&lock_hare); 
        hare+=3;                                        //incrementing hare position by 3
        pthread_mutex_unlock(&lock_hare);

        printf("hare_called\n");
    }
    return NULL;
}

/*============================================== TURTLE FUNCTION DEFINATION =============================*/
void *turtle_function(void* argv)
{
    while(turtle < finish  && turtle < finish){

        pthread_mutex_lock(&lock_hare); 
        turtle+=1;                                        //incrementing turtle position by 1
        pthread_mutex_unlock(&lock_hare);

        printf("turtle_called\n");
    }
    return NULL;
}

/*============================================== REPORTER FUNCTION DEFINATION ===========================*/
void *reporter_function(void* argv)
{
    while(hare < finish && turtle < finish){
        printf("reporter_called => Hare: %d, Turtle: %d\n\n", hare,turtle);         //print hare and turtle position
    }
    return NULL;
    

}

/*======================================== PRINT ERROR MESSAGE FUNCTION DEFINATION ======================*/
void printerrormsg(int ret){
    fprintf(stderr,"Error - pthread_create() return code: %d\n",ret);               //printing error message
    exit(EXIT_FAILURE);
}