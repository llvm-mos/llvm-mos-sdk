#ifndef _ERRNO_H_
#define _ERRNO_H_

#ifdef __cplusplus
extern "C" {
#endif

extern int _errno;
#define errno (_errno)

#define ERANGE 1
#define EDOM 2
#define EILSEQ 3
#define EINVAL 4
#define ENOMEM 5
#define ELAST 5

#ifdef __cplusplus
}
#endif

#endif // not _ERRNO_H_
