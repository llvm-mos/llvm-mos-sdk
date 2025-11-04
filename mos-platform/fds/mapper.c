#include "mapper.h"
#include <peekpoke.h>
#include <stdbool.h>

#define FDS_IO 0x4023

#define FDS_WRITE 0x4024

#define FDS_CTRL 0x4025
#define FDS_CTRL_MIRROR 0xFA

#define FDS_EXT 0x4026
#define FDS_EXT_MIRROR 0xF9

#define IO_DISK 0x01
#define IO_SOUND 0x02

#define CTRL_RESET_TRANSFER 0x01
#define CTRL_TRANSFER_MODE 0x04
#define CTRL_MIRRORING 0x08

__attribute__((section(".zp.bss"))) volatile char _IO_ENABLED;

void fds_set_disk_io(bool value) {
  char old = _IO_ENABLED;
  _IO_ENABLED = (old & (~IO_DISK)) | (value ? IO_DISK : 0);
  POKE(FDS_IO, _IO_ENABLED);
}

void fds_set_sound_io(bool value) {
  char old = _IO_ENABLED;
  _IO_ENABLED = (old & (~IO_SOUND)) | (value ? IO_SOUND : 0);
  POKE(FDS_IO, _IO_ENABLED);
}

void fds_write_disk_data(char value) {
  POKE(FDS_WRITE, value);
}

void fds_set_transfer_mode(bool mode) {
  char old = PEEK(FDS_CTRL_MIRROR);
  char new = (old & (~CTRL_TRANSFER_MODE)) | (mode ? CTRL_TRANSFER_MODE : 0);
  POKE(FDS_CTRL_MIRROR, new);
  POKE(FDS_CTRL, new);
}

void set_mirroring(char mirroring) {
  char old = PEEK(FDS_CTRL_MIRROR);
  char new = (old & (~CTRL_MIRRORING)) | (mirroring ? CTRL_MIRRORING : 0);
  POKE(FDS_CTRL_MIRROR, new);
  POKE(FDS_CTRL, new);
}

void fds_set_ctrl(char value) {
  POKE(FDS_CTRL_MIRROR, value);
  POKE(FDS_CTRL, value);
}

void fds_write_ext_data(char value) {
  POKE(FDS_EXT_MIRROR, value);
  POKE(FDS_EXT, value);
}
