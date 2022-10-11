/* C calling-convention converts around the CP/M and BIOS entrypoints. This is
 * mostly concerned about moving pointers to and from XA, which is where CP/M
 * expects to find them. These will all get inlined and compile into no code.
 *
 * © 2022 David Given
 * This file is part of the llvm-mos-sdk project and is redistributable under
 * the terms of the Apache 2.0 license. See the LICENSE file in the project
 * root for the full text.
 */

#include "cpm.h"

void cpm_printstring(const char* s) /* $-terminated */
{
    cpm_printstring_i((uint16_t)s);
}

uint8_t cpm_open_file(FCB* fcb)
{
    return cpm_open_file_i((uint16_t)fcb);
}

uint8_t cpm_close_file(FCB* fcb)
{
    return cpm_close_file_i((uint16_t)fcb);
}

uint8_t cpm_findfirst(FCB* fcb)
{
    return cpm_findfirst_i((uint16_t)fcb);
}

uint8_t cpm_findnext(FCB* fcb)
{
    return cpm_findnext_i((uint16_t)fcb);
}

uint8_t cpm_delete_file(FCB* fcb)
{
    return cpm_delete_file_i((uint16_t)fcb);
}

uint8_t cpm_read_sequential(FCB* fcb)
{
    return cpm_read_sequential_i((uint16_t)fcb);
}

uint8_t cpm_write_sequential(FCB* fcb)
{
    return cpm_write_sequential_i((uint16_t)fcb);
}

uint8_t cpm_make_file(FCB* fcb)
{
    return cpm_make_file_i((uint16_t)fcb);
}

uint8_t cpm_rename_file(RCB* rcb)
{
    return cpm_rename_file_i((uint16_t)rcb);
}

void cpm_set_dma(void* ptr)
{
    cpm_set_dma_i((uint16_t)ptr);
}

uint8_t* cpm_get_allocation_vector(void)
{
    return (uint8_t*)cpm_get_allocation_vector_i();
}

uint8_t cpm_set_file_attributes(FCB* fcb)
{
    return cpm_set_file_attributes_i((uint16_t)fcb);
}

DPB* cpm_get_dpb(void)
{
    return (DPB*)cpm_get_dpb_i();
}

uint8_t cpm_read_random(FCB* fcb)
{
    return cpm_read_random_i((uint16_t)fcb);
}

uint8_t cpm_write_random(FCB* fcb)
{
    return cpm_write_random_i((uint16_t)fcb);
}

void cpm_seek_to_end(FCB* fcb)
{
    return cpm_seek_to_end_i((uint16_t)fcb);
}

void cpm_seek_to_seq_pos(FCB* fcb)
{
    return cpm_seek_to_seq_pos_i((uint16_t)fcb);
}

uint8_t cpm_write_random_filled(FCB* fcb)
{
    return cpm_write_random_filled_i((uint16_t)fcb);
}

DPH* cpm_bios_seldsk(uint8_t drive)
{
	return (DPH*) cpm_bios_seldsk_i(drive);
}

void cpm_bios_setdma(void* dma)
{
	cpm_bios_setdma_i((uint16_t) dma);
}

void cpm_bios_setsec(uint32_t* sector)
{
	cpm_bios_setsec_i((uint16_t) sector);
}

