// llvm-mos-sdk cx16 kernel file access tests
//
// vim: set et ts=4 sw=4

#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#include <cbm.h>  // Commodore kernal functions
#include <cx16.h> // X16 specific kernal functions

uint8_t device_num = 8; // CBM device number (8 = main disk)
uint8_t cbm_error;      // CBM error code
char cbm_status[64];    // CBM device status string
char cbm_tempstr[128];  // CBM temp for device commands

uint8_t cbm_get_status(void);
uint8_t cbm_device_cmd(const char *cmd);
uint8_t cbm_delete_file(const char *fn);
uint8_t cbm_rename_file(const char *old_fn, const char *new_fn);
uint8_t cbm_open_file(uint8_t lfn, const char *fn, const char rw);
uint8_t cbm_close_file(uint8_t lfn);
long cbm_file_read(uint8_t lfn, void *buf, size_t maxsize);
long cbm_file_write(uint8_t lfn, const void *buf, size_t size);

// read device status channel, returns cbm_error and sets cbm_status
uint8_t cbm_get_status(void)
{
    uint8_t len = 0;
    cbm_k_setlfs(15, device_num, 15);
    cbm_k_setnam("");
    cbm_k_open();
    cbm_k_chkin(15);
    while (len < sizeof(cbm_status) && !cbm_k_readst())
    {
        uint8_t c = cbm_k_chrin();
        if (c == '\r')
        {
            break;
        }
        cbm_status[len++] = c;
    }
    cbm_status[len] = 0;
    cbm_k_clrch();
    cbm_k_close(15);
    cbm_error = ((cbm_status[0] - '0') * 10) + (cbm_status[1] - '0');
    if (cbm_error < 20) // quash trivial errors
    {
        cbm_error = 0;
    }

    return cbm_error;
}

// send device command
uint8_t cbm_device_cmd(const char *cmd)
{
    cbm_k_setlfs(15, device_num, 15);
    cbm_k_setnam(cmd);
    cbm_k_open();
    cbm_k_close(15);
    return cbm_get_status();
}

// delete file
uint8_t cbm_delete_file(const char *fn)
{
    strcpy(cbm_tempstr, "S0:");
    strncat(cbm_tempstr, fn, sizeof(cbm_tempstr) - 1);
    return cbm_device_cmd(cbm_tempstr);
}
// rename file
uint8_t cbm_rename_file(const char *old_fn, const char *new_fn)
{
    strcpy(cbm_tempstr, "R0:");
    strncat(cbm_tempstr, new_fn, sizeof(cbm_tempstr) - 1);
    strncat(cbm_tempstr, "=", sizeof(cbm_tempstr) - 1);
    strncat(cbm_tempstr, old_fn, sizeof(cbm_tempstr) - 1);
    return cbm_device_cmd(cbm_tempstr);
}

// returns 0 on success, else error code (also in cbm_error)
uint8_t cbm_open_file(uint8_t lfn, const char *fn, const char rw)
{
    static char file_ops[] = ",P,?";
    if (rw == 'w')
    {
        cbm_delete_file(fn);
        file_ops[3] = 'W';
    }
    else
    {
        file_ops[3] = 'R';
    }
    strncpy(cbm_tempstr, fn, sizeof(cbm_tempstr));
    strncat(cbm_tempstr, file_ops, sizeof(cbm_tempstr) - 1);

    cbm_get_status();
    cbm_k_setlfs(lfn, device_num, lfn);
    cbm_k_setnam(cbm_tempstr);
    cbm_k_open();
    if (cbm_get_status())
    {
        cbm_k_close(lfn);
    }
    return cbm_error;
}

// returns 0 on success, else error code (also in cbm_error)
uint8_t cbm_close_file(uint8_t lfn)
{
    cbm_k_close(lfn);
    cbm_get_status();
    return cbm_error;
}

// return bytes read (if < maxsize cbm_error has error code)
long cbm_file_read(uint8_t lfn, void *buf, size_t maxsize)
{
    uint8_t *p = buf;
    size_t size = 0;
    cbm_error = cbm_k_chkin(lfn);
    while (!cbm_error && size < maxsize)
    {
        if ((cbm_error = cbm_k_readst()))
        {
            break;
        }
        *p++ = cbm_k_chrin();
        size += 1;
    }
    cbm_k_clrch();
    cbm_get_status();
    return (long)size;
}

// return bytes written (if < size, cbm_error has error code)
long cbm_file_write(uint8_t lfn, const void *buf, size_t size)
{
    const uint8_t *p = buf;
    size_t written = 0;
    cbm_error = cbm_k_ckout(lfn);
    while (!cbm_error && written < size)
    {
        cbm_k_chrout(*p++);
        if ((cbm_error = cbm_k_readst()))
        {
            break;
        }
        written += 1;
    }
    cbm_k_clrch();
    cbm_get_status();
    return (long)written;
}

// testing/example file access code
const char *test1name = "TESTFILE1.TXT";
const char *test2name = "TESTFILE2.TXT";
const char *tempname = "TEMPFILE.TXT";
const char *badname = "FOOBAR.BAZ";

const char payload[] =
    "THIS IS A TEXT FILE CREATED BY LLVM-MOS\r"
    "ON THE COMMANDER X16 USING CBM FILE I/O.\r";

const char payload2[] =
    "THIS IS A COMPLETELY DIFFERNT STRING TO \r"
    "MAKE SURE WE CAN WRITE CONCURRENT FILES.\r";

char read_buffer[256];

#define LFN_FD1 2 // 1st logical file (2-14 are allowed)
#define LFN_FD2 3 // 2st logical file

void show_status(void)
{
    printf("%s=%c%d \"%s\"%c\n", cbm_error < 20 ? "success" : "failure", cbm_error < 20 ? CH_WHITE : CH_LIGHTRED, cbm_error, cbm_status, CH_WHITE);
}

int main(void)
{
    int16_t len;

    putchar(CH_FONT_ISO); // use ISO character set mode (for upper/lower)
    printf("Simple test of CBM file access routines.\n\n");
    cbm_get_status();
    printf("Initial device 8 status: \"%s\"\n\n", cbm_status);

    printf("Open \"%s\" for writing: ", tempname);

    cbm_open_file(LFN_FD1, tempname, 'w');
    show_status();
    if (!cbm_error)
    {
        printf("Write: ");
        len = (int16_t)cbm_file_write(LFN_FD1, payload, sizeof(payload) - 1); // don't write NUL char
        if (len >= 0)
        {
            printf("%d bytes, ", len);
        }
        show_status();
    }
    printf("Close: ");
    cbm_close_file(LFN_FD1);
    show_status();

    printf("\nOpen \"%s\" for reading: ", tempname);

    cbm_open_file(LFN_FD1, tempname, 'r');
    show_status();
    if (!cbm_error)
    {
        printf("Read: ");
        len = (int16_t)cbm_file_read(LFN_FD1, read_buffer, sizeof(read_buffer) - 1); // leave  NUL char
        if (len >= 0)
        {
            printf("%d bytes, ", len);
        }
        show_status();
    }
    printf("Close: ");
    cbm_close_file(LFN_FD1);
    show_status();

    printf("\n");

    if (memcmp(payload, read_buffer, sizeof(payload) - 1) == 0)
    {
        printf("OK, verified written data matches read data\n");
    }
    else
    {
        printf("ERROR Data written vs read mismatch!\n");
    }

    printf("\nOpen   \"%s\" error test: ", badname);
    cbm_open_file(LFN_FD1, badname, 'r');
    show_status();

    printf("Delete \"%s\" error test: ", badname);
    cbm_delete_file(badname);
    show_status();

    printf("Rename \"%s\"->\"%s\" test: ", tempname, badname);
    cbm_rename_file(tempname, badname);
    show_status();

    printf("Delete \"%s\" test: ", badname);
    cbm_delete_file(badname);
    show_status();

    printf("\nWriting to both \"%s\" and \"%s\"\n", test1name, test2name);
    printf(" Open  \"%s\": ", test1name);
    cbm_open_file(LFN_FD1, test1name, 'w');
    show_status();
    printf(" Open  \"%s\": ", test2name);
    cbm_open_file(LFN_FD2, test2name, 'w');
    show_status();
    printf(" Write \"%s\": ", test1name);
    cbm_file_write(LFN_FD1, payload, sizeof(payload) - 1); // don't write NUL char
    show_status();
    printf(" Write \"%s\": ", test2name);
    cbm_file_write(LFN_FD2, payload2, sizeof(payload2) - 1); // don't write NUL char
    show_status();
    printf(" Write \"%s\": ", test1name);
    cbm_file_write(LFN_FD1, payload, sizeof(payload) - 1); // don't write NUL char
    show_status();
    printf(" Write \"%s\": ", test2name);
    cbm_file_write(LFN_FD2, payload2, sizeof(payload2) - 1); // don't write NUL char
    show_status();
    printf(" Close \"%s\": ", test1name);
    cbm_close_file(LFN_FD1);
    show_status();
    printf(" Close \"%s\": ", test2name);
    cbm_close_file(LFN_FD2);
    show_status();

    puts("Done.");
    return 0;
}
