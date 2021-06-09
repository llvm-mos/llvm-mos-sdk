#ifdef _ASSERT_H_
#undef assert
#undef _ASSERT_H_
#endif // _ASSERT_H_

#define _ASSERT_H_

#ifdef NDEBUG
#define assert(ignore) ((void)0)
#else
#define assert(expr)                                                           \
  ((expr) ? (void)0 : __assert(__FILE__, __LINE__, __PRETTY_FUNCTION__, #expr))
#endif

#ifdef __cplusplus
extern "C" {
#endif

void __assert(const char *file, const char *line, const char *func,
              const char *expr);

#ifdef __cplusplus
}
#endif
