/******************************************************************************
 *
 *  $Workfile: AKDOECore.h $
 *
 *  $Author: Rikita $
 *  $Date: 09/09/10 17:11 $
 *  $Revision: 12 $
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
#ifndef AKSC_INC_AKDOECORE_H
#define AKSC_INC_AKDOECORE_H

#include "AKMDevice.h"

//========================= Type declaration  ===========================//
typedef enum _AKSC_OVALID	{AKSC_OERROR, AKSC_ONARROWXYZ, AKSC_OXYZ} AKSC_OVALID;		//validity of offset

//========================= Constant definition =========================//
#define AKSC_ORDER				3		// Maximum order of matrix. Do not change definition, or critical failure might caused for the system.
#define AKSC_ORDER_E			5		// Maximum order of matrix. Do not change definition, or critical failure might caused for the system.

//========================= Prototype of Function =======================//

#endif

