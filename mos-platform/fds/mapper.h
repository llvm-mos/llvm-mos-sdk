#ifndef _MAPPER_H_
#define _MAPPER_H_

#include <stdbool.h>

#ifdef __cplusplus
extern "C" {
#endif

// Enables/disables disk I/O registers.
void fds_set_disk_io(bool value);

// Enables/disables sound I/O registers.
void fds_set_sound_io(bool value);

// Set the next byte to write to disk.
void fds_write_disk_data(char value);

#define TRANSFER_WRITE 0
#define TRANSFER_READ 1

// Set the current disk transfer mode. Your options are
// TRANSFER_WRITE and TRANSFER_READ.
void fds_set_transfer_mode(bool mode);

#define MIRROR_VERTICAL 0
#define MIRROR_HORIZONTAL 1

// Set the current mirroring mode. Your options are
// MIRROR_HORIZONTAL and MIRROR_VERTICAL.
void set_mirroring(char mirroring);

// Set all 8 bits of the $4025 FDS Control register.
void fds_set_ctrl(char value);

// Write 7-bit data to the rear expansion port ($4026).
void fds_write_ext_data(char value);

struct __fds_read {
    unsigned char disk_status;
    unsigned char data;
    unsigned char drive_status;
    unsigned char ext_data;
};

#define FDS_READ (*(volatile struct __fds_read*)0x4030)

struct __fds_apu {
  unsigned char wavetable[64];
  struct {
    unsigned char vol_env;
    unsigned char unused;
    unsigned char freq_lo;
    unsigned char freq_hi;
  } wave;
  struct {
    unsigned char env;
    unsigned char counter;
    unsigned char freq_lo;
    unsigned char freq_hi;
    unsigned char mod_table;
  } mod;
  unsigned char write_vol;
  unsigned char env_speed;
  unsigned char unused[5];
  unsigned char vol_gain;
  unsigned char wave_acm;
  unsigned char mod_gain;
  unsigned char mod_acm;
  unsigned char mod_ctr_gain;
  unsigned char mod_ctr_inc;
  unsigned char wave_value;
  unsigned char mod_ctr_val;
};

#define FDS_APU (*(volatile struct __fds_apu*)0x4040)

#ifdef __cplusplus
}
#endif

#endif
