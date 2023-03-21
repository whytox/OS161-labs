
#include <types.h>
#include <syscall.h>
#include <lib.h>  // definition of putch, getch

ssize_t sys_write(int fd, const void* buffer, ssize_t len) {

    if (fd != 1) return 0; // only on standard output, for now...
    char* c_buffer = ((char*)buffer);
    for (ssize_t i=0; i<len; i++) {
        putch(c_buffer[i]);
    }
    return len;
}

ssize_t sys_read(int fd, void* buffer, ssize_t len) {
    if (fd != 0) return 0; // only from standard input, for now
    char* c_buffer = (char*)buffer;

    for (ssize_t i=0; i<len; i++) {
        c_buffer[i] = getch();
    }
    return 0;
}