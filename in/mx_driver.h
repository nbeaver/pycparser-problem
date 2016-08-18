/*
 * Name:     mx_driver.h
 *
 * Purpose:  Contains the preprocessor symbols defining all the MX class
 *           and device types.
 *
 * Notes:    Each site is expected to add any special classes defined at
 *           that site.
 *
 *           Also, do _not_ rely on the numerical value of the #defines
 *           in this file.  They have changed before and may change again.
 *           If you need to save type information in a file, the preferred
 *           mechanism is to use the MX_DRIVER lists to convert the
 *           numerical value back to a text string that can be saved
 *           in a file.
 *
 * Author:   William Lavender
 *
 *--------------------------------------------------------------------------
 *
 * Copyright 1999-2016 Illinois Institute of Technology
 *
 * See the file "LICENSE" for information on usage and redistribution
 * of this file, and for a DISCLAIMER OF ALL WARRANTIES.
 *
 */

#ifndef __MX_DRIVER_H__
#define __MX_DRIVER_H__

#include "mx_record.h"

/* Make the header file C++ safe. */

#ifdef __cplusplus
extern "C" {
#endif

/* The following is a list of currently supported server protocols.
 * The protocol values are ORed together to form the value of the field
 * server_protocols_active in the MX_LIST_HEAD structure for the list.
 * This means that the values must be powers of 2.
 *
 * For a client or standalone program, server_protocols_active will normally
 * be set to zero.
 */

#define MXPROT_MX		1

/* The following three defines are used to select the level of a record. */

/* It is important that MXR_ANY be defined specifically as (-1), since
 * the savefile record classes are listed as bitmasks below.
 */

#define MXR_ANY			(-1)	/* any superclass */
#define MXC_ANY			(-2)	/* any class */
#define MXT_ANY			(-3)	/* any type */

/*========================== Superclasses ===========================*/


#define MXR_LIST_HEAD			1
#define MXR_INTERFACE			2
#define MXR_DEVICE			3
#define MXR_SCAN			4
#define MXR_VARIABLE			5
#define MXR_SERVER			6
#define MXR_OPERATION			7

#define MXR_SPECIAL			9

#define MXR_PLACEHOLDER			32768

/*============================= Classes =============================*/

/* --- List head class --- */

#define MXL_LIST_HEAD			1

/* --- Interface classes --- */

#define MXI_RS232			2
#define MXI_GPIB   			3
#define MXI_CAMAC			4
#define MXI_CONTROLLER			5
#define MXI_PORTIO			6
#define MXI_VME				7
#define MXI_MMIO			8
#define MXI_MODBUS			9
#define MXI_USB				10
#define MXI_CAMERA_LINK			11

/* --- Device classes --- */

#define MXC_ANALOG_INPUT		21
#define MXC_ANALOG_OUTPUT		22
#define MXC_DIGITAL_INPUT		23
#define MXC_DIGITAL_OUTPUT		24
#define MXC_MOTOR			25
#define MXC_ENCODER			26
#define MXC_SCALER			27
#define MXC_TIMER			28
#define MXC_AMPLIFIER			29
#define MXC_RELAY			30
#define MXC_MULTICHANNEL_ANALYZER	31
#define MXC_MULTICHANNEL_SCALER		32
#define MXC_MULTICHANNEL_ENCODER	33
#define MXC_TABLE			34
#define MXC_AUTOSCALE			35
#define MXC_PULSE_GENERATOR		36
#define MXC_SINGLE_CHANNEL_ANALYZER	37

#define MXC_SAMPLE_CHANGER		39
#define MXC_MULTICHANNEL_ANALOG_INPUT	40
#define MXC_MULTICHANNEL_ANALOG_OUTPUT	41
#define MXC_MULTICHANNEL_DIGITAL_INPUT	42
#define MXC_MULTICHANNEL_DIGITAL_OUTPUT	43
#define MXC_PAN_TILT_ZOOM		44
#define MXC_VIDEO_INPUT			45
#define MXC_VIDEO_OUTPUT		46
#define MXC_AREA_DETECTOR		47
#define MXC_WAVEFORM_INPUT		48
#define MXC_WAVEFORM_OUTPUT		49

/* --- Scan classes --- */

#define MXS_LINEAR_SCAN			51
#define MXS_LIST_SCAN			52
#define MXS_XAFS_SCAN			53
#define MXS_QUICK_SCAN			54
#define MXS_AREA_DETECTOR_SCAN		55

/* --- Variable classes --- */

#define MXV_INLINE			61
#define MXV_NETWORK			62
#define MXV_EPICS			63
#define MXV_CALC			64
#define MXV_PMAC			65
#define MXV_SPEC			66
#define MXV_BLUICE			67
#define MXV_FILE			68
#define MXV_U500			69
#define MXV_POWERPMAC			70
#define MXV_FIELD			71
#define MXV_SPECIAL			72

/* --- Server classes --- */

#define MXN_NETWORK_SERVER		81
#define MXN_SPEC			82
#define MXN_BLUICE			83

/* --- Operation classes --- */

#define MXO_OPERATION			501

/* --- Special classes --- */

#define MXZ_PROGRAM			901
#define MXZ_MOD				902
#define MXZ_DICTIONARY			903

/*============================= Types =============================*/

/* --- List head type --- */

#define MXT_LIST_HEAD			99

/* --- Interface types --- */

#define MXI_232_SOFTWARE		100
#define MXI_232_TTY			101
#define MXI_232_COM			102
#define MXI_232_FOSSIL			103
#define MXI_232_KS3344			104
#define MXI_232_WIN32COM		105
#define MXI_232_TCP232			106

#define MXI_232_NETWORK			108
#define MXI_232_VMS			109
#define MXI_232_VXWORKS			110
#define MXI_232_WAGO750_SERIAL		111
#define MXI_232_CAMERA_LINK		112
#define MXI_232_TELNET			113
#define MXI_232_SIM900_PORT		114
#define MXI_232_FILE			115

#define MXI_232_SPEC_COMMAND		150

#define MXI_GPIB_SOFTWARE		200
#define MXI_GPIB_NI488			201
#define MXI_GPIB_LINUX			202
#define MXI_GPIB_K500SERIAL		203

#define MXI_GPIB_MICRO488EX		205
#define MXI_GPIB_NETWORK		206
#define MXI_GPIB_PROLOGIX		207

#define MXI_CAM_SOFTWARE		300
#define MXI_CAM_DSP6001			301

#define MXI_CTRL_MM3000			400
#define MXI_CTRL_MM4000			401
#define MXI_CTRL_ESP			402
#define MXI_CTRL_PMAC			403
#define MXI_CTRL_COMPUMOTOR		404
#define MXI_CTRL_ORTEC974		405

#define MXI_CTRL_D8			408
#define MXI_CTRL_PDI40			409
#define MXI_CTRL_PDI45			410
#define MXI_CTRL_VP9000			411
#define MXI_CTRL_8255			412
#define MXI_CTRL_AM9513			413
#define MXI_CTRL_HSC1			414
#define MXI_CTRL_VME58			415
#define MXI_CTRL_VSC16			416
#define MXI_CTRL_SCIPE			417

#define MXI_CTRL_PCSTEP			419
#define MXI_CTRL_6821			420
#define MXI_CTRL_DATABOX		421

#define MXI_CTRL_LPT			426
#define MXI_CTRL_SIS3807		427
#define MXI_CTRL_MARDTB			428
#define MXI_CTRL_UGLIDE			429
#define MXI_CTRL_VME58_ESRF		430
#define MXI_CTRL_APS_ADCMOD2		431
#define MXI_CTRL_LINUX_PARPORT		432
#define MXI_CTRL_CXTILT02		433
#define MXI_CTRL_ISERIES		434
#define MXI_CTRL_PHIDGET_OLD_STEPPER	435
#define MXI_CTRL_PFCU			436
#define MXI_CTRL_KEITHLEY2700		437
#define MXI_CTRL_KEITHLEY2400		438
#define MXI_CTRL_KEITHLEY2000		439

#define MXI_CTRL_KOHZU_SC		441

#define MXI_CTRL_PICOMOTOR		443
#define MXI_CTRL_SR630			444
#define MXI_CTRL_TPG262			445
#define MXI_CTRL_CM17A			446
#define MXI_CTRL_SONY_VISCA		447
#define MXI_CTRL_PANASONIC_KX_DP702	448

#define MXI_CTRL_SPELLMAN_DF3		451
#define MXI_CTRL_BKPRECISION_912X	452
#define MXI_CTRL_ISOBUS			453
#define MXI_CTRL_ILM			454
#define MXI_CTRL_ITC503			455
#define MXI_CTRL_CRYOJET		456

#define MXI_CTRL_LINKAM_T9X		459

#define MXI_CTRL_SIM900			461
#define MXI_CTRL_I404			462
#define MXI_CTRL_SYNACCESS_NETBOOTER	463
#define MXI_CTRL_NEWPORT_XPS		464

#define MXI_PIO_PORTIO			600
#define MXI_PIO_DOS			601
#define MXI_PIO_IOPL			602
#define MXI_PIO_IOPERM			603
#define MXI_PIO_VXWORKS			604

#define MXI_VME_VXWORKS			700
#define MXI_VME_MMAP			701
#define MXI_VME_RTEMS			702

#define MXI_MOD_TCP			800
#define MXI_MOD_SERIAL_RTU		801

#define MXI_CL_SOFTWARE			900
#define MXI_CL_NETWORK			901
#define MXI_CL_API			902


/* --- Analog input types --- */

#define MXT_AIN_SOFTWARE		10000
#define MXT_AIN_KS3512			10001
#define MXT_AIN_PDI45			10002

#define MXT_AIN_NETWORK			10005
#define MXT_AIN_PMAC			10006

#define MXT_AIN_MCA_VALUE		10009
#define MXT_AIN_MARDTB_STATUS		10010
#define MXT_AIN_SCIPE			10011
#define MXT_AIN_CRYOSTREAM600		10012
#define MXT_AIN_MCLENNAN		10013
#define MXT_AIN_ICPLUS			10014
#define MXT_AIN_QBPM			10015
#define MXT_AIN_SI9650			10016
#define MXT_AIN_MDRIVE			10017
#define MXT_AIN_APS_ADCMOD2		10018
#define MXT_AIN_APS_ADCMOD2_AVERAGE	10019
#define MXT_AIN_ITC503			10020
#define MXT_AIN_SMARTMOTOR		10021
#define MXT_AIN_CXTILT02		10022
#define MXT_AIN_MODBUS			10023
#define MXT_AIN_ISERIES			10024
#define MXT_AIN_MCAI_FUNCTION		10025
#define MXT_AIN_KEITHLEY2700		10026
#define MXT_AIN_KEITHLEY2400		10027
#define MXT_AIN_KEITHLEY2000		10028

#define MXT_AIN_PICOMOTOR		10031
#define MXT_AIN_TRACKER			10032
#define MXT_AIN_SR630			10033
#define MXT_AIN_P6000A			10034
#define MXT_AIN_TPG262			10035
#define MXT_AIN_BLUICE_DCSS_ION_CHAMBER	10036
#define MXT_AIN_BLUICE_DHS_ION_CHAMBER	10037
#define MXT_AIN_SPELLMAN_DF3		10038
#define MXT_AIN_BKPRECISION_912X	10039
#define MXT_AIN_ILM			10040
#define MXT_AIN_CRYOJET			10041
#define MXT_AIN_MCA_WEIGHTED_SUM	10042

#define MXT_AIN_SIM980			10046
#define MXT_AIN_SYNACCESS_NETBOOTER	10047

/* --- Analog input subclasses -- */

#define MXT_AIN_LONG			101
#define MXT_AIN_DOUBLE			102

/* --- Analog output types --- */

#define MXT_AOU_SOFTWARE		20000
#define MXT_AOU_KS3112			20001
#define MXT_AOU_PDI45			20002

#define MXT_AOU_NETWORK			20005
#define MXT_AOU_PMAC			20006
#define MXT_AOU_SCIPE			20007
#define MXT_AOU_MCLENNAN		20008
#define MXT_AOU_ICPLUS			20009
#define MXT_AOU_QBPM			20010
#define MXT_AOU_CYBERSTAR_X1000		20011
#define MXT_AOU_ITC503			20012
#define MXT_AOU_SMARTMOTOR		20013
#define MXT_AOU_MODBUS			20014
#define MXT_AOU_WAGO750_MODBUS		20015
#define MXT_AOU_ISERIES			20016
#define MXT_AOU_KEITHLEY2400		20017

#define MXT_AOU_TRACKER			20020
#define MXT_AOU_SR630			20021
#define MXT_AOU_SPELLMAN_DF3		20022
#define MXT_AOU_BKPRECISION_912X	20023
#define MXT_AOU_CRYOJET			20024
#define MXT_AOU_SYSTRON_DONNER_M107	20025
#define MXT_AOU_LINKAM_T9X_PUMP		20026
#define MXT_AOU_FANOUT			20027

/* --- Analog output subclasses -- */

#define MXT_AOU_LONG			201
#define MXT_AOU_DOUBLE			202

/* --- Digital input types --- */

#define MXT_DIN_SOFTWARE		30000
#define MXT_DIN_KS3063			30001
#define MXT_DIN_PDI45			30002

#define MXT_DIN_NETWORK			30005
#define MXT_DIN_8255			30006
#define MXT_DIN_6821			30007
#define MXT_DIN_BIT			30008
#define MXT_DIN_VME			30009
#define MXT_DIN_PMAC			30010
#define MXT_DIN_COMPUMOTOR		30011
#define MXT_DIN_LPT			30012
#define MXT_DIN_PORTIO			30013
#define MXT_DIN_SCIPE			30014
#define MXT_DIN_MCLENNAN		30015
#define MXT_DIN_ICPLUS			30016
#define MXT_DIN_QBPM			30017
#define MXT_DIN_MDRIVE			30018
#define MXT_DIN_LINUX_PARPORT		30019
#define MXT_DIN_SMARTMOTOR		30020
#define MXT_DIN_MODBUS			30021
#define MXT_DIN_ISERIES			30022

#define MXT_DIN_PICOMOTOR		30026
#define MXT_DIN_TRACKER			30027

#define MXT_DIN_SPELLMAN_DF3		30029
#define MXT_DIN_BKPRECISION_912X	30030
#define MXT_DIN_ILM			30031
#define MXT_DIN_ITC503			30032
#define MXT_DIN_CRYOJET			30033

#define MXT_DIN_KEYBOARD		30035
#define MXT_DIN_FILE			30036
#define MXT_DIN_AINPUT			30037
#define MXT_DIN_FANIN			30038

/* --- Digital output types --- */

#define MXT_DOU_SOFTWARE		40000
#define MXT_DOU_KS3063			40001
#define MXT_DOU_PDI45			40002

#define MXT_DOU_NETWORK			40005
#define MXT_DOU_8255			40006
#define MXT_DOU_6821			40007
#define MXT_DOU_BIT			40008
#define MXT_DOU_VME			40009
#define MXT_DOU_PMAC			40010
#define MXT_DOU_COMPUMOTOR		40011
#define MXT_DOU_LPT			40012
#define MXT_DOU_PORTIO			40013
#define MXT_DOU_SCIPE			40014
#define MXT_DOU_MCLENNAN		40015
#define MXT_DOU_ICPLUS			40016
#define MXT_DOU_QBPM			40017
#define MXT_DOU_MDRIVE			40018
#define MXT_DOU_LINUX_PARPORT		40019
#define MXT_DOU_SMARTMOTOR		40020
#define MXT_DOU_MODBUS			40021
#define MXT_DOU_WAGO750_MODBUS		40022
#define MXT_DOU_ISERIES			40023
#define MXT_DOU_KEITHLEY2400		40024

#define MXT_DOU_PFCU_FILTER_SUMMARY	40026

#define MXT_DOU_PICOMOTOR		40028
#define MXT_DOU_TRACKER			40029
#define MXT_DOU_TPG262			40030
#define MXT_DOU_CM17A			40031

#define MXT_DOU_SPELLMAN_DF3		40033
#define MXT_DOU_BKPRECISION_912X	40034
#define MXT_DOU_ILM_SAMPLE_RATE		40035
#define MXT_DOU_ITC503			40036
#define MXT_DOU_CRYOJET			40037
#define MXT_DOU_AOUTPUT			40038
#define MXT_DOU_RELAY			40039
#define MXT_DOU_FANOUT			40040

/* --- Motor subclasses --- */

#define MXC_MTR_STEPPER			501
#define MXC_MTR_ANALOG			502

/* --- Motor types --- */

#define MXT_MTR_SOFTWARE		50000
#define MXT_MTR_E500			50001
#define MXT_MTR_SMC24			50002
#define MXT_MTR_PANTHER_HI		50003
#define MXT_MTR_PANTHER_HE		50004
#define MXT_MTR_MMC32			50005
#define MXT_MTR_PM304			50006

#define MXT_MTR_MM3000			50008
#define MXT_MTR_MM4000			50009
#define MXT_MTR_ESP			50010
#define MXT_MTR_PMAC			50011

#define MXT_MTR_COMPUMOTOR		50015
#define MXT_MTR_NETWORK			50016

#define MXT_MTR_D8			50018
#define MXT_MTR_VP9000			50019
#define MXT_MTR_AM9513			50020
#define MXT_MTR_HSC1			50021
#define MXT_MTR_E662			50022
#define MXT_MTR_STP100			50023
#define MXT_MTR_PDI40			50024
#define MXT_MTR_VME58			50025
#define MXT_MTR_SCIPE			50026

#define MXT_MTR_PCSTEP			50028
#define MXT_MTR_DAC_MOTOR		50029
#define MXT_MTR_LAKESHORE330		50030
#define MXT_MTR_DATABOX			50031
#define MXT_MTR_DISABLED		50032
#define MXT_MTR_MARDTB			50033
#define MXT_MTR_CRYOSTREAM600		50034
#define MXT_MTR_SI9650			50035
#define MXT_MTR_UGLIDE			50036
#define MXT_MTR_MCLENNAN		50037
#define MXT_MTR_MDRIVE			50038
#define MXT_MTR_ITC503			50039
#define MXT_MTR_PMAC_COORDINATE_SYSTEM	50040
#define MXT_MTR_SMARTMOTOR		50041
#define MXT_MTR_PHIDGET_OLD_STEPPER	50042
#define MXT_MTR_SPEC			50043

#define MXT_MTR_KOHZU_SC		50045

#define MXT_MTR_PICOMOTOR		50047
#define MXT_MTR_MCU2			50048
#define MXT_MTR_BLUICE_DCSS		50049
#define MXT_MTR_BLUICE_DHS		50050
#define MXT_MTR_PTZ			50051
#define MXT_MTR_SRC_MONO		50052
#define MXT_MTR_CRYOJET			50053
#define MXT_MTR_LINKAM_T9X_TEMPERATURE	50054
#define MXT_MTR_LINKAM_T9X_MOTOR	50055

#define MXT_MTR_SIM960			50057
#define MXT_MTR_NEWPORT_XPS		50058

   /* Pseudomotors. */

#define MXT_MTR_ENERGY			55001
#define MXT_MTR_WAVELENGTH		55002
#define MXT_MTR_WAVENUMBER		55003
#define MXT_MTR_SLIT_MOTOR		55004
#define MXT_MTR_TRANSLATION		55005
#define MXT_MTR_XAFS_WAVENUMBER		55006
#define MXT_MTR_DELTA           	55007
#define MXT_MTR_ELAPSED_TIME		55008
#define MXT_MTR_MONOCHROMATOR		55009
#define MXT_MTR_LINEAR_FUNCTION		55010
#define MXT_MTR_TABLE			55011
#define MXT_MTR_THETA_2THETA		55012
#define MXT_MTR_Q			55013
#define MXT_MTR_SEGMENTED_MOVE		55014
#define MXT_MTR_TANGENT_ARM		55015
#define MXT_MTR_SINE_ARM		55016
#define MXT_MTR_AFRAME_DETECTOR_MOTOR	55017
#define MXT_MTR_ADSC_TWO_THETA		55018
#define MXT_MTR_RECORD_FIELD		55019
#define MXT_MTR_GATED_BACKLASH		55020
#define MXT_MTR_POLYNOMIAL		55021
#define MXT_MTR_CUBIC_SPLINE		55022
#define MXT_MTR_LIMITED_MOVE		55023

#define MXT_MTR_ALS_DEWAR_POSITIONER	55103
#define MXT_MTR_COORDINATED_ANGLE	55104

#define MXT_MTR_COMPUMOTOR_LINEAR	55501

/* --- Encoder types --- */

#define MXT_ENC_SOFTWARE		60000
#define MXT_ENC_KS3640			60001

/* --- Scaler types --- */

#define MXT_SCL_SOFTWARE		70000
#define MXT_SCL_QS450			70001
#define MXT_SCL_KS3610			70002
#define MXT_SCL_PDI45			70003

#define MXT_SCL_ORTEC974		70005
#define MXT_SCL_NETWORK			70006
#define MXT_SCL_AM9513			70007
#define MXT_SCL_MCS			70008
#define MXT_SCL_VSC16			70009
#define MXT_SCL_SCIPE			70010
#define MXT_SCL_MCA_CHANNEL		70011
#define MXT_SCL_MCA_ROI_INTEGRAL	70012
#define MXT_SCL_MCA_ALTERNATE_TIME	70013
#define MXT_SCL_DATABOX			70014
#define MXT_SCL_AUTOSCALE		70015
#define MXT_SCL_GAIN_TRACKING		70016
#define MXT_SCL_SCALER_FUNCTION		70017
#define MXT_SCL_SPEC			70018
#define MXT_SCL_GM10			70019
#define MXT_SCL_FUNCTION_GENERATOR	70020

/* --- Timer types --- */

#define MXT_TIM_SOFTWARE		80000
#define MXT_TIM_RTC018			80001
#define MXT_TIM_PDI45			80002

#define MXT_TIM_ORTEC974		80004
#define MXT_TIM_NETWORK			80005
#define MXT_TIM_AM9513			80006
#define MXT_TIM_MCS			80007
#define MXT_TIM_VSC16			80008
#define MXT_TIM_SCIPE			80009
#define MXT_TIM_MCA			80010
#define MXT_TIM_FANOUT			80011
#define MXT_TIM_DATABOX			80012
#define MXT_TIM_PFCU_SHUTTER		80013
#define MXT_TIM_SPEC			80014
#define MXT_TIM_GM10			80015
#define MXT_TIM_INTERVAL		80016
#define MXT_TIM_BLUICE_DCSS		80017
#define MXT_TIM_BLUICE_DHS		80018

#define MXT_TIM_AREA_DETECTOR		80022

/* --- Amplifier types --- */

#define MXT_AMP_SOFTWARE		90000
#define MXT_AMP_NETWORK			90001
#define MXT_AMP_KEITHLEY428		90002
#define MXT_AMP_SR570			90003
#define MXT_AMP_SCIPE			90004
#define MXT_AMP_ICPLUS			90005
#define MXT_AMP_QBPM			90006
#define MXT_AMP_APS_ADCMOD2		90007
#define MXT_AMP_UDT_TRAMP		90008

#define MXT_AMP_KEITHLEY2700		90010
#define MXT_AMP_KEITHLEY2400		90011
#define MXT_AMP_KEITHLEY2000		90012
#define MXT_AMP_SIM983			90013
#define MXT_AMP_I404			90014

/* --- Relay types --- */

#define MXT_RLY_SOFTWARE		100000
#define MXT_RLY_NETWORK			100001
#define MXT_RLY_GENERIC			100002
#define MXT_RLY_BLIND  			100003
#define MXT_RLY_PULSED 			100004
#define MXT_RLY_MARCCD_SHUTTER		100005
#define MXT_RLY_PFCU_FILTER		100006
#define MXT_RLY_PFCU_SHUTTER		100007
#define MXT_RLY_MARDTB_SHUTTER		100008
#define MXT_RLY_BLUICE_DCSS_SHUTTER	100009
#define MXT_RLY_BLUICE_DHS_SHUTTER	100010
#define MXT_RLY_SYNACCESS_NETBOOTER	100011

/* --- Multichannel analyzer types --- */

#define MXT_MCA_SOFTWARE		110000
#define MXT_MCA_NETWORK			110001

#define MXT_MCA_ROENTEC_RCL		110005
#define MXT_MCA_MONTE_CARLO		110006

/* --- Multichannel encoder types --- */

#define MXT_MCE_SOFTWARE		120001
#define MXT_MCE_NETWORK			120002
#define MXT_MCE_MCS			120003
#define MXT_MCE_DATABOX			120004
#define MXT_MCE_MCS_TIME		120005
#define MXT_MCE_PMAC			120006

/* --- Multichannel scaler types --- */

#define MXT_MCS_SOFTWARE		130000
#define MXT_MCS_NETWORK			130001

#define MXT_MCS_DATABOX			130003
#define MXT_MCS_SIS3801			130004

#define MXT_MCS_SCALER_FUNCTION		130006

/* --- Table types --- */

#define MXT_TAB_ADC			140001

/* --- Autoscale types --- */

#define MXT_AUT_FILTER			150001
#define MXT_AUT_AMPLIFIER		150002
#define MXT_AUT_NETWORK			150003
#define MXT_AUT_FILTER_AMPLIFIER	150004

/* --- Pulse generator types --- */

#define MXT_PGN_SOFTWARE		160001
#define MXT_PGN_NETWORK			160002
#define MXT_PGN_SIS3807			160003
#define MXT_PGN_SIS3801			160004
#define MXT_PGN_PDI45			160005

#define MXT_PGN_DIGITAL_OUTPUT		160008
#define MXT_PGN_GITTELSOHN		160009

/* --- Single channel analyzer types --- */

#define MXT_SCA_SOFTWARE		170001
#define MXT_SCA_NETWORK			170002
#define MXT_SCA_CYBERSTAR_X1000		170003

/* --- Sample changer types --- */

#define MXT_CHG_SOFTWARE		190001
#define MXT_CHG_NETWORK			190002

#define MXT_CHG_SERCAT_ALS_ROBOT	190004

/* --- Multichannel analog input types --- */

#define MXT_MCAI_SOFTWARE		200001
#define MXT_MCAI_NETWORK		200002
#define MXT_MCAI_QBPM			200003
#define MXT_MCAI_I404			200004

/* --- Pan/Tilt/Zoom types --- */

#define MXT_PTZ_SOFTWARE		210001
#define MXT_PTZ_NETWORK			210002
#define MXT_PTZ_SONY_VISCA		210003
#define MXT_PTZ_HITACHI_KP_D20		210004
#define MXT_PTZ_PANASONIC_KX_DP702	210005
#define MXT_PTZ_CANON_VC_C4		210006

/* --- Video input types --- */

#define MXT_VIN_SOFTWARE		220001
#define MXT_VIN_NETWORK			220002
#define MXT_VIN_FILE			220003
#define MXT_VIN_SONY_SNC		220004

/* --- Video output types --- */

#define MXT_VOU_SOFTWARE		230001
#define MXT_VOU_NETWORK			230002

/* --- Area detector types --- */

#define MXT_AD_SOFTWARE			240001
#define MXT_AD_FILE			240002
#define MXT_AD_NETWORK			240003

#define MXT_AD_MARCCD			240009
#define MXT_AD_BLUICE_DCSS		240010
#define MXT_AD_BLUICE_DHS		240011
#define MXT_AD_MARCCD_SERVER_SOCKET	240012

#define MXT_AD_MLFSOM			240014

#define MXT_AD_MAR345			240016
#define MXT_AD_PILATUS			240017
#define MXT_AD_MERLIN_MEDIPIX		240018

/* --- Waveform input types --- */

#define MXT_WVI_SOFTWARE		250001
#define MXT_WVI_NETWORK			250002

/* --- Waveform output types --- */

#define MXT_WVO_SOFTWARE		260001
#define MXT_WVO_NETWORK			260002
#define MXT_WVO_BKPRECISION_912X	260003
#define MXT_WVO_WGM_101			260004

/* --- Scan types --- */

#define MXS_LIN_INPUT 			401001
#define MXS_LIN_MOTOR			401002
#define MXS_LIN_2THETA			401003
#define MXS_LIN_SLIT			401004
#define MXS_LIN_PSEUDOMOTOR		401005
#define MXS_LIN_K_POWER_LAW		401006

#define MXS_LST_FILE			403001
#define MXS_LST_MEMORY			403002

#define MXS_XAF_STANDARD		405001
#define MXS_XAF_K_POWER_LAW		405002

#define MXS_QUI_MCS			407001

#define MXS_QUI_ENERGY_MCS		407103

#define MXS_QUI_APS_ID			407201

#define MXS_AD_WEDGE			409001

/* --- Variable types --- */

#define MXV_INL_STRING			500001
#define MXV_INL_CHAR			500002
#define MXV_INL_UCHAR			500003
#define MXV_INL_SHORT			500004
#define MXV_INL_USHORT			500005
#define MXV_INL_BOOL			500006
#define MXV_INL_LONG			500008
#define MXV_INL_ULONG			500009
#define MXV_INL_FLOAT			500010
#define MXV_INL_DOUBLE			500011
#define MXV_INL_INT64			500014
#define MXV_INL_UINT64			500015
#define MXV_INL_RECORD			500031

#define MXV_NET_STRING			501001
#define MXV_NET_CHAR			501002
#define MXV_NET_UCHAR			501003
#define MXV_NET_SHORT			501004
#define MXV_NET_USHORT			501005
#define MXV_NET_BOOL			501006
#define MXV_NET_LONG			501008
#define MXV_NET_ULONG			501009
#define MXV_NET_FLOAT			501010
#define MXV_NET_DOUBLE			501011
#define MXV_NET_INT64			501014
#define MXV_NET_UINT64			501015
#define MXV_NET_RECORD			501031

#define MXV_EPI_STRING			502001
#define MXV_EPI_CHAR			502002
#define MXV_EPI_SHORT			502004
#define MXV_EPI_INT			502006
#define MXV_EPI_LONG			502008
#define MXV_EPI_FLOAT			502010
#define MXV_EPI_DOUBLE			502011

#define MXV_CAL_MATHOP			503001
#define MXV_CAL_POLYNOMIAL		503002

#define MXV_CAL_POSITION_SELECT		503601

#define MXV_CAL_INDIRECT_STRING		503701

#define MXV_PMA_LONG			504008
#define MXV_PMA_ULONG			504009
#define MXV_PMA_DOUBLE			504011

#define MXV_SPEC_STRING			505001
#define MXV_SPEC_CHAR			505002
#define MXV_SPEC_UCHAR			505003
#define MXV_SPEC_SHORT			505004
#define MXV_SPEC_USHORT			505005
#define MXV_SPEC_LONG			505008
#define MXV_SPEC_ULONG			505009
#define MXV_SPEC_FLOAT			505010
#define MXV_SPEC_DOUBLE			505011

#define MXV_BLUICE_MASTER		506001
#define MXV_BLUICE_COMMAND		506002
#define MXV_BLUICE_DCSS_STRING		506003
#define MXV_BLUICE_DHS_STRING		506004
#define MXV_BLUICE_SELF_STRING		506005
#define MXV_BLUICE_DCSS_OPERATION	506006
#define MXV_BLUICE_DHS_OPERATION	506007
#define MXV_BLUICE_SELF_OPERATION	506008

#define MXV_FILE_STRING			507001
#define MXV_FILE_LONG			507008
#define MXV_FILE_ULONG			507009
#define MXV_FILE_DOUBLE			507011

#define MXV_FIELD_STRING		508001
#define MXV_FIELD_CHAR			508002
#define MXV_FIELD_UCHAR			508003
#define MXV_FIELD_SHORT			508004
#define MXV_FIELD_USHORT		508005
#define MXV_FIELD_BOOL			508006
#define MXV_FIELD_LONG			508008
#define MXV_FIELD_ULONG			508009
#define MXV_FIELD_FLOAT			508010
#define MXV_FIELD_DOUBLE		508011
#define MXV_FIELD_HEX			508012
#define MXV_FIELD_INT64			508014
#define MXV_FIELD_UINT64		508015
#define MXV_FIELD_RECORD		508031

/* --- Server types --- */

#define MXN_NET_TCPIP			600001
#define MXN_NET_UNIX			600002

#define MXN_SPEC_SERVER			601001

#define MXN_BLUICE_DCSS_SERVER		602001
#define MXN_BLUICE_DHS_SERVER		602002

#define MXN_BLUICE_DHS_MANAGER		602101

/* --- Operation types --- */

#define MXO_NETWORK			700001
#define MXO_TOAST			700002

/* --- Special types --- */

#define MXZ_PRG_EXTERNAL_COMMAND	900001
#define MXZ_DICT_DICTIONARY		900002

#ifdef __cplusplus
}
#endif

#endif /* __MX_DRIVER_H__ */
