/******************************************************************************
 *
 *  $Id: AK8975HTC_HUAN.h 1 2011-04-07 08:43:23Z nakamaru.ab $
 *
 * -- Copyright Notice --
 *
 * Copyright (c) 2004 - 2010 Asahi Kasei Microdevices Corporation, Japan
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
#ifndef AKSC_INC_AK8975HTC_HUAN_H
#define AKSC_INC_AK8975HTC_HUAN_H

#include "AKMDevice.h"

//========================= Type declaration  ===========================//

//========================= Constant definition =========================//

//========================= Prototype of Function =======================//
AKLIB_C_API_START

int16 AKSC_Decomp8975HTC_HUAN(			//(o)	: (1)normally calculated,(0)not allowed input parameter
	const	int16				bdata[],//(i)	: block data
	const	int16				hNave,	//(i)	: the number of magnetic data to be averaged. hNave must be power of 2 (1,2,4,8,16,32).
	const	int16vec*			asa,	//(i)	: sensitivity adjustment value(the value read from Fuse ROM)
			int16vec			hdata[],//(i/o)	: magnetic data. index 0 is earlier data.
			int16*				hn,		//(o)	: the number of magnetic data, output 1.
			int16vec*			have,	//(o)	: average of magnetic data
			int16*				dor,	//(o)	: 0;normal data, 1;data overrun is occurred.
			int16*				derr,	//(o)	: 0;normal data, 1;data read error occurred.
			int16*				hofl	//(o)	: 0;normal data, 1;data overflow occurred.
);

AKLIB_C_API_END

#endif
