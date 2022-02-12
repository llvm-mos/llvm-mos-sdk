#include <sim_io.h>

volatile sim_reg_t *const sim_reg_iface = ((volatile sim_reg_t *)0xFFF0);

char __getchar() { return sim_reg_iface->getchar; }
