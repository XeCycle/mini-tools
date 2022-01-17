#include "minisys.h"
#include <asm/errno.h>
#include <linux/fcntl.h>
#include <linux/fs.h>

__attribute__((noreturn, used))
void main_noret(int argc, char** argv, char** envp)
{
  if (argc != 3)
    _exit(EINVAL);
  long ret = renameat2(AT_FDCWD, argv[1], AT_FDCWD, argv[2], RENAME_EXCHANGE);
  _exit(-ret);
}
