#include <cdefs.h>
#include <types.h>
#include <syscall.h>
#include <current.h>
#include <thread.h>

void sys__exit(int exit_code) {
    curthread->exit_code = exit_code;
    thread_exit();
}