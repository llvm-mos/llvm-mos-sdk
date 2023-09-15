// Including this header defines a specialization of soa::Ptr for a structure
// type that makes the structure members accessible as their own individual
// soa::Ptr objects. That is, given struct Foo { int a, b; }, soa::Ptr<Foo>
// would have two public members, a, and b, both of type soa::Ptr<int>.
//
// To use this, #define SOA_STRUCT to the struct type, and #define SOA_MEMBERS
// to a space-separated list of the struct member names, each wrapped with
// MEMBER(). Then, include the header. These preprocessors macros will be
// automatically undefined by this header.
//
// This header must be used before the first use of soa::Ptr for the struct
// type.
//
// Example:
//   struct Foo { int a, b; }
//   #define SOA_STRUCT Foo
//   #define SOA_MEMBERS \
//     MEMBER(a)         \
//     MEMBER(b)
//   #include <soa-struct.inc>
//
//   soa::Array<Foo, 10> a;
//   a[5].b = 42;

template <>
class soa::Ptr<const SOA_STRUCT> : public soa::BasePtr<const SOA_STRUCT> {
public:
#define MEMBER(NAME) soa::Ptr<const decltype(SOA_STRUCT::NAME)> NAME;
  SOA_MEMBERS
#undef MEMBER

  template <uint8_t N>
  [[clang::always_inline]] constexpr Ptr(const uint8_t ByteArrays[][N],
                                         uint8_t Idx)
      : BasePtr(ByteArrays, Idx)
#define MEMBER(NAME) , NAME(ByteArrays + offsetof(SOA_STRUCT, NAME), Idx)
            SOA_MEMBERS
#undef MEMBER
  {
  }

  using BasePtr<const SOA_STRUCT>::operator=;
};

template <> class soa::Ptr<SOA_STRUCT> : public soa::BasePtr<SOA_STRUCT> {
public:
#define MEMBER(NAME) soa::Ptr<decltype(SOA_STRUCT::NAME)> NAME;
  SOA_MEMBERS
#undef MEMBER

  template <uint8_t N>
  [[clang::always_inline]] constexpr Ptr(uint8_t ByteArrays[][N], uint8_t Idx)
      : BasePtr(ByteArrays, Idx)
#define MEMBER(NAME) , NAME(ByteArrays + offsetof(SOA_STRUCT, NAME), Idx)
            SOA_MEMBERS
#undef MEMBER
  {
  }

  using BasePtr<SOA_STRUCT>::operator=;
};

#undef SOA_STRUCT
#undef SOA_MEMBERS
