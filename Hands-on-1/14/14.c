/*
==============================
Name: 14.c
Author: Atharva Ratnadeep Pingale
Description: Write a program to find the type of a file.
a. Input should be taken from command line.
b. program should be able to identify any type of a file.
Date: 6th Sept 2025
==============================
*/



#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
    
    struct stat fileStat;
    // fileName is not set during compilation as the problem asks to take the file name as input from the STDIN

    if (argc != 2) {
        fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }


    if(lstat(argv[1], &fileStat) == -1){
        perror("lstat");
        exit(EXIT_FAILURE);
    }   



    printf("File: %s\n", argv[1]);
    printf("Type: ");

    if (S_ISREG(fileStat.st_mode))
        printf("Regular File\n");
    else if (S_ISDIR(fileStat.st_mode))
        printf("Directory\n");
    else if (S_ISCHR(fileStat.st_mode))
        printf("Character Device\n");
    else if (S_ISBLK(fileStat.st_mode))
        printf("Block Device\n");
    else if (S_ISFIFO(fileStat.st_mode))
        printf("FIFO (Named Pipe)\n");
    else if (S_ISLNK(fileStat.st_mode))
        printf("Symbolic Link\n");
    else if (S_ISSOCK(fileStat.st_mode))
        printf("Socket\n");
    else
        printf("Unknown Type\n");

    return 0;
}


/*
OUTPUT : 
==============================
BEFORE ( CREATING DIFFERENT FILE TYPES USING THE COMMAND LINE ) : 
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/14$ ls -l 
total 116
-rwxrwxr-x 1 atharva0300 atharva0300  1506 Sep  7 06:52 14.c

=> CREATING REGULAR FILE: 
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/14$ echo 'This is a dummy file' > dummyFile.txt

=> CREATING DIRECTORY: 
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/14$ mkdir dummyDir

=> CREATING CHARACTER DEVICE: 
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/14$ sudo mknod dummyCharacterDevice c 1 7
[sudo] password for atharva0300: 

=> CREATING BLOCK DEVICE: 
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/14$ sudo mknod dummyBlockDevice b 1 0

=> CREATING FIFO: 
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/14$ mkfifo dummyFIFO

=> CREATING SYMBOLIC LINK: 
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/14$ ln -s dummySymbolicLink randomFile.txt

=> CREATING SOCKET: 
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/14$ socat UNIX-LISTEN:dummySocket -

=> LS -L: 
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/14$ ls -l 
total 124
-rwxrwxr-x 1 atharva0300 atharva0300  2758 Sep  7 06:59 14.c
brw-r--r-- 1 root        root         1, 0 Sep  7 06:54 dummyBlockDevice
crw-r--r-- 1 root        root         1, 7 Sep  7 06:53 dummyCharacterDevice
drwxrwxr-x 2 atharva0300 atharva0300  4096 Sep  7 06:53 dummyDir
prw-rw-r-- 1 atharva0300 atharva0300     0 Sep  7 06:54 dummyFIFO
-rw-rw-r-- 1 atharva0300 atharva0300    21 Sep  7 06:53 dummyFile.txt
lrwxrwxrwx 1 atharva0300 atharva0300    17 Sep  7 06:55 randomFile.txt -> dummySymbolicLink




AFTER ( CHECKING IF IT IDENTIFIES EACH FILE TYPE OR NOT ) :
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/14$ g++ 14.c -o 14
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/14$ ./14 dummyFile.txt
File: dummyFile.txt
Type: Regular File
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/14$ ./14 dummyBlockDevice
File: dummyBlockDevice
Type: Block Device
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/14$ ./14 dummyCharacterDevice
File: dummyCharacterDevice
Type: Character Device
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/14$ ./14 dummyDir
File: dummyDir
Type: Directory
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/14$ ./14 dummyFIFO
File: dummyFIFO
Type: FIFO (Named Pipe)
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/14$ ./14 randomFile.txt
File: randomFile.txt
Type: Symbolic Link



*/