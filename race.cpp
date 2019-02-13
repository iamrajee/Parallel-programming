/*============================================== INCLUDING LIBRARIES ====================================*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include<time.h>
#include<unistd.h>
#include <iostream>
#include <string>
using namespace std;


clock_t tStart = clock();
/*============================================== GLOBAL VARIABLES =======================================*/
int turtle=0;                                             //variable to store distance covered by turtle
int hare=0;                                               //variable to store distance covered by hare
int finish=1000;                                           //variable to store finish line distance
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
    srand ( time(NULL) ); //seeding random number so as to get different sequence each time.

    pthread_t hare_thread, turtle_thread, god_thread, reporter_thread;         //creating threads variable
    int  ret;                                                               //variable to store return value


    ret = pthread_create( &god_thread, NULL, god_function, NULL);                   //creating god thread
    if(ret) printerrormsg(ret);                    //if return value equal to 1, then print error message
    cout << "\033[1;4;30m"<<"god_thread created!"<<"\033[0m\n"<<endl;

    ret = pthread_create( &hare_thread, NULL, hare_function, NULL);                 //creating hare thread
    if(ret) printerrormsg(ret);
    cout << "\033[1;4;30m"<<"hare_thread created!"<<"\033[0m\n"<<endl;

    ret = pthread_create( &turtle_thread, NULL, turtle_function, NULL);            //creating turtle thread
    if(ret) printerrormsg(ret);
    cout << "\033[1;4;30m"<<"turtle_thread created!"<<"\033[0m\n"<<endl;

    ret = pthread_create( &reporter_thread, NULL, reporter_function, NULL);        //creating reporter thread
    if(ret) printerrormsg(ret);
    cout << "\033[1;4;30m"<<"reporter_thread created!"<<"\033[0m\n"<<endl;




    /*Waiting for all thread to end*/
    pthread_join( god_thread, NULL); 
    pthread_join( turtle_thread, NULL);
    pthread_join( hare_thread, NULL);
    pthread_join( reporter_thread, NULL); 


    /*Printing Results*/
    // printf("\n\n***************Race ends, Hare: %d, Turtle: %d*******************\n\n", hare,turtle);
    cout << "\033[1;30m"<<"\n\n***************  Race ends, Hare: "<< hare<<", Turtle: "<<turtle<<"  *******************\n\n"<<"\033[0m\n";
    if (hare>turtle){
        cout << "\033[1;4;31m"<<"\t\tHare Wins!!!\n\n"<<"\033[0m\n";
    }
    else if (turtle>hare){
        cout << "\033[1;4;31m"<<"\t\tTurtle Win!!!\n\n"<<"\033[0m\n";
    }
    else{
        cout << "\033[1;4;31m"<<"\t\tRace Ties!!!\n\n"<<"\033[0m\n";
    }
    
    cout << "\033[1;32m"<<"Execution time: "<< (double)(clock() - tStart)/CLOCKS_PER_SEC<<"\033[0m\n"<<endl;
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

        printf("\ngod_called\t");

        pthread_mutex_lock(&lock_flag);
        flag = 1;                                      //seting flag = 1, to tell hare that god is called
        pthread_mutex_unlock(&lock_flag);

    }
    return NULL;
}

/*============================================== HARE FUNCTION DEFINATION ===============================*/
void *hare_function(void* argv)
{
    
    while(hare < finish  && turtle < finish){
   
        // if(flag !=1) continue;

        pthread_mutex_lock(&lock_hare); 
        hare_temp = hare+rand()%4 + 2;                                    //incrementing hare position by 2,3,4,5 randomly
        pthread_mutex_unlock(&lock_hare);

        printf("hare_called\t");

        pthread_mutex_lock(&lock_flag);
        flag = 3;                                      //seting flag = 2, to tell turtle that hare is called
        pthread_mutex_unlock(&lock_flag);

    }
    return NULL;
}

/*============================================== TURTLE FUNCTION DEFINATION =============================*/
void *turtle_function(void* argv)
{
    while(hare < finish  && turtle < finish){
   
        // if(flag !=1) continue;

        pthread_mutex_lock(&lock_hare); 
        turtle+=1;                                        //incrementing turtle position by 1
        pthread_mutex_unlock(&lock_hare);

        printf("turtle_called\t");

        pthread_mutex_lock(&lock_flag);
        flag = 3;                                      //seting flag = 3, to tell reporter that turtle is called
        pthread_mutex_unlock(&lock_flag);

        
    }
    return NULL;
}

/*============================================== REPORTER FUNCTION DEFINATION ===========================*/
void *reporter_function(void* argv)
{
    while(hare < finish && turtle < finish){
        if(flag !=1) continue;

        printf("Hare: %d, Turtle: %d\n", hare,turtle);         //print hare and turtle position

        pthread_mutex_lock(&lock_flag);
        flag = 0;                                      //seting flag = 0 again, to tell god that reporter is called
        pthread_mutex_unlock(&lock_flag);

    }
    return NULL;
    

}

/*======================================== PRINT ERROR MESSAGE FUNCTION DEFINATION ======================*/
void printerrormsg(int ret){
    fprintf(stderr,"Error - pthread_create() return code: %d\n",ret);               //printing error message
    exit(EXIT_FAILURE);
}