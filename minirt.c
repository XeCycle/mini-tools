/* taken from https://en.wikipedia.org/wiki/Crt0 */
__attribute__((naked, noreturn))
void _start(void)
{
  asm volatile (
    "xor %ebp, %ebp\n"
    "mov (%rsp), %edi\n"
    "lea 8(%rsp), %rsi\n"
    "lea 16(%rsp,%rdi,8), %rdx\n"
    "xor %eax, %eax\n"
    "call main_noret"
    );
}
