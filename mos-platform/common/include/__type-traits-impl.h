#ifndef __TYPE_TRAITS_IMPL_H__
#define __TYPE_TRAITS_IMPL_H__

// This implementation header factors out common type traits
// needed in multiple headers.
// Some portions of type_traits depend on cstddef, and
// Some portions of cstddef depend on type_traits.

namespace std {

template <class T, T v> struct integral_constant {
  static constexpr T value = v;
  using value_type = T;
  using type = integral_constant;
  constexpr operator value_type() const noexcept { return value; }
  constexpr value_type operator()() const noexcept { return value; }
};

template <class T>
struct is_integral : public integral_constant<bool, __is_integral(T)> {};

template <class T> inline constexpr bool is_integral_v = is_integral<T>::value;

template <bool B, class T = void> struct enable_if {};

template <class T> struct enable_if<true, T> {
  typedef T type;
};

template <bool B, class T = void>
using enable_if_t = typename enable_if<B, T>::type;

// Suppress deprecation notice for volatile-qualified return type resulting
// from volatile-qualified types _Tp.
template <class _Tp> _Tp &&__declval(int);
template <class _Tp> _Tp __declval(long);

template <class _Tp> decltype(__declval<_Tp>(0)) declval() noexcept;

} // namespace std

#endif //__TYPE_TRAITS_IMPL_H__
