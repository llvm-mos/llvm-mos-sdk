#include "rp6502.h"
#include <errno.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

int remove(const char *name) {
  size_t namelen;
  namelen = strlen(name);
  if (namelen > 255) {
    errno = EINVAL;
    return -1;
  }
  while (namelen)
    RIA.xstack = name[--namelen];
  RIA.op = RIA_OP_REMOVE;
  return ria_spin();
}

/* The directory bit of fattrib in f_stat_t. */
#define FATTRIB_DIR 0x10

/* REMOVE takes a file or an empty directory, so the type is tested first.
 * unlink() takes a file and refuses a directory, and rmdir() takes a
 * directory and refuses a file, both with EACCES. */
static int remove_type(const char *name, bool want_dir) {
  unsigned char i = offsetof(f_stat_t, fattrib) + 1, fattrib;
  size_t namelen = strlen(name);
  if (namelen > 255) {
    errno = EINVAL;
    return -1;
  }
  while (namelen)
    RIA.xstack = name[--namelen];
  RIA.op = RIA_OP_STAT;
  if (ria_spin() < 0)
    return -1;
  while (i--)
    fattrib = RIA.xstack;
  ria_drop();
  bool is_dir = (fattrib & FATTRIB_DIR) != 0;
  if (is_dir != want_dir) {
    errno = EACCES;
    return -1;
  }
  return remove(name);
}

int unlink(const char *name) { return remove_type(name, false); }

int rmdir(const char *name) { return remove_type(name, true); }
