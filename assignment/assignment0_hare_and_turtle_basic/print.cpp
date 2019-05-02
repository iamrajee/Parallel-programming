#include <iostream>
#include<stdio.h> 
#include<stdlib.h>
// #include <windows.h>
// #include <string>

using namespace std;
int main()
{
    int a = 5;
    // system("color F1");
    cout << "\033[1;4;31m"<<"bold red text"<<"\033[0m\n";
    cout << "\n"<<"Started!!" << "\t" << a << endl;
    cout << "Started!!" << "\t" << "6" <<"\n";
    cout << "\033[1;4;31mbold red text\033[0m\n";
}