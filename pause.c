#include "minisys.h"

static void on_sigterm(int sig)
{
  _exit(0);
}

__attribute__((noreturn, used))
void main_noret(int argc, char** argv, char** envp)
{
  struct sigaction sa = {
    .sa_handler = &on_sigterm,
    0,
  };
  long ret = sigaction(SIGTERM, &sa, (void*)0);
  if (ret < 0) {
    _exit(-ret);
  }
  while (1) {
    pause();
  }
}
