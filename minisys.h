#pragma once

#include <stddef.h>
#include <asm/signal.h>

long pause(void);

long sigaction(int signum,
               struct sigaction* restrict act,
               struct sigaction* restrict oldact);

__attribute__((noreturn))
void _exit(int exit_status);

long renameat2(int olddirfd, char const* oldpath,
               int newdirfd, char const* newpath,
               unsigned flags);

int socket(int domain, int type, int protocol);

struct sockaddr;
int connect(int sockfd, struct sockaddr const* addr, unsigned addrlen);
