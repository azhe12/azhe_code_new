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
#ifndef INC_DISPMESG_H
#define INC_DISPMESG_H

/* Standard include files for windows.*/
#include "AKCommon.h"

/* Include file for user definition.*/
#include "CustomerSpec.h"

#include "AccSensorFunction.h"

/* Include file for AK8975 library.*/
#include "AKCompass.h"

/*========================= Type declaration ==================================*/
/* These defined types are passed to Disp_ErrorMessage() function.             */
typedef enum _ERROR_MESSAGE_ID{
	ERMES_DEVNAME_INVALID,
	ERMES_INIT_DEVICE_FAILED,
	ERMES_TMPFILEOPEN_FAILED,
	ERMES_LOAD_PARAMS_FAILED,
	ERMES_FCTSHIPMNTTEST_ABORTED,
	ERMES_DETECT_INTPIN_HIGH_FAILED,
	ERMES_NO_OPERATION_SELECTED,
	ERMES_INIT_AK8973_FAILED,
	ERMES_MEASURING_FAILED
} ERROR_MESSAGE_ID;

/* These defined values are passed to Disp_StatusMessage() function.*/
/* These defined types represents the current mode.*/

typedef enum _MODE{
	MODE_ERROR,
	MODE_FctShipmntTestBody,
	MODE_MeasureCONT,
	MODE_MeasureSNG,
	MODE_MeasureSNGWithoutDRDY,
	MODE_MeasureTrigger,
	MODE_HDOECalibration,
	MODE_HCalibration,
	MODE_ACalibration,
	MODE_Quit
} MODE;

typedef enum _MSGLEVELS{
	MSG_LEVEL0,	/* ALWAYS DISPLAY*/
	MSG_LEVEL1	/* INFORMATION*/
} MSGLEVELS;

#define DISPMESSAGE_LEVEL	MSG_LEVEL1

/*========================= Prototype of Function =============================
 *	Disp_	: Display messages.
 *	Menu_	: Display menu (two or more selection) and wait for user to select one.
 *=============================================================================*/
void Disp_StartMessage(void);
void Disp_EndMessage(void);

void DispMessage(
	const MSGLEVELS msgLevel,
	const char *format,
	...
);

void Disp_MeasurementResult(AK8975PRMS *prms);
void Disp_HDOECalibResult(AK8975PRMS *prms);
void Disp_HDOELevel(AK8975PRMS *prms);
void Disp_ErrorMessage(ERROR_MESSAGE_ID errID);

int16	Menu_ACalibration(void);
int16	Menu_FctShipmntTest(void);
MODE	Menu_Main(void);
int16	Menu_YesNo(void);

void	Prmpt_Kbhit(void);
int16	Prmpt_ComPort(char *strCom);

int16 TEST_DATA(
	const char testno[],
	const char testname[],
	const int16 testdata,
	const int16 lolimit,
	const int16 hilimit,
	int16 *pf_total
);

#endif


