 /*
        Author    :   Rajendra Singh
        RollNo.   :   111601017
        Topic     :   Parallel program for hare and turtle race.
        Logic     :     
                        > Created four thread for god, hare, turtle, reporter.
                        > These thread are runing in below order using 3 flag variables.
                                a) god
                                b) hare or turtle
                                c) reporter
                        > In each iteration turtle updates its position by 1.
                        > In each iteration hare updates its position by 2,3,4,5. Also if
                            hare is way ahead of turtle then hare sleep(i.e updates its position by 0)
                        > When the race is finished(i.e either of them reached finish position), then we 
                          end each of thread. And display result.
                        
*/


/*============================================== INCLUDING LIBRARIES ====================================*/
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include<time.h>
#include<unistd.h>
#include <iostream>
#include <string>

using namespace std;


clock_t tStart = clock(); //starting clock
/*============================================== GLOBAL VARIABLES =======================================*/
int turtle=0;                                             //variable to store distance covered by turtle
int hare=0;                                               //variable to store distance covered by hare
int finish=1000;                                          //variable to store finish line distance

int god_flag = 0;                                         //flag to remember if god called(flag = 1) or not(flag = 0) in a each iteration
int hare_flag = 0;                                       //flag to remember if hare stepped(flag = 1) or not(flag = 0) in a each iteration
int turtle_flag = 0;                                     //flag to remember if turtle stepped(flag = 1) or not(flag = 0) in a each iteration

/*============================================== MUTEX VARIABLES =======================================*/
pthread_mutex_t lock;                                //mutex lock for shared variable

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
    cout << "\033[1;30m"<<"\n\n***************  Race ends, Hare: "<< hare<<", Turtle: "<<turtle<<"  *******************\n\n"<<"\033[0m";


    if (hare>turtle){
        cout << "\033[1;4;31m"<<"\t\tHare Wins!!!\n\n"<<"\033[0m\n";
    }
    else if (turtle>hare){
        cout << "\033[1;4;31m"<<"\t\tTurtle Win!!!\n\n"<<"\033[0m\n";
    }
    else{
        cout << "\033[1;4;31m"<<"\t\tRace Ties!!!\n\n"<<"\033[0m\n";
    }
    
    /*Printing execution time*/
    cout << "\033[1;32m"<<"Execution time: "<< (double)(clock() - tStart)/CLOCKS_PER_SEC<<" s"<<"\033[0m\n"<<endl;
     exit(EXIT_SUCCESS);
}

/*============================================== GOD FUNCTION DEFINATION ================================*/
void *god_function(void* argv)
{
    while(hare < finish && turtle < finish){            //condition of ending race, i.e one of them wins!
        if(god_flag !=0) continue;                      //skip all if not god_flag = 0

        if((hare < finish && turtle < finish)!=1)   break;
        pthread_mutex_lock(&lock);
        hare = rand()%finish + 1;                       //randomly placing hare in (1,fininsh)
        turtle = rand()%finish + 1;                       //randomly placing turtle in (1,fininsh)
        god_flag = 1;                                      //seting god_flag = 1, to tell that god is called
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

/*============================================== HARE FUNCTION DEFINATION ===============================*/
void *hare_function(void* argv)
{
    
    while(hare < finish  && turtle < finish){
   
        if(god_flag !=1 || hare_flag !=0) continue;                      //skip all if not god_flag = 1 and hare_flag = 0

        // if((hare < finish && turtle < finish)!=1)   break;
        pthread_mutex_lock(&lock);
        if (hare - turtle>finish/2) {
            hare = hare;                               //hare sleeps if hare is more than finish/2 ahead of turtle
        }
        else{
            hare = hare+rand()%4 + 2;                                    //incrementing hare position by 2,3,4,5 randomly
        }
        hare_flag = 1;                                       //seting hare_flag = 1, to tell that hare is called
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

/*============================================== TURTLE FUNCTION DEFINATION =============================*/
void *turtle_function(void* argv)
{
    while(hare < finish  && turtle < finish){
        if(god_flag !=1 || turtle_flag !=0) continue;                      //skip all if not god_flag = 1 and turtle_flag = 0

        // if((hare < finish && turtle < finish)!=1)   break;
        pthread_mutex_lock(&lock);
        turtle = turtle+1;                                        //incrementing turtle position by 1
        turtle_flag = 1;                                      //seting turtle_flag = 1, to tell that turtle is called
        pthread_mutex_unlock(&lock);
    }
    return NULL;
}

/*============================================== REPORTER FUNCTION DEFINATION ===========================*/
void *reporter_function(void* argv)
{
    while(hare < finish && turtle < finish){
        if(god_flag !=1 || hare_flag !=1 || turtle_flag !=1) continue;                      //skip all if not god_flag = 1 and hare_flag = 1 and turtle_flag = 1

        // if((hare < finish && turtle < finish)!=1)   break;

        printf("Hare: %d, Turtle: %d\n", hare,turtle);         //print hare and turtle position

        /*reseting all flags onces reporter called*/     
        pthread_mutex_lock(&lock); 
        god_flag = 0;
        hare_flag = 0;
        turtle_flag = 0;
        pthread_mutex_unlock(&lock);
    }
    return NULL;
    

}

/*======================================== PRINT ERROR MESSAGE FUNCTION DEFINATION ======================*/
void printerrormsg(int ret){
    fprintf(stderr,"Error - pthread_create() return code: %d\n",ret);               //printing error message
    exit(EXIT_FAILURE);
}