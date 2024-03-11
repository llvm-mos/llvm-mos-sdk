// Copyright 2024 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#include <string.h>
#include "../neo6502.h"
#include "../kernel.h"
#include "api-internal.h"

struct neo_file_stat;
typedef struct neo_file_stat neo_file_stat_t;

__attribute__((leaf))
void neo_file_list_directory(void) {
    KSendMessage(API_GROUP_FILEIO, API_FN_LIST_DIRECTORY);
}

__attribute__((leaf))
void neo_file_load_p(const void *filename, void *dest) {
    *((volatile uint16_t*) (ControlPort.params)) = (uint16_t) filename;
    *((volatile uint16_t*) (ControlPort.params + 2)) = (uint16_t) dest;
    KSendMessage(API_GROUP_FILEIO, API_FN_LOAD_FILENAME);
}

__attribute__((leaf))
void neo_file_load(const char *filename, void *dest) {
    PASCALIZE_INPUT(filename);
    neo_file_load_p(filename_p, dest);
    // Wait for message to finish before deallocating VLA.
    KWaitMessage();
}

__attribute__((leaf))
void neo_file_store_p(const void *filename, const void *src, uint16_t len) {
    *((volatile uint16_t*) (ControlPort.params)) = (uint16_t) filename;
    *((volatile uint16_t*) (ControlPort.params + 2)) = (uint16_t) src;
    *((volatile uint16_t*) (ControlPort.params + 4)) = len;
    KSendMessage(API_GROUP_FILEIO, API_FN_STORE_FILENAME);
}

__attribute__((leaf))
void neo_file_store(const void *filename, const void *src, uint16_t len) {
    PASCALIZE_INPUT(filename);
    neo_file_store_p(filename_p, src, len);
    // Wait for message to finish before deallocating VLA.
    KWaitMessage();
}

__attribute__((leaf))
void neo_file_open_p(uint8_t channel, const void *filename, uint8_t mode) {
    ControlPort.params[0] = channel;
    *((volatile uint16_t*) (ControlPort.params + 1)) = (uint16_t) filename;
    ControlPort.params[3] = mode;
    KSendMessage(API_GROUP_FILEIO, API_FN_FILE_OPEN);
}

__attribute__((leaf))
void neo_file_open(uint8_t channel, const void *filename, uint8_t mode) {
    PASCALIZE_INPUT(filename);
    neo_file_open_p(channel, filename_p, mode);
    // Wait for message to finish before deallocating VLA.
    KWaitMessage();
}

__attribute__((leaf))
void neo_file_close(uint8_t channel) {
    ControlPort.params[0] = channel;
    KSendMessage(API_GROUP_FILEIO, API_FN_FILE_CLOSE);
}

__attribute__((leaf))
void neo_file_seek(uint8_t channel, uint32_t pos) {
    ControlPort.params[0] = channel;
    *((volatile uint32_t*) (ControlPort.params + 1)) = pos;
    KSendMessage(API_GROUP_FILEIO, API_FN_FILE_SEEK);
}

__attribute__((leaf))
uint32_t neo_file_tell(uint8_t channel) {
    ControlPort.params[0] = channel;
    KSendMessageSync(API_GROUP_FILEIO, API_FN_FILE_TELL);
    return *((volatile uint32_t*) (ControlPort.params + 1));
}

__attribute__((leaf))
uint16_t neo_file_read(uint8_t channel, void *dest, uint16_t len) {
    ControlPort.params[0] = channel;
    *((volatile uint16_t*) (ControlPort.params + 1)) = (uint16_t) dest;
    *((volatile uint16_t*) (ControlPort.params + 3)) = len;
    KSendMessageSync(API_GROUP_FILEIO, API_FN_FILE_READ);
    return *((volatile uint16_t*) (ControlPort.params + 3));
}

__attribute__((leaf))
uint32_t neo_file_write(uint8_t channel, const void *src, uint16_t len) {
    ControlPort.params[0] = channel;
    *((volatile uint16_t*) (ControlPort.params + 1)) = (uint16_t) src;
    *((volatile uint16_t*) (ControlPort.params + 3)) = len;
    KSendMessageSync(API_GROUP_FILEIO, API_FN_FILE_WRITE);
    return *((volatile uint16_t*) (ControlPort.params + 3));
}

__attribute__((leaf))
uint32_t neo_file_size(uint8_t channel) {
    ControlPort.params[0] = channel;
    KSendMessageSync(API_GROUP_FILEIO, API_FN_FILE_SIZE);
    return *((volatile uint32_t*) (ControlPort.params + 1));
}

__attribute__((leaf))
void neo_file_set_size(uint8_t channel, uint32_t size) {
    ControlPort.params[0] = channel;
    *((volatile uint32_t*) (ControlPort.params + 1)) = size;
    KSendMessage(API_GROUP_FILEIO, API_FN_FILE_SET_SIZE);
}

__attribute__((leaf))
void neo_file_rename_p(const void *from, const void *to) {
    *((volatile uint16_t*) (ControlPort.params)) = (uint16_t) from;
    *((volatile uint16_t*) (ControlPort.params + 2)) = (uint16_t) to;
    KSendMessage(API_GROUP_FILEIO, API_FN_FILE_RENAME);
}

__attribute__((leaf))
void neo_file_rename(const char *from, const char *to) {
    PASCALIZE_INPUT(from);
    PASCALIZE_INPUT(to);
    neo_file_rename_p(from_p, to_p);
    // Wait for message to finish before deallocating VLA.
    KWaitMessage();
}

__attribute__((leaf))
void neo_file_delete_p(const void *filename) {
    *((volatile uint16_t*) (ControlPort.params)) = (uint16_t) filename;
    KSendMessage(API_GROUP_FILEIO, API_FN_FILE_DELETE);
}

__attribute__((leaf))
void neo_file_delete(const char *filename) {
    PASCALIZE_INPUT(filename);
    neo_file_delete_p(filename_p);
    // Wait for message to finish before deallocating VLA.
    KWaitMessage();
}

__attribute__((leaf))
void neo_file_chdir_p(const void *path) {
    *((volatile uint16_t*) (ControlPort.params)) = (uint16_t) path;
    KSendMessage(API_GROUP_FILEIO, API_FN_DIR_CHDIR);
}

__attribute__((leaf))
void neo_file_chdir(const char *path) {
    PASCALIZE_INPUT(path);
    neo_file_chdir_p(path_p);
    // Wait for message to finish before deallocating VLA.
    KWaitMessage();
}

__attribute__((leaf))
void neo_file_mkdir_p(const void *path) {
    *((volatile uint16_t*) (ControlPort.params)) = (uint16_t) path;
    KSendMessage(API_GROUP_FILEIO, API_FN_DIR_MKDIR);
}

__attribute__((leaf))
void neo_file_mkdir(const char *path) {
    PASCALIZE_INPUT(path);
    neo_file_mkdir_p(path_p);
    // Wait for message to finish before deallocating VLA.
    KWaitMessage();
}

__attribute__((leaf))
void neo_file_stat_p(const void *path, neo_file_stat_t *st) {
    *((volatile uint16_t*) (ControlPort.params)) = (uint16_t) path;
    KSendMessageSync(API_GROUP_FILEIO, API_FN_FILE_STAT);
    memcpy(st, (const void*) (ControlPort.params + 2), 5);
}

__attribute__((leaf))
void neo_file_stat(const char *path, neo_file_stat_t *st) {
    PASCALIZE_INPUT(path);
    neo_file_stat_p(path_p, st);
    // Wait for message to finish before deallocating VLA.
    KWaitMessage();
}

__attribute__((leaf))
void neo_file_opendir_p(const void *path) {
    *((volatile uint16_t*) (ControlPort.params)) = (uint16_t) path;
    KSendMessage(API_GROUP_FILEIO, API_FN_DIR_OPEN);
}

__attribute__((leaf))
void neo_file_opendir(const char *path) {
    PASCALIZE_INPUT(path);
    neo_file_opendir_p(path_p);
    // Wait for message to finish before deallocating VLA.
    KWaitMessage();
}

/**
 * @brief Read the next file item from the directory, returning a Pascal string for the path.
 *
 * @param filename Returned filename (Pascal string)
 * @param st Stat information structure
 *
 * Check errors with @see neo_api_error
 */
__attribute__((leaf))
void neo_file_readdir_p(void *path, neo_file_stat_t *st) {
    *((volatile uint16_t*) (ControlPort.params)) = (uint16_t) path;
    KSendMessageSync(API_GROUP_FILEIO, API_FN_DIR_READ);
    if (st) memcpy(st, (const void*) (ControlPort.params + 2), 5);
}

__attribute__((leaf))
void neo_file_readdir(char *path, neo_file_stat_t *st) {
    neo_file_readdir_p(path, st);
    if (!ControlPort.error) {
        __neo_depascalize_output(path);
    }
}

__attribute__((leaf))
void neo_file_closedir(void) {
    KSendMessage(API_GROUP_FILEIO, API_FN_DIR_CLOSE);
}

__attribute__((leaf))
void neo_file_copy_p(const void *from ,const void *to) {
    *((volatile uint16_t*) (ControlPort.params)) = (uint16_t) from;
    *((volatile uint16_t*) (ControlPort.params + 2)) = (uint16_t) to;
    KSendMessage(API_GROUP_FILEIO, API_FN_FILE_COPY);
}

__attribute__((leaf))
void neo_file_copy(const char *from, const char *to) {
    PASCALIZE_INPUT(from);
    PASCALIZE_INPUT(to);
    neo_file_copy_p(from_p, to_p);
    // Wait for message to finish before deallocating VLA.
    KWaitMessage();
}

__attribute__((leaf))
void neo_file_set_attr_p(const void *path, uint8_t attr) {
    *((volatile uint16_t*) (ControlPort.params)) = (uint16_t) path;
    ControlPort.params[2] = attr;
    KSendMessage(API_GROUP_FILEIO, API_FN_FILE_SET_ATTR);
}

__attribute__((leaf))
void neo_file_set_attr(const char *path, uint8_t attr) {
    PASCALIZE_INPUT(path);
    neo_file_set_attr_p(path_p, attr);
    // Wait for message to finish before deallocating VLA.
    KWaitMessage();
}

__attribute__((leaf))
void neo_file_list_filtered_p(const void *filter) {
    *((volatile uint16_t*) (ControlPort.params)) = (uint16_t) filter;
    KSendMessage(API_GROUP_FILEIO, API_FN_LIST_FILTERED);
}

__attribute__((leaf))
void neo_file_list_filtered(const void *filter) {
    PASCALIZE_INPUT(filter);
    neo_file_list_filtered_p(filter_p);
    // Wait for message to finish before deallocating VLA.
    KWaitMessage();
}
