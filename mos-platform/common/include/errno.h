#ifndef _ERRNO_H_
#define _ERRNO_H_

#ifdef __cplusplus
extern "C" {
#endif

extern int _errno;
#define errno _errno

#define ERANGE 34
#define EDOM 33
#define EILSEQ 84
#define EINVAL 22
#define ENOMEM 12
#define ESPIPE 29

#ifdef __cplusplus
}
#endif

#endif // not _ERRNO_H_
