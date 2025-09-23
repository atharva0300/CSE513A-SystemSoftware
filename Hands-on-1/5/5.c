/*
==============================
Name: 5.c
Author: Atharva Ratnadeep Pingale
Description: Write a program to create five new files with infinite loop. Execute the program in the background
and check the file descriptor table at /proc/pid/fd.
Date: 6th Sept 2025
==============================
*/


#include <stdio.h>
#include <fcntl.h>   // for open() and flags
#include <unistd.h>  // for close(), getpid()
#include <time.h>    // for time display

int main() {
    int fd[5];
    const char *filenames[5] = {
        "file1.txt", "file2.txt", "file3.txt", "file4.txt", "file5.txt"
    };


    // Create and open 5 files
    for (int i = 0; i < 5; i++) {
        fd[i] = open(filenames[i], O_CREAT | O_RDWR, 0644);
        if (fd[i] == -1) {
            perror("open failed");
            return 1;
        }
        printf("Created and opened %s (FD = %d)\n", filenames[i], fd[i]);
    }

    printf("Process PID: %d\n", getpid());

    // infintie loop
    while (1) {
        printf("Running...\n");
        fflush(stdout);
        sleep(5);
    }

    // closing hte files
    for (int i = 0; i < 5; i++) {
        close(fd[i]);
    }

    return 0;
}


/*
OUTPUT : 
========================
BEFORE :
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/5$ ls -l
total 188
-rwxrwxr-x 1 atharva0300 atharva0300  1159 Sep  6 22:22 5.c


AFTER : 
TERMINAL 1 : 
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/5$ g++ 5.c -o 5
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/5$ ./5
Created and opened file1.txt (FD = 3)
Created and opened file2.txt (FD = 4)
Created and opened file3.txt (FD = 5)
Created and opened file4.txt (FD = 6)
Created and opened file5.txt (FD = 7)
Process PID: 13121
Running...
Running...



TERMINAL 2 : 
atharva0300@systems-software:~/Desktop/Github/systems-software-programs$ cd /proc/13121/fd
atharva0300@systems-software:/proc/13121/fd$ ls -l
total 0
lrwx------ 1 atharva0300 atharva0300 64 Sep  6 22:25 0 -> /dev/pts/1
lrwx------ 1 atharva0300 atharva0300 64 Sep  6 22:25 1 -> /dev/pts/1
lr-x------ 1 atharva0300 atharva0300 64 Sep  6 22:25 103 -> /snap/code/202/usr/share/code/v8_context_snapshot.bin
lrwx------ 1 atharva0300 atharva0300 64 Sep  6 22:25 2 -> /dev/pts/1
lrwx------ 1 atharva0300 atharva0300 64 Sep  6 22:25 3 -> /home/atharva0300/Desktop/Github/systems-software-programs/hands-on-1/5/file1.txt
lrwx------ 1 atharva0300 atharva0300 64 Sep  6 22:25 4 -> /home/atharva0300/Desktop/Github/systems-software-programs/hands-on-1/5/file2.txt
l-wx------ 1 atharva0300 atharva0300 64 Sep  6 22:25 40 -> /home/atharva0300/.config/Code/logs/20250906T204459/ptyhost.log
lrwx------ 1 atharva0300 atharva0300 64 Sep  6 22:25 41 -> 'socket:[16150]'
lrwx------ 1 atharva0300 atharva0300 64 Sep  6 22:25 42 -> /dev/ptmx
lrwx------ 1 atharva0300 atharva0300 64 Sep  6 22:25 5 -> /home/atharva0300/Desktop/Github/systems-software-programs/hands-on-1/5/file3.txt
lrwx------ 1 atharva0300 atharva0300 64 Sep  6 22:25 6 -> /home/atharva0300/Desktop/Github/systems-software-programs/hands-on-1/5/file4.txt
lrwx------ 1 atharva0300 atharva0300 64 Sep  6 22:25 7 -> /home/atharva0300/Desktop/Github/systems-software-programs/hands-on-1/5/file5.txt




*/