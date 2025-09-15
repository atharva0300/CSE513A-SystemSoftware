/*
==============================
Name: 27.execvp.c
Author: Atharva Ratnadeep Pingale
Description: Write a program to execute ls -Rl by the following system calls
            a. execl   
            b. execlp  
            c. execle   
            d. execv   
            e. execvp   [X]
Date: 6th Sept 2025
==============================
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    const char *args[] = {"ls", "-Rl", NULL};

    printf("Executing ls -Rl using execvp\n");
    execvp("ls", (char * const *)args);

    perror("execvp failed");
    return EXIT_FAILURE;
}


/*
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/27$ g++ 27.execvp.c -o 27.execvp
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/27$ ./27.execvp
Executing ls -Rl using execvp
.:
total 100
-rwxrwxr-x 1 atharva0300 atharva0300 16048 Sep  7 22:27 27.execl
-rw-rw-r-- 1 atharva0300 atharva0300   990 Sep  7 22:27 27.execl.c
-rwxrwxr-x 1 atharva0300 atharva0300 16120 Sep  7 22:29 27.execle
-rw-rw-r-- 1 atharva0300 atharva0300  1300 Sep  7 22:33 27.execle.c
-rwxrwxr-x 1 atharva0300 atharva0300 16048 Sep  7 22:28 27.execlp
-rw-rw-r-- 1 atharva0300 atharva0300  1123 Sep  7 22:33 27.execlp.c
-rwxrwxr-x 1 atharva0300 atharva0300 16096 Sep  7 22:32 27.execv
-rw-rw-r-- 1 atharva0300 atharva0300  1448 Sep  7 22:33 27.execv.c
-rwxrwxr-x 1 atharva0300 atharva0300 16104 Sep  7 22:35 27.execvp
-rw-rw-r-- 1 atharva0300 atharva0300   613 Sep  7 22:35 27.execvp.c


*/



