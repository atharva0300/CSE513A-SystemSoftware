/*
==============================
Name: 7.c
Author: Atharva Ratnadeep Pingale
Description: Write a simple program to print the created thread ids.
Date: 23rd Sept 2025
==============================
*/

// print_thread_ids.c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* thread_function(void* arg) {
    pthread_t tid = pthread_self(); // Get thread ID
    printf("Thread running. Thread ID = %lu\n", (unsigned long)tid);
    return NULL;
}

int main(void) {
    pthread_t threads[3];
    int i;

    for (i = 0; i < 3; i++) {
        if (pthread_create(&threads[i], NULL, thread_function, NULL) != 0) {
            perror("pthread_create");
            exit(EXIT_FAILURE);
        }
    }

    // Wait for threads to finish
    for (i = 0; i < 3; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("All threads finished.\n");
    return 0;
}


/*
OUTPUT : 
==============================
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/7$ g++ 7.c -o 7
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/7$ ./7
Thread running. Thread ID = 138007759812160
Thread running. Thread ID = 138007743026752
Thread running. Thread ID = 138007751419456
All threads finished.


*/