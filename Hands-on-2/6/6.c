/*
==============================
Name: 6.c
Author: Atharva Ratnadeep Pingale
Description: Write a simple program to create three threads.
Date: 23rd Sept 2025
==============================
*/


// three_threads.c
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>

void* thread_function(void* arg) {
    int id = *(int*)arg;
    printf("Hello from thread %d\n", id);
    free(arg);  // Free the allocated memory
    return NULL;
}

int main(void) {
    pthread_t threads[3];
    int i;

    for (i = 0; i < 3; i++) {
        int *thread_id = new int;
        if (!thread_id) {
            perror("malloc");
            exit(EXIT_FAILURE);
        }
        *thread_id = i + 1;  // Thread IDs: 1, 2, 3

        if (pthread_create(&threads[i], NULL, thread_function, thread_id) != 0) {
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
=========================
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/6$ g++ 6.c -o 6
atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/6$ ./6
Hello from thread 1
Hello from thread 3
Hello from thread 2
All threads finished.

*/