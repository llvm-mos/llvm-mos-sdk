# Imaginary (Zero Page) Register Definitions

This directory contains linker script includes to assist with defining the
available zero-page registers for a given target. Instead of specifying the
value of each imaginary register symbol, only the beginning of each continous
region needs to be provided. Afterwards, the file from this directory with
the number of the highest imaginary register present can be imported to fill
in the rest.

## Example

Say the available zero page locations are 10-19, 25-26, and 30-39. That's a
total of 10 + 2 + 10 = 22 zero page registers, ranging from `__rc0` to
`__rc21`. The continuous regions begin with 10, 25, and 30, respectively.
These will be the addresses of the imaginary registers `__rc0`, `__rc10`, and
`__rc12`, respectively.

The following linker script fragment can then be used to provide all 22
imaginary registers. It's usually a good idea to ASSERT on the first and last
address to make sure that the math works out.

```ld
PROVIDE(__rc0 = 10);
PROVIDE(__rc10 = 25);
PROVIDE(__rc12 = 30);
INCLUDE imag_reg/21.ld
ASSERT(__rc0 == 0, "...")
ASSERT(__rc21 == 39, "...")

/* Just for illustration. */
ASSERT(__rc1 == 1, "...")
ASSERT(__rc9 == 9, "...")
ASSERT(__rc10 == 25, "...")
ASSERT(__rc11 == 26, "...")
ASSERT(__rc12 == 30, "...")
ASSERT(__rc13 == 31, "...")
```