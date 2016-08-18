/*
 * Name:    mx_stdint.h
 *
 * Purpose: This header file declares sets of integer types having
 *          specified widths using the names from the <stdint.h>
 *          header file of the C99 standard.
 *
 * Author:  William Lavender
 *
 *---------------------------------------------------------------------------
 *
 * Copyright 2006-2007, 2009-2010, 2012-2016 Illinois Institute of Technology
 *
 * See the file "LICENSE" for information on usage and redistribution
 * of this file, and for a DISCLAIMER OF ALL WARRANTIES.
 *
 */

#ifndef __MX_STDINT_H__
#define __MX_STDINT_H__

#include "mx_program_model.h"	/* We get the native word size from here. */

/* The non-standard build targets are listed first. */

/*=======================================================================*/
#if defined(OS_WIN32) && (defined(_MSC_VER) || defined(__BORLANDC__))

typedef __int8			int8_t;
typedef __int16			int16_t;
typedef __int32			int32_t;
typedef __int64			int64_t;

typedef unsigned __int8		uint8_t;
typedef unsigned __int16	uint16_t;
typedef unsigned __int32	uint32_t;
typedef unsigned __int64	uint64_t;

typedef int64_t			intmax_t;
typedef uint64_t		uintmax_t;

#include <stddef.h>	/* For ptrdiff_t, intptr_t, and friends. */

#  if defined(_MSC_VER) && (_MSC_VER < 1300)
     typedef __int32		intptr_t;
     typedef unsigned __int32	uintptr_t;

#  elif defined(__BORLANDC__)
     typedef __int32		intptr_t;
     typedef unsigned __int32	uintptr_t;
#  endif

/* Note: In some places, i64 and ui64 are suggested instead of LL and ULL
 * for Visual C++.  I stick with LL and ULL since that is what is used
 * on other build targets.
 *
 * Note (2012-07-02):
 * It turns out that Visual C++ 6 supports i64 and ui64, but not LL and ULL.
 * For that reason, we switch to using i64 and ui64 in the following macros.
 */

#  if ( defined(_MSC_VER) || defined(__BORLANDC__) )

#     if defined(INT64_C)
#        undef(INT64_C)
#     endif
#     define INT64_C(x)		x ## i64

#     if defined(UINT64_C)
#        undef(UINT64_C)
#     endif
#     define UINT64_C(x)	x ## ui64

#  endif   /* _MSC_VER */

/*=======================================================================*/
#elif defined(OS_VXWORKS)

#  include <types/vxTypes.h>

#  if ( MX_WORDSIZE == 64 )
typedef long			int64_t;
typedef unsigned long		uint64_t;
#  define INT64_C(c)		c ## L
#  define UINT64_C(c)		c ## UL
#  else
typedef long long		int64_t;
typedef unsigned long long	uint64_t;
#  define INT64_C(c)		c ## LL
#  define UINT64_C(c)		c ## ULL
#  endif

typedef int64_t			intmax_t;
typedef uint64_t		uintmax_t;

/*=======================================================================*/
#elif defined(OS_ECOS)

#include <machine/types.h>

/*=======================================================================*/
#elif defined(OS_SOLARIS) || defined(OS_IRIX) || defined(OS_HPUX) \
	|| defined(OS_VMS) || defined(OS_TRU64)

   /* Some build targets do not have <stdint.h>, but have the same
    * information available in <inttypes.h>.
    */

#  include <inttypes.h>

#  if defined(OS_VMS) && defined(__VAX)

      /* OpenVMS on Vax does not really have a 64-bit integer type, even
       * though it provides a broken definition for int64_t and uint64_t.
       * The following sleight of hand allows MX to compile on the Vax,
       * but does not constitute real 64-bit support.
       */

      typedef int32_t   mx_vax_int64_t;    /* This is, of course, bogus. */
      typedef uint32_t  mx_vax_uint64_t;

#     define int64_t    mx_vax_int64_t
#     define uint64_t   mx_vax_uint64_t
#  endif

/*=======================================================================*/
#elif defined(OS_LINUX)

#  if ( defined(MX_GLIBC_VERSION) && (MX_GLIBC_VERSION < 2001000L) )

      /* For very old Linux distributions, we must code this by hand. */

#     if ( MX_PROGRAM_MODEL == MX_PROGRAM_MODEL_LP64 )

      typedef char                 int8_t;
      typedef short                int16_t;
      typedef int                  int32_t;
      typedef long                 int64_t;

      typedef unsigned char        int8_t;
      typedef unsigned short       int16_t;
      typedef unsigned int         int32_t;
      typedef unsigned long        int64_t;

      typedef int32_t              intmax_t;
      typedef uint32_t             uintmax_t;

#     else

      typedef char                 int8_t;
      typedef short                int16_t;
      typedef int                  int32_t;
      typedef long long            int64_t;

      typedef unsigned char        int8_t;
      typedef unsigned short       int16_t;
      typedef unsigned int         int32_t;
      typedef unsigned long long   int64_t;

      typedef int32_t              intmax_t;
      typedef uint32_t             uintmax_t;

#     endif

#  else
#    include <stdint.h>
#  endif

/*=======================================================================*/
#elif defined(OS_UNIXWARE)

   /* UnixWare defines int32_t and friends in <sys/types.h> */

   /* However, it does not define INT64_C() and UINT64_C(). */

#  if ( MX_WORDSIZE == 64 )
#  define INT64_C(c)		c ## L
#  define UINT64_C(c)		c ## UL
#  else
#  define INT64_C(c)		c ## LL
#  define UINT64_C(c)		c ## ULL
#  endif

#include <sys/types.h>

/*=======================================================================*/
#else
   /* Most build targets should be able to use a vendor provided <stdint.h>. */

#  include <stdint.h>

#endif

/*=======================================================================*/

/* Typedef some special integer data types. */

typedef int32_t   mx_bool_type;

/*=======================================================================*/

/* Define limit macros if they have not yet been defined.  We assume that
 * they are not yet defined if INT32_MIN does not exist.
 */

#if !defined(INT32_MIN) && !defined(OS_HPUX)

#  include "mx_private_limits.h"

#endif

#endif /* __MX_STDINT_H__ */
