/*
==============================
Name: 30.c
Author: Atharva Ratnadeep Pingale
Description: Write a program to run a script at a specific time using a Daemon process.
Date: 6th Sept 2025
==============================
*/


#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <string.h>
#include <signal.h>

void daemonize() {
    pid_t pid = fork();
    if (pid < 0) exit(EXIT_FAILURE);
    if (pid > 0) exit(EXIT_SUCCESS); // Parent exit

    if (setsid() < 0) exit(EXIT_FAILURE);

    signal(SIGCHLD, SIG_IGN);
    signal(SIGHUP, SIG_IGN);

    pid = fork();
    if (pid < 0) exit(EXIT_FAILURE);
    if (pid > 0) exit(EXIT_SUCCESS);

    chdir("/");

    // Close all open file descriptors including stdout and stderr
    for (int x = sysconf(_SC_OPEN_MAX); x>=0; x--) {
        close(x);
    }

    // open /dev/null for stdin, stdout, stderr to prevent errors
    // int fd = open("/dev/null", O_RDWR);
    // if (fd != -1) {
    //     dup2(fd, STDIN_FILENO);
    //     dup2(fd, STDOUT_FILENO);
    //     dup2(fd, STDERR_FILENO);
    //     if (fd > 2) close(fd);
    // }
}



int main() {
    // Target time to run script in 24-hour format
    int target_hour = 23;   
    int target_min = 10;

    // Set full absolute path to script (assuming your script is in /home/atharva0300/...)
    const char *script_path = "/home/atharva0300/Desktop/Github/systems-software-programs/hands-on-1/30/30.script.sh";

    daemonize();


    while(1) {
        time_t now = time(NULL);
        struct tm *t = localtime(&now);
        if (t->tm_hour == target_hour && t->tm_min == target_min) {
            // Run the script; handle output/return if desired
            system(script_path);

            // Sleep 60 seconds to avoid running the script repeatedly within the same minute
            sleep(60);
        }
        // sleep(30);  // Check every 30 seconds
    }

    return 0;
}


/*
OUTPUT : 
========================
** TERMINAL **
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/30$ g++ 30.c -o 30
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/30$ ./30

30.daemon_script.log FILE : 
Script executed at Sun 06 Sep 2025 11:10:00 PM IST


comment => the while loop executes the code every second and checks if the target time has arrived or not




*/