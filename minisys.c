#include "minisys.h"
#include <asm/unistd.h>

static long syscall0(long sysnr)
{
  long ret;
  asm volatile (
    "syscall"
    : "=a" (ret)
    : "0" (sysnr)
    : "rcx", "r11", "memory");
  return ret;
}

static long syscall1(long sysnr, long arg1)
{
  long ret;
  asm volatile (
    "syscall"
    : "=a" (ret)
    : "0" (sysnr), "D" (arg1)
    : "rcx", "r11", "memory");
  return ret;
}

static long syscall2(long sysnr, long arg1, long arg2)
{
  long ret;
  asm volatile (
    "syscall"
    : "=a" (ret)
    : "0" (sysnr), "D" (arg1), "S" (arg2)
    : "rcx", "r11", "memory");
  return ret;
}

static long syscall3(long sysnr, long arg1, long arg2, long arg3)
{
  long ret;
  asm volatile (
    "syscall"
    : "=a" (ret)
    : "0" (sysnr), "D" (arg1), "S" (arg2), "d" (arg3)
    : "rcx", "r11", "memory");
  return ret;
}

static long syscall4(long sysnr, long arg1, long arg2, long arg3, long arg4)
{
  long ret;
  register long r10 asm("r10") = arg4;
  asm volatile (
    "syscall"
    : "=a" (ret)
    : "0" (sysnr), "D" (arg1), "S" (arg2), "d" (arg3), "r" (r10)
    : "rcx", "r11", "memory");
  return ret;
}

static long syscall5(long sysnr, long arg1, long arg2, long arg3, long arg4, long arg5)
{
  long ret;
  register long r10 asm("r10") = arg4;
  register long r8 asm("r8") = arg5;
  asm volatile (
    "syscall"
    : "=a" (ret)
    : "0" (sysnr), "D" (arg1), "S" (arg2), "d" (arg3), "r" (r10), "r" (r8)
    : "rcx", "r11", "memory");
  return ret;
}

static long syscall6(long sysnr, long arg1, long arg2, long arg3, long arg4, long arg5, long arg6)
{
  long ret;
  register long r10 asm("r10") = arg4;
  register long r8 asm("r8") = arg5;
  register long r9 asm("r9") = arg6;
  asm volatile (
    "syscall"
    : "=a" (ret)
    : "0" (sysnr), "D" (arg1), "S" (arg2), "d" (arg3), "r" (r10), "r" (r8), "r" (r9)
    : "rcx", "r11", "memory");
  return ret;
}

long pause(void)
{
  return syscall0(__NR_pause);
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
  return syscall4(__NR_rt_sigaction, signum, (long)act, (long)oldact, sizeof(sigset_t));
}

__attribute__((noreturn))
void _exit(int exit_status)
{
  syscall1(__NR_exit_group, exit_status);
}
