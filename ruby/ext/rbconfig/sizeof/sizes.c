#include "ruby/ruby.h"

void
Init_sizeof(void)
{
    VALUE s = rb_hash_new();
    rb_define_const(rb_define_module("RbConfig"), "SIZEOF", s);

#define DEFINE(type, size) rb_hash_aset(s, rb_str_new_cstr(#type), INT2FIX(SIZEOF_##size))

#if SIZEOF_INT != 0
    DEFINE(int, INT);
#endif
#if SIZEOF_SHORT != 0
    DEFINE(short, SHORT);
#endif
#if SIZEOF_LONG != 0
    DEFINE(long, LONG);
#endif
#if SIZEOF_LONG_LONG != 0 && defined(HAVE_TRUE_LONG_LONG)
    DEFINE(long long, LONG_LONG);
#endif
#if SIZEOF___INT64 != 0
    DEFINE(__int64, __INT64);
#endif
#if SIZEOF_OFF_T != 0
    DEFINE(off_t, OFF_T);
#endif
#if SIZEOF_VOIDP != 0
    DEFINE(void*, VOIDP);
#endif
#if SIZEOF_FLOAT != 0
    DEFINE(float, FLOAT);
#endif
#if SIZEOF_DOUBLE != 0
    DEFINE(double, DOUBLE);
#endif
#if SIZEOF_TIME_T != 0
    DEFINE(time_t, TIME_T);
#endif
#if SIZEOF_CLOCK_T != 0
    DEFINE(clock_t, CLOCK_T);
#endif
#if SIZEOF_SIZE_T != 0
    DEFINE(size_t, SIZE_T);
#endif
#if SIZEOF_PTRDIFF_T != 0
    DEFINE(ptrdiff_t, PTRDIFF_T);
#endif
#if SIZEOF_INT8_T != 0
    DEFINE(int8_t, INT8_T);
#endif
#if SIZEOF_UINT8_T != 0
    DEFINE(uint8_t, UINT8_T);
#endif
#if SIZEOF_INT16_T != 0
    DEFINE(int16_t, INT16_T);
#endif
#if SIZEOF_UINT16_T != 0
    DEFINE(uint16_t, UINT16_T);
#endif
#if SIZEOF_INT32_T != 0
    DEFINE(int32_t, INT32_T);
#endif
#if SIZEOF_UINT32_T != 0
    DEFINE(uint32_t, UINT32_T);
#endif
#if SIZEOF_INT64_T != 0
    DEFINE(int64_t, INT64_T);
#endif
#if SIZEOF_UINT64_T != 0
    DEFINE(uint64_t, UINT64_T);
#endif
#if SIZEOF_INTPTR_T != 0
    DEFINE(intptr_t, INTPTR_T);
#endif
#if SIZEOF_UINTPTR_T != 0
    DEFINE(uintptr_t, UINTPTR_T);
#endif
#if SIZEOF_SSIZE_T != 0
    DEFINE(ssize_t, SSIZE_T);
#endif
#if SIZEOF_INT_LEAST8_T != 0
    DEFINE(int_least8_t, INT_LEAST8_T);
#endif
#if SIZEOF_INT_LEAST16_T != 0
    DEFINE(int_least16_t, INT_LEAST16_T);
#endif
#if SIZEOF_INT_LEAST32_T != 0
    DEFINE(int_least32_t, INT_LEAST32_T);
#endif
#if SIZEOF_INT_LEAST64_T != 0
    DEFINE(int_least64_t, INT_LEAST64_T);
#endif
#if SIZEOF_INT_FAST8_T != 0
    DEFINE(int_fast8_t, INT_FAST8_T);
#endif
#if SIZEOF_INT_FAST16_T != 0
    DEFINE(int_fast16_t, INT_FAST16_T);
#endif
#if SIZEOF_INT_FAST32_T != 0
    DEFINE(int_fast32_t, INT_FAST32_T);
#endif
#if SIZEOF_INT_FAST64_T != 0
    DEFINE(int_fast64_t, INT_FAST64_T);
#endif
#if SIZEOF_INTMAX_T != 0
    DEFINE(intmax_t, INTMAX_T);
#endif
#if SIZEOF_SIG_ATOMIC_T != 0
    DEFINE(sig_atomic_t, SIG_ATOMIC_T);
#endif
#if SIZEOF_WCHAR_T != 0
    DEFINE(wchar_t, WCHAR_T);
#endif
#if SIZEOF_WINT_T != 0
    DEFINE(wint_t, WINT_T);
#endif
#if SIZEOF_WCTRANS_T != 0
    DEFINE(wctrans_t, WCTRANS_T);
#endif
#if SIZEOF_WCTYPE_T != 0
    DEFINE(wctype_t, WCTYPE_T);
#endif
#if SIZEOF__BOOL != 0
    DEFINE(_Bool, _BOOL);
#endif
#if SIZEOF_LONG_DOUBLE != 0
    DEFINE(long double, LONG_DOUBLE);
#endif
#if SIZEOF_FLOAT__COMPLEX != 0
    DEFINE(float _Complex, FLOAT__COMPLEX);
#endif
#if SIZEOF_DOUBLE__COMPLEX != 0
    DEFINE(double _Complex, DOUBLE__COMPLEX);
#endif
#if SIZEOF_LONG_DOUBLE__COMPLEX != 0
    DEFINE(long double _Complex, LONG_DOUBLE__COMPLEX);
#endif
#if SIZEOF_FLOAT__IMAGINARY != 0
    DEFINE(float _Imaginary, FLOAT__IMAGINARY);
#endif
#if SIZEOF_DOUBLE__IMAGINARY != 0
    DEFINE(double _Imaginary, DOUBLE__IMAGINARY);
#endif
#if SIZEOF_LONG_DOUBLE__IMAGINARY != 0
    DEFINE(long double _Imaginary, LONG_DOUBLE__IMAGINARY);
#endif
#if SIZEOF___INT128 != 0
    DEFINE(__int128, __INT128);
#endif
#if SIZEOF___FLOAT128 != 0
    DEFINE(__float128, __FLOAT128);
#endif
#if SIZEOF__DECIMAL32 != 0
    DEFINE(_Decimal32, _DECIMAL32);
#endif
#if SIZEOF__DECIMAL64 != 0
    DEFINE(_Decimal64, _DECIMAL64);
#endif
#if SIZEOF__DECIMAL128 != 0
    DEFINE(_Decimal128, _DECIMAL128);
#endif
#if SIZEOF___M64 != 0
    DEFINE(__m64, __M64);
#endif
#if SIZEOF___M128 != 0
    DEFINE(__m128, __M128);
#endif
#if SIZEOF___FLOAT80 != 0
    DEFINE(__float80, __FLOAT80);
#endif

#undef DEFINE
}
