#ifndef _ERRNO_H_
#define _ERRNO_H_

#ifdef __cplusplus
extern "C" {
#endif

extern int _errno;
#define errno _errno

#define EACCES 13
#define EBADF 9
#define EBUSY 16
#define EDOM 33
#define EEXIST 17
#define EILSEQ 84
#define EINVAL 22
#define EIO 5
#define ENODEV 19
#define ENOENT 2
#define ENOMEM 12
#define ENOSPC 28
#define ENOSYS 38
#define EMFILE 24
#define ERANGE 34
#define ESPIPE 29

#define EUNKNOWN 85

#ifdef __cplusplus
}
#endif

#endif // not _ERRNO_H_
