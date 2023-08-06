#ifndef _EATER_H_
#define _EATER_H_

#ifdef __cplusplus
extern "C" {
#endif

// Raw version of putchar() that doesn't do LF to CRLF conversion.
void putchar_raw(char c);

// Version of getchar() that doesn't wait, but returns -1 if no character.
int getchar_no_wait(void);

// Get the value of the system millisecond tick counter.
unsigned long millis(void);

// Wait for a specific number of milliseconds.
void delay(unsigned ms);

#ifdef __cplusplus
}
#endif

#endif // not _EATER_H_
