/*
 * Name:    mx_variable.h
 *
 * Purpose: Header file for generic variable superclass support.
 *
 * Author:  William Lavender
 *
 *--------------------------------------------------------------------------
 *
 * Copyright 1999-2001, 2006-2007, 2010 Illinois Institute of Technology
 *
 * See the file "LICENSE" for information on usage and redistribution
 * of this file, and for a DISCLAIMER OF ALL WARRANTIES.
 *
 */


#ifndef __MX_VARIABLE_H__
#define __MX_VARIABLE_H__

/* Make the header file C++ safe. */

#ifdef __cplusplus
extern "C" {
#endif

typedef struct {
	MX_RECORD *record; /* Pointer to the MX_RECORD structure that points
			    * to this MX_VARIABLE structure.
			    */
	long num_dimensions;
	long *dimension;

	void *pointer_to_value;
} MX_VARIABLE;

typedef struct {
	mx_status_type ( *send_value )( MX_VARIABLE *variable );
	mx_status_type ( *receive_value )( MX_VARIABLE *variable );
} MX_VARIABLE_FUNCTION_LIST;

MX_API_PRIVATE mx_status_type mx_variable_initialize_driver( MX_DRIVER *driver);

MX_API mx_status_type mx_send_variable( MX_RECORD *record );
MX_API mx_status_type mx_receive_variable( MX_RECORD *record );

MX_API mx_status_type mx_get_variable_parameters( MX_RECORD *record,
					long *num_dimensions,
					long **dimension_array,
					long *field_type,
					void **pointer_to_value );

MX_API mx_status_type mx_get_variable_pointer( MX_RECORD *record,
						void **pointer_to_value );

/* The following functions only work for 1-dimensional array variables. */

MX_API mx_status_type mx_get_1d_array_by_name( MX_RECORD *record_list,
					char *record_name,
					long field_type,
					long *num_elements,
					void **pointer_to_value );

MX_API mx_status_type mx_get_1d_array( MX_RECORD *record,
					long field_type,
					long *num_elements,
					void **pointer_to_value );

MX_API mx_status_type mx_set_1d_array( MX_RECORD *record,
					long field_type,
					long num_elements,
					void *pointer_to_value );

/*---*/

MX_API mx_status_type mx_get_bool_variable_by_name(
					MX_RECORD *record_list,
					char *record_name,
					mx_bool_type *bool_value );

MX_API mx_status_type mx_get_long_variable_by_name(
					MX_RECORD *record_list,
					char *record_name,
					long *long_value );

MX_API mx_status_type mx_get_unsigned_long_variable_by_name(
					MX_RECORD *record_list,
					char *record_name,
					unsigned long *unsigned_long_value );

MX_API mx_status_type mx_get_double_variable_by_name(
					MX_RECORD *record_list,
					char *record_name,
					double *double_value );

MX_API mx_status_type mx_get_string_variable_by_name(
					MX_RECORD *record_list,
					char *record_name,
					char *string_value,
					size_t max_string_length );

/*---*/

MX_API mx_status_type mx_get_char_variable( MX_RECORD *record,
					char *char_value );

MX_API mx_status_type mx_get_unsigned_char_variable( MX_RECORD *record,
					unsigned char *unsigned_char_value );

MX_API mx_status_type mx_get_short_variable( MX_RECORD *record,
					short *short_value );

MX_API mx_status_type mx_get_unsigned_short_variable( MX_RECORD *record,
					unsigned short *unsigned_short_value );

MX_API mx_status_type mx_get_bool_variable( MX_RECORD *record,
					mx_bool_type *bool_value );

MX_API mx_status_type mx_get_long_variable( MX_RECORD *record,
					long *long_value );

MX_API mx_status_type mx_get_unsigned_long_variable( MX_RECORD *record,
					unsigned long *unsigned_long_value );

MX_API mx_status_type mx_get_int64_variable( MX_RECORD *record,
					int64_t *int64_value );

MX_API mx_status_type mx_get_uint64_variable( MX_RECORD *record,
					uint64_t *uint64_value );

MX_API mx_status_type mx_get_float_variable( MX_RECORD *record,
					float *float_value );

MX_API mx_status_type mx_get_double_variable( MX_RECORD *record,
					double *double_value );

MX_API mx_status_type mx_get_string_variable( MX_RECORD *record,
					char *string_value,
					size_t max_string_length );

/*---*/

MX_API mx_status_type mx_set_char_variable( MX_RECORD *record,
					char char_value );

MX_API mx_status_type mx_set_unsigned_char_variable( MX_RECORD *record,
					unsigned char unsigned_char_value );

MX_API mx_status_type mx_set_short_variable( MX_RECORD *record,
					short short_value );

MX_API mx_status_type mx_set_unsigned_short_variable( MX_RECORD *record,
					unsigned short unsigned_short_value );

MX_API mx_status_type mx_set_bool_variable( MX_RECORD *record,
					mx_bool_type bool_value );

MX_API mx_status_type mx_set_long_variable( MX_RECORD *record,
					long long_value );

MX_API mx_status_type mx_set_unsigned_long_variable( MX_RECORD *record,
					unsigned long unsigned_long_value );

MX_API mx_status_type mx_set_int64_variable( MX_RECORD *record,
					int64_t int64_value );

MX_API mx_status_type mx_set_uint64_variable( MX_RECORD *record,
					uint64_t uint64_value );

MX_API mx_status_type mx_set_float_variable( MX_RECORD *record,
					float float_value );

MX_API mx_status_type mx_set_double_variable( MX_RECORD *record,
					double double_value );

MX_API mx_status_type mx_set_string_variable( MX_RECORD *record,
					char *string_value );

/*---*/

/* The following definitions of MXA_XXX_SIZEOF assume that
 * MXU_FIELD_MAX_DIMENSIONS is equal to 8.
 */

#define MXA_STRING_SIZEOF \
	{ sizeof(char), sizeof(char *), \
	sizeof(char **), sizeof(char ***), \
	sizeof(char ****), sizeof(char *****), \
	sizeof(char ******), sizeof(char *******) }

#define MXA_CHAR_SIZEOF     MXA_STRING_SIZEOF

#define MXA_UCHAR_SIZEOF \
	{ sizeof(unsigned char), sizeof(unsigned char *), \
	sizeof(unsigned char **), sizeof(unsigned char ***), \
	sizeof(unsigned char ****), sizeof(unsigned char *****), \
	sizeof(unsigned char ******), sizeof(unsigned char *******) }

#define MXA_SHORT_SIZEOF \
	{ sizeof(short), sizeof(short *), \
	sizeof(short **), sizeof(short ***), \
	sizeof(short ****), sizeof(short *****), \
	sizeof(short ******), sizeof(short *******) }

#define MXA_USHORT_SIZEOF \
	{ sizeof(unsigned short), sizeof(unsigned short *), \
	sizeof(unsigned short **), sizeof(unsigned short ***), \
	sizeof(unsigned short ****), sizeof(unsigned short *****), \
	sizeof(unsigned short ******), sizeof(unsigned short *******) }

#define MXA_BOOL_SIZEOF \
	{ sizeof(mx_bool_type), sizeof(mx_bool_type *), \
	sizeof(mx_bool_type **), sizeof(mx_bool_type ***), \
	sizeof(mx_bool_type ****), sizeof(mx_bool_type *****), \
	sizeof(mx_bool_type ******), sizeof(mx_bool_type *******) }

#define MXA_LONG_SIZEOF \
	{ sizeof(long), sizeof(long *), \
	sizeof(long **), sizeof(long ***), \
	sizeof(long ****), sizeof(long *****), \
	sizeof(long ******), sizeof(long *******) }

#define MXA_ULONG_SIZEOF \
	{ sizeof(unsigned long), sizeof(unsigned long *), \
	sizeof(unsigned long **), sizeof(unsigned long ***), \
	sizeof(unsigned long ****), sizeof(unsigned long *****), \
	sizeof(unsigned long ******), sizeof(unsigned long *******) }

#define MXA_INT64_SIZEOF \
	{ sizeof(int64_t), sizeof(int64_t *), \
	sizeof(int64_t **), sizeof(int64_t ***), \
	sizeof(int64_t ****), sizeof(int64_t *****), \
	sizeof(int64_t ******), sizeof(int64_t *******) }

#define MXA_UINT64_SIZEOF \
	{ sizeof(uint64_t), sizeof(uint64_t *), \
	sizeof(uint64_t **), sizeof(uint64_t ***), \
	sizeof(uint64_t ****), sizeof(uint64_t *****), \
	sizeof(uint64_t ******), sizeof(uint64_t *******) }

#define MXA_FLOAT_SIZEOF \
	{ sizeof(float), sizeof(float *), \
	sizeof(float **), sizeof(float ***), \
	sizeof(float ****), sizeof(float *****), \
	sizeof(float ******), sizeof(float *******) }

#define MXA_DOUBLE_SIZEOF \
	{ sizeof(double), sizeof(double *), \
	sizeof(double **), sizeof(double ***), \
	sizeof(double ****), sizeof(double *****), \
	sizeof(double ******), sizeof(double *******) }

#define MXA_RECORD_SIZEOF \
	{ sizeof(MX_RECORD *), sizeof(MX_RECORD **), \
	sizeof(MX_RECORD ***), sizeof(MX_RECORD ****), \
	sizeof(MX_RECORD *****), sizeof(MX_RECORD ******), \
	sizeof(MX_RECORD *******), sizeof(MX_RECORD ********) }

#define MXA_INTERFACE_SIZEOF \
	{ sizeof(MX_INTERFACE *), sizeof(MX_INTERFACE **), \
	sizeof(MX_INTERFACE ***), sizeof(MX_INTERFACE ****), \
	sizeof(MX_INTERFACE *****), sizeof(MX_INTERFACE ******), \
	sizeof(MX_INTERFACE *******), sizeof(MX_INTERFACE ********) }

/* =========================================== */

#define MXLV_VAR_VALUE		1001

#define MX_VARIABLE_STANDARD_FIELDS \
  {-1, -1, "num_dimensions", MXFT_LONG, NULL, 0, {0}, \
	MXF_REC_SUPERCLASS_STRUCT, offsetof(MX_VARIABLE, num_dimensions), \
	{0}, NULL, MXFF_IN_DESCRIPTION}, \
\
  {-1, -1, "dimension", MXFT_LONG, NULL, 1, {MXU_VARARGS_LENGTH}, \
	MXF_REC_SUPERCLASS_STRUCT, offsetof(MX_VARIABLE, dimension), \
	{sizeof(long)}, NULL, (MXFF_IN_DESCRIPTION | MXFF_VARARGS) }


/* =========================================== */

#define MX_STRING_VARIABLE_STANDARD_FIELDS \
  {MXLV_VAR_VALUE, -1, "value", MXFT_STRING, NULL, \
	MXU_VARARGS_LENGTH, {MXU_VARARGS_LENGTH}, \
	MXF_REC_SUPERCLASS_STRUCT, offsetof(MX_VARIABLE, pointer_to_value), \
	MXA_STRING_SIZEOF, NULL, \
	(MXFF_IN_DESCRIPTION | MXFF_IN_SUMMARY | MXFF_VARARGS) }

#define MX_CHAR_VARIABLE_STANDARD_FIELDS \
  {MXLV_VAR_VALUE, -1, "value", MXFT_CHAR, NULL, \
	MXU_VARARGS_LENGTH, {MXU_VARARGS_LENGTH}, \
	MXF_REC_SUPERCLASS_STRUCT, offsetof(MX_VARIABLE, pointer_to_value), \
	MXA_CHAR_SIZEOF, NULL, \
	(MXFF_IN_DESCRIPTION | MXFF_IN_SUMMARY | MXFF_VARARGS) }

#define MX_UCHAR_VARIABLE_STANDARD_FIELDS \
  {MXLV_VAR_VALUE, -1, "value", MXFT_UCHAR, NULL, \
	MXU_VARARGS_LENGTH, {MXU_VARARGS_LENGTH}, \
	MXF_REC_SUPERCLASS_STRUCT, offsetof(MX_VARIABLE, pointer_to_value), \
	MXA_UCHAR_SIZEOF, NULL, \
	(MXFF_IN_DESCRIPTION | MXFF_IN_SUMMARY | MXFF_VARARGS) }

#define MX_SHORT_VARIABLE_STANDARD_FIELDS \
  {MXLV_VAR_VALUE, -1, "value", MXFT_SHORT, NULL, \
	MXU_VARARGS_LENGTH, {MXU_VARARGS_LENGTH}, \
	MXF_REC_SUPERCLASS_STRUCT, offsetof(MX_VARIABLE, pointer_to_value), \
	MXA_SHORT_SIZEOF, NULL, \
	(MXFF_IN_DESCRIPTION | MXFF_IN_SUMMARY | MXFF_VARARGS) }

#define MX_USHORT_VARIABLE_STANDARD_FIELDS \
  {MXLV_VAR_VALUE, -1, "value", MXFT_USHORT, NULL, \
	MXU_VARARGS_LENGTH, {MXU_VARARGS_LENGTH}, \
	MXF_REC_SUPERCLASS_STRUCT, offsetof(MX_VARIABLE, pointer_to_value), \
	MXA_USHORT_SIZEOF, NULL, \
	(MXFF_IN_DESCRIPTION | MXFF_IN_SUMMARY | MXFF_VARARGS) }

#define MX_BOOL_VARIABLE_STANDARD_FIELDS \
  {MXLV_VAR_VALUE, -1, "value", MXFT_BOOL, NULL, \
	MXU_VARARGS_LENGTH, {MXU_VARARGS_LENGTH}, \
	MXF_REC_SUPERCLASS_STRUCT, offsetof(MX_VARIABLE, pointer_to_value), \
	MXA_BOOL_SIZEOF, NULL, \
	(MXFF_IN_DESCRIPTION | MXFF_IN_SUMMARY | MXFF_VARARGS) }

#define MX_LONG_VARIABLE_STANDARD_FIELDS \
  {MXLV_VAR_VALUE, -1, "value", MXFT_LONG, NULL, \
	MXU_VARARGS_LENGTH, {MXU_VARARGS_LENGTH}, \
	MXF_REC_SUPERCLASS_STRUCT, offsetof(MX_VARIABLE, pointer_to_value), \
	MXA_LONG_SIZEOF, NULL, \
	(MXFF_IN_DESCRIPTION | MXFF_IN_SUMMARY | MXFF_VARARGS) }

#define MX_ULONG_VARIABLE_STANDARD_FIELDS \
  {MXLV_VAR_VALUE, -1, "value", MXFT_ULONG, NULL, \
	MXU_VARARGS_LENGTH, {MXU_VARARGS_LENGTH}, \
	MXF_REC_SUPERCLASS_STRUCT, offsetof(MX_VARIABLE, pointer_to_value), \
	MXA_ULONG_SIZEOF, NULL, \
	(MXFF_IN_DESCRIPTION | MXFF_IN_SUMMARY | MXFF_VARARGS) }

#define MX_INT64_VARIABLE_STANDARD_FIELDS \
  {MXLV_VAR_VALUE, -1, "value", MXFT_INT64, NULL, \
	MXU_VARARGS_LENGTH, {MXU_VARARGS_LENGTH}, \
	MXF_REC_SUPERCLASS_STRUCT, offsetof(MX_VARIABLE, pointer_to_value), \
	MXA_INT64_SIZEOF, NULL, \
	(MXFF_IN_DESCRIPTION | MXFF_IN_SUMMARY | MXFF_VARARGS) }

#define MX_UINT64_VARIABLE_STANDARD_FIELDS \
  {MXLV_VAR_VALUE, -1, "value", MXFT_UINT64, NULL, \
	MXU_VARARGS_LENGTH, {MXU_VARARGS_LENGTH}, \
	MXF_REC_SUPERCLASS_STRUCT, offsetof(MX_VARIABLE, pointer_to_value), \
	MXA_UINT64_SIZEOF, NULL, \
	(MXFF_IN_DESCRIPTION | MXFF_IN_SUMMARY | MXFF_VARARGS) }

#define MX_FLOAT_VARIABLE_STANDARD_FIELDS \
  {MXLV_VAR_VALUE, -1, "value", MXFT_FLOAT, NULL, \
	MXU_VARARGS_LENGTH, {MXU_VARARGS_LENGTH}, \
	MXF_REC_SUPERCLASS_STRUCT, offsetof(MX_VARIABLE, pointer_to_value), \
	MXA_FLOAT_SIZEOF, NULL, \
	(MXFF_IN_DESCRIPTION | MXFF_IN_SUMMARY | MXFF_VARARGS) }

#define MX_DOUBLE_VARIABLE_STANDARD_FIELDS \
  {MXLV_VAR_VALUE, -1, "value", MXFT_DOUBLE, NULL, \
	MXU_VARARGS_LENGTH, {MXU_VARARGS_LENGTH}, \
	MXF_REC_SUPERCLASS_STRUCT, offsetof(MX_VARIABLE, pointer_to_value), \
	MXA_DOUBLE_SIZEOF, NULL, \
	(MXFF_IN_DESCRIPTION | MXFF_IN_SUMMARY | MXFF_VARARGS) }

#define MX_RECORD_VARIABLE_STANDARD_FIELDS \
  {MXLV_VAR_VALUE, -1, "value", MXFT_RECORD, NULL, \
	MXU_VARARGS_LENGTH, {MXU_VARARGS_LENGTH}, \
	MXF_REC_SUPERCLASS_STRUCT, offsetof(MX_VARIABLE, pointer_to_value), \
	MXA_RECORD_SIZEOF, NULL, \
	(MXFF_IN_DESCRIPTION | MXFF_IN_SUMMARY | MXFF_VARARGS) }

#define MX_HEX_VARIABLE_STANDARD_FIELDS   MX_ULONG_VARIABLE_STANDARD_FIELDS

#ifdef __cplusplus
}
#endif

#endif /* __MX_VARIABLE_H__ */

