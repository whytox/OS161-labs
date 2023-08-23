#include <cdefs.h>
#include <types.h>
#include <syscall.h>
#include <current.h>
#include <thread.h>
#include <proc.h>

void sys__exit(int exit_code) {
    #if OPT_WAITPID

        lock_acquire(curproc->p_cv_lock);
        spinlock_acquire(&curproc->p_lock);
        curthread->exit_code = exit_code;
        cv_broadcast(curproc->p_cv, curproc->p_cv_lock);
        spinlock_release(&curproc->p_lock);
        lock_release(curproc->p_cv_lock);

    #endif
    thread_exit();
}