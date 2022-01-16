#pragma once

#include <stddef.h>
#include <asm/signal.h>

long pause(void);

long sigaction(int signum,
               struct sigaction* restrict act,
               struct sigaction* restrict oldact);

__attribute__((noreturn))
void _exit(int exit_status);
