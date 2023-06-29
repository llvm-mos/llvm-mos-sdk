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

/* CAUTION: Some X16 kernal calls deviate from this convention!         */

/* X16 kernal reg      X16 convention   LLVM reg alias  LLVM convention */
__r0  = 0x0002;     /* in/out (args)    __rc2,  __rc3   trash           */
__r1  = 0x0004;     /* in/out (args)    __rc4,  __rc5   trash           */
__r2  = 0x0006;     /* in/out (args)    __rc6,  __rc7   trash           */
__r3  = 0x0008;     /* in/out (args)    __rc8,  __rc9   trash           */
__r4  = 0x000a;     /* in/out (args)      -      -      (mos-sdk temp)  */
__r5  = 0x000c;     /* in/out (args)      -      -      (unused)        */
__r6  = 0x000e;     /* preserve         __rc20, __rc21  preserve        */
__r7  = 0x0010;     /* preserve         __rc22, __rc23  preserve        */
__r8  = 0x0012;     /* preserve         __rc24, __rc25  preserve        */
__r9  = 0x0014;     /* preserve         __rc26, __rc27  preserve        */
__r10 = 0x0016;     /* preserve         __rc28, __rc29  preserve        */
__r11 = 0x0018;     /* trash            __rc10, __rc11  trash           */
__r12 = 0x001a;     /* trash            __rc12, __rc13  trash           */
__r13 = 0x001c;     /* trash            __rc14, __rc15  trash           */
__r14 = 0x001e;     /* trash            __rc16, __rc17  trash           */
__r15 = 0x0020;     /* trash            __rc18, __rc19  trash           */
/*    = 0x0022                          __rc0,  __rc1   preserve        */
/*    = 0x0024                          __rc30, __rc31  preserve        */

/* LLVM-MOS caller-saved => X16 callee-saved (arguments; rs1-rs4 => r0-r3).
 * This allows setting arguments in KERNAL wrappers without stashing.
 */
__rc2  = __r0;
__rc4  = __r1;
__rc6  = __r2;
__rc8  = __r3;
/* X16 r4, r5 is left unallocated. */

/* LLVM-MOS caller-saved => X16 caller-saved (rs5-rs9 => r11-r15). */
__rc10 = __r11;
__rc12 = __r12;
__rc14 = __r13;
__rc16 = __r14;
__rc18 = __r15;

/* LLVM-MOS callee-saved => X16 callee-saved (scratch; rs10-rs14 => r6-r10). */
__rc20 = __r6;
__rc22 = __r7;
__rc24 = __r8;
__rc26 = __r9;
__rc28 = __r10;

/* Remaining LLVM-MOS imaginary registers (rs0, rs15). */
__rc0  = 0x0022;
__rc30 = 0x0024;

/* Odd pairs. */
__rc1 = __rc0 + 1;
__rc3 = __rc2 + 1;
__rc5 = __rc4 + 1;
__rc7 = __rc6 + 1;
__rc9 = __rc8 + 1;
__rc11 = __rc10 + 1;
__rc13 = __rc12 + 1;
__rc15 = __rc14 + 1;
__rc17 = __rc16 + 1;
__rc19 = __rc18 + 1;
__rc21 = __rc20 + 1;
__rc23 = __rc22 + 1;
__rc25 = __rc24 + 1;
__rc27 = __rc26 + 1;
__rc29 = __rc28 + 1;
__rc31 = __rc30 + 1;
