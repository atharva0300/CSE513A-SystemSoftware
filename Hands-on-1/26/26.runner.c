/*
==============================
Name: 26.runner.c
Author: Atharva Ratnadeep Pingale
Description: Write a program to execute an executable program.
            a. use some executable program
            b. pass some input to an executable program. (for example execute an executable of $./a.out name)
Date: 6th Sept 2025
==============================
*/



#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <name>\n", argv[0]);
        return EXIT_FAILURE;
    }

    printf("Executing target.out with argument \"%s\"\n", argv[1]);

    // Pass the input argument argv[1] to target.out
    execl("./26.target", "26.target", argv[1], (char *)NULL);

    // If execl returns, an error occurred
    perror("execl failed");
    return EXIT_FAILURE;
}



/*
OUTPUT : 
============================
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/26$ g++ 26.target.c -o 26.target
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/26$ ./26.target Atharva
Hello, Atharva!
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/26$ g++ 26.runner.c -o 26.runner
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/26$ ./26.runner AtharvaPingale!
Executing target.out with argument "AtharvaPingale!"
Hello, AtharvaPingale!!


*/