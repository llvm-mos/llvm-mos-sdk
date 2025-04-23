__attribute__((always_inline, weak)) int
__from_ascii(char c, void *ctx, int (*write)(char c, void *ctx)) {
  return write(c, ctx);
}

__attribute__((always_inline, weak)) int __to_ascii(void *ctx,
                                                    int (*read)(void *ctx)) {
  return read(ctx);
}
