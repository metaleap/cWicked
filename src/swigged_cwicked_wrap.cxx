/* ----------------------------------------------------------------------------
 * This file was automatically generated by SWIG (https://www.swig.org).
 * Version 4.3.0
 *
 * Do not make changes to this file unless you know what you are doing - modify
 * the SWIG interface file instead.
 * ----------------------------------------------------------------------------- */


#define SWIG_VERSION 0x040300
#define SWIGC
/* -----------------------------------------------------------------------------
 *  This section contains generic SWIG labels for method/variable
 *  declarations/attributes, and other compiler dependent labels.
 * ----------------------------------------------------------------------------- */

/* template workaround for compilers that cannot correctly implement the C++ standard */
#ifndef SWIGTEMPLATEDISAMBIGUATOR
# if defined(__SUNPRO_CC) && (__SUNPRO_CC <= 0x560)
#  define SWIGTEMPLATEDISAMBIGUATOR template
# elif defined(__HP_aCC)
/* Needed even with `aCC -AA' when `aCC -V' reports HP ANSI C++ B3910B A.03.55 */
/* If we find a maximum version that requires this, the test would be __HP_aCC <= 35500 for A.03.55 */
#  define SWIGTEMPLATEDISAMBIGUATOR template
# else
#  define SWIGTEMPLATEDISAMBIGUATOR
# endif
#endif

/* inline attribute */
#ifndef SWIGINLINE
# if defined(__cplusplus) || (defined(__GNUC__) && !defined(__STRICT_ANSI__))
#   define SWIGINLINE inline
# else
#   define SWIGINLINE
# endif
#endif

/* attribute recognised by some compilers to avoid 'unused' warnings */
#ifndef SWIGUNUSED
# if defined(__GNUC__)
#   if !(defined(__cplusplus)) || (__GNUC__ > 3 || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4))
#     define SWIGUNUSED __attribute__ ((__unused__))
#   else
#     define SWIGUNUSED
#   endif
# elif defined(__ICC)
#   define SWIGUNUSED __attribute__ ((__unused__))
# else
#   define SWIGUNUSED
# endif
#endif

#ifndef SWIG_MSC_UNSUPPRESS_4505
# if defined(_MSC_VER)
#   pragma warning(disable : 4505) /* unreferenced local function has been removed */
# endif
#endif

#ifndef SWIGUNUSEDPARM
# ifdef __cplusplus
#   define SWIGUNUSEDPARM(p)
# else
#   define SWIGUNUSEDPARM(p) p SWIGUNUSED
# endif
#endif

/* internal SWIG method */
#ifndef SWIGINTERN
# define SWIGINTERN static SWIGUNUSED
#endif

/* internal inline SWIG method */
#ifndef SWIGINTERNINLINE
# define SWIGINTERNINLINE SWIGINTERN SWIGINLINE
#endif

/* exporting methods */
#if defined(__GNUC__)
#  if (__GNUC__ >= 4) || (__GNUC__ == 3 && __GNUC_MINOR__ >= 4)
#    ifndef GCC_HASCLASSVISIBILITY
#      define GCC_HASCLASSVISIBILITY
#    endif
#  endif
#endif

#ifndef SWIGEXPORT
# if defined(_WIN32) || defined(__WIN32__) || defined(__CYGWIN__)
#   if defined(STATIC_LINKED)
#     define SWIGEXPORT
#   else
#     define SWIGEXPORT __declspec(dllexport)
#   endif
# else
#   if defined(__GNUC__) && defined(GCC_HASCLASSVISIBILITY)
#     define SWIGEXPORT __attribute__ ((visibility("default")))
#   else
#     define SWIGEXPORT
#   endif
# endif
#endif

/* calling conventions for Windows */
#ifndef SWIGSTDCALL
# if defined(_WIN32) || defined(__WIN32__) || defined(__CYGWIN__)
#   define SWIGSTDCALL __stdcall
# else
#   define SWIGSTDCALL
# endif
#endif

/* Deal with Microsoft's attempt at deprecating C standard runtime functions */
#if !defined(SWIG_NO_CRT_SECURE_NO_DEPRECATE) && defined(_MSC_VER) && !defined(_CRT_SECURE_NO_DEPRECATE)
# define _CRT_SECURE_NO_DEPRECATE
#endif

/* Deal with Microsoft's attempt at deprecating methods in the standard C++ library */
#if !defined(SWIG_NO_SCL_SECURE_NO_DEPRECATE) && defined(_MSC_VER) && !defined(_SCL_SECURE_NO_DEPRECATE)
# define _SCL_SECURE_NO_DEPRECATE
#endif

/* Deal with Apple's deprecated 'AssertMacros.h' from Carbon-framework */
#if defined(__APPLE__) && !defined(__ASSERT_MACROS_DEFINE_VERSIONS_WITHOUT_UNDERSCORES)
# define __ASSERT_MACROS_DEFINE_VERSIONS_WITHOUT_UNDERSCORES 0
#endif

/* Intel's compiler complains if a variable which was never initialised is
 * cast to void, which is a common idiom which we use to indicate that we
 * are aware a variable isn't used.  So we just silence that warning.
 * See: https://github.com/swig/swig/issues/192 for more discussion.
 */
#ifdef __INTEL_COMPILER
# pragma warning disable 592
#endif

#if defined(__cplusplus) && __cplusplus >=201103L
# define SWIG_NULLPTR nullptr
#else
# define SWIG_NULLPTR NULL
#endif 

/* -----------------------------------------------------------------------------
 * swigcompat.swg
 *
 * Macros to provide support compatibility with older C and C++ standards.
 *
 * Note that SWIG expects __cplusplus to be defined to the appropriate C++ standard.
 * MSVC users are urged to check and examine the /Zc:__cplusplus compiler option.
 * See https://learn.microsoft.com/en-us/cpp/build/reference/zc-cplusplus.
 * ----------------------------------------------------------------------------- */

/* C99 and C++11 should provide snprintf, but define SWIG_NO_SNPRINTF
 * if you're missing it.
 */
#if ((defined __STDC_VERSION__ && __STDC_VERSION__ >= 199901L) || \
     (defined __cplusplus && __cplusplus >= 201103L) || \
     defined SWIG_HAVE_SNPRINTF) && \
    !defined SWIG_NO_SNPRINTF
# define SWIG_snprintf(O,S,F,A) snprintf(O,S,F,A)
# define SWIG_snprintf2(O,S,F,A,B) snprintf(O,S,F,A,B)
#else
/* Fallback versions ignore the buffer size, but most of our uses either have a
 * fixed maximum possible size or dynamically allocate a buffer that's large
 * enough.
 */
# define SWIG_snprintf(O,S,F,A) sprintf(O,F,A)
# define SWIG_snprintf2(O,S,F,A,B) sprintf(O,F,A,B)
#endif

/* -----------------------------------------------------------------------------
 * clabels.swg
 *
 * Definitions of C specific preprocessor symbols.
 * ----------------------------------------------------------------------------- */

// this is used instead of default SWIGEXPORT symbol

#ifndef SWIGEXPORTC
# if defined(_WIN32) || defined(__WIN32__) || defined(__CYGWIN__)
#   if defined(STATIC_LINKED)
#     define SWIGEXPORTC
#   else
#     define SWIGEXPORTC __declspec(dllexport)
#   endif
# else
#   if defined(__GNUC__) && defined(GCC_HASCLASSVISIBILITY)
#     define SWIGEXPORTC __attribute__ ((visibility("default")))
#   else
#     define SWIGEXPORTC
#   endif
# endif
#endif


#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <setjmp.h>

#define SWIG_contract_assert(expr, msg) if(!(expr)) { printf("%s\n", msg); SWIG_exit(0); } else


typedef struct SwigObj SwigObj;


#ifndef SWIG_exception
#define SWIG_exception(code, msg)
#endif


#ifdef __cplusplus
extern "C" {
#endif
SWIGEXPORTC int SWIG_exit(int code) { exit(code); }
#ifdef __cplusplus
}
#endif


#ifdef __cplusplus
#include <utility>
/* SwigValueWrapper is described in swig.swg */
template<typename T> class SwigValueWrapper {
  struct SwigSmartPointer {
    T *ptr;
    SwigSmartPointer(T *p) : ptr(p) { }
    ~SwigSmartPointer() { delete ptr; }
    SwigSmartPointer& operator=(SwigSmartPointer& rhs) { T* oldptr = ptr; ptr = 0; delete oldptr; ptr = rhs.ptr; rhs.ptr = 0; return *this; }
    void reset(T *p) { T* oldptr = ptr; ptr = 0; delete oldptr; ptr = p; }
  } pointer;
  SwigValueWrapper& operator=(const SwigValueWrapper<T>& rhs);
  SwigValueWrapper(const SwigValueWrapper<T>& rhs);
public:
  SwigValueWrapper() : pointer(0) { }
  SwigValueWrapper& operator=(const T& t) { SwigSmartPointer tmp(new T(t)); pointer = tmp; return *this; }
#if __cplusplus >=201103L
  SwigValueWrapper& operator=(T&& t) { SwigSmartPointer tmp(new T(std::move(t))); pointer = tmp; return *this; }
  operator T&&() const { return std::move(*pointer.ptr); }
#else
  operator T&() const { return *pointer.ptr; }
#endif
  T *operator&() const { return pointer.ptr; }
  static void reset(SwigValueWrapper& t, T *p) { t.pointer.reset(p); }
};

/*
 * SwigValueInit() is a generic initialisation solution as the following approach:
 * 
 *       T c_result = T();
 * 
 * doesn't compile for all types for example:
 * 
 *       unsigned int c_result = unsigned int();
 */
template <typename T> T SwigValueInit() {
  return T();
}

#if __cplusplus >=201103L
# define SWIG_STD_MOVE(OBJ) std::move(OBJ)
#else
# define SWIG_STD_MOVE(OBJ) OBJ
#endif

#endif


#include "../pch/wi_pch.h"

#ifdef __cplusplus
extern "C" {
#endif

SWIGEXPORTC void wi_Application_Initialize(SwigObj* carg1) {
  wi::Application *arg1 = (wi::Application *) 0 ;
  
  arg1 = (wi::Application *) carg1;
  (arg1)->Initialize();
}


SWIGEXPORTC SwigObj* wi_Application_new() {
  wi::Application *cppresult;
  SwigObj* result;
  
  cppresult = (wi::Application *)new wi::Application();
  result = (SwigObj*) cppresult;
  return result;
}


SWIGEXPORTC void wi_Application_delete(SwigObj* carg1) {
  wi::Application *arg1 = (wi::Application *) 0 ;
  
  arg1 = (wi::Application *) carg1;
  delete arg1;
}


SWIGEXPORTC void wi_arguments_Parse(int carg1, char ** carg2) {
  int arg1 ;
  char **arg2 = (char **) (char **)0 ;
  
  arg1 = (int) carg1;
  arg2 = (char * *) carg2;
  wi::arguments::Parse(arg1,arg2);
}


#ifdef __cplusplus
}
#endif

