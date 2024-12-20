#include "types.h"
#include "riscv.h"
#include "defs.h"
#include "param.h"
#include "memlayout.h"
#include "spinlock.h"
#include "proc.h"

uint64
sys_describe(void)
{
  cprintf("System Call Descriptions:\n\n");

    cprintf("1. fork():\n");
    cprintf("   Creates a new process by duplicating the calling process.\n");
    cprintf("   Returns 0 to the child process and the PID of the child to the parent.\n\n");

    cprintf("2. exec(path, argv):\n");
    cprintf("   Replaces the current process with a new process from the program at 'path'.\n");
    cprintf("   'argv' is an array of arguments. Returns -1 on failure, does not return on success.\n\n");

    cprintf("3. wait():\n");
    cprintf("   Suspends execution until a child process terminates, then returns the child PID.\n");
    cprintf("   Returns -1 if there are no children.\n\n");

    cprintf("4. kill(pid):\n");
    cprintf("   Sends a signal to terminate the process with the specified PID.\n");
    cprintf("   Returns 0 on success, or -1 if the PID is invalid.\n\n");

    cprintf("5. exit(status):\n");
    cprintf("   Terminates the calling process with the specified status code.\n");
    cprintf("   Does not return.\n\n");

    cprintf("6. getpid():\n");
    cprintf("   Returns the process ID (PID) of the calling process.\n\n");

    cprintf("7. sleep(seconds):\n");
    cprintf("   Suspends execution of the calling process for a specified time (in seconds).\n");
    cprintf("   Returns 0 on success.\n\n");

    cprintf("8. uptime():\n");
    cprintf("   Returns the number of timer ticks since the system started.\n\n");

    cprintf("9. sbrk(n):\n");
    cprintf("   Increases the process’s data space by 'n' bytes. Returns the start address of the new area.\n\n");

    cprintf("10. open(filename, flags):\n");
    cprintf("    Opens the file specified by 'filename' with the given 'flags'.\n");
    cprintf("    Returns a file descriptor, or -1 if the file could not be opened.\n\n");

    cprintf("11. read(fd, buffer, nbytes):\n");
    cprintf("    Reads 'nbytes' from file descriptor 'fd' into 'buffer'.\n");
    cprintf("    Returns the number of bytes read, or -1 on error.\n\n");

    cprintf("12. write(fd, buffer, nbytes):\n");
    cprintf("    Writes 'nbytes' from 'buffer' to the file descriptor 'fd'.\n");
    cprintf("    Returns the number of bytes written, or -1 on error.\n\n");

    cprintf("13. close(fd):\n");
    cprintf("    Closes the file descriptor 'fd'.\n");
    cprintf("    Returns 0 on success, or -1 on error.\n\n");

    cprintf("14. fstat(fd, stat):\n");
    cprintf("    Retrieves file status information for the file descriptor 'fd' into 'stat'.\n");
    cprintf("    Returns 0 on success, or -1 on error.\n\n");

    cprintf("15. link(oldpath, newpath):\n");
    cprintf("    Creates a new link (newpath) to an existing file (oldpath).\n");
    cprintf("    Returns 0 on success, or -1 on error.\n\n");

    cprintf("16. unlink(path):\n");
    cprintf("    Removes the specified file (path) if it has no other links.\n");
    cprintf("    Returns 0 on success, or -1 on error.\n\n");

    cprintf("17. mkdir(path):\n");
    cprintf("    Creates a new directory at the specified path.\n");
    cprintf("    Returns 0 on success, or -1 on error.\n\n");

    cprintf("18. chdir(path):\n");
    cprintf("    Changes the current working directory to the specified path.\n");
    cprintf("    Returns 0 on success, or -1 on error.\n\n");

    cprintf("19. dup(fd):\n");
    cprintf("    Duplicates the file descriptor 'fd'.\n");
    cprintf("    Returns a new file descriptor pointing to the same file, or -1 on error.\n\n");

    cprintf("20. pipe(pipefd):\n");
    cprintf("    Creates a pipe, a unidirectional data channel, and places the two ends of the pipe\n");
    cprintf("    in the array 'pipefd'. Returns 0 on success, or -1 on error.\n\n");

    cprintf("21. mknod(path, major, minor):\n");
    cprintf("    Creates a device file with the specified path, major number, and minor number.\n");
    cprintf("    Returns 0 on success, or -1 on error.\n\n");

    cprintf("22. sendmsg(pid, message):\n");
    cprintf("    Sends a message to the process with the specified PID.\n");
    cprintf("    'message' is the content to be sent. Returns 0 on success, or -1 if the PID is invalid.\n\n");

    cprintf("23. recvmsg(buffer, maxlen):\n");
    cprintf("    Receives a message sent to the calling process and stores it in 'buffer'.\n");
    cprintf("    'maxlen' specifies the maximum number of characters to read.\n");
    cprintf("    Returns the number of bytes received, or -1 if no messages are available.\n\n");

    cprintf("End of System Call Descriptions.\n");

    return 0;
}
uint64
sys_exit(void)
{
  int n;
  argint(0, &n);
  exit(n);
  return 0;  // not reached
}

uint64
sys_getpid(void)
{
  return myproc()->pid;
}

uint64
sys_fork(void)
{
  return fork();
}

uint64
sys_wait(void)
{
  uint64 p;
  argaddr(0, &p);
  return wait(p);
}

uint64
sys_sbrk(void)
{
  uint64 addr;
  int n;

  argint(0, &n);
  addr = myproc()->sz;
  if(growproc(n) < 0)
    return -1;
  return addr;
}

uint64
sys_sleep(void)
{
  int n;
  uint ticks0;

  argint(0, &n);
  if(n < 0)
    n = 0;
  acquire(&tickslock);
  ticks0 = ticks;
  while(ticks - ticks0 < n){
    if(killed(myproc())){
      release(&tickslock);
      return -1;
    }
    sleep(&ticks, &tickslock);
  }
  release(&tickslock);
  return 0;
}

uint64
sys_kill(void)
{
  int pid;

  argint(0, &pid);
  return kill(pid);
}

// return how many clock tick interrupts have occurred
// since start.
uint64
sys_uptime(void)
{
  uint xticks;

  acquire(&tickslock);
  xticks = ticks;
  release(&tickslock);
  return xticks;
}
