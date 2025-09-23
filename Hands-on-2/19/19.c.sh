# !bin/bash



# ==============================
# Name: 19.c.sh
# Author: Atharva Ratnadeep Pingale
# Description: Create a FIFO file by
#                 a. mknod command            
#                 b. mkfifo command
#                 c. use strace command to find out, which command (mknod or mkfifo) is better.      
#                 c. mknod system call    [X]
#                 d. mkfifo library function
# Date: 23rd Sept 2025
# ==============================

strace ./19.a
strace ./19.b


... '
OUTPUT: 
=============================================

atharva0300@systems-software:~/Desktop/Github/CSE513A-SystemSoftware/Hands-on-2/19$ bash 19.c.sh
execve("./19.a", ["./19.a"], 0x7ffe5c108ec0 /* 77 vars */) = 0
brk(NULL)                               = 0x5a50fae81000
arch_prctl(0x3001 /* ARCH_??? */, 0x7ffdb2fa7af0) = -1 EINVAL (Invalid argument)
mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x793e2ad01000
access("/etc/ld.so.preload", R_OK)      = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
newfstatat(3, "", {st_mode=S_IFREG|0644, st_size=59163, ...}, AT_EMPTY_PATH) = 0
mmap(NULL, 59163, PROT_READ, MAP_PRIVATE, 3, 0) = 0x793e2acf2000
close(3)                                = 0
openat(AT_FDCWD, "/lib/x86_64-linux-gnu/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0P\237\2\0\0\0\0\0"..., 832) = 832
pread64(3, "\6\0\0\0\4\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0"..., 784, 64) = 784
pread64(3, "\4\0\0\0 \0\0\0\5\0\0\0GNU\0\2\0\0\300\4\0\0\0\3\0\0\0\0\0\0\0"..., 48, 848) = 48
pread64(3, "\4\0\0\0\24\0\0\0\3\0\0\0GNU\0\325\31p\226\367\t\200\30)\261\30\257\33|\366c"..., 68, 896) = 68
newfstatat(3, "", {st_mode=S_IFREG|0755, st_size=2220400, ...}, AT_EMPTY_PATH) = 0
pread64(3, "\6\0\0\0\4\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0"..., 784, 64) = 784
mmap(NULL, 2264656, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x793e2aa00000
mprotect(0x793e2aa28000, 2023424, PROT_NONE) = 0
mmap(0x793e2aa28000, 1658880, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x28000) = 0x793e2aa28000
mmap(0x793e2abbd000, 360448, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1bd000) = 0x793e2abbd000
mmap(0x793e2ac16000, 24576, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x215000) = 0x793e2ac16000
mmap(0x793e2ac1c000, 52816, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x793e2ac1c000
close(3)                                = 0
mmap(NULL, 12288, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x793e2acef000
arch_prctl(ARCH_SET_FS, 0x793e2acef740) = 0
set_tid_address(0x793e2acefa10)         = 16436
set_robust_list(0x793e2acefa20, 24)     = 0
rseq(0x793e2acf00e0, 0x20, 0, 0x53053053) = 0
mprotect(0x793e2ac16000, 16384, PROT_READ) = 0
mprotect(0x5a50bd9a6000, 4096, PROT_READ) = 0
mprotect(0x793e2ad3b000, 8192, PROT_READ) = 0
prlimit64(0, RLIMIT_STACK, NULL, {rlim_cur=8192*1024, rlim_max=RLIM64_INFINITY}) = 0
munmap(0x793e2acf2000, 59163)           = 0
mknodat(AT_FDCWD, "myfifo_mknod", S_IFIFO|0666) = -1 EEXIST (File exists)
dup(2)                                  = 3
fcntl(3, F_GETFL)                       = 0x2 (flags O_RDWR)
getrandom("\xf4\x14\xf5\xee\x18\xc2\x23\x33", 8, GRND_NONBLOCK) = 8
brk(NULL)                               = 0x5a50fae81000
brk(0x5a50faea2000)                     = 0x5a50faea2000
newfstatat(3, "", {st_mode=S_IFCHR|0620, st_rdev=makedev(0x88, 0), ...}, AT_EMPTY_PATH) = 0
write(3, "mknod: File exists\n", 19mknod: File exists
)    = 19
close(3)                                = 0
exit_group(1)                           = ?
+++ exited with 1 +++
execve("./19.b", ["./19.b"], 0x7ffd7da3d290 /* 77 vars */) = 0
brk(NULL)                               = 0x585225bd4000
arch_prctl(0x3001 /* ARCH_??? */, 0x7ffe598ad340) = -1 EINVAL (Invalid argument)
mmap(NULL, 8192, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7789432e9000
access("/etc/ld.so.preload", R_OK)      = -1 ENOENT (No such file or directory)
openat(AT_FDCWD, "/etc/ld.so.cache", O_RDONLY|O_CLOEXEC) = 3
newfstatat(3, "", {st_mode=S_IFREG|0644, st_size=59163, ...}, AT_EMPTY_PATH) = 0
mmap(NULL, 59163, PROT_READ, MAP_PRIVATE, 3, 0) = 0x7789432da000
close(3)                                = 0
openat(AT_FDCWD, "/lib/x86_64-linux-gnu/libc.so.6", O_RDONLY|O_CLOEXEC) = 3
read(3, "\177ELF\2\1\1\3\0\0\0\0\0\0\0\0\3\0>\0\1\0\0\0P\237\2\0\0\0\0\0"..., 832) = 832
pread64(3, "\6\0\0\0\4\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0"..., 784, 64) = 784
pread64(3, "\4\0\0\0 \0\0\0\5\0\0\0GNU\0\2\0\0\300\4\0\0\0\3\0\0\0\0\0\0\0"..., 48, 848) = 48
pread64(3, "\4\0\0\0\24\0\0\0\3\0\0\0GNU\0\325\31p\226\367\t\200\30)\261\30\257\33|\366c"..., 68, 896) = 68
newfstatat(3, "", {st_mode=S_IFREG|0755, st_size=2220400, ...}, AT_EMPTY_PATH) = 0
pread64(3, "\6\0\0\0\4\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0@\0\0\0\0\0\0\0"..., 784, 64) = 784
mmap(NULL, 2264656, PROT_READ, MAP_PRIVATE|MAP_DENYWRITE, 3, 0) = 0x778943000000
mprotect(0x778943028000, 2023424, PROT_NONE) = 0
mmap(0x778943028000, 1658880, PROT_READ|PROT_EXEC, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x28000) = 0x778943028000
mmap(0x7789431bd000, 360448, PROT_READ, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x1bd000) = 0x7789431bd000
mmap(0x778943216000, 24576, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_DENYWRITE, 3, 0x215000) = 0x778943216000
mmap(0x77894321c000, 52816, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_FIXED|MAP_ANONYMOUS, -1, 0) = 0x77894321c000
close(3)                                = 0
mmap(NULL, 12288, PROT_READ|PROT_WRITE, MAP_PRIVATE|MAP_ANONYMOUS, -1, 0) = 0x7789432d7000
arch_prctl(ARCH_SET_FS, 0x7789432d7740) = 0
set_tid_address(0x7789432d7a10)         = 16440
set_robust_list(0x7789432d7a20, 24)     = 0
rseq(0x7789432d80e0, 0x20, 0, 0x53053053) = 0
mprotect(0x778943216000, 16384, PROT_READ) = 0
mprotect(0x5851eeb65000, 4096, PROT_READ) = 0
mprotect(0x778943323000, 8192, PROT_READ) = 0
prlimit64(0, RLIMIT_STACK, NULL, {rlim_cur=8192*1024, rlim_max=RLIM64_INFINITY}) = 0
munmap(0x7789432da000, 59163)           = 0
mknodat(AT_FDCWD, "myfifo_mkfifo", S_IFIFO|0666) = -1 EEXIST (File exists)
dup(2)                                  = 3
fcntl(3, F_GETFL)                       = 0x2 (flags O_RDWR)
getrandom("\xe4\xb7\x0f\xb4\xd5\xdf\xee\x8d", 8, GRND_NONBLOCK) = 8
brk(NULL)                               = 0x585225bd4000
brk(0x585225bf5000)                     = 0x585225bf5000
newfstatat(3, "", {st_mode=S_IFCHR|0620, st_rdev=makedev(0x88, 0), ...}, AT_EMPTY_PATH) = 0
write(3, "mkfifo: File exists\n", 20mkfifo: File exists
)   = 20
close(3)                                = 0
exit_group(1)                           = ?
+++ exited with 1 +++
'