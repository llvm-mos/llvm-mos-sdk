/**
 * hello-sortron
 *
 * To the extent possible under law, the person who associated CC0 with
 * hello-sortron has waived all copyright and related or neighboring rights
 * to hello-sortron.
 *
 * You should have received a copy of the CC0 legalcode along with this
 * work.  If not, see <http://creativecommons.org/publicdomain/zero/1.0/>.
 */

#include <stdio.h>
#include <rpc8e.h>

// The Sortron is an inventory access device.

#define SORTRON_ID 4

int main(void) {
  static uint16_t i, slot_count;
  static uint8_t item_count;
  static uint32_t item_hash;
  static uint16_t item_damage;
  static uint16_t item_max_damage;

  rpc8e_display_clear();
  printf("Sortron Demo\n\n");

  rpc8e_redbus_set_map(SORTRON_ID);

  if (!rpc8e_sortron_command(SORTRON_COMMAND_READ_SLOT_COUNT)) {
    printf("Error reading inventory! Shutting down.\n");
    return 1;
  }
  slot_count = *IO_SORTRON_ITEM_SLOT;

  for (i = 0; i < slot_count; i++) {
    rpc8e_redbus_set_map(SORTRON_ID);

    *IO_SORTRON_ITEM_SLOT = i;
    if (!rpc8e_sortron_command(SORTRON_COMMAND_READ_SLOT)) {
      rpc8e_redbus_set_map(boot_display_id);
      printf("- Error reading slot!\n");
      continue;
    }

    item_count = *IO_SORTRON_ITEM_COUNT;
    item_hash = *IO_SORTRON_ITEM_HASH;
    item_damage = *IO_SORTRON_ITEM_DAMAGE;
    item_max_damage = *IO_SORTRON_ITEM_MAX_DAMAGE;

    rpc8e_redbus_set_map(boot_display_id);
    if (item_count == 0) {
      printf("- <no item>\n");
    } else {
      printf("- %d x %08lX", item_count, item_hash);
      if (item_max_damage) {
        printf(" (%u/%u)", item_damage, item_max_damage);
      }
      putchar('\n');
    }
  }

  printf("\nRead %u slots. Shutting down.\n", slot_count);
  return 0;
}
