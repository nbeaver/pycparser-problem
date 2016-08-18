/*
 * Name:    mx_clock.h
 *
 * Purpose: Header file for MX time keeping functions.  This is mostly used
 *          by servers.
 *
 * Author:  William Lavender
 *
 *---------------------------------------------------------------------------
 *
 * Copyright 1999, 2004, 2007, 2013 Illinois Institute of Technology
 *
 * See the file "LICENSE" for information on usage and redistribution
 * of this file, and for a DISCLAIMER OF ALL WARRANTIES.
 *
 */

#ifndef __MX_CLOCK_H__
#define __MX_CLOCK_H__

#include <time.h>

/* Make the header file C++ safe. */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
	unsigned long high_order;
	unsigned long low_order;
} MX_CLOCK_TICK;

MX_API double mx_clock_ticks_per_second( void );

MX_API void mx_initialize_clock_ticks( void );

MX_API MX_CLOCK_TICK mx_current_clock_tick( void );

MX_API MX_CLOCK_TICK mx_convert_seconds_to_clock_ticks( double seconds );

MX_API double mx_convert_clock_ticks_to_seconds( MX_CLOCK_TICK clock_tick );

MX_API MX_CLOCK_TICK mx_add_clock_ticks( MX_CLOCK_TICK clock_tick_1,
					MX_CLOCK_TICK clock_tick_2 );

MX_API MX_CLOCK_TICK mx_subtract_clock_ticks( MX_CLOCK_TICK clock_tick_1,
					MX_CLOCK_TICK clock_tick_2 );

MX_API int mx_compare_clock_ticks( MX_CLOCK_TICK clock_tick_1,
					MX_CLOCK_TICK clock_tick_2 );

MX_API MX_CLOCK_TICK mx_set_clock_tick_to_zero( void );

MX_API MX_CLOCK_TICK mx_set_clock_tick_to_maximum( void );

#define mx_clock_tick_is_zero(t) \
	( ((t).high_order == 0) && ((t).low_order == 0) )

#ifdef __cplusplus
}
#endif

#endif /* __MX_CLOCK_H__ */

