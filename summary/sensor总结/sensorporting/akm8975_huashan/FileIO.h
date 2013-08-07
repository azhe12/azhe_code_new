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
#ifndef INC_FILEIO_H
#define INC_FILEIO_H

/* Standard include files for windows.*/
#include "AKCommon.h"

/* Include file for user definition.*/
#include "CustomerSpec.h"

/* Include file for AK8975 library.*/
#include "AKCompass.h"

/*========================= Constant definition ==============================*/
/*< The name of APP*/
#define SETTING_APP_NAME        "AK8975"
/*< The name of setting file.*/
#define SETTING_FILE_NAME	"/data/misc/AK8975Prms.ini"
/*< The maximum size of parameter name.*/
#define KEYNAME_SIZE		64
/*< Separate the name of parameter and value in setting file.*/
#define DELIMITER "="

/*========================= Prototype of Function ============================*/
int16 LoadParameters(
	AK8975PRMS *prms
);

int16 LoadInt16(
	FILE *lpFile,
	const char *lpKeyName,
	int16 *val
);

int16 LoadInt16vec(
	FILE *lpFile,
	const char *lpKeyName,
	int16vec * vec
);

/* Save*/
int16 SaveParameters(
	AK8975PRMS *prms
);

void SaveInt16(
   FILE *lpFile,
   const char *lpKeyName,
   const int16 val
);

void SaveInt16vec(
	FILE *lpFile,
	const char *lpKeyName,
	const int16vec * vec
);

#endif

