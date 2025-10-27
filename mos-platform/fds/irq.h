#include <stdbool.h>

#ifndef _BIOS_H_
#define _BIOS_H_

#ifdef __cplusplus
extern "C" {
#endif

// Set the reload value for the timer IRQ.
void fds_set_timer_irq_reload(unsigned value);

// Set the control bits for the timer IRQ.
void fds_set_timer_irq_ctrl(bool enabled, bool repeat);

#define NMI_ACTION_VINTWAIT 0b00000000
#define NMI_ACTION_USER_1 0b01000000
#define NMI_ACTION_USER_2 0b10000000
#define NMI_ACTION_USER_3 0b11000000

// Set action on NMI. Should be one of NMI_ACTION_VINTWAIT,
// NMI_ACTION_USER_1, NMI_ACTION_USER_2, or NMI_ACTION_USER_3.
void fds_set_nmi_action(char action);

#define IRQ_ACTION_DISK_SKIP(bytes) bytes & 0b00111111
#define IRQ_ACTION_DISK_TRANSFER 0b01000000
#define IRQ_ACTION_ACK_DELAY 0b10000000
#define IRQ_ACTION_USER 0b11000000

// Set action on IRQ. Should be one of IRQ_ACTION_DISK_SKIP,
// IRQ_ACTION_DISK_TRANSFER, IRQ_ACTION_ACK_DELAY, or IRQ_ACTION_USER.
void fds_set_irq_action(char action);

#define RESET_TYPE_HARD 0xAC
#define RESET_TYPE_SOFT 0x53

// Set reset type. Should be one of RESET_TYPE_HARD
// or RESET_TYPE_SOFT.
void fds_set_reset_type(char type);

#ifdef __cplusplus
}
#endif

#endif
