#ifndef _SETJMP_H_
#define _SETJMP_H_

struct __jmp_buf_tag {
  void *ret_addr;
  char s;
  void *sp;
  char csrs[14];
};

typedef struct __jmp_buf_tag jmp_buf[1];

// Using preserve-none means that setjmp is only responsible for saving reserved
// registers: FP, SP, and S.
__attribute__((preserve_none, leaf)) int setjmp(jmp_buf src);
void longjmp(jmp_buf dst, int arg);

#endif // not _SETJMP_H_
