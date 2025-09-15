/*
==============================
Name: 20.c
Author: Atharva Ratnadeep Pingale
Description: Find out the priority of your running program. Modify the priority with nice command.
Date: 6th Sept 2025
==============================
*/


#include <stdio.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
    pid_t pid = getpid();
    int priority = getpriority(PRIO_PROCESS, pid);

    if (priority == -1) {
        perror("getpriority");
        return 1;
    }

    printf("Current nice value of process %d is: %d\n", pid, priority);
    getchar();  // waiting for the user to press a character on the keyboard, so that the program is kept running 
    // so that we can change the niceness of that program. 

    priority = getpriority(PRIO_PROCESS , pid);
    if (priority == -1) {
        perror("getpriority");
        return 1;
    }

    printf("After changing the niceness of the process\n");
    printf("Current nice value of process %d is: %d\n", pid, priority);


    return 0;
}


/*
OUTPUT : 
==========================
=> SETTING THE PRIORITY USING 'NICE' BEFORE THE PROGRAM IS RUN : 
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/20$ nice -n 19 ./20 
Current nice value of process 37492 is: 19



=> SETTING THE PRIORITY USING 'RENICE' WHEN THE PROGRAM IR RUNNING : 
** TERMINAL 1: ** 
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/20$ nice -n 19 ./20 
Current nice value of process 37599 is: 19

After changing the niceness of the process
Current nice value of process 37599 is: 12


** TERMINAL 2 : **
atharva0300@systems-software:~/Desktop/Github/systems-software-programs$ sudo renice 5 -p 37599
[sudo] password for atharva0300: 
37599 (process ID) old priority 19, new priority 5
atharva0300@systems-software:~/Desktop/Github/systems-software-programs$ renice 12 -p 37599
37599 (process ID) old priority 5, new priority 12




comment => note that to reduce the priority of the process, the user needs to have sudo priviledges.
            but to increase t he priority, the user does not need to have sudo priviledges.
comment => note that in terminal 1, the priority displayed is 19 -> 12 . But actually it is 19 -> 5 -> 12 , as the 12 displayed here is the final priority 


*/

