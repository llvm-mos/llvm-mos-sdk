#ifndef _CHRIN_H_
#define _CHRIN_H_

#ifdef __cplusplus
extern "C" {
#endif

// Get a character from the serial console.
int __chrin(void);

// Get a character from the serial console, returns -1 if none available.
int __chrin_no_wait(void);

#ifdef __cplusplus
}
#endif

#endif // not _CHRIN_H_
