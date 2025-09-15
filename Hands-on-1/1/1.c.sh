#!/bin/bash

: '
/*
==============================
Name: 1.c.sh
Author: Atharva Ratnadeep Pingale
Description: Create a FIFO using shell command
Date: 6th Sept 2025
==============================
*/
'

mkfifo fifo-with-shell

: 'Writing to the FIFO' 
echo "Hello Pune through FIFO" > fifo-with-shell & 

: '
OUTPUT : 
======================
BEFORE : 
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/1$ ls -l
total 368
-rwxrwxr-x 1 atharva0300 atharva0300 16056 Sep  6 21:37 1.c.mkfifo
-rwxrwxr-x 1 atharva0300 atharva0300  1123 Sep  6 21:39 1.c.mkfifo.c
-rw-rw-r-- 1 atharva0300 atharva0300   167 Sep  6 21:41 1.c.sh

AFTER : 
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/1$ ./1.c.sh
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/1$ ls -l
total 368
-rwxrwxr-x 1 atharva0300 atharva0300 16056 Sep  6 21:37 1.c.mkfifo
-rwxrwxr-x 1 atharva0300 atharva0300  1123 Sep  6 21:39 1.c.mkfifo.c
-rwxrwxr-x 1 atharva0300 atharva0300   477 Sep  6 21:42 1.c.sh
prw-rw-r-- 1 atharva0300 atharva0300     0 Sep  6 21:42 fifo-with-shell

'