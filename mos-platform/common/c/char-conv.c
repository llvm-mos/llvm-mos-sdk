__attribute__((always_inline, weak)) void
__from_ascii(char c, void *ctx, void (*write)(char c, void *ctx)) {
  write(c, ctx);
}

__attribute__((always_inline, weak)) int __to_ascii(void *ctx,
                                                    int (*read)(void *ctx)) {
  return read(ctx);
}
