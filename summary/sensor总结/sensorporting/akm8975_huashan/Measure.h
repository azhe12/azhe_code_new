/******************************************************************************
 * -- Copyright Notice --
 *
 * Copyright (c) 2009 Asahi Kasei Microdevices Corporation, Japan
 * All Rights Reserved.
 *
 * This software program is proprietary program of Asahi Kasei Microdevices
 * Corporation("AKM") licensed to authorized Licensee under Software License
 * Agreement (SLA) executed between the Licensee and AKM.
 *
 * Use of the software by unauthorized third party, or use of the software
 * beyond the scope of the SLA is strictly prohibited.
 *
 * -- End Asahi Kasei Microdevices Copyright Notice --
 *
 ******************************************************************************/
#ifndef INC_MEASURE_H
#define INC_MEASURE_H

/* Include file for windows system.*/
/*#include "AK8975Driver.h"        */

#include "AccSensorFunction.h"

/* Include file for user definition.*/
#include "CustomerSpec.h"

/* Include files for AK8975 library.*/
#include "AKCompass.h"

/*========================= Constant definition =========================//*/
#define AKRET_PROC_SUCCEED	0x01	/* The process has been successfully done.*/
#define AKRET_FORMATION_CHANGED 0x02	/* The formation is changed               */
#define AKRET_HFLUC_OCCURRED	0x03	/* A fluctuation of magnetic field occurred.*/
#define AKRET_DATA_OVERFLOW	0x04	/* Data overflow occurred.                  */
#define AKRET_DATA_READERROR	0x05	/* Data read error occurred.                */

/* Andy Chuang added*/
#define AKRET_PROC_KILL		0x06    /* Error was detected, thread will be close.          */
#define AKRET_PROC_FAIL         0x07    /* Error was detected, but thread will be continue.   */
#define AKRET_PROC_QUIT         0x08    /* The process finished, so that thread will be close.*/
/* End Andy Chuang added*/

/*========================= Type declaration  ===========================//*/
#define KEY_FORM0	'0'
#define KEY_FORMMAX	(KEY_FORM0+CSPEC_NUM_FORMATION-1)
#define KEY_SMALL_C 'c'
#define KEY_LARGE_C 'C'

typedef int16 BYTE;

#define TRUE 1
#define FLASE 0

/*========================= Global variables ============================//*/
/*extern BOOL		g_DRDYIsHigh;                                      */
extern int16	g_Form;

/*========================= Prototype of Function =============================//*/

/*============= May be, these functions are dependent to system. ========*/
int16 WaitForDRDY(void);		/* 0:Timeout (or Failed), 1:Success.*/
int CheckKeyCondition(void);
int16 getFormation(void);

/*============= These functions are independent from system. ============//*/

void InitAK8975PRMS(
	AK8975PRMS	*prms	/*(o)Pointer to parameters of AK8975*/
);

void SetDefaultPRMS(
	AK8975PRMS	*prms /*(i/o)Pointer to parameters of AK8975*/
);

/***************************************************/
/* Example of standard measuring implementation.   */

void ReadAK8975FUSEROM(
	AK8975PRMS	*prms	/*(o)Pointer to parameters of AK8975*/
);

int16 InitAK8975_Measure(
	AK8975PRMS	*prms	/* (i/o)Pointer to parameters of AK8975.*/
);

int16 SwitchFormation(
	AK8975PRMS	*prms	/* (i/o)Pointer to parameters of AK8975*/
);

int16 FctShipmntTest_Body(
	AK8975PRMS	*prms	/* (i/o)Pointer to parameters of AK8975.*/
);

int16 FctShipmntTestProcess_Body(
	AK8975PRMS	*prms		/* (i/o)Pointer to parameters of AK8975.*/
);

void MeasureCONTLoop(
	AK8975PRMS	*prms,	/* (i/o)Pointer to parameters of AK8975.*/
	ACCPRMS	* accprms
);

void MeasureSNGLoop(
	AK8975PRMS	*prms,	/* (i/o)Pointer to parameters of AK8975.*/
	ACCPRMS	* accprms
);

void MeasureSNGWithoutDRDYLoop(
	AK8975PRMS	*prms	/* (i/o)Pointer to parameters of AK8975*/
);

void MeasureTriggerLoop(
	AK8975PRMS	*prms,	/* (i/o)Pointer to parameters of AK8975*/
	ACCPRMS	* accprms
);

int16 MeasuringEventProcess(
	int16		bData[],	/* (i)  Measuring block data*/
	AK8975PRMS	*prms,		/* (i/o)Pointer to parameters of AK8975*/
	int16		curForm,	/* (i)  current formation     */
	int16		hDecimator,	/* (i)  decimator             */
	int16		cntSuspend	/* (i)	the counter of suspend*/
);

/*********************************************************/
void HDOECalibrationLoop(
	AK8975PRMS	*prms	/* (i/o)Pointer to parameters of AK8975*/
);

int16 HDOECalibrationEventProcess(
	int16		bData[],	/* (i)  Measuring block data*/
	AK8975PRMS	*prms,		/* (i/o)Pointer to parameters of AK8975*/
	int16		curForm,	/* (i)  current formation*/
	int16		hDecimator	/* (i)  decimator        */
);

int16 HCalibration(
	AK8975PRMS	*prms		/* (i/o)Pointer to parameters of AK8975*/
);

void GetAccVec(
	AK8975PRMS	*prms,		/* (i)Pointer to parameters of AK8975*/
	ACCPRMS		* accprms,	/* (i/o)Pointer to parameters of AK8975*/
	float		*avecf
);

/****************************************************************/

#endif
