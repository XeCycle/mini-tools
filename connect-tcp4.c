#include "minisys.h"
#include "sockdefs.h"

#include <asm/errno.h>

/*

A simple nc -z 1.2.3.4 1234.

Only supports IPv4 in literal, no resolving support; exits errno, or
if command line arguments are invalid, EINVAL.

*/

struct parse_u32_result {
  uint32_t r;
  char const* tail;
};
static struct parse_u32_result parse_u32(char const* str)
{
  struct parse_u32_result res = { 0 };
  for (; '0' <= (*str) && (*str) <= '9'; ++str) {
    res.r *= 10;
    res.r += *str - '0';
  }
  res.tail = str;
  return res;
}

#define verify(cond)                            \
  do {                                          \
    if (!(cond)) _exit(EINVAL);                 \
  } while (0)

__attribute__((noreturn, used))
void main_noret(int argc, char** argv, char** envp)
{
  verify(argc == 3);

  uint32_t host;
  {
    uint32_t b1, b2, b3, b4;
    struct parse_u32_result r;
    r = parse_u32(argv[1]);
    verify(r.r < 256 && (*r.tail) == '.');
    b1 = r.r;
    r = parse_u32(r.tail+1);
    verify(r.r < 256 && (*r.tail) == '.');
    b2 = r.r;
    r = parse_u32(r.tail+1);
    verify(r.r < 256 && (*r.tail) == '.');
    b3 = r.r;
    r = parse_u32(r.tail+1);
    verify(r.r < 256 && (*r.tail) == 0);
    b4 = r.r;
    host = b1 | (b2<<8) | (b3<<16) | (b4<<24);
  }

  uint16_t port;
  {
    struct parse_u32_result r = parse_u32(argv[2]);
    verify(r.r < 65536 && (*r.tail) == 0);
    port = __builtin_bswap16((uint16_t)r.r);
  }

  struct sockaddr_in sa = {
    .sin_family = AF_INET,
    .sin_addr = {
      .s_addr = host,
    },
    .sin_port = port,
  };
  int sock = socket(AF_INET, SOCK_STREAM, 0);
  if (sock < 0)
    _exit(-sock);
  int ret = connect(sock, (struct sockaddr*)&sa, sizeof sa);
  _exit(-ret);
}
