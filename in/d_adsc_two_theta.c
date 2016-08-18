/*
 * Name:    d_adsc_two_theta.c 
 *
 * Purpose: MX motor driver to control the two theta angle of an 
 *          ADSC Quantum 210 goniostat by changing the detector height.
 *
 * Author:  William Lavender
 *
 * WARNING: This driver expects height to be in mm and angle to be in degrees.
 *
 *--------------------------------------------------------------------------
 *
 * Copyright 2002-2003, 2015-2016 Illinois Institute of Technology
 *
 * See the file "LICENSE" for information on usage and redistribution
 * of this file, and for a DISCLAIMER OF ALL WARRANTIES.
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <math.h>

#include "mx_util.h"
#include "mx_driver.h"
#include "mx_variable.h"
#include "mx_motor.h"
#include "d_adsc_two_theta.h"

/* Initialize the motor driver jump table. */

MX_RECORD_FUNCTION_LIST mxd_adsc_two_theta_record_function_list = {
	NULL,
	mxd_adsc_two_theta_create_record_structures,
	mxd_adsc_two_theta_finish_record_initialization,
	NULL,
	mxd_adsc_two_theta_print_motor_structure
};

MX_MOTOR_FUNCTION_LIST mxd_adsc_two_theta_motor_function_list = {
	NULL,
	mxd_adsc_two_theta_move_absolute,
	mxd_adsc_two_theta_get_position,
	mxd_adsc_two_theta_set_position,
	mxd_adsc_two_theta_soft_abort,
	mxd_adsc_two_theta_immediate_abort,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	NULL,
	mxd_adsc_two_theta_get_status
};

/* Photon adsc_two_theta motor data structures. */

MX_RECORD_FIELD_DEFAULTS mxd_adsc_two_theta_record_field_defaults[] = {
	MX_RECORD_STANDARD_FIELDS,
	MX_ANALOG_MOTOR_STANDARD_FIELDS,
	MX_MOTOR_STANDARD_FIELDS,
	MXD_ADSC_TWO_THETA_STANDARD_FIELDS
};

long mxd_adsc_two_theta_num_record_fields
		= sizeof( mxd_adsc_two_theta_record_field_defaults )
			/ sizeof( mxd_adsc_two_theta_record_field_defaults[0] );

MX_RECORD_FIELD_DEFAULTS *mxd_adsc_two_theta_rfield_def_ptr
			= &mxd_adsc_two_theta_record_field_defaults[0];

/* A private function for the use of the driver. */

static mx_status_type
mxd_adsc_two_theta_get_pointers( MX_MOTOR *motor,
			MX_ADSC_TWO_THETA **adsc_two_theta,
			MX_RECORD **height_motor_record,
			const char *calling_fname )
{
	static const char fname[] = "mxd_adsc_two_theta_get_pointers()";

	if ( motor == (MX_MOTOR *) NULL ) {
		return mx_error( MXE_NULL_ARGUMENT, fname,
			"The MX_MOTOR pointer passed by '%s' was NULL.",
			calling_fname );
	}

	if ( adsc_two_theta == (MX_ADSC_TWO_THETA **) NULL ) {
		return mx_error( MXE_NULL_ARGUMENT, fname,
		"The adsc_two_theta pointer passed by '%s' was NULL.",
			calling_fname );
	}

	*adsc_two_theta = (MX_ADSC_TWO_THETA *)
				motor->record->record_type_struct;

	if ( *adsc_two_theta == (MX_ADSC_TWO_THETA *) NULL ) {
		return mx_error( MXE_CORRUPT_DATA_STRUCTURE, fname,
		"The MX_ADSC_TWO_THETA pointer for record '%s' is NULL.",
			motor->record->name );
	}

	if ( height_motor_record == (MX_RECORD **) NULL ) {
		return mx_error( MXE_NULL_ARGUMENT, fname,
		"The height_motor_record pointer passed by '%s' was NULL.",
			motor->record->name );
	}

	*height_motor_record = (*adsc_two_theta)->height_motor_record;

	if ( *height_motor_record == (MX_RECORD *) NULL ) {
		return mx_error( MXE_CORRUPT_DATA_STRUCTURE, fname,
		"Dependent motor record pointer for record '%s' is NULL.",
			motor->record->name );
	}


	return MX_SUCCESSFUL_RESULT;
}

/* === */

MX_EXPORT mx_status_type
mxd_adsc_two_theta_create_record_structures( MX_RECORD *record )
{
	static const char fname[] =
			"mxd_adsc_two_theta_create_record_structures()";

	MX_MOTOR *motor;
	MX_ADSC_TWO_THETA *adsc_two_theta;

	/* Allocate memory for the necessary structures. */

	motor = (MX_MOTOR *) malloc( sizeof(MX_MOTOR) );

	if ( motor == (MX_MOTOR *) NULL ) {
		return mx_error( MXE_OUT_OF_MEMORY, fname,
		"Can't allocate memory for MX_MOTOR structure." );
	}

	adsc_two_theta = (MX_ADSC_TWO_THETA *)
				malloc( sizeof(MX_ADSC_TWO_THETA) );

	if ( adsc_two_theta == (MX_ADSC_TWO_THETA *) NULL ) {
		return mx_error( MXE_OUT_OF_MEMORY, fname,
	"Can't allocate memory for MX_ADSC_TWO_THETA structure." );
	}

	/* Now set up the necessary pointers. */

	record->record_class_struct = motor;
	record->record_type_struct = adsc_two_theta;
	record->class_specific_function_list
				= &mxd_adsc_two_theta_motor_function_list;

	motor->record = record;

	/* An X-ray adsc_two_theta motor is treated as an analog motor. */

	motor->subclass = MXC_MTR_ANALOG;

	return MX_SUCCESSFUL_RESULT;
}

MX_EXPORT mx_status_type
mxd_adsc_two_theta_finish_record_initialization( MX_RECORD *record )
{
	static const char fname[] =
		"mxd_adsc_two_theta_finish_record_initialization()";

	MX_MOTOR *motor;
	MX_ADSC_TWO_THETA *adsc_two_theta;

	mx_status_type status;

	status = mx_motor_finish_record_initialization( record );

	if ( status.code != MXE_SUCCESS )
		return status;

	motor = (MX_MOTOR *) record->record_class_struct;

	if ( motor == (MX_MOTOR *)NULL ) {
		return mx_error( MXE_CORRUPT_DATA_STRUCTURE, fname,
		"The MX_MOTOR pointer for record '%s' is NULL.",
			record->name );
	}

	motor->motor_flags |= MXF_MTR_IS_PSEUDOMOTOR;

	adsc_two_theta = (MX_ADSC_TWO_THETA *) record->record_type_struct;

	if ( adsc_two_theta == (MX_ADSC_TWO_THETA *)NULL ) {
		return mx_error( MXE_CORRUPT_DATA_STRUCTURE, fname,
		"The MX_ADSC_TWO_THETA pointer for record '%s' is NULL.",
			record->name );
	}

	motor->real_motor_record = adsc_two_theta->height_motor_record;

	return MX_SUCCESSFUL_RESULT;
}

MX_EXPORT mx_status_type
mxd_adsc_two_theta_print_motor_structure( FILE *file, MX_RECORD *record )
{
	static const char fname[] =
			"mxd_adsc_two_theta_print_motor_structure()";

	MX_MOTOR *motor;
	MX_RECORD *height_motor_record;
	MX_MOTOR *height_motor;
	MX_ADSC_TWO_THETA *adsc_two_theta;
	double position, move_deadband;
	mx_status_type status;

	if ( record == (MX_RECORD *) NULL ) {
		return mx_error( MXE_NULL_ARGUMENT, fname,
			"MX_RECORD pointer passed is NULL." );
	}

	motor = (MX_MOTOR *) record->record_class_struct;

	status = mxd_adsc_two_theta_get_pointers( motor, &adsc_two_theta,
					&height_motor_record,fname );

	if ( status.code != MXE_SUCCESS )
		return status;

        height_motor = (MX_MOTOR *) height_motor_record->record_class_struct;

        if ( height_motor == (MX_MOTOR *) NULL ) {
                return mx_error( MXE_CORRUPT_DATA_STRUCTURE, fname,
                        "MX_MOTOR pointer for record '%s' is NULL.",
                        height_motor_record->name );
        }

	fprintf(file, "MOTOR parameters for motor '%s':\n", record->name);
	fprintf(file, "  Motor type             = ADSC_TWO_THETA.\n\n");

	fprintf(file, "  name                   = %s\n", record->name);
	fprintf(file, "  height motor record    = %s\n",
					height_motor_record->name);

	status = mx_motor_get_position( record, &position );

	if ( status.code != MXE_SUCCESS ) {
		return mx_error( MXE_FUNCTION_FAILED, fname,
			"Unable to read position of motor '%s'",
			record->name );
	}

        fprintf(file, "  position               = %.*g %s  (%.*g)\n",
		record->precision,
                motor->position, motor->units,
		record->precision,
                motor->raw_position.analog );
	fprintf(file, "  adsc_two_theta scale   = %.*g %s per unscaled "
						"adsc_two_theta unit.\n",
		record->precision,
		motor->scale, motor->units);
	fprintf(file, "  adsc_two_theta offset          = %.*g %s.\n",
		record->precision,
		motor->offset, motor->units);
        fprintf(file, "  backlash               = %.*g %s  (%.*g).\n",
		record->precision,
                motor->backlash_correction, motor->units,
		record->precision,
                motor->raw_backlash_correction.analog);
        fprintf(file, "  negative limit         = %.*g %s  (%.*g).\n",
		record->precision,
                motor->negative_limit, motor->units,
		record->precision,
                motor->raw_negative_limit.analog);
        fprintf(file, "  positive limit         = %.*g %s  (%.*g).\n",
		record->precision,
		motor->positive_limit, motor->units,
		record->precision,
		motor->raw_positive_limit.analog);

	move_deadband = motor->scale * motor->raw_move_deadband.analog;

	fprintf(file, "  move deadband          = %.*g %s  (%.*g).\n\n",
		record->precision,
		move_deadband, motor->units,
		record->precision,
		motor->raw_move_deadband.analog);

	return MX_SUCCESSFUL_RESULT;
}

/*=======================================================================*/

/* The two following functions were obtained from Chris Nielson of
 * Area Detector Systems Corporation.
 *
 */

#define	RADC	(180. / 3.1415926535)

static double
theta_to_h( double theta )
{
  	static	double	d1 = 13.303 * 25.4;
	static	double	d2 = 28.040 * 25.4;

	double	c,s,t,angle,h;

	angle = theta / RADC;
	c = cos(angle);
	s = sin(angle);
	t = tan(angle);

	h = d1 * (1. - c - s * t) + d2 * t;
	return(h);
}

static double
h_to_theta( double h )
{
  	static	double	d1 = 13.303 * 25.4;
	static	double	d2 = 28.040 * 25.4;
	double	a,b,c,beta1,beta2,sum,angle;

	a = (h - d1) * (h - d1) + d2 * d2;
	b = 2 * d1 * (h - d1);
	c = d1 * d1 - d2 * d2;
	sum = a + b + c;
	beta1 = (-b + sqrt(b * b - 4 * a * c)) / (2 * a);
	beta2 = (-b - sqrt(b * b - 4 * a * c)) / (2 * a);
	angle = RADC * acos(beta1);
	if(h < 0)
		angle = -angle;

	MXW_UNUSED( sum );
	MXW_UNUSED( beta2 );

	return(angle);
}

/*=======================================================================*/

MX_EXPORT mx_status_type
mxd_adsc_two_theta_move_absolute( MX_MOTOR *motor )
{
	static const char fname[] = "mxd_adsc_two_theta_move_absolute()";

	MX_ADSC_TWO_THETA *adsc_two_theta;
	MX_RECORD *height_motor_record;
	double two_theta, height;
	mx_status_type status;

	status = mxd_adsc_two_theta_get_pointers( motor, &adsc_two_theta,
					&height_motor_record,fname );

	if ( status.code != MXE_SUCCESS )
		return status;

	/* The unscaled adsc_two_theta position is in mm. */

	two_theta = motor->raw_destination.analog;

	height = theta_to_h( two_theta );

	status = mx_motor_move_absolute( height_motor_record, height, 0 );

	return status;
}

MX_EXPORT mx_status_type
mxd_adsc_two_theta_get_position( MX_MOTOR *motor )
{
	static const char fname[] = "mxd_adsc_two_theta_get_position()";

	MX_ADSC_TWO_THETA *adsc_two_theta;
	MX_RECORD *height_motor_record;
	double two_theta, height;
	mx_status_type status;

	status = mxd_adsc_two_theta_get_pointers( motor, &adsc_two_theta,
					&height_motor_record,fname );

	if ( status.code != MXE_SUCCESS )
		return status;

	status = mx_motor_get_position( height_motor_record, &height );

	if ( status.code != MXE_SUCCESS )
		return status;

	two_theta = h_to_theta( height );

	motor->raw_position.analog = two_theta;

	return MX_SUCCESSFUL_RESULT;
}

MX_EXPORT mx_status_type
mxd_adsc_two_theta_set_position( MX_MOTOR *motor )
{
	static const char fname[] = "mxd_adsc_two_theta_set_position()";

	MX_ADSC_TWO_THETA *adsc_two_theta;
	MX_RECORD *height_motor_record;
	double two_theta, height;
	mx_status_type status;

	status = mxd_adsc_two_theta_get_pointers( motor, &adsc_two_theta,
					&height_motor_record,fname );

	if ( status.code != MXE_SUCCESS )
		return status;

	two_theta = motor->raw_set_position.analog;

	height = theta_to_h( two_theta );

	status = mx_motor_set_position( height_motor_record, height );

	return status;
}

MX_EXPORT mx_status_type
mxd_adsc_two_theta_soft_abort( MX_MOTOR *motor )
{
	static const char fname[] = "mxd_adsc_two_theta_soft_abort()";

	MX_ADSC_TWO_THETA *adsc_two_theta;
	MX_RECORD *height_motor_record;
	mx_status_type status;

	status = mxd_adsc_two_theta_get_pointers( motor, &adsc_two_theta,
					&height_motor_record,fname );

	if ( status.code != MXE_SUCCESS )
		return status;

	status = mx_motor_soft_abort( height_motor_record );

	return status;
}

MX_EXPORT mx_status_type
mxd_adsc_two_theta_immediate_abort( MX_MOTOR *motor )
{
	static const char fname[] = "mxd_adsc_two_theta_immediate_abort()";

	MX_ADSC_TWO_THETA *adsc_two_theta;
	MX_RECORD *height_motor_record;
	mx_status_type status;

	status = mxd_adsc_two_theta_get_pointers( motor, &adsc_two_theta,
					&height_motor_record,fname );

	if ( status.code != MXE_SUCCESS )
		return status;

	status = mx_motor_immediate_abort( height_motor_record );

	return status;
}

MX_EXPORT mx_status_type
mxd_adsc_two_theta_get_status( MX_MOTOR *motor )
{
	static const char fname[] = "mxd_adsc_two_theta_get_status()";

	MX_ADSC_TWO_THETA *adsc_two_theta;
	MX_RECORD *height_motor_record;
	unsigned long motor_status;
	mx_status_type status;

	status = mxd_adsc_two_theta_get_pointers( motor, &adsc_two_theta,
					&height_motor_record,fname );

	if ( status.code != MXE_SUCCESS )
		return status;

	status = mx_motor_get_status( height_motor_record, &motor_status );

	if ( status.code != MXE_SUCCESS )
		return status;

	motor->status = motor_status;

	return MX_SUCCESSFUL_RESULT;
}

