/*
==============================
Name: 27.execv.c
Author: Atharva Ratnadeep Pingale
Description: Write a program to execute ls -Rl by the following system calls
            a. execl   
            b. execlp  
            c. execle   
            d. execv   [X]
            e. execvp
Date: 6th Sept 2025
==============================
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    const char *args[] = {"ls", "-Rl", NULL};

    printf("Executing ls -Rl using execv\n");
    execv("/bin/ls", (char * const *)args);

    perror("execv failed");
    return EXIT_FAILURE;
}


/*
OUTPUT : 
====================================
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/27$ g++ 27.execv.c -o 27.execv
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/27$ ./27.execv
Executing ls -Rl using execv
.:
total 80
-rwxrwxr-x 1 atharva0300 atharva0300 16048 Sep  7 22:27 27.execl
-rw-rw-r-- 1 atharva0300 atharva0300   990 Sep  7 22:27 27.execl.c
-rwxrwxr-x 1 atharva0300 atharva0300 16120 Sep  7 22:29 27.execle
-rw-rw-r-- 1 atharva0300 atharva0300  1299 Sep  7 22:29 27.execle.c
-rwxrwxr-x 1 atharva0300 atharva0300 16048 Sep  7 22:28 27.execlp
-rw-rw-r-- 1 atharva0300 atharva0300  1122 Sep  7 22:28 27.execlp.c
-rwxrwxr-x 1 atharva0300 atharva0300 16096 Sep  7 22:32 27.execv
-rw-rw-r-- 1 atharva0300 atharva0300   608 Sep  7 22:32 27.execv.c

*/

