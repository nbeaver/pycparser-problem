/*
 * Name:    d_adsc_two_theta.h 
 *
 * Purpose: Header file for MX motor driver to control the two theta
 *          angle of an ADSC Quantum 210 goniostat by changing the
 *          detector_height.
 *
 * Author:  William Lavender
 *
 * WARNING: This driver expects height to be in mm and angle to be in degrees.
 *
 *--------------------------------------------------------------------------
 *
 * Copyright 2002 Illinois Institute of Technology
 *
 * See the file "LICENSE" for information on usage and redistribution
 * of this file, and for a DISCLAIMER OF ALL WARRANTIES.
 *
 */

#ifndef __D_ADSC_TWO_THETA_H__
#define __D_ADSC_TWO_THETA_H__

/* ===== MX adsc_two_theta motor data structures ===== */

typedef struct {
	MX_RECORD *height_motor_record;
} MX_ADSC_TWO_THETA;

/* Define all of the interface functions. */

MX_API mx_status_type mxd_adsc_two_theta_create_record_structures(
					MX_RECORD *record );
MX_API mx_status_type mxd_adsc_two_theta_finish_record_initialization(
					MX_RECORD *record );
MX_API mx_status_type mxd_adsc_two_theta_print_motor_structure(
					FILE *file, MX_RECORD *record );
MX_API mx_status_type mxd_adsc_two_theta_move_absolute( MX_MOTOR *motor );
MX_API mx_status_type mxd_adsc_two_theta_get_position( MX_MOTOR *motor );
MX_API mx_status_type mxd_adsc_two_theta_set_position( MX_MOTOR *motor );
MX_API mx_status_type mxd_adsc_two_theta_soft_abort( MX_MOTOR *motor );
MX_API mx_status_type mxd_adsc_two_theta_immediate_abort( MX_MOTOR *motor );
MX_API mx_status_type mxd_adsc_two_theta_get_status( MX_MOTOR *motor );

extern MX_RECORD_FUNCTION_LIST mxd_adsc_two_theta_record_function_list;
extern MX_MOTOR_FUNCTION_LIST mxd_adsc_two_theta_motor_function_list;

extern long mxd_adsc_two_theta_num_record_fields;
extern MX_RECORD_FIELD_DEFAULTS *mxd_adsc_two_theta_rfield_def_ptr;

#define MXD_ADSC_TWO_THETA_STANDARD_FIELDS \
  {-1, -1, "height_motor_record", MXFT_RECORD, NULL, 0, {0}, \
        MXF_REC_TYPE_STRUCT, offsetof(MX_ADSC_TWO_THETA, height_motor_record),\
        {0}, NULL, (MXFF_IN_DESCRIPTION | MXFF_IN_SUMMARY) }

#endif /* __D_ADSC_TWO_THETA_H__ */

