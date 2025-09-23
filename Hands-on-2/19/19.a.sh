! #bin/bash 


# ==============================
# Name: 19.a.sh
# Author: Atharva Ratnadeep Pingale
# Description: Create a FIFO file by
#                 a. mknod command        [X]   
#                 b. mkfifo command       
#                 c. use strace command to find out, which command (mknod or mkfifo) is better.
#                 c. mknod system call
#                 d. mkfifo library function
# Date: 23rd Sept 2025
# ==============================
#


mknod myfifo1 p
ls -l myfifo1



# OUTPUT: 
# =============================
# atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/19$ bash 19.a.sh
# prw-rw-r-- 1 atharva0300 atharva0300 0 Sep 23 13:40 myfifo1
