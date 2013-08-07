/******************************************************************************
 *
 * $Id:  $
 *
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

#ifndef INC_ACCSENSORFUNCTION_H
#define INC_ACCSENSORFUNCTION_H

// Include file for windows system.
//#include "AK8975Driver.h"

#include "CustomerSpec.h"
#include "AKCompass.h"
#include "AKCommon.h"

//========================= Constant definition ==============================//
#define SETTING_ACC_FILE_NAME	"/data/misc/AccPrmsF.ini"
#define ACALIB_MEASURE			16
#define	ASENSE_TARGET			0x02D0			//720
#define ACC_INIT_VALUE			((int16)0x7FFF)		// Initial value
#define CSPEC_ANAVE				4

//========================= Prototype of Function ============================//
void SetDefaultPRMSAcc(
	ACCPRMS*		prms
);

void GetAccVec(
	AK8975PRMS*	prms,		// (i)Pointer to parameters of AK8975
	ACCPRMS*	accprms,
	float*		avecf
);

int ACalibration(
			ACCPRMS*	prms
);

int LoadParametersAcc(
	ACCPRMS*	prms
);

int LoadFloat(
			FILE*		fp,
	const	char*		lpKeyName,
			float*		val
);

int LoadFvec(
			FILE*		fp,
	const	char*		lpKeyName,
			float		vec[]
);

int SaveParametersAcc(
			ACCPRMS*	prms
);

void SaveFvec(
			FILE*		fp,
	const	char*		lpKeyName,
	const	float		vec[]
);

void InitAccBuffer(
	int16 adata[][3]
);

#endif

