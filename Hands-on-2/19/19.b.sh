! #bin/bash

# ==============================
# Name: 19.a.sh
# Author: Atharva Ratnadeep Pingale
# Description: Create a FIFO file by
#                 a. mknod command          
#                 b. mkfifo command        [X]
#                 c. use strace command to find out, which command (mknod or mkfifo) is better.
#                 c. mknod system call
#                 d. mkfifo library function
# Date: 23rd Sept 2025
# ==============================
#


mkfifo myfifo2 
ls -l myfifo2


# OUTPUT 
# ==============================
# atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/19$ bash 19.b.sh 
# prw-rw-r-- 1 atharva0300 atharva0300 0 Sep 23 13:44 myfifo2