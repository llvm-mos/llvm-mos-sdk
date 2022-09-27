// Keeping these in C LTOs them in, which informs LTO code generation that the
// ZP regions aren't available. This saves users of the library from having to
// manually reserve ZP space from LTO.
__attribute__((section(".zp.ft_temp"))) char FT_TEMP[3];
