/**
 * Copyright (c) 2023 Adrian "asie" Siekierka
 *
 * This software is provided 'as-is', without any express or implied
 * warranty. In no event will the authors be held liable for any damages
 * arising from the use of this software.
 *
 * Permission is granted to anyone to use this software for any purpose,
 * including commercial applications, and to alter it and redistribute it
 * freely, subject to the following restrictions:
 *
 * 1. The origin of this software must not be misrepresented; you must not
 *    claim that you wrote the original software. If you use this software
 *    in a product, an acknowledgment in the product documentation would be
 *    appreciated but is not required.
 *
 * 2. Altered source versions must be plainly marked as such, and must not be
 *    misrepresented as being the original software.
 *
 * 3. This notice may not be removed or altered from any source distribution.
*/

#include <stdint.h>
#include <rpc8e.h>

bool rpc8e_drive_command(uint8_t id) {
	*IO_DRIVE_COMMAND = id;
	while (true) {
		uint8_t status = *IO_DRIVE_STATUS;
		if (status == DRIVE_STATUS_SUCCESS) return true;
		if (status == DRIVE_STATUS_ERROR) return false;
		rpc8e_cpu_wait();
	}
}

bool rpc8e_drive_read_disk_name(void) {
	rpc8e_drive_command(DRIVE_COMMAND_READ_NAME);
}

bool rpc8e_drive_write_disk_name(void) {
	rpc8e_drive_command(DRIVE_COMMAND_WRITE_NAME);
}

bool rpc8e_drive_read_disk_serial(void) {
	rpc8e_drive_command(DRIVE_COMMAND_READ_SERIAL);
}

bool rpc8e_drive_read_disk_sector(uint16_t sector) {
	*IO_DRIVE_SECTOR = sector;
	rpc8e_drive_command(DRIVE_COMMAND_READ_SECTOR);
}

bool rpc8e_drive_write_disk_sector(uint16_t sector) {
	*IO_DRIVE_SECTOR = sector;
	rpc8e_drive_command(DRIVE_COMMAND_WRITE_SECTOR);
}
