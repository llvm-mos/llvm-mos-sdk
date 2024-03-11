// Copyright 2024 LLVM-MOS Project
// Licensed under the Apache License, Version 2.0 with LLVM Exceptions.
// See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
// information.

#include <stdint.h>

#ifndef _NEO_FILE_H
#define _NEO_FILE_H

#include <neo6502.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef enum neo_file_mode {
    NEO_FILE_READ = 0,
    NEO_FILE_WRITE = 1,
    NEO_FILE_READ_WRITE = 2,
    NEO_FILE_CREATE = 3
} neo_file_mode_t;

#define NEO_FILE_DESTINATION_GRAPHICS ((void*) 0xFFFF)

typedef struct neo_file_stat {
    uint32_t size;
    uint8_t attr;
} neo_file_stat_t;

#define NEO_FILE_ATTR_DIRECTORY 0x01
#define NEO_FILE_ATTR_SYSTEM    0x02
#define NEO_FILE_ATTR_ARCHIVE   0x04
#define NEO_FILE_ATTR_READ_ONLY 0x08
#define NEO_FILE_ATTR_HIDDEN    0x10

/**
 * @brief Display the listing of files in the current directory.
 */
__attribute__((leaf))
void neo_file_list_directory(void);

/**
 * @brief Load a file into memory, using a Pascal string for the filename.
 *
 * To load a file into graphics memory, use @see NEO_FILE_DESTINATION_GRAPHICS .
 *
 * @param filename Filename (Pascal string)
 * @param dest Destination
 *
 * Check errors with @see neo_api_error
 */
__attribute__((leaf))
void neo_file_load_p(const void *filename, void *dest);

/**
 * @brief Load a file into memory, using a C string for the filename.
 *
 * To load a file into graphics memory, use @see NEO_FILE_DESTINATION_GRAPHICS .
 *
 * @param filename Filename (C string)
 * @param dest Destination
 *
 * Check errors with @see neo_api_error
 */
__attribute__((leaf))
void neo_file_load(const char *filename, void *dest);

/**
 * @brief Store a file from memory, using a Pascal string for the filename.
 *
 * @param filename Filename (Pascal string)
 * @param src Source
 * @param len Length, in bytes
 *
 * Check errors with @see neo_api_error
 */
__attribute__((leaf))
void neo_file_store_p(const void *filename, const void *src, uint16_t len);

/**
 * @brief Store a file from memory, using a C string for the filename.
 *
 * @param filename Filename (Pascal string)
 * @param src Source
 * @param len Length, in bytes
 *
 * Check errors with @see neo_api_error
 */
__attribute__((leaf))
void neo_file_store(const void *filename, const void *src, uint16_t len);

/**
 * @brief Open a file channel, using a Pascal string for the filename.
 *
 * @param channel Channel ID
 * @param filename Filename (Pascal string)
 * @param mode Mode @see neo_file_mode_t
 *
 * Check errors with @see neo_api_error
 */
__attribute__((leaf))
void neo_file_open_p(uint8_t channel, const void *filename, uint8_t mode);

/**
 * @brief Open a file channel, using a C string for the filename.
 *
 * @param channel Channel ID
 * @param filename Filename (C string)
 * @param mode Mode @see neo_file_mode_t
 *
 * Check errors with @see neo_api_error
 */
__attribute__((leaf))
void neo_file_open(uint8_t channel, const void *filename, uint8_t mode);

/**
 * @brief Close a file channel.
 *
 * @param channel Channel ID
 *
 * Check errors with @see neo_api_error
 */
__attribute__((leaf))
void neo_file_close(uint8_t channel);

/**
 * @brief Seek a file.
 *
 * @param channel Channel ID
 * @param pos New file position
 *
 * Check errors with @see neo_api_error
 */
__attribute__((leaf))
void neo_file_seek(uint8_t channel, uint32_t pos);

/**
 * @brief Tell a file's position.
 *
 * @param channel Channel ID
 * @return Current file position
 *
 * Check errors with @see neo_api_error
 */
__attribute__((leaf))
uint32_t neo_file_tell(uint8_t channel);

/**
 * @brief Read bytes from an open file.
 *
 * To read into graphics memory, use @see NEO_FILE_DESTINATION_GRAPHICS .
 *
 * @param channel Channel ID
 * @param dest Destination
 * @param len Length, in bytes
 * @return Amount of data actually read
 *
 * Check errors with @see neo_api_error
 */
__attribute__((leaf))
uint16_t neo_file_read(uint8_t channel, void *dest, uint16_t len);

/**
 * @brief Write bytes to an open file.
 *
 * @param channel Channel ID
 * @param src Source
 * @param len Length, in bytes
 * @return Amount of data actually written
 *
 * Check errors with @see neo_api_error
 */
__attribute__((leaf))
uint32_t neo_file_write(uint8_t channel, const void *src, uint16_t len);

/**
 * @brief Get the file's size, in bytes.
 *
 * @param channel Channel ID
 * @return File size, in bytes
 *
 * Check errors with @see neo_api_error
 */
__attribute__((leaf))
uint32_t neo_file_size(uint8_t channel);

/**
 * @brief Set the file's size.
 *
 * @param channel Channel ID
 * @param size New file size, in bytes
 *
 * Check errors with @see neo_api_error
 */
__attribute__((leaf))
void neo_file_set_size(uint8_t channel, uint32_t size);

/**
 * @brief Rename file, using Pascal strings for the filenames.
 *
 * @param from Old filename (Pascal string)
 * @param to New filename (Pascal string)
 *
 * Check errors with @see neo_api_error
 */
__attribute__((leaf))
void neo_file_rename_p(const void *from, const void *to);

/**
 * @brief Rename file, using C strings for the filenames.
 *
 * @param from Old filename (C string)
 * @param to New filename (C string)
 *
 * Check errors with @see neo_api_error
 */
__attribute__((leaf))
void neo_file_rename(const char *from, const char *to);

/**
 * @brief Delete file, using Pascal strings for the filename.
 *
 * Note that deleting an open file is undefined behaviour.
 * In addition, directories can only be deleted if empty.
 *
 * @param filename Filename (Pascal string)
 *
 * Check errors with @see neo_api_error
 */
__attribute__((leaf))
void neo_file_delete_p(const void *filename);

/**
 * @brief Delete file, using C strings for the filename.
 *
 * Note that deleting an open file is undefined behaviour.
 * In addition, directories can only be deleted if empty.
 *
 * @param filename Filename (C string)
 *
 * Check errors with @see neo_api_error
 */
__attribute__((leaf))
void neo_file_delete(const char *filename);

/**
 * @brief Change current working directory, using a Pascal string for the path.
 *
 * @param path Path (Pascal string)
 *
 * Check errors with @see neo_api_error
 */
__attribute__((leaf))
void neo_file_chdir_p(const void *path);

/**
 * @brief Change current working directory, using a C string for the path.
 *
 * @param path Path (C string)
 *
 * Check errors with @see neo_api_error
 */
__attribute__((leaf))
void neo_file_chdir(const char *path);

/**
 * @brief Create directory, using a Pascal string for the path.
 *
 * @param path Path (Pascal string)
 *
 * Check errors with @see neo_api_error
 */
__attribute__((leaf))
void neo_file_mkdir_p(const void *path);

/**
 * @brief Create directory, using a C string for the path.
 *
 * @param path Path (C string)
 *
 * Check errors with @see neo_api_error
 */
__attribute__((leaf))
void neo_file_mkdir(const char *path);

/**
 * @brief Retrieve file information, using a Pascal string for the path.
 *
 * @param path Path (Pascal string)
 * @param st Stat information structure
 *
 * Check errors with @see neo_api_error
 */
__attribute__((leaf))
void neo_file_stat_p(const void *path, neo_file_stat_t *st);

/**
 * @brief Retrieve file information, using a C string for the path.
 *
 * @param path Path (C string)
 * @param st Stat information structure
 *
 * Check errors with @see neo_api_error
 */
__attribute__((leaf))
void neo_file_stat(const char *path, neo_file_stat_t *st);

/**
 * @brief Open a directory for enumeration, using a Pascal string for the path.
 *
 * @param path Path (Pascal string)
 *
 * Check errors with @see neo_api_error
 */
__attribute__((leaf))
void neo_file_opendir_p(const void *path);

/**
 * @brief Open a directory for enumeration, using a C string for the path.
 *
 * @param path Path (C string)
 *
 * Check errors with @see neo_api_error
 */
__attribute__((leaf))
void neo_file_opendir(const char *path);

/**
 * @brief Read the next file item from the directory, returning a Pascal string for the path.
 *
 * @param filename Returned filename (Pascal string)
 * @param st Stat information structure
 *
 * Check errors with @see neo_api_error
 */
__attribute__((leaf))
void neo_file_readdir_p(void *path, neo_file_stat_t *st);

/**
 * @brief Read the next file item from the directory, returning a C string for the path.
 *
 * @param filename Returned filename (C string)
 * @param st Stat information structure
 *
 * Check errors with @see neo_api_error
 */
__attribute__((leaf))
void neo_file_readdir(char *path, neo_file_stat_t *st);

/**
 * @brief Close the directory opened with @see neo_file_opendir .
 *
 * Check errors with @see neo_api_error
 */
__attribute__((leaf))
void neo_file_closedir(void);

/**
 * @brief Copy file, using Pascal strings for the filenames.
 *
 * @param from Old filename (Pascal string)
 * @param to New filename (Pascal string)
 *
 * Check errors with @see neo_api_error
 */
__attribute__((leaf))
void neo_file_copy_p(const void *from, const void *to);

/**
 * @brief Copy file, using C strings for the filenames.
 *
 * @param from Old filename (C string)
 * @param to New filename (C string)
 *
 * Check errors with @see neo_api_error
 */
__attribute__((leaf))
void neo_file_copy(const char *from, const char *to);

/**
 * @brief Set file attributes, using a Pascal string for the filename.
 *
 * @param path Filename (Pascal string)
 * @param attr New attributes
 *
 * Check errors with @see neo_api_error
 */
__attribute__((leaf))
void neo_file_set_attr_p(const void *path, uint8_t attr);

/**
 * @brief Set file attributes, using a C string for the filename.
 *
 * @param path Filename (C string)
 * @param attr New attributes
 *
 * Check errors with @see neo_api_error
 */
__attribute__((leaf))
void neo_file_set_attr(const char *path, uint8_t attr);

/**
 * @brief Display a filtered listing of files in the current directory, using a Pascal string for the needle.
 *
 * @param filter Filename search needle (Pascal string)
 */
__attribute__((leaf))
void neo_file_list_filtered_p(const void *filter);

/**
 * @brief Display a filtered listing of files in the current directory, using a C string for the needle.
 *
 * @param filter Filename search needle (C string)
 */
__attribute__((leaf))
void neo_file_list_filtered(const void *filter);

#ifdef __cplusplus
}
#endif

#endif
