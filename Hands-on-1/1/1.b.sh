#!/bin/bash


: '/*
==============================
Name: 1.b.sh
Author: Atharva Ratnadeep Pingale
Description: Create a hardlink using shell command
Date: 6th Sept 2025
==============================
*/'

ln original.txt hardlink-with-sh.txt 

: '
OUTPUT : 
=============================
BEFORE : 

atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/1$ ls -l
total 344
-rwxrwxr-x 1 atharva0300 atharva0300 16048 Sep  6 21:14 1.b.link
-rwxrwxr-x 1 atharva0300 atharva0300  1411 Sep  6 21:17 1.b.link.c
-rw-rw-r-x 1 atharva0300 atharva0300   248 Sep  6 21:18 1.b.sh
-rw-rw-r-- 2 atharva0300 atharva0300    21 Sep  6 21:24 hardlink-with-link.txt
-rwxrwxr-- 2 atharva0300 atharva0300    21 Sep  6 21:08 original.txt


AFTER : 
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/1$ ./1.b.sh
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/1$ ls -l
-rwxrwxr-x 1 atharva0300 atharva0300 16048 Sep  6 21:26 1.b.link
-rwxrwxr-x 1 atharva0300 atharva0300  1613 Sep  6 21:27 1.b.link.c
-rwxrwxr-x 1 atharva0300 atharva0300   685 Sep  6 21:20 1.b.sh
-rw-rw-r-- 3 atharva0300 atharva0300    21 Sep  6 21:24 hardlink-with-link.txt
-rw-rw-r-- 3 atharva0300 atharva0300    21 Sep  6 21:24 hardlink-with-sh.txt
-rw-rw-r-- 3 atharva0300 atharva0300    21 Sep  6 21:24 original.txt


'

