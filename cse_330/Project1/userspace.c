// file: /home/tyler/project_1/userspace.c

#include <stdio.h>
#include <linux/kernel.h>
#include <sys/syscall.h>
#include <unistd.h>

int main() {
    long int shoutout = syscall(450);
    printf("The new system call returned %ld\n", shoutout);
    return 0;
}
