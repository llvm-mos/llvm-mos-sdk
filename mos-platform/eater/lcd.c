/*
 * Copyright (c) 2023 Rhys Weatherley
 *
 * Licensed under the Apache License, Version 2.0 with LLVM Exceptions,
 * See https://github.com/llvm-mos/llvm-mos-sdk/blob/main/LICENSE for license
 * information.
 */

#include <eater.h>

#define LCD_VIA_PORT    (*((volatile unsigned char *)0x6000))
#define LCD_VIA_DDR     (*((volatile unsigned char *)0x6002))

// Pins on the 16x2 LCD panel (assumed to be connected in 4-bit mode to PORTB).
#define LCD_E       0x40
#define LCD_RW      0x20
#define LCD_RS      0x10
#define LCD_DATA4   0x0F

void lcd_init(void)
{
    // Set all LCD pins to be outputs.
    LCD_VIA_DDR = LCD_E | LCD_RW | LCD_RS | LCD_DATA4;

    // Enable 4-bit mode.
    LCD_VIA_PORT = 0x02;
    LCD_VIA_PORT = 0x02 | LCD_E;
    LCD_VIA_PORT = 0x0F;

    // Set up the display.
    lcd_instruction(LCD_I_FUNC_SET);
    lcd_instruction(LCD_I_DISP_ON);
    lcd_instruction(LCD_I_MODE_INC);
    lcd_instruction(LCD_I_CLEAR);
}

// Wait for the LCD to not be busy.
static void lcd_wait(void)
{
    unsigned char status1, status2;

    // Convert the LCD data pins to inputs.
    LCD_VIA_DDR = LCD_E | LCD_RW | LCD_RS;

    // Wait until the LCD reports that it is not busy.
    do {
        // Read the high nibble of the status.
        LCD_VIA_PORT = LCD_RW;
        LCD_VIA_PORT = LCD_RW | LCD_E;
        status1 = LCD_VIA_PORT;

        // Read the low nibble of the status.
        LCD_VIA_PORT = LCD_RW;
        LCD_VIA_PORT = LCD_RW | LCD_E;
        status2 = LCD_VIA_PORT;
        (void)status2;
    } while ((status1 & 0x08) != 0);

    // Lower the E pin.
    LCD_VIA_PORT = LCD_RW;

    // Return all LCD pins to outputs.
    LCD_VIA_DDR = LCD_E | LCD_RW | LCD_RS | LCD_DATA4;
}

void lcd_instruction(unsigned char insn)
{
    unsigned char nibble;
    lcd_wait();
    nibble = insn >> 4;
    LCD_VIA_PORT = nibble;
    LCD_VIA_PORT = nibble | LCD_E;
    LCD_VIA_PORT = nibble;
    nibble = insn & 0x0F;
    LCD_VIA_PORT = nibble;
    LCD_VIA_PORT = nibble | LCD_E;
    LCD_VIA_PORT = nibble;
}

void lcd_putchar(unsigned char c)
{
    unsigned char nibble;
    lcd_wait();
    nibble = (c >> 4) | LCD_RS;
    LCD_VIA_PORT = nibble;
    LCD_VIA_PORT = nibble | LCD_E;
    LCD_VIA_PORT = nibble;
    nibble = (c & 0x0F) | LCD_RS;
    LCD_VIA_PORT = nibble;
    LCD_VIA_PORT = nibble | LCD_E;
    LCD_VIA_PORT = nibble;
}

void lcd_puts(const char *str)
{
    char c;
    while ((c = *str++) != '\0')
        lcd_putchar((unsigned char)c);
}
