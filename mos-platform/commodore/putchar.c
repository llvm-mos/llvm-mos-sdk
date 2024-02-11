#include <stdio.h>

#define __CBM__
#include <cbm.h>

void __putchar(char c) { cbm_k_chrout(c); }
