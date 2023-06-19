/* Commander X16 imaginary registers.
 *
 * Due to the difference between the Commander X16 and llvm-mos's calling
 * conventions, we try to provide a satisfactory mix of both.
 *
 * Commander X16 registers: r0-r15
 * - caller-saved: r11-r15
 * - callee-saved: r0-r10
 *   - arguments: r0-r5
 *
 * llvm-mos registers: rs0-rs15
 * - caller-saved: rs1-rs9
 * - callee-saved: rs0, rs10-rs15
 *   - rs15 is expected to be the last register on the zero page in
 *     commodore.ld.
 * - symbols refer to bytes: __rc(2N) => __rs(N)
 *
 * In addition, this file provides symbols for Commander X16 registers - that
 * is, __r0 through __r15.
 */

__r0  = 0x0002;
__r1  = 0x0004;
__r2  = 0x0006;
__r3  = 0x0008;
__r4  = 0x000a;
__r5  = 0x000c;
__r6  = 0x000e;
__r7  = 0x0010;
__r8  = 0x0012;
__r9  = 0x0014;
__r10 = 0x0016;
__r11 = 0x0018;
__r12 = 0x001a;
__r13 = 0x001c;
__r14 = 0x001e;
__r15 = 0x0020;

/* LLVM-MOS caller-saved => X16 callee-saved (arguments; rs1-rs4 => r0-r3).
 * This allows setting arguments in KERNAL wrappers without stashing.
 */
__rc2  = __r0;
__rc4  = __r1;
__rc6  = __r2;
__rc8  = __r3;
/* X16 r4, r5 is left unallocated. */

/* LLVM-MOS caller-saved => X16 caller-saved (rs5-rs9 => r6-r10). */
__rc10 = __r6;
__rc12 = __r7;
__rc14 = __r8;
__rc16 = __r9;
__rc18 = __r10;

/* LLVM-MOS callee-saved => X16 callee-saved (scratch; rs10-rs14 => r11-r15). */
__rc20 = __r11;
__rc22 = __r12;
__rc24 = __r13;
__rc26 = __r14;
__rc28 = __r15;

/* Remaining LLVM-MOS imaginary registers (rs0, rs15). */
__rc0  = 0x0022;
__rc30 = 0x0024;
