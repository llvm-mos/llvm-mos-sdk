#ifndef _EATER_H_
#define _EATER_H_

#ifdef __cplusplus
extern "C" {
#endif

// Get the value of the system millisecond tick counter.
unsigned long millis(void);

// Wait for a specific number of milliseconds.
void delay(unsigned ms);

#ifdef __cplusplus
}
#endif

#endif // not _EATER_H_
