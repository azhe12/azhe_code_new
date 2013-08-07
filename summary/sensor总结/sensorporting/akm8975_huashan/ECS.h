/*------------------------------------------------------------------------------
 *
 *  Copyright (c) Microsoft Corporation.  All rights reserved.
 *
 *
 *  Use of this source code is subject to the terms of the Microsoft end-user
 *  license agreement (EULA) under which you licensed this SOFTWARE PRODUCT.
 *  If you did not accept the terms of the EULA, you are not authorized to use
 *  this source code. For a copy of the EULA, please see the LICENSE.RTF on
 *  your install media.
 *
 *------------------------------------------------------------------------------
 *
 *  Copyright (C) 2004, Motorola Inc. All Rights Reserved
 *
 *------------------------------------------------------------------------------
 *
 *  Copyright (C) 2004-2006, Freescale Semiconductor, Inc. All Rights Reserved
 *  THIS SOURCE CODE IS CONFIDENTIAL AND PROPRIETARY AND MAY NOT
 *  BE USED OR DISTRIBUTED WITHOUT THE WRITTEN PERMISSION OF
 *  Freescale Semiconductor, Inc.
 *
 *------------------------------------------------------------------------------*/

/*------------------------------------------------------------------------------
 *
 *  File:  ECS.h
 *
 *  Definitions for ECompass Driver
 *
 *------------------------------------------------------------------------------*/
#ifndef AKSC_INC_ECS_H
#define AKSC_INC_ECS_H

#include <linux/ioctl.h>

#define AKMIO                           0xA1

/*------------------------------------------------------------------------------
 * Defines
 *------------------------------------------------------------------------------
 * Debug zone bit positions*/
#define ZONEID_INIT             0
#define ZONEID_DEINIT           1
#define ZONEID_IOCTL            2
#define ZONEID_INFO            12
#define ZONEID_FUNCTION        13
#define ZONEID_WARN            14
#define ZONEID_ERROR           15

/* Debug zone masks*/
#define ZONEMASK_INIT		(1<<ZONEID_INIT)
#define ZONEMASK_DEINIT		(1<<ZONEID_DEINIT)
#define ZONEMASK_IOCTL		(1<<ZONEID_IOCTL)

#define ZONEMASK_INFO		(1<<ZONEID_INFO)
#define ZONEMASK_FUNCTION	(1<<ZONEID_FUNCTION)
#define ZONEMASK_WARN		(1<<ZONEID_WARN)
#define ZONEMASK_ERROR		(1<<ZONEID_ERROR)

/* Debug zone args to DEBUGMSG */
#define ZONE_INIT			DEBUGZONE(ZONEID_INIT)
#define ZONE_DEINIT			DEBUGZONE(ZONEID_DEINIT)
#define ZONE_IOCTL			DEBUGZONE(ZONEID_IOCTL)
#define ZONE_INFO			DEBUGZONE(ZONEID_INFO)
#define ZONE_FUNCTION			DEBUGZONE(ZONEID_FUNCTION)
#define ZONE_WARN			DEBUGZONE(ZONEID_WARN)
#define ZONE_ERROR			DEBUGZONE(ZONEID_ERROR)

/*------------------------------------------------------------------------------
 * Types
 *------------------------------------------------------------------------------
 * IOCTLs for AKM library*/
#define ECS_IOCTL_WRITE                 _IOW(AKMIO, 0x01, char[5])
#define ECS_IOCTL_READ                  _IOWR(AKMIO, 0x02, char[5])
#define ECS_IOCTL_RESET                 _IO(AKMIO, 0x03)
#define ECS_IOCTL_SET_MODE              _IOW(AKMIO, 0x0F, short)
#define ECS_IOCTL_GETDATA               _IOR(AKMIO, 0x05, char[RBUFF_SIZE_8975 + 1])
#define ECS_IOCTL_SET_YPR               _IOW(AKMIO, 0x06, short[12])
#define ECS_IOCTL_GET_OPEN_STATUS       _IOR(AKMIO, 0x07, int)
#define ECS_IOCTL_GET_CLOSE_STATUS      _IOR(AKMIO, 0x08, int)
#define ECS_IOCTL_GET_DELAY             _IOR(AKMIO, 0x30, short)
#define ECS_IOCTL_GET_PROJECT_NAME      _IOR(AKMIO, 0x0D, char[64])
#define ECS_IOCTL_GET_MATRIX            _IOR(AKMIO, 0x0E, short[4][3][3])

/* IOCTLs for APPs*/
#define ECS_IOCTL_APP_SET_MODE		_IOW(AKMIO, 0x10, short)
#define ECS_IOCTL_APP_SET_MFLAG		_IOW(AKMIO, 0x11, short)
#define ECS_IOCTL_APP_GET_MFLAG		_IOW(AKMIO, 0x12, short)
#define ECS_IOCTL_APP_SET_AFLAG		_IOW(AKMIO, 0x13, short)
#define ECS_IOCTL_APP_GET_AFLAG		_IOR(AKMIO, 0x14, short)
#define ECS_IOCTL_APP_SET_TFLAG		_IOR(AKMIO, 0x15, short)
#define ECS_IOCTL_APP_GET_TFLAG		_IOR(AKMIO, 0x16, short)
#define ECS_IOCTL_APP_RESET_PEDOMETER   _IO(AKMIO, 0x17)
#define ECS_IOCTL_APP_SET_DELAY		_IOW(AKMIO, 0x18, short)
#define ECS_IOCTL_APP_GET_DELAY		ECS_IOCTL_GET_DELAY
#define ECS_IOCTL_APP_SET_MVFLAG	_IOW(AKMIO, 0x19, short) /* Set raw magnetic vector flag */
#define ECS_IOCTL_APP_GET_MVFLAG	_IOR(AKMIO, 0x1A, short) /* Get raw magnetic vector flag */

/* IOCTLs for pedometer*/
#define ECS_IOCTL_SET_STEP_CNT          _IOW(AKMIO, 0x20, short)
#endif
