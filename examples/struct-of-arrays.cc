#include <cstdio>
#include <soa.h>
#include <string.h>

// This provides an exposition of the C++ struct-of-arrays library, soa.h.
// This represents an array of types as a multidimensional array of bytes: the
// outer index is the byte offset within the wrapped type, and the inner index
// is the array index. That is, all of the first bytes are stored, then all of
// the second bytes, etc. With some care, this allows using the absolute indexed
// addressing mode to access any byte of the array without pointer arithmetic.

void transparent_struct();

int main() {
  // This accepts any non-volatile, no alignment, trivial type with standard
  // layout (loosely, "plain old data").
  static soa::Array<char, 10> CharArray;

  // SoA array elements can be assigned to.
  CharArray[0] = 1;

  // An element is a wrapper type, soa::Ptr<T>, that can implicitly be coerced
  // to the wrapped type, T.
  char v = CharArray[0];
  printf("%d\n", v);
  printf("%d\n", CharArray[0] + 42);

  // When applicable, mutation operations are defined on the wrapper type in
  // terms of binary operations. For example, the following:
  CharArray[0] += 42;
  // Lowers to CharArray[0] = CharArray[0] + 42
  printf("%d\n", CharArray[0].get());

  // Using them in contexts where implicit coercion doesn't occur (e.g. printf)
  // requires .get()
  printf("%d\n", CharArray[0].get());

  // Arrays can be initialized as per usual; this occurs at compile time.
  static soa::Array<char, 10> InitializedArray = {1, 2};
  printf("%d\n", InitializedArray[0].get());
  printf("%d\n", InitializedArray[1].get());

  // Multi-byte types are stored strided by byte, i.e., the below type has all
  // 10 of the low bytes followed by all 10 of the high bytes. This is true for
  // any element type; the bytes are treated totally agnostically of what they
  // contain.
  static soa::Array<int, 10> IntArray;
  // The low byte will be at IntArray+1, and the high byte will be at
  // IntArray+11.
  IntArray[1] = 0x1234;
  printf("%x\n", IntArray[1].get());

  // By default, struct types can be accessed by a copy made through implicit
  // conversion or the arrow operator. This allows access and assignment as a
  // whole. The compiler may or may be able to optimize this away, but this
  // doesn't allow ergonomic mutation of individual fields.
  struct Struct {
    char c;
  };
  static soa::Array<Struct, 10> StructArray;
  StructArray[0] = {42};
  printf("%d\n", StructArray[0].get().c);
  printf("%d\n", StructArray[0]->c);
  // Won't compile: StructArray[0].c = 3;
  // Won't compile: StructArray[0]->c = 3;

  // See below for details on how to make struct types transparent.
  transparent_struct();

  // Array types are supported. Indices into contained arrays must
  // be compile-time constants; otherwise, the compiler will instantiate a
  // temporary array of pointers, one per array element, and index through that.
  static soa::Array<char[3], 10> CharArrayArray = {{45}};
  printf("%d\n", CharArrayArray[0][0].get());
  // At CharArrayArray + 2 * 10 + 1
  CharArrayArray[1][2] = 46;
  printf("%d\n", CharArrayArray[1][2].get());

  // Even multi-dimensional arrays work.
  static soa::Array<char[4][4], 10> CharMDArray;
  // At CharMDArray + ((2 * 4) + 3) * 10 + 1 (whew!)
  CharMDArray[1][2][3] = 47;
  // Note that the first index can still be variable, and this would still use
  // absolute indexed addressing. E.g., CharMDArray[x][2][3], but not
  // CharMDArray[2][x][3].
  printf("%d\n", CharMDArray[1][1][1].get());

  // Both indirection and the arrow operator are supported for pointer elements;
  // using these on the wrapper type forwards to the wrapped type.
  static soa::Array<Struct *, 10> PtrArray;
  Struct s = {48};
  PtrArray[0] = &s;
  printf("%d\n", (*PtrArray[0]).c);
  printf("%d\n", PtrArray[0]->c);

  // For non-pointer types, as previously mentioned, the arrow operator produces
  // a copy of the wrapped element; this allows calling const methods on the
  // type. Note that this produces a copy; the this pointer may be different on
  // each invocation.
  struct MemberFunctions {
    const MemberFunctions *whoami() const { return this; }
    char c() const { return 49; }
  };
  static soa::Array<MemberFunctions, 10> MemberFunctionsArray;
  printf("%p\n", MemberFunctionsArray[0]->whoami());
  printf("%p\n", MemberFunctionsArray[0]->whoami());
  printf("%d\n", MemberFunctionsArray[0]->c());

  // Call operators are forwarded to functors.
  struct Functor {
    char operator()(char x) const { return x; }
    char operator()(int x) const { return 2 * x; }
  };
  static soa::Array<Functor, 10> FunctorArray;
  // 5
  printf("%d\n", FunctorArray[0](static_cast<char>(5)));
  // 20
  printf("%d\n", FunctorArray[0](10));

  // Derived types work too, so long as they meet the other criteria.
  struct DerivedStruct : public MemberFunctions {
    char d() const { return 50; }
  };
  static soa::Array<DerivedStruct, 10> DerivedStructArray;
  printf("%d\n", DerivedStructArray[0]->c());
  printf("%d\n", DerivedStructArray[0]->d());

  return 0;
}

// The header <soa-struct.inc> can be used to provide access to the fields of
// a struct. This specializes soa::Ptr and provides member access to the
// fields as derived soa::Ptrs. The semantics of field access and mutation
// are thus the same as with elements of the array. This must be done at the top
// level.
struct TransparentStruct {
  char c, d;
};
#define SOA_STRUCT TransparentStruct
#define SOA_MEMBERS                                                            \
  MEMBER(c)                                                                    \
  MEMBER(d)
#include <soa-struct.inc>
// The previous defines are automatically #undef-ed by soa-struct.inc. This
// must be included once per type, and this must be done before the type is
// first used in a soa::Ptr.

// Unfortunately, derived structs do not automatically inherit the
// specialization for their parent.
struct DerivedTransparentStruct : public TransparentStruct {};
#define SOA_STRUCT DerivedTransparentStruct
#define SOA_MEMBERS                                                            \
  MEMBER(c)                                                                    \
  MEMBER(d)
#include <soa-struct.inc>

void transparent_struct() {
  static soa::Array<TransparentStruct, 10> TransparentStructArray;
  // Note that these are accessed through the dot operator; the arrow still
  // makes a copy of the struct, as before. The semantics are identical to array
  // element access; all of the operators described previously work on struct
  // members.
  TransparentStructArray[0].c = 43;
  TransparentStructArray[0].d = 43;
  ++TransparentStructArray[0].d;
  // The members are of type soa::Ptr<char>.
  printf("%d\n", TransparentStructArray[0].c.get());
  printf("%d\n", TransparentStructArray[0].d.get());

  static soa::Array<DerivedTransparentStruct, 10> DerivedTransparentStructArray;
  DerivedTransparentStructArray[0].c = 43;
  printf("%d\n", DerivedTransparentStructArray[0].c.get());
}
