#ifndef _SIGNAL_H_
#define _SIGNAL_H_

#ifdef __cplusplus
extern "C" {
#endif

typedef char sig_atomic_t;

// Originally from the Public Domain C Library (PDCLib).

/* These are the values used by Linux. */

/* Abnormal termination / abort() */
#define SIGABRT 6
/* Arithmetic exception / division by zero / overflow */
#define SIGFPE 8
/* Illegal instruction */
#define SIGILL 4
/* Interactive attention signal */
#define SIGINT 2
/* Invalid memory access */
#define SIGSEGV 11
/* Termination request */
#define SIGTERM 15

/* The following should be defined to pointer values that could NEVER point to
   a valid signal handler function. (They are used as special arguments to
   signal().) Again, these are the values used by Linux.
*/
#define SIG_DFL ((void (*)(int))0)
#define SIG_ERR ((void (*)(int))-1)
#define SIG_IGN ((void (*)(int))1)

void (*signal(int sig, void (*func)(int)))(int);
int raise(int sig);

#ifdef __cplusplus
}
#endif

#endif // not _SIGNAL_H_
