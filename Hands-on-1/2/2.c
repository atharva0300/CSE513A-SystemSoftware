/*
==============================
Name: 2.c
Author: Atharva Ratnadeep Pingale
Description: Write a simple program to execute in an infinite loop at the background. Go to /proc directory and
identify all the process related information in the corresponding proc directory.
Date: 6th Sept 2025
==============================
*/


#include <stdio.h>
#include <unistd.h>



int main() {
    while (1) {
        printf("Process running PID: %d\n", getpid());
        fflush(stdout);
        sleep(5);
    }
    return 0;
}


/*
OUTPUT : 
===================
TERMINAL 1 : 
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/2$ g++ 2.c -o 2
atharva0300@systems-software:~/Desktop/Github/systems-software-programs/hands-on-1/2$ ./2
Process running PID: 10905
Process running PID: 10905


TERMINAL 2 : 
atharva0300@systems-software:~/Desktop/Github/systems-software-programs$ cd /proc/10905/
atharva0300@systems-software:/proc/10905$ ls
arch_status  clear_refs          cpuset   fdinfo             latency    mem         ns             pagemap      sched      smaps_rollup  syscall         uid_map
attr         cmdline             cwd      gid_map            limits     mountinfo   numa_maps      patch_state  schedstat  stack         task            wchan
autogroup    comm                environ  io                 loginuid   mounts      oom_adj        personality  sessionid  stat          timens_offsets
auxv         coredump_filter     exe      ksm_merging_pages  map_files  mountstats  oom_score      projid_map   setgroups  statm         timers
cgroup       cpu_resctrl_groups  fd       ksm_stat           maps       net         oom_score_adj  root         smaps      status        timerslack_ns


*/