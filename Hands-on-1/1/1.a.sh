#!/bin/bash

: '
==============================
Name: 1.a.syscall.c
Author: Atharva Ratnadeep Pingale
Description: Create a softlink using Symlink syscall
Date: 6th Sept 2025
==============================
'


ln -s original.txt softlink-with-sh.txt

# OUTPUT : 

# BEFORE
: '
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/1$ ls -l 
total 304
-rwxrwxr-x 1 atharva0300 atharva0300   681 Sep  6 21:00 1.a.sh
-rwxrwxr-x 1 atharva0300 atharva0300  1464 Sep  6 21:06 1.a.symlink.c
-rwxrwxr-x 1 atharva0300 atharva0300    21 Sep  6 21:08 original.txt
'

# AFTER RUNNING THE SHELL FILE 
: '
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/1$ ./1.a.sh
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/1$ ls -l 
total 304
-rwxrwxr-x 1 atharva0300 atharva0300   853 Sep  6 21:10 1.a.sh
-rwxrwxr-x 1 atharva0300 atharva0300  1464 Sep  6 21:06 1.a.symlink.c
-rwxrwxr-x 1 atharva0300 atharva0300    21 Sep  6 21:08 original.txt
lrwxrwxrwx 1 atharva0300 atharva0300    12 Sep  6 21:10 softlink-with-sh.txt -> original.txt
'

