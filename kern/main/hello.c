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
#include "opt-lock_1.h"
#include "opt-lock_2.h"
#include "opt-cond_var.h"

// 'hello' function for lab 1
// the prototype is in /kern/include/hello.h
void hello(void) {
    kprintf("\n\nHello World!\n\n");
    #if OPT_LOCK_1
    kprintf("LAB3 - lock implementation version 1\n\n");
    #elif OPT_LOCK_2
    kprintf("LAB3 - lock implementation version 2\n\n");
    #endif

    #if OPT_COND_VAR
    kprintf("Condition variable support\n\n");
    #endif
}