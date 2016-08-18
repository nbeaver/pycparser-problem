/*
 * Name:    mx_poison.h
 *
 * Purpose: Enforce prohibition of unsafe functions.
 *
 *          Some classic runtime functions such as gets() and strcpy() are
 *          prohibited from being used in MX programs, since they are
 *          unsafe to use.  You can enforce this prohibition by including
 *          this header file.  The list of prohibited functions can be
 *          found below.
 *
 *          Unfortunately, poisoning a function name prohibits its use as
 *          a variable name as well.  At present, there is no way around
 *          this.  However, I regard it as a small price to pay.  If you
 *          need to suppress poisoning for a given file, define the macro
 *          MX_NO_POISON before including this header file.  If you are
 *          having problems with an external package's header files, just
 *          include "mx_poison.h" _after_ including the external package
 *          header file.
 *
 *          Poisoning is implemented for GCC 3.0 and after as well as
 *          Microsoft Visual C++.
 *
 * Author:  William Lavender
 *
 *---------------------------------------------------------------------------
 *
 * Copyright 2006-2007, 2016 Illinois Institute of Technology
 *
 * See the file "LICENSE" for information on usage and redistribution
 * of this file, and for a DISCLAIMER OF ALL WARRANTIES.
 *
 */

#ifndef __MX_POISON_H__
#define __MX_POISON_H__

#ifndef MX_NO_POISON	/* Suppress poisoning if MX_NO_POISON is defined. */

/*-----------------------------------------------------------------------*/

/* For Microsoft Visual C++, we mark functions we want to poison
 * as deprecated.  This generates a warning that will abort the
 * MX compilation process.
 */

#if defined(OS_WIN32) && defined(_MSC_VER) && (_MSC_VER >= 1300)

#pragma deprecated( gets, sprintf, vsprintf )
#pragma deprecated( strcpy, strncpy, strcat, strncat, strtok )

#endif

/*-----------------------------------------------------------------------*/

/* Poisoning is available for GCC version 3 or later.  However, we do not
 * turn it on for MinGW running on Windows, since MinGW's headers use lots
 * of functions that would otherwise trigger poisoning.
 */

#if (__GNUC__ >= 3) && !defined(OS_WIN32)

#ifdef gets
#  undef gets
#endif
#pragma GCC poison gets

#ifdef sprintf
#  undef sprintf
#endif
#pragma GCC poison sprintf

#ifdef vsprintf
#  undef vsprintf
#endif
#pragma GCC poison vsprintf

#ifdef strcpy
#  undef strcpy
#endif
#pragma GCC poison strcpy

#ifdef strncpy
#  undef strncpy
#endif
#pragma GCC poison strncpy

#ifdef strcat
#  undef strcat
#endif
#pragma GCC poison strcat

#ifdef strncat
#  undef strncat
#endif
#pragma GCC poison strncat

#ifdef strtok
#  undef strtok
#endif
#pragma GCC poison strtok

#endif /* (__GNUC__ >= 3) */


#endif /* MX_NO_POISON */

#endif /* __MX_POISON_H__ */

