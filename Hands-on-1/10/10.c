/*
==============================
Name: 10.c
Author: Atharva Ratnadeep Pingale
Description: Write a program to open a file with read write mode, write 10 bytes, move the file pointer by 10
bytes (use lseek) and write again 10 bytes.
a. check the return value of lseek
b. open the file with od and check the empty spaces in between the data.
Date: 6th Sept 2025
==============================
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <string.h>

int main() {
    int fd;
    ssize_t bytes_written;
    off_t offset;
    char buf1[] = "This is Atharva Pingale.";  // >10 bytes
    char buf2[] = "From I";             // <10 bytes

    // size_t buf1_length = strlen(buf1);
    // size_t buf2_length = strlen(buf2); 

    // Open file in read-write mode, create if not exists, truncate
    fd = open("lseek_file.txt", O_RDWR | O_CREAT | O_TRUNC, 0644);
    if (fd < 0) {
        perror("open");
        exit(EXIT_FAILURE);
    }

    // write first 10 bytes of buf1
    bytes_written = write(fd, buf1, 10);
    if (bytes_written != 10) {
        perror("write buf1");
        close(fd);
        exit(EXIT_FAILURE);
    }

    // move file pointer forward by 10 bytes => this creates a hole
    offset = lseek(fd,10 , SEEK_CUR);
    if (offset == (off_t)-1) {
        perror("lseek");
        close(fd);
        exit(EXIT_FAILURE);
    }
    printf("New file offset after lseek: %lld\n", (long long)offset);

    // write next 10 bytes of buf2 at new offset
    bytes_written = write(fd, buf2, 10);
    if (bytes_written != 10) {
        perror("write buf2");
        close(fd);
        exit(EXIT_FAILURE);
    }

    close(fd);

    return 0;
}


/*
OUTPUT : 
=========================
BEFORE : 
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/10$ ls -l
total 160
-rwxrwxr-x 1 atharva0300 atharva0300  1994 Sep  6 23:11 10.c



AFTER : 
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/10$ g++ 10.c -o 10
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/10$ ./10
New file offset after lseek: 34
Data written successfully to lseek_file.txt

atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/10$ cat lseek_file.txt
This is Atharva Pingale.From IIITB.
$ od -c lseek_file.txt
0000000   T   h   i   s       i   s       A   t  \0  \0  \0  \0  \0  \0
0000020  \0  \0  \0  \0   F   r   o   m       I  \0   T   h   i
0000036


*/

// comment => \0 is a hole