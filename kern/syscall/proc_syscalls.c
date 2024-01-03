#include <cdefs.h>
#include <types.h>
#include <syscall.h>
#include <current.h>
#include <thread.h>
#include <proc.h>

#if OPT_WAITPID
void sys__exit(int exit_code)
{

    lock_acquire(curproc->p_cv_lock);
    spinlock_acquire(&curproc->p_lock);
    curthread->exit_code = exit_code;
    cv_broadcast(curproc->p_cv, curproc->p_cv_lock);
    spinlock_release(&curproc->p_lock);
    lock_release(curproc->p_cv_lock);
    thread_exit();
}

pid_t sys_getpid(void)
{
    spinlock_acquire(&curproc->p_lock);
    pid_t pid = curproc->pid;
    spinlock_release(&curproc->p_lock);
    return pid;
}

int sys_waitpid(pid_t pid)
{
    struct proc *proc = get_proc_by_pid(pid);
    return proc_wait(proc);
}
#endif