#include "minisys.h"
#include <asm/unistd.h>

long pause(void)
{
  long ret;
  asm volatile (
    "syscall"
    : "=a" (ret)
    : "0" (__NR_pause)
    : "rcx", "r11", "memory"
    );
  return ret;
}

__attribute__((naked, noreturn))
static void signal_restorer(void)
{
  asm volatile (
    "syscall"
    :
    : "a" (__NR_rt_sigreturn)
    : "rcx", "r11", "memory"
    );
}

long sigaction(int signum,
               struct sigaction* restrict act,
               struct sigaction* restrict oldact)
{
  act->sa_flags |= SA_RESTORER;
  act->sa_restorer = &signal_restorer;
  long ret;
  asm volatile (
    "mov %0, %%r10"
    :
    : "i" (sizeof(sigset_t))
    : "r10");
  asm volatile (
    "syscall"
    : "=a" (ret)
    : "0" (__NR_rt_sigaction), "D" (signum), "S" (act), "d" (oldact)
    : "rcx", "r11", "memory"
    );
  return ret;
}

__attribute__((noreturn))
void _exit(int exit_status)
{
  long ret;
  asm volatile (
    "syscall"
    : "=a" (ret)
    : "0" (__NR_exit_group), "D" (exit_status)
    : "rcx", "r11", "memory"
    );
  __builtin_unreachable();
}
