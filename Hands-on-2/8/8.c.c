/*
==============================
Name: 8.c.c
Author: Atharva Ratnadeep Pingale
Description: Write a separate program using signal system call to catch the following signals.
                a. SIGSEGV                                  
                b. SIGINT                                   
                c. SIGFPE                               [X]
                d. SIGALRM (use alarm system call)
                e. SIGALRM (use setitimer system call)
                f. SIGVTALRM (use setitimer system call)
                g. SIGPROF (use setitimer system call)
Date: 23rd Sept 2025
==============================
*/



// sigfpe.c
#include <stdio.h>
#include <signal.h>

void handler(int sig) {
    printf("Caught SIGFPE! (Divide by zero)\n");
    _exit(1);
}

int main() {
    signal(SIGFPE, handler);

    printf("Triggering SIGFPE...\n");
    int x = 1 / 0; // Cause divide by zero

    return 0;
}


/*
OUTPUT : 
========================
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/8$ g++ 8.c.c -o 8.c 
8.c.c: In function ‘int main()’:
8.c.c:32:15: warning: division by zero [-Wdiv-by-zero]
   32 |     int x = 1 / 0; // Cause divide by zero
      |             ~~^~~
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/8$ ./8.c
Triggering SIGFPE...
Caught SIGFPE! (Divide by zero)

*/
