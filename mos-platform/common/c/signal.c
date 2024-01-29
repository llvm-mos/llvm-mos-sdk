#include <signal.h>

#include <errno.h>
#include <stdlib.h>

// Originally from the Public Domain C Library (PDCLib).

static void (*sigabrt)(int) = SIG_DFL;
static void (*sigfpe)(int) = SIG_DFL;
static void (*sigill)(int) = SIG_DFL;
static void (*sigint)(int) = SIG_DFL;
static void (*sigsegv)(int) = SIG_DFL;
static void (*sigterm)(int) = SIG_DFL;

void (*signal(int sig, void (*func)(int)))(int) {
  void (*oldhandler)(int);

  if (sig <= 0 || func == SIG_ERR)
    return SIG_ERR;

  switch (sig) {
  case SIGABRT:
    oldhandler = sigabrt;
    sigabrt = func;
    break;

  case SIGFPE:
    oldhandler = sigfpe;
    sigfpe = func;
    break;

  case SIGILL:
    oldhandler = sigill;
    sigill = func;
    break;

  case SIGINT:
    oldhandler = sigint;
    sigint = func;
    break;

  case SIGSEGV:
    oldhandler = sigsegv;
    sigsegv = func;
    break;

  case SIGTERM:
    oldhandler = sigterm;
    sigterm = func;
    break;

  default:
    /* The standard calls for an unspecified "positive value".
       Copying Linux' behaviour of setting EINVAL. */
    errno = EINVAL;
    return SIG_ERR;
  }

  return oldhandler;
}

// Default signal handlers, sans the final _Exit.
void __sigabrt(void);
void __sigfpe(void);
void __sigill(void);
void __sigint(void);
void __sigsegv(void);
void __sigterm(void);

int raise(int sig) {
  void (*sighandler)(int);
  switch (sig) {
  case SIGABRT:
    sighandler = sigabrt;
    break;
  case SIGFPE:
    sighandler = sigfpe;
    break;
  case SIGILL:
    sighandler = sigill;
    break;
  case SIGINT:
    sighandler = sigint;
    break;
  case SIGSEGV:
    sighandler = sigsegv;
    break;
  case SIGTERM:
    sighandler = sigterm;
    break;
  default:
    return 1;
  }

  if (sighandler == SIG_DFL) {
    switch (sig) {
    case SIGABRT:
      __sigabrt();
      break;
    case SIGFPE:
      __sigfpe();
      break;
    case SIGILL:
      __sigill();
      break;
    case SIGINT:
      __sigint();
      break;
    case SIGSEGV:
      __sigsegv();
      break;
    case SIGTERM:
      __sigterm();
      break;
    default:
      return 1;
    }
    exit(128 + sig);
  } else if (sighandler != SIG_IGN) {
    sighandler = signal(sig, SIG_DFL);
    sighandler(sig);
  }

  return 0;
}
