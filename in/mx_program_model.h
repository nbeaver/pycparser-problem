/*
 * Name:    mx_program_model.h
 *
 * Purpose: Describes the native programming model for the current platform.
 *
 * Author:  William Lavender
 *
 *-------------------------------------------------------------------------
 *
 * Copyright 2006-2008, 2011-2012, 2014 Illinois Institute of Technology
 *
 * See the file "LICENSE" for information on usage and redistribution
 * of this file, and for a DISCLAIMER OF ALL WARRANTIES.
 *
 */

#ifndef __MX_PROGRAM_MODEL_H__
#define __MX_PROGRAM_MODEL_H__

#include "mx_private_version.h"

/* See http://www.unix.org/version2/whatsnew/lp64_wp.html for a discussion
 * of the various programming models.  In 2006, the most common programming
 * models are:
 *
 *     ILP32 for most 32-bit systems
 *     LP64  for most 64-bit Unix-like systems
 *     LLP64 for Win64 systems
 *
 * Of the others, LP32 was the programming model for Win16, while ILP64 is
 * apparently used by 64-bit Cray systems.
 */

#define MX_PROGRAM_MODEL_LP32   0x10  /* int=16, long=32, ptr=32 */

#define MX_PROGRAM_MODEL_ILP32  0x20  /* int=32, long=32, ptr=32 */
#define MX_PROGRAM_MODEL_LLP64  0x24  /* int=32, long=32, ptr=64, long long=64*/

#define MX_PROGRAM_MODEL_LP64   0x40  /* int=32, long=64, ptr=64 */
#define MX_PROGRAM_MODEL_ILP64  0x41  /* int=64, long=64, ptr=64 */

#define MX_PROGRAM_MODEL_UNKNOWN  0x80000000

/*---*/

/***** Determine the native programming model. *****/

#include <limits.h>

#if defined(OS_WIN32)

#  if defined(_WIN64)
#     define MX_PROGRAM_MODEL    MX_PROGRAM_MODEL_LLP64
#  else
#     define MX_PROGRAM_MODEL    MX_PROGRAM_MODEL_ILP32
#  endif

#elif defined(OS_SOLARIS)

#  include <sys/types.h>

#  if defined(_ILP32)
#     define MX_PROGRAM_MODEL    MX_PROGRAM_MODEL_ILP32

#  elif defined(_LP64)
#     define MX_PROGRAM_MODEL    MX_PROGRAM_MODEL_LP64
#  else
#     error "Neither _ILP32 nor _LP64 are defined for Solaris!"
#  endif

#elif defined(OS_IRIX)

#  if (_MIPS_SZLONG == 32)
#     define MX_PROGRAM_MODEL    MX_PROGRAM_MODEL_ILP32

#  elif (_MIPS_SZLONG == 64)
#     define MX_PROGRAM_MODEL    MX_PROGRAM_MODEL_LP64
#  else
#     error "Unexpected value for _MIPS_SZLONG"
#  endif

#elif defined(OS_HPUX)

#  if defined(__LP64__)
#     define MX_PROGRAM_MODEL    MX_PROGRAM_MODEL_LP64
#  else
#     define MX_PROGRAM_MODEL    MX_PROGRAM_MODEL_ILP32
#  endif

#elif defined(OS_VMS)

#  if defined(__VAX)
#     define MX_PROGRAM_MODEL    MX_PROGRAM_MODEL_ILP32
#  else
#     define MX_PROGRAM_MODEL    MX_PROGRAM_MODEL_LP64
#  endif

#elif defined(__GNUC__) && ( MX_GNUC_VERSION >= 3004000L )

   /* GCC 3.4 and above define the __LP64__ and _LP64 macros on all
    * 64-bit platforms.  This was not true for GCC 3.3 and before.
    *
    * This is stated in the "Porting to 64 bit" paper presented at
    * the 2003 GCC Developers Summit and can be found at page 107 of
    * http://www.linux.org.uk/~ajh/gcc/gccsummit-2003-proceedings.pdf
    * or as a separate PDF document at
    * http://gcc.fyxm.net/summit/2003/Porting%20to%2064%20bit.pdf
    */

#  if defined(__LP64__)
#     define MX_PROGRAM_MODEL    MX_PROGRAM_MODEL_LP64
#  else
#     define MX_PROGRAM_MODEL    MX_PROGRAM_MODEL_ILP32
#  endif

   /* Jim Fait has suggested looking for the equality of __LONG_MAX__
    * to either __INT_MAX__ or __LONG_LONG_MAX__ to test for a 64-bit
    * wordsize on other systems.  This possibility has not yet been
    * investigated.
    */

#else
   /* All other cases. */

   /* WARNING: The test using ULONG_MAX is not foolproof.  When porting to
   * a new platform, you must verify that this check does the right thing.
   */

#  if ( ULONG_MAX == 4294967295U )
#     define MX_PROGRAM_MODEL    MX_PROGRAM_MODEL_ILP32
#  else
#     define MX_PROGRAM_MODEL    MX_PROGRAM_MODEL_LP64
#  endif
#endif

#if ( MX_PROGRAM_MODEL == MX_PROGRAM_MODEL_LLP64 )
#  define MX_WORDSIZE		32
#  define MX_POINTER_SIZE	64
#else
#  define MX_WORDSIZE		( MX_PROGRAM_MODEL & ~0xf )
#  define MX_POINTER_SIZE	MX_WORDSIZE
#endif

#endif /* __MX_PROGRAM_MODEL_H__ */

