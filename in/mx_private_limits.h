/*
 * Name:     mx_private_limits.h
 *
 * Purpose:  This header file defines the minimum and maximum values of
 *           the fixed-width C99 datatypes.  This header file is meant
 *           to be included by either mx_stdint.h or mx_inttypes.h and
 *           should not be included directly.
 *
 * Author:   William Lavender
 *
 *---------------------------------------------------------------------------
 *
 * Copyright 2006-2007, 2011 Illinois Institute of Technology
 *
 * See the file "LICENSE" for information on usage and redistribution
 * of this file, and for a DISCLAIMER OF ALL WARRANTIES.
 *
 */

#ifndef __MX_PRIVATE_LIMITS__
#define __MX_PRIVATE_LIMITS__

#include "mx_program_model.h"	/* We get the native word size from here. */

/* C99 states that these macros should only be defined in C++ if they
 * are specifically requested.
 */

#if ( !defined(__cplusplus) || defined(__STDC_LIMIT_MACROS) ) \
	&& !defined(__MX_MAKEDEPEND__)

   /* WARNING: The following assumes twos complement integer arithmetic. */

#  if MX_WORDSIZE == 64
#     define __INT64_C(c)	c ## L
#     define __UINT64_C(c)	c ## UL
#  else
#     define __INT64_C(c)	c ## LL
#     define __UINT64_C(c)	c ## ULL
#  endif

#  define INT8_MIN		(-128)
#  define INT16_MIN		(-32768)
#  define INT32_MIN		(-2147483648)
#  define INT64_MIN		(-__INT64_C(9223372036854775807)-1)

#  define INT8_MAX		(127)
#  define INT16_MAX		(32767)
#  define INT32_MAX		(2147483647)
#  define INT64_MAX		(__INT64_C(9223372036854775807))

#  define UINT8_MAX		(255)
#  define UINT16_MAX		(65535)
#  define UINT32_MAX		(4294967295U)
#  define UINT64_MAX		(__UINT64_C(18446744073709551615))

#  if MX_WORDSIZE == 64
#     define INTPTR_MIN		INT64_MIN
#     define INTPTR_MAX		INT64_MAX
#     define UINTPTR_MAX	UINT64_MAX
#  else
#     define INTPTR_MIN		INT32_MIN
#     define INTPTR_MAX		INT32_MAX
#     define UINTPTR_MAX	UINT32_MAX
#  endif

#  define INTMAX_MIN		INT64_MIN
#  define INTMAX_MAX		INT64_MAX
#  define UINTMAX_MAX	UINT64_MAX

#endif

#endif /* __MX_PRIVATE_LIMITS__ */
