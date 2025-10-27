#include <peekpoke.h>
#include <stdbool.h>

void set_timer_irq_reload(unsigned value) {
  POKE(0x4020, value & 0xFF);
  POKE(0x4021, value >> 8);
}

void set_timer_irq_ctrl(bool enabled, bool repeat) {
  POKE(0x4022, (enabled << 1) & repeat);
}

void set_nmi_action(char action) {
  POKE(0x100, action);
}

void set_irq_action(char action) {
  POKE(0x101, action);
}

void set_reset_type(char type) {
  POKE(0x103, type);
}
