/* Section definitions required by C. */

__load_start = .;
INCLUDE ro_sections.ld
INCLUDE rw_sections.ld
__load_end = .;

INCLUDE noalloc_sections.ld
__heap_start = .;
