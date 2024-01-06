#include "hello.h"
#include <types.h>
#include <kern/errno.h>
#include <kern/reboot.h>
#include <kern/unistd.h>
#include <lib.h>
#include <spl.h>
#include <clock.h>
#include <thread.h>
#include <proc.h>
#include <current.h>
#include <synch.h>
#include <vm.h>
#include <mainbus.h>
#include <vfs.h>
#include <device.h>
#include <syscall.h>
#include <test.h>
#include <version.h>
#include "autoconf.h"  // for pseudoconfig
#include "opt-exit_syscall.h"
#include "opt-file_syscalls.h"
#include "opt-lock_1.h"
#include "opt-lock_2.h"
#include "opt-cond_var.h"
#include "opt-waitpid.h"

// 'hello' function for lab 1
// the prototype is in /kern/include/hello.h
void hello(void) {
    kprintf("\n\nHello World!\n\n");

    kprintf("Available features:\n");
    #if OPT_EXIT_SYSCALL
    kprintf("[lab 2] - exit syscall\n");
    #endif

    #if OPT_FILE_SYSCALLS
    kprintf("[lab 2] - file syscalls\n");
    #endif

    #if OPT_LOCK_1
    kprintf("[lab 3] - lock (semaphore)\n");
    #elif OPT_LOCK_2
    kprintf("[lab 3] - lock (wait channel)\n");
    #endif

    #if OPT_COND_VAR
    kprintf("[lab 3] - condition variable\n");
    #endif

    #if OPT_WAITPID
    kprintf("[lab 4] - waitpid & getpid\n");
    #endif

    #if OPT_FILE_IO
    kprintf("[lab 5] - file descriptor support: open, close, remove syscalls\n         with stdin, stdout and stderr support!");
    #endif

    kprintf("\n\n");
}