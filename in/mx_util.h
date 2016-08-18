/*
 * Name:    mx_util.h
 *
 * Purpose: Define utility functions and generally used symbols.
 *
 * Author:  William Lavender
 *
 *---------------------------------------------------------------------
 *
 * Copyright 1999-2016 Illinois Institute of Technology
 *
 * See the file "LICENSE" for information on usage and redistribution
 * of this file, and for a DISCLAIMER OF ALL WARRANTIES.
 *
 */

#ifndef __MX_UTIL_H__
#define __MX_UTIL_H__

#include "mx_private_version.h"

#include <string.h>	/* We get 'size_t' from here. */
#include <stdarg.h>	/* We get 'va_list' from here. */

/*-----*/

#include <time.h>	/* We usually get 'struct timespec' from here. */

#if defined( OS_BSD )
#include <sys/time.h>	/* Sometimes we get 'struct timespec' from here. */
#endif

#if defined( OS_DJGPP )
#include <sys/wtime.h>	/* Sometimes we get 'struct timespec' from here. */
#endif

/*-----*/

/* Some build targets do not define 'struct timespec' in a header file.
 * We need to check for these special cases.  How annoying.
 */

#if defined( OS_WIN32 )
#   if defined( _MSC_VER )
#      if (_MSC_VER < 1900)
#         define __MX_NEED_TIMESPEC  1
#      else
#         define __MX_NEED_TIMESPEC  0
#      endif
#   elif defined( __GNUC__ )
#      if defined(_TIMESPEC_DEFINED)
#         define __MX_NEED_TIMESPEC  0
#      else
#         define __MX_NEED_TIMESPEC  1
#      endif
#   else
#      define __MX_NEED_TIMESPEC  1
#   endif

#elif defined( OS_VMS )
#   if (__VMS_VER < 80000000)
#      define __MX_NEED_TIMESPEC  1
#   else
#      define __MX_NEED_TIMESPEC  0
#   endif

#else
#   define __MX_NEED_TIMESPEC  0
#endif

/*-----*/

#if __MX_NEED_TIMESPEC

/* If we need to define 'struct timespec' ourselves, then we
 * include a C++ safe declaration below.
 */

#ifdef __cplusplus
extern "C" {
#endif

struct timespec {
	time_t tv_sec;	  /* seconds */
	long   tv_nsec;   /* nanoseconds */
};

#ifdef __cplusplus
}
#endif

#endif /* __MX_NEED_TIMESPEC */

/*-----*/

#ifdef __MX_NEED_TIMESPEC
#   undef __MX_NEED_TIMESPEC
#endif

/*-----*/

/* Prohibit MX code from using poisoned C runtime functions.
 *
 * This only applies to MX-supplied programs and libraries.
 * It is not imposed on third-party programs or on programs
 * that define MX_NO_POISON.
 */

#if !defined(MX_NO_POISON)
#  if defined(__MX_LIBRARY__) || defined(__MX_APP__)
#    include "mx_poison.h"
#  endif
#endif

/*-----*/

/*
 * Macros for declaring shared library or DLL functions.
 *
 * The MX_API and MX_EXPORT macros are used for the declaration of functions
 * in shared libraries or DLLs.  They must be used by publically visible
 * functions in a shared library or DLL and must _not_ be used by functions
 * that are not in a shared library or DLL.
 *
 * MX_API and MX_EXPORT are similar but not the same.  MX_API is used only
 * in header files (.h files), while MX_EXPORT is used only in .c files
 * where the body of the function appears.
 */

#if defined(OS_WIN32)
#   if defined(__GNUC__)	/* MinGW */
#      if defined(__MX_LIBRARY__)
#         define MX_API		__attribute__ ((dllexport))
#         define MX_EXPORT	__attribute__ ((dllexport))
#      else
#         define MX_API		__attribute__ ((dllimport))
#         define MX_EXPORT	__ERROR_ONLY_USE_THIS_IN_LIBRARIES__
#      endif
#   else
#      if defined(__MX_LIBRARY__)
#         define MX_API		_declspec(dllexport)
#         define MX_EXPORT	_declspec(dllexport)
#      else
#         define MX_API		_declspec(dllimport)
#         define MX_EXPORT	__ERROR_ONLY_USE_THIS_IN_LIBRARIES__
#      endif
#   endif

#elif defined(OS_VMS)
#      define MX_API		extern
#      define MX_EXPORT

#else
#   if defined(__MX_LIBRARY__)
#      define MX_API		extern
#      define MX_EXPORT
#   else
#      define MX_API		extern
#      define MX_EXPORT	__ERROR_ONLY_USE_THIS_IN_LIBRARIES__
#   endif
#endif

/*
 * The MX_API_PRIVATE macro is used to indicate functions that may be exported
 * by the MX library, but which are not intended to be used by general
 * application programs.  At present, it is just an alias for MX_API, but
 * this may change later.
 */

#define MX_API_PRIVATE		MX_API

/*-----*/

#if defined(OS_WIN32)
#   define MX_STDCALL	__stdcall
#else
#   define MX_STDCALL
#endif

/*------------------------------------------------------------------------*/

#if (_MSC_VER >= 1400)		/* Visual C++ 2005 Express and above. */

   /* FIXME: The following statement disables Visual C++ warning messages
    *        about deprecated functions.  Someday we should rewrite the
    *        code so that we no longer need this.
    */

#  pragma warning( disable:4996 )
#endif

/*------------------------------------------------------------------------*/

/*
 * Solaris 2 defines SIG_DFL, SIG_ERR, SIG_IGN, and SIG_HOLD in a way
 * such that GCC on Solaris 2 generates a warning about a function
 * definition being an invalid prototype.
 */

#if defined( OS_SOLARIS ) && defined( __GNUC__ )

# ifdef SIG_DFL
#   undef SIG_DFL
# endif

# ifdef SIG_ERR
#   undef SIG_ERR
# endif

# ifdef SIG_IGN
#   undef SIG_IGN
# endif

# ifdef SIG_HOLD
#   undef SIG_HOLD
# endif

#define SIG_DFL  (void(*)(int))0
#define SIG_ERR  (void(*)(int))-1
#define SIG_IGN  (void(*)(int))1
#define SIG_HOLD (void(*)(int))2

#endif /* OS_SOLARIS && __GNUC__ */

/*------------------------------------------------------------------------*/

#if defined( OS_DJGPP )

   /* Prevent Watt-32 from making its own definitions of int16_t and int32_t. */

#  define HAVE_INT16_T
#  define HAVE_INT32_T

   /* This has to appear before we include <sys/param.h> below, which
    * includes <sys/swap.h>, which requires these prototypes to exist.
    * They are also used by the mx_socket.h header file.
    */
   extern __inline__ unsigned long  __ntohl( unsigned long );
   extern __inline__ unsigned short __ntohs( unsigned short );

#endif /* OS_DJGPP */

#if defined( OS_WIN32 )
#  include <stdlib.h>
#  define MXU_FILENAME_LENGTH		_MAX_PATH

#elif defined( OS_VXWORKS )
#  include <limits.h>
#  define MXU_FILENAME_LENGTH		PATH_MAX

#elif defined( OS_ECOS ) || defined( OS_HURD )
#  include <limits.h>
#  define MXU_FILENAME_LENGTH		_POSIX_PATH_MAX

#elif defined( OS_VMS )
#  define MXU_FILENAME_LENGTH		255	/* According to comp.os.vms */

#else
#  include <sys/param.h>
#  if defined( MAXPATHLEN )
#     define MXU_FILENAME_LENGTH	MAXPATHLEN
#  else
#     error Maximum path length not yet defined for this platform.
#  endif
#endif

/*------------------------------------------------------------------------*/

#if defined( __GNUC__)
#  define MXW_UNUSED( x ) \
	(void) (x)
#elif 0
#  define MXW_UNUSED( x ) \
	do { (x) = (x); } while(0)
#else
#  define MXW_UNUSED( x )
#endif

/*------------------------------------------------------------------------*/

/*
 * Some compilers will emit a warning message if they find a statement
 * that can never be reached.  For some other compilers, they will emit
 * a warning if a statement is _not_ placed at the unreachable location.
 * An example of this is a while(1) loop that can never be broken out of 
 * with a return statement following it.
 *
 * The MXW_NOT_REACHED() was created to handle this situation.
 *
 * Note for Solaris:
 *   In principle, for the Sun Studio or Solaris Studio compiler you could
 *   bracket the not reached line with something like this
 *
 *   #pragma error_messages (off, E_STATEMENT_NOT_REACHED)
 *       unreached_line();
 *   #pragma error_messages (on, E_STATEMENT_NOT_REACHED)
 *
 *   But you cannot use #pragmas in a macro definition.
 *
 *   Alternately you could use C99's _Pragma() which can go in a macro.
 *   But older versions of Sun Studio do not have _Pragma(), so we can't
 *   use it.
 *
 *   For now, we deal with this by just not emitting the offending statement.
 *
 * Note for #else case:
 *
 *   The 'x' at the end of the macro _must_ _not_ be surrounded by a pair
 *   of parenthesis.  If you _did_ put in parenthesis, you would end up
 *   with situations like
 *
 *   (return MX_SUCCESSFUL_RESULT);
 *
 *   which is not valid C.
 */

#if defined(__SUNPRO_C)
#  define MXW_NOT_REACHED( x )
#else
#  define MXW_NOT_REACHED( x )    x
#endif

/*------------------------------------------------------------------------*/

#ifndef TRUE
#define TRUE	1
#define FALSE	0
#endif

/*------------------------------------------------------------------------*/

/* Define malloc(), free(), etc. as well as memory debugging functions. */

#include "mx_malloc.h"

/*------------------------------------------------------------------------*/

/* Make the rest of the header file C++ safe. */

#ifdef __cplusplus
extern "C" {
#endif

/*------------------------------------------------------------------------*/

/* The following definitions allow for typechecking of printf and scanf
 * style function arguments with GCC.
 */

#if defined( __GNUC__ )

#define MX_PRINTFLIKE( a, b ) __attribute__ ((format (printf, a, b)))
#define MX_SCANFLIKE( a, b )  __attribute__ ((format (scanf, a, b)))

#else

#define MX_PRINTFLIKE( a, b )
#define MX_SCANFLIKE( a, b )

#endif

/*------------------------------------------------------------------------*/

#define MX_WHITESPACE		" \t"

#define MXU_STRING_LENGTH       20
#define MXU_BUFFER_LENGTH	400
#define MXU_HOSTNAME_LENGTH	100

/*------------------------------------------------------------------------*/

/* Environment variable related functions. */

MX_API int mx_setenv( const char *env_name, const char *env_value );

/*------------------------------------------------------------------------*/

/* Sleep functions with higher resolution than sleep(). */

MX_API void mx_sleep( unsigned long seconds );
MX_API void mx_msleep( unsigned long milliseconds );
MX_API void mx_usleep( unsigned long microseconds );

/* mx_standard_signal_error_handler() is used by several MX programs to provide
 * a standard response to a program crash.
 */

MX_API void mx_standard_signal_error_handler( int signal_number );

/*--- Stack debugging tools ---*/

/* mx_stack_traceback() does its best to provide a traceback of the
 * function call stack at the time of invocation.
 */

MX_API void mx_stack_traceback( void );

/* mx_stack_check() tries to see if the stack is in a valid state.
 * It returns TRUE if the stack is valid and attempts to return FALSE
 * if the stack is not valid.  However, in cases of bad stack frame
 * corruption, it may not be possible to successfully invoke and
 * return from this function, so keep one's expectations low.
 */

MX_API int mx_stack_check( void );

/*--- Heap debugging tools ---*/

/* mx_heap_pointer_is_valid() checks to see if the supplied pointer
 * was allocated from the heap.
 */

MX_API int mx_heap_pointer_is_valid( void *pointer );

/* mx_heap_check() looks to see if the heap is in a valid state.
 * It returns TRUE if the heap is valid and FALSE if the heap is
 * corrupted.  Your program is likely to crash soon if the heap 
 * is corrupted though.
 */

/*--- Flag values for mx_heap_check() ---*/

#define MXF_HEAP_CHECK_OK			0x1
#define MXF_HEAP_CHECK_OK_VERBOSE		0x2
#define MXF_HEAP_CHECK_CORRUPTED		0x4
#define MXF_HEAP_CHECK_CORRUPTED_VERBOSE	0x8
#define MXF_HEAP_CHECK_STACK_TRACEBACK		0x10

#define MXF_HEAP_CHECK_OK_ALL	(MXF_HEAP_CHECK_OK | MXF_HEAP_CHECK_OK_VERBOSE)
#define MXF_HEAP_CHECK_CORRUPTED_ALL \
		(MXF_HEAP_CHECK_CORRUPTED | MXF_HEAP_CHECK_CORRUPTED_VERBOSE)

MX_API int mx_heap_check( unsigned long heap_flags );

/*--- Other debugging tools ---*/

/* mx_pointer_is_valid() __attempts__ to see if the memory range pointed
 * to by the supplied pointer is mapped into the current process with
 * the requested access mode.  The length argument is the length of the
 * memory range that is checked.  The access mode is a bit-wise OR of the
 * desired R_OK and W_OK bits as defined in "mx_unistd.h".
 *
 * WARNING: mx_pointer_is_valid() is not guaranteed to work on all
 * platforms by any means.  On some platforms, it may have a severe
 * performance penalty and can have other very undesirable side effects.
 * You should not use this function during normal operation!
 */

MX_API int mx_pointer_is_valid( void *pointer, size_t length, int access_mode );

/*
 * mx_force_core_dump() attempts to force the creation of a snapshot
 * of the state of the application that can be examined with a debugger
 * and then exit.  On Unix, this is done with a core dump.  On other
 * platforms, an appropriate platform-specific action should occur.
 */

MX_API void mx_force_core_dump( void );

/*
 * mx_start_debugger() attempts to start an external debugger such as the
 * Visual C++ debugger, DDD, gdb, etc. with the program stopped at the
 * line where mx_start_debugger() was invoked.
 *
 * The 'command' argument to mx_start_debugger() is a platform-dependent
 * way of changing the debugger to be started, modifying the way the debugger
 * is run, or anything else appropriate for a given platform.  If the 'command'
 * argument is set to NULL, then a default debugging environment will be
 * started.
 *
 * Warning: This feature is not implemented on all platforms.
 */

MX_API void mx_prepare_for_debugging( char *command,
				int just_in_time_debugging );

MX_API void mx_start_debugger( char *command );

MX_API int mx_debugger_is_present( void );

MX_API void mx_wait_for_debugger( void );

/* mx_breakpoint_helper() is a tiny function that can be used as the
 * target of a debugger breakpoint, assuming it hasn't been optimized
 * away by compiler optimization.  It exists because some versions of
 * GDB have problems with setting breakpoints in C++ constructors.
 * By adding a call to the empty mx_breakpoint_helper() function, it
 * now becomes easy to set a breakpoint in a constructor.
 */

MX_API int mx_breakpoint_helper( void );

/* mx_breakpoint() inserts a debugger breakpoint into the code.
 * This function is not available on all platforms.
 */

MX_API void mx_breakpoint( void );

/* "Numbered breakpoints" only fire when their breakpoint number has
 * been enabled.
 */

MX_API void mx_numbered_breakpoint( unsigned long breakpoint_number );

MX_API void mx_set_numbered_breakpoint( unsigned long breakpoint_number,
					int breakpoint_enable );

MX_API int mx_get_numbered_breakpoint( unsigned long breakpoint_number );

/*
 * mx_set_debugger_started_flag() provides a way to directly set the internal
 * 'mx_debugger_started' flag.  This can be useful if an MX program is started
 * manually from a debugger.
 */

MX_API void mx_set_debugger_started_flag( int started_flag );

MX_API int mx_get_debugger_started_flag( void );

/*
 * mx_global_debug_pointer and mx_global_debug_initialized are used to
 * provide a global "debug" object that can be accessed from anywhere
 * in MX.  These objects are provided only for debugging and should
 * not be used in normal operation.  These declarations are only
 * valid in C.  If you use them from C++ code, you may get multiple
 * definitions of symbols.
 */

#ifndef __cplusplus
MX_API int mx_global_debug_initialized[10];
MX_API void *mx_global_debug_pointer[10];
#endif

/*
 * mx_hex_char_to_unsigned_long() converts a hexadecimal character to an
 * unsigned long integer.  mx_hex_string_to_unsigned_long() does the same
 * thing for a string.
 */

MX_API unsigned long mx_hex_char_to_unsigned_long( char c );

MX_API unsigned long mx_hex_string_to_unsigned_long( char *string );

MX_API long mx_hex_string_to_long( char *string );

/* mx_string_to_long() and mx_string_to_unsigned_long() can handle decimal,
 * octal, and hexadecimal representations of numbers.  If the string starts
 * with '0x' the number is taken to be hexadecimal.  If not, then if it
 * starts with '0', it is taken to be octal.  Otherwise, it is taken to be
 * decimal.  The functions are just wrappers for strtol() and strtoul(), so
 * read strtol's and strtoul's man pages for the real story.
 */

MX_API long mx_string_to_long( char *string );

MX_API unsigned long mx_string_to_unsigned_long( char *string );

/* mx_round() rounds to the nearest integer, while mx_round_away_from_zero()
 * and mx_round_toward_zero() round to the integer in the specified direction.
 *
 * The mx_round_away_from_zero() function subtracts threshold from the
 * number before rounding it up, while mx_round_toward_zero() adds it.
 * This is to prevent numbers that are only non-integral due to roundoff
 * error from being incorrectly rounded to the wrong integer.
 *
 * mx_round_down() rounds to the next lower integer, while mx_round_up()
 * rounds to the next higher integer.
 */

MX_API long mx_round( double value );
MX_API long mx_round_down( double value );
MX_API long mx_round_up( double value );
MX_API long mx_round_away_from_zero( double value, double threshold );
MX_API long mx_round_toward_zero( double value, double threshold );

/* mx_multiply_safely multiplies two floating point numbers by each other
 * while testing for and avoiding infinities.
 */

MX_API double mx_multiply_safely( double multiplier1, double multiplier2 );

/* mx_divide_safely divides two floating point numbers by each other
 * while testing for and avoiding division by zero.
 */

MX_API double mx_divide_safely( double numerator, double denominator );

/* mx_difference() computes a relative difference function. */

MX_API double mx_difference( double value1, double value2 );

/* mx_match() does simple wildcard matching. */

MX_API int mx_match( const char *pattern, const char *string );

/* mx_parse_command_line() takes a string and creates argv[] and envp[]
 * style arrays from it.  Spaces and tabs are taken to be whitespace, while
 * text enclosed by double quotes are assumed to be a single token.  Tokens
 * with an embedded '=' character are assumed to be environment variables.
 * The argv and envp arrays are terminated by NULL entries.
 *
 * The argv and envp arrays returned by mx_parse_command_line() must be
 * freed by mx_free_command_line().  It is not sufficient to just directly
 * free the argv and envp arrays, since mx_free_command_line() must also
 * free an internal buffer created by strdup().
 */

MX_API int mx_parse_command_line( const char *command_line,
		int *argc, char ***argv, int *envc, char ***envp );

MX_API void mx_free_command_line( char **argv, char **envp );

/* mx_free_pointer() is a wrapper for free() that attempts to verify
 * that the pointer is valid to be freed before trying to free() it.
 * The function returns TRUE if freeing the memory succeeded and 
 * FALSE if not.
 */

MX_API void mx_free_pointer( void *pointer );

/* mx_free() is a macro that checks to see if the pointer is NULL
 * before attempting to free it.  After the pointer is freed, the
 * local copy of the pointer is set to NULL.
 */

#define mx_free( ptr ) \
			do {				\
				if ( (ptr) != NULL ) {	\
					free(ptr);	\
					(ptr) = NULL;	\
				} \
			} while (0)

#if ( defined(OS_WIN32) && defined(_MSC_VER) ) || defined(OS_VXWORKS) \
	|| defined(OS_DJGPP) || (defined(OS_VMS) && (__VMS_VER < 70320000 ))

/* These provide definitions of snprintf() and vsnprintf() for systems
 * that do not come with them.  On most such systems, snprintf() and
 * vsnprintf() are merely redefined as sprintf() and vsprintf().
 * Obviously, this removes the buffer overrun safety on such platforms.
 * However, snprintf() and vsnprintf() are supported on most systems
 * and hopefully the buffer overruns will be detected on systems
 * that that support them.
 */

#define snprintf	mx_snprintf
#define vsnprintf	mx_vsnprintf

MX_API int mx_snprintf( char *dest, size_t maxlen, const char *format, ... );

MX_API int mx_vsnprintf( char *dest, size_t maxlen, const char *format,
							va_list args );
#endif

/* If you want to use something like snprintf() to print a list of arguments,
 * but you do not know how many arguments you will have until run time, then 
 * snprintf() cannot help you, since C does not allow you to manually create
 * a va_list using portable C code.
 *
 * Instead, we use our homebrew mx_snprint_from_pointer_array(), where you
 * provide an array of void pointers to individual arguments that you
 * want to print.  snprintf() is actually used to implement the printing
 * of individual items from 'pointer_array'.
 */

MX_API int mx_snprintf_from_pointer_array( char *dest,
					size_t maxlen,
					const char *format,
					size_t num_pointers,
					void **pointer_array );

#if defined(OS_LINUX) || defined(OS_WIN32) || defined(OS_IRIX) \
	|| defined(OS_HPUX) || defined(OS_TRU64) || defined(OS_VMS) \
	|| defined(OS_QNX) || defined(OS_VXWORKS) || defined(OS_RTEMS) \
	|| defined(OS_DJGPP) || defined(OS_ECOS) || defined(OS_HURD)

/* These prototypes provide definitions of strlcpy() and strlcat() for
 * systems that do not come with them.  For systems that do not come with
 * them, the OpenBSD source code for strlcpy() and strlcat() is bundled
 * with the base MX distribution in the directory mx/tools/generic/src.
 */

MX_API size_t strlcpy( char *dest, const char *src, size_t maxlen );

MX_API size_t strlcat( char *dest, const char *src, size_t maxlen );

#endif

/* This prototype provides a definition of strptime() for systems that
 * do not come with it.  For such systems, the NetBSD source code for
 * strptime() is bundled with the base MX distribution in the directory
 * mx/tools/generic/strptime.
 */

#if defined(OS_WIN32) || defined(OS_DJGPP) || defined(OS_VXWORKS)

MX_API char *strptime( const char *s, const char *format, struct tm *tm );

#endif

/* mx_strncmp_end() is analogous to strncmp(), but it compares its second
 * argument to the _end_ of the first argument instead of the beginning.
 */

MX_API int mx_strncmp_end( const char *s1, const char *s2, size_t n );

#define mx_strcmp_end(s1,s2)  mx_strncmp_end( (s1), (s2), strlen((s2)) )

/* mx_fgets() is a replacement for fgets() that automatically trims off
 * trailing newlines.
 */

MX_API char *mx_fgets( char *s, int size, FILE *stream );

/*----------------------*/

/* Case insensitive string comparisons. */

#if defined(OS_VXWORKS)

   MX_API int mx_strcasecmp( const char *s1, const char *s2 );
   MX_API int mx_strncasecmp( const char *s1, const char *s2, size_t n );

#elif defined(_MSC_VER) || defined(__BORLANDC__) || defined(OS_DJGPP) \
	|| defined(OS_QNX)
#  define mx_strcasecmp   stricmp
#  define mx_strncasecmp  strnicmp

#else
#  define mx_strcasecmp   strcasecmp
#  define mx_strncasecmp  strncasecmp
#endif

/* The following function is only used by Visual C++ 6.0 SP6 and before. */

#if ( defined(_MSC_VER) && (_MSC_VER < 1300) )
MX_API double mx_uint64_to_double( unsigned __int64 );
#endif

/* == Debugging functions. == */

MX_API const char *mx_timestamp( char *buffer, size_t buffer_length );

/* Note that in any call to MX_DEBUG(), _all_ the arguments together 
 * after the debug level are enclosed in _one_ extra set of parentheses.
 * If you don't do this, the code will not compile.
 *
 * For example,
 *    MX_DEBUG( 2, ("The current value of foo is %d\n", foo) );
 * 
 * This is so that the preprocessor will treat everything after "2,"
 * as one _big_ macro argument.  This is the closest one can come to
 * "varargs" macros in standard ANSI C.  Also, the line below that
 * reads "mx_debug_function  text ;" is _not_ in error and is _not_
 * missing any needed parentheses.  The preprocessor will get the
 * needed parentheses from the extra set of parentheses in the
 * original invocation of MX_DEBUG().  Go read up on just how macro
 * expansion by the C preprocessor is supposed to work if you want
 * to understand this better.  Also, the Frequently Asked Questions
 * file for comp.lang.c on Usenet has a few words about this.
 *
 * Yes, it's a trick, but it's a trick that works very well as long
 * you don't forget those extra set of parentheses.  Incidentally,
 * you still need the parentheses even if the format field in the
 * second argument is a constant string with no %'s in it.  That's
 * because if you don't you'll end up after the macro expansion
 * with something like:   mx_debug_function "This doesn't work" ;
 */

MX_API void mx_debug_function( const char *format, ... ) MX_PRINTFLIKE( 1, 2 );

#ifndef DEBUG
#define MX_DEBUG( level, text )
#else
#define MX_DEBUG( level, text ) \
		if ( (level) <= mx_get_debug_level() )  { \
			mx_debug_function  text ; \
		}
#endif

MX_API void mx_set_debug_level( int debug_level );
MX_API int  mx_get_debug_level( void );

MX_API void mx_set_debug_output_function( void (*)( char * ) );
MX_API void mx_debug_default_output_function( char *string );

MX_API void mx_debug_pause( const char *format, ... ) MX_PRINTFLIKE( 1, 2 );

/* === User interrupts. === */

#define MXF_USER_INT_NONE	0
#define MXF_USER_INT_ABORT	1
#define MXF_USER_INT_PAUSE	2

#define MXF_USER_INT_ERROR	(-1)

MX_API int  mx_user_requested_interrupt( void );
MX_API int  mx_user_requested_interrupt_or_pause( void );
MX_API void mx_set_user_interrupt_function( int (*)( void ) );
MX_API int  mx_default_user_interrupt_function( void );

/* === Informational messages. === */

MX_API void mx_info( const char *format, ... ) MX_PRINTFLIKE( 1, 2 );

MX_API void mx_info_dialog( char *text_prompt,
					char *gui_prompt,
					char *button_label );

MX_API void mx_info_entry_dialog( char *text_prompt,
					char *gui_prompt,
					int echo_characters,
					char *response,
					size_t max_response_length );

MX_API void mx_set_info_output_function( void (*)( char * ) );
MX_API void mx_info_default_output_function( char *string );

MX_API void mx_set_info_dialog_function( void (*)( char *, char *, char * ) );
MX_API void mx_info_default_dialog_function( char *, char *, char * );

MX_API void mx_set_info_entry_dialog_function(
			void (*)( char *, char *, int, char *, size_t ) );
MX_API void mx_info_default_entry_dialog_function(
					char *, char *, int, char *, size_t );

/* Informational messages during a scan are handled specially, since some
 * applications may want to suppress them, but not suppress other messages.
 */

MX_API void mx_scanlog_info( const char *format, ... ) MX_PRINTFLIKE( 1, 2 );

MX_API void mx_set_scanlog_enable( int enable_flag );
MX_API int  mx_get_scanlog_enable( void );

/* === Warning messages. === */

MX_API void mx_warning( const char *format, ... ) MX_PRINTFLIKE( 1, 2 );

MX_API void mx_set_warning_output_function( void (*)( char * ) );
MX_API void mx_warning_default_output_function( char *string );

/* === Error messages. === */

#define MXU_ERROR_MESSAGE_LENGTH	2000

#if USE_STACK_BASED_MX_ERROR

typedef struct {
	long code;		/* The error code. */
	const char *location;	/* Function name where the error occurred. */
	char message[MXU_ERROR_MESSAGE_LENGTH+1]; /* The specific error msg.*/
} mx_status_type;

#else /* not USE_STACK_BASED_MX_ERROR */

typedef struct {
	long code;		/* The error code. */
	const char *location;	/* Function name where the error occurred. */
	char *message;                            /* The specific error msg.*/
} mx_status_type;

#endif /* USE_STACK_BASED_MX_ERROR */

MX_API mx_status_type mx_error( long error_code,
				const char *location,
				const char *format, ... ) MX_PRINTFLIKE( 3, 4 );

#define MX_CHECK_FOR_ERROR( function )				\
	do { 							\
		mx_status_type mx_private_status;		\
								\
		mx_private_status = (function);			\
								\
		if ( mx_private_status.code != MXE_SUCCESS )	\
			return mx_private_status;		\
	} while(0)

MX_API char *mx_strerror(long error_code, char *buffer, size_t buffer_length);

MX_API long mx_errno_to_mx_status_code( int errno_value );

MX_API const char *mx_errno_string( long errno_value );
MX_API const char *mx_status_code_string( long mx_status_code_value );

MX_API void mx_set_error_output_function( void (*)( char * ) );
MX_API void mx_error_default_output_function( char *string );

MX_API mx_status_type mx_successful_result( void );

#define MX_SUCCESSFUL_RESULT	mx_successful_result()

#if defined(OS_WIN32)
MX_API long mx_win32_error_message( long error_code,
					char *buffer, size_t buffer_length );
#endif

/*------------------------------------------------------------------------*/

/* Setup the parts of the MX runtime environment that do not depend
 * on the presence of an MX database.
 */

MX_API mx_status_type mx_initialize_runtime( void ); 

/*------------------------------------------------------------------------*/

MX_API mx_status_type mx_get_os_version_string( char *version_string,
					size_t max_version_string_length );

MX_API mx_status_type mx_get_os_version( int *os_major,
					int *os_minor,
					int *os_update );

MX_API unsigned long mx_get_os_version_number( void );

#if defined(OS_WIN32)
MX_API mx_status_type mx_win32_get_osversioninfo( unsigned long *major,
						unsigned long *minor,
						unsigned long *platform_id,
						unsigned char *product_type );

MX_API mx_status_type mx_win32_is_windows_9x( int *is_windows_9x );
#endif /* OS_WIN32 */

MX_API mx_status_type mx_get_cpu_architecture( char *architecture_type,
					size_t max_architecture_type_length,
					char *architecture_subtype,
					size_t max_architecture_subtype_length);

MX_API mx_status_type mx_get_system_boot_time( struct timespec *boot_timespec );

MX_API mx_status_type mx_get_system_boot_time_from_ticks(
					struct timespec *boot_timespec );

/*------------------------------------------------------------------------*/

/* Flag bits for mx_copy_file(). */

#define MXF_CP_OVERWRITE		0x1

#define MXF_CP_USE_CLASSIC_COPY		0x80000000

/* mx_copy_file() copies an old file to a new file where new_file_mode
 * specifies the permissions for the new file using the same bit patterns
 * for the mode as the Posix open() and creat() calls.
 */

MX_API mx_status_type mx_copy_file( char *original_filename,
				char *new_filename,
				int new_file_mode,
				unsigned long copy_flags );

MX_API mx_status_type mx_copy_file_classic( char *original_filename,
				char *new_filename,
				int new_file_mode );

MX_API mx_status_type mx_get_num_lines_in_file( char *filename,
						size_t *num_lines_in_file );

MX_API mx_status_type mx_skip_num_lines_in_file( FILE *file,
						size_t num_lines_to_skip );

MX_API mx_status_type mx_get_current_directory_name( char *filename_buffer,
						size_t max_filename_length );

MX_API mx_status_type mx_change_filename_prefix( const char *old_filename,
						const char *old_prefix,
						const char *new_prefix,
						char *new_filename,
						size_t max_new_filename_length);

MX_API mx_status_type mx_construct_file_name_from_file_pattern(
						char *filename_buffer,
						size_t filename_buffer_size,
						const char file_pattern_char,
						unsigned long file_number,
						const char *file_pattern );

MX_API mx_status_type mx_make_directory_hierarchy( char *directory_name );

MX_API int mx_command_found( char *command_name );

/*--- Flag bits used by mx_find_file_in_path() ---*/

#define MXF_FPATH_LOOK_IN_CURRENT_DIRECTORY	0x1
#define MXF_FPATH_TRY_WITHOUT_EXTENSION		0x2

MX_API mx_status_type mx_find_file_in_path( const char *original_filename,
					char *full_filename,
					size_t full_filename_length,
					const char *path_variable_name,
					const char *extension,
					int file_access_mode,
					unsigned long flags,
					int *match_found );

/* mx_verify_directory() verifies the existence of the specified directory
 * and optionally creates it if it does not already exist.
 */

MX_API mx_status_type mx_verify_directory( char *directory_name,
					int create_flag );

/* Converts a filename into the canonical form for that operating system. */

MX_API mx_status_type mx_canonicalize_filename( char *original_name,
						char *canonical_name,
					size_t max_canonical_name_length );

/*------------------------------------------------------------------------*/

MX_API mx_status_type mx_get_filesystem_root_name( char *filename,
						char *root_name,
						size_t max_root_name_length );

/* The following flags are used to report the filesystem type below. */

#define MXF_FST_NOT_FOUND	1
#define MXF_FST_NOT_MOUNTED	2

#define MXF_FST_LOCAL		0x100000
#define MXF_FST_REMOTE		0x200000

#define MXF_FST_ISO9660		(MXF_FST_LOCAL + 1)
#define MXF_FST_UDF		(MXF_FST_LOCAL + 2)

#define MXF_FST_FAT		(MXF_FST_LOCAL + 1001)
#define MXF_FST_EXFAT		(MXF_FST_LOCAL + 1002)
#define MXF_FST_NTFS		(MXF_FST_LOCAL + 1003)

#define MXF_FST_EXT2		(MXF_FST_LOCAL + 2002)
#define MXF_FST_EXT3		(MXF_FST_LOCAL + 2003)
#define MXF_FST_EXT4		(MXF_FST_LOCAL + 2004)

#define MXF_FST_NFS		(MXF_FST_REMOTE + 3001)
#define MXF_FST_SMB		(MXF_FST_REMOTE + 3002)
#define MXF_FST_AFP		(MXF_FST_REMOTE + 3003)

MX_API mx_status_type mx_get_filesystem_type( char *filename,
					unsigned long *filesystem_type );

/*------------------------------------------------------------------------*/

/* Flags for mx_spawn() */

#define MXF_SPAWN_NEW_SESSION		0x1

#define MXF_SPAWN_NO_PRELOAD		0x10000000

MX_API mx_status_type mx_spawn( char *command_line,
				unsigned long flags,
				unsigned long *process_id );

MX_API int mx_process_id_exists( unsigned long process_id );

MX_API mx_status_type mx_kill_process_id( unsigned long process_id );

MX_API unsigned long mx_process_id( void );

MX_API mx_status_type mx_wait_for_process_id( unsigned long process_id,
						long *process_status );

/*------------------------------------------------------------------------*/

MX_API char *mx_username( char *buffer, size_t buffer_length );

MX_API mx_status_type mx_get_number_of_cpu_cores( unsigned long *num_cores );

MX_API unsigned long mx_get_current_cpu_number( void );

MX_API mx_status_type mx_get_process_affinity_mask( unsigned long process_id,
							unsigned long *mask );

MX_API mx_status_type mx_set_process_affinity_mask( unsigned long process_id,
							unsigned long mask );

/*----*/

MX_API int mx_get_true_or_false( char *true_false_string );

/*----*/

MX_API char *mx_skip_string_fields( char *buffer, int num_fields );

/* mx_string_token() extracts the next token from a string using the
 * characters in 'delim' as token separators.  It is similar to strsep()
 * except for the fact that it treats a string of several delimiters in
 * a row as being only one delimiter.  By contrast, strsep() would say
 * that there were empty tokens between each of the delimiter characters.
 * 
 * Please note that the original contents of *string_ptr are modified.
 */

MX_API char *mx_string_token( char **string_ptr, const char *delim );

/* mx_string_split() uses mx_string_token() to break up the contents of
 * a string into an argv style array.  The original string is modified,
 * so you should make a copy of it if you want to keep the original
 * contents.
 */

MX_API int mx_string_split( char *original_string, const char *delim,
					int *argc, char ***argv );

/*------------------------------------------------------------------------*/

MX_API unsigned long mx_random( void );

MX_API void mx_seed_random( unsigned long seed );

MX_API unsigned long mx_get_random_max( void );

/*------------------------------------------------------------------------*/

/* === Define error message codes. === */

#define MXE_SUCCESS				1000	/* No error. */

#define MXE_NULL_ARGUMENT			1001
#define MXE_ILLEGAL_ARGUMENT			1002
#define MXE_CORRUPT_DATA_STRUCTURE		1003
#define MXE_UNPARSEABLE_STRING			1004
#define MXE_END_OF_DATA				1005
#define MXE_UNEXPECTED_END_OF_DATA		1006
#define MXE_NOT_FOUND				1007
#define MXE_TYPE_MISMATCH			1008
#define MXE_NOT_YET_IMPLEMENTED			1009
#define MXE_UNSUPPORTED				1010
#define MXE_OUT_OF_MEMORY			1011
#define MXE_WOULD_EXCEED_LIMIT			1012
#define MXE_LIMIT_WAS_EXCEEDED			1013
#define MXE_INTERFACE_IO_ERROR			1014
#define MXE_DEVICE_IO_ERROR			1015
#define MXE_FILE_IO_ERROR			1016
#define MXE_TERMINAL_IO_ERROR			1017
#define MXE_IPC_IO_ERROR			1018
#define MXE_IPC_CONNECTION_LOST			1019
#define MXE_NETWORK_IO_ERROR			1020
#define MXE_NETWORK_CONNECTION_LOST		1021
#define MXE_NOT_READY				1022
#define MXE_INTERRUPTED				1023
#define MXE_PAUSE_REQUESTED			1024
#define MXE_INTERFACE_ACTION_FAILED		1025
#define MXE_DEVICE_ACTION_FAILED		1026
#define MXE_FUNCTION_FAILED			1027
#define MXE_CONTROLLER_INTERNAL_ERROR		1028
#define MXE_PERMISSION_DENIED			1029
#define MXE_CLIENT_REQUEST_DENIED		1030
#define MXE_TRY_AGAIN				1031
#define MXE_TIMED_OUT				1032
#define MXE_HARDWARE_CONFIGURATION_ERROR	1033
#define MXE_HARDWARE_FAULT			1034
#define MXE_RECORD_DISABLED_DUE_TO_FAULT	1035
#define MXE_RECORD_DISABLED_BY_USER		1036
#define MXE_INITIALIZATION_ERROR		1037
#define MXE_READ_ONLY				1038
#define MXE_SOFTWARE_CONFIGURATION_ERROR	1039
#define MXE_OPERATING_SYSTEM_ERROR		1040
#define MXE_UNKNOWN_ERROR			1041
#define MXE_NOT_VALID_FOR_CURRENT_STATE		1042
#define MXE_CONFIGURATION_CONFLICT		1043
#define MXE_NOT_AVAILABLE			1044
#define MXE_STOP_REQUESTED			1045
#define MXE_BAD_HANDLE				1046
#define MXE_OBJECT_ABANDONED			1047
#define MXE_MIGHT_CAUSE_DEADLOCK		1048
#define MXE_ALREADY_EXISTS			1049
#define MXE_INVALID_CALLBACK			1050
#define MXE_EARLY_EXIT				1051
#define MXE_PROTOCOL_ERROR			1052
#define MXE_DISK_FULL				1053
#define MXE_DATA_WAS_LOST			1054
#define MXE_NETWORK_CONNECTION_REFUSED		1055

/* If the error message code is OR-ed with MXE_QUIET, then
 * the error message is not displayed to the user.
 */

#define MXE_QUIET				0x8000

#ifdef __cplusplus
}
#endif

#endif /* __MX_UTIL_H__ */
