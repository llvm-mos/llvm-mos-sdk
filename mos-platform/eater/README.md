
This directory contains support for [Ben Eater's Breadboard 6502](https://eater.net/6502) project.

Features of the port
--------------------

This port has the following features:

* .text and .rodata segments are placed into ROM, between $8000 and $FFFF.
* .data and .bss segments are placed into RAM, between $0200 and $3FFF.
* The C stack grows downwards from $4000.
* LLVM registers are stored between $E0 and $FF in the zero page.
* Support for serial input and output via the W65C51N Asynchronous
Communications Interface Adapter (ACIA).
* System millisecond tick counter based on the T2 timer in the
W65C22 Versatile Interface Adapter (VIA).

Serial console
--------------

The W65C51N Asynchronous Communications Interface Adapter (ACIA)
at address $5000 in the breadboard's memory map is used to implement the
\_\_putchar() and \_\_getchar() functions for the C library.

The ACIA is configured for 19200 bps N-8-1 communications and RTS
handshaking.  The handshaking lines on the W65C51N should be hooked
up as follows:

* Connect pin 8 (RTS) of the W65C51N to pin 10 (T2IN) of the MAX232.
* Connect pin 7 (T2OUT) of the MAX232 to pin 8 (CTS) on the DB9 connector.
* Connect pins 9 (CTS), 16 (DCD), and 17 (DSR) of the W65C51N to ground.
* Everything else should be connected up the same way as in
[Ben Eater's standard schematic](https://eater.net/schematics/6502-serial.png),
including the diodes D1 and D2 on the IRQ lines for the chips.

Serial output uses busy-waiting after transmitting each character,
due to bugs in the W65C51N chip.

Interrupts and RTS handshaking are used to reduce the chance of missing
incoming characters.  A 256-byte buffer is used to hold incoming data
until it can be read.  If the buffer fills up, then RTS will be disabled
and communications with the host will stop until the program starts
reading bytes again with getchar().

System tick counter
-------------------

The system tick counter can be read by program code with the millis()
function:

    unsigned long millis(void);

The counter starts at zero at startup time and increments every millisecond.
The value will wrap around after 49.7 days.

The millis() function is intended for implementing timeouts and delays without
using hard-coded delay loops.  The built-in delay() function makes it easy
to introduce a simple delay up to 65535 milliseconds into your program:

    void delay(unsigned ms);

Interrupt handling
------------------

The crt0 code takes care of serial and system tick interrupts automatically.
After the standard interrupt sources have been handled, the crt0 code
will call the irq() function, which must be declared as follows:

    __attribute__((interrupt)) void irq(void)
    {
        ...
    }

Non-maskable interrupts can also be handled if the program declares the
nmi() function as follows:

    __attribute__((interrupt)) void nmi(void)
    {
        ...
    }

The linker script provides stub definitions for irq() and nmi() in case
you don't need them.
