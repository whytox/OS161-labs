
#include <types.h>
#include <syscall.h>
#include <lib.h>  // definition of putch, getch
#include <kern/unistd.h>
#include <uio.h>
#include <proc.h>
#include <vnode.h>
#include <vfs.h>
#include <kern/fcntl.h>
#include <current.h>

ssize_t sys_write(int fd, void* buffer, ssize_t len) {

#if OPT_FILE_IO
    // if there is support for vnode, use proc's vnode
    // to write by using VOP_WRITE
    // this should be also more general, as the code is the same
    // both for STDOUT and other file descriptors
    size_t result;
	struct iovec iov;
	struct uio ku;
    struct vnode* vnode;
	char tmp[NAME_MAX];

    vnode = proc_find_fd(curproc, fd);
    /* we cannot init stdin e out directly in proc_create because it's
    used by proc_bootstrap, which is called before vfs_bootstrap, which is in turn
    required to call vfs_ope, so we add the stdout at request. */
    if (vnode == NULL && (fd == STDERR_FILENO || fd == STDOUT_FILENO)) {
        // add std fd
        strcpy(tmp, "con:");
        vfs_open(tmp, O_WRONLY, 0644, &vnode);
        spinlock_acquire(&curproc->p_lock);
        curproc->p_vnodes[fd] = vnode;
        spinlock_release(&curproc->p_lock);
    }

	uio_kinit(&iov, &ku, buffer, len, 0, UIO_WRITE);
    result = VOP_WRITE(vnode, &ku);
    return result;
#else
    if (fd != 1) return 0; // only on standard output, for now...
    char* c_buffer = ((char*)buffer);
    for (ssize_t i=0; i<len; i++) {
        putch(c_buffer[i]);
    }
    return len;
#endif
}

ssize_t sys_read(int fd, void* buffer, ssize_t len) {

#if OPT_FILE_IO
    size_t result;
	struct iovec iov;
	struct uio ku;
    struct vnode* vnode;
	char tmp[NAME_MAX];

    vnode = proc_find_fd(curproc, fd);
    /* we cannot init stdin e out directly in proc_create because it's
    used by proc_bootstrap, which is called before vfs_bootstrap, which is in turn
    required to call vfs_ope, so we add the stdout at request. */
    if (vnode == NULL && fd == STDIN_FILENO) {
        // add std fd
        strcpy(tmp, "con:");
        vfs_open(tmp, O_RDONLY, 0644, &vnode);
        spinlock_acquire(&curproc->p_lock);
        curproc->p_vnodes[fd] = vnode;
        spinlock_release(&curproc->p_lock);
    }

	uio_kinit(&iov, &ku, buffer, len, 0, UIO_READ);
    result = VOP_READ(vnode, &ku);
    return result;
#else
    if (fd != 0) return 0; // only from standard input, for now
    char* c_buffer = (char*)buffer;

    for (ssize_t i=0; i<len; i++) {
        c_buffer[i] = getch();
    }
    return 0;
#endif
}

#if OPT_FILE_IO
#include <vnode.h>
#include <vfs.h>
#include <current.h>
#include <proc.h>

int sys_open(const char* pathname, int openflags, int mode) {
    
    struct vnode *vnode;
    char pathcopy[NAME_MAX];
    strcpy(pathcopy, pathname);
    vfs_open(pathcopy, openflags, mode, &vnode);
    int fd = proc_add_vnode(curthread->t_proc, vnode);
    return fd;
}

int sys_close(int fd) {
    int result = proc_del_vnode(curthread->t_proc, fd);
    return result;
}

int sys_remove(char *path) {
    
    int result = vfs_remove(path);
    return result;
}
#endif