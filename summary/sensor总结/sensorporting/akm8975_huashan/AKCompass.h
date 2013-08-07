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
#ifndef INC_AKCOMPASS_H
#define INC_AKCOMPASS_H

#include "CustomerSpec.h"

//**************************************
// Include files for AK8975  library.
//**************************************
#include "AK8975.h"
#include "AK8975HTC_HUAN.h"
#include "AKConfigure.h"
#include "AKMDevice.h"
#include "AKCertification.h"
#include "AKDirection6D.h"
#include "AKHDOE.h"
#include "AKHFlucCheck.h"
#include "AKManualCal.h"
#include "AKVersion.h"
#include <pthread.h>

//========================= Constant definition ==============================//

//========================= Type declaration  ================================//
typedef struct _ACCPRMS {
	float AO[3];
	float AS[3];
	int16 adata[CSPEC_ADATA_SIZE][3];

	/* Andy Chuang add */
	int16 offset[3];
	/* End Andy Chuang add */
}ACCPRMS;

//========================= Type declaration  ================================//

// A parameter structure.
typedef struct _AK8975PRMS{

	/* Add by Andy Chuang */
	int16           m_iStatusCurrent;
	int16           m_iStatusNew;
	/* End add by Andy Chuang */

	// Variables for magnetic sensor.
	int16vec	m_ho;
	int16vec	HSUC_HO[CSPEC_NUM_FORMATION];
	int16vec	m_hs;
	int16vec	HFLUCV_HREF[CSPEC_NUM_FORMATION];
	AKSC_HFLUCVAR	m_hflucv;

	// Variables for Decomp8975.
	int16vec	m_hdata[AKSC_HDATA_SIZE];
	int16		m_hn;		// Number of acquired data
	int16vec	m_hvec;		// Averaged value
	int16vec	m_asa;

	// Variables for HDOE.
	AKSC_HDOEVAR	m_hdoev;
	AKSC_HDST	m_hdst;
	AKSC_HDST	HSUC_HDST[CSPEC_NUM_FORMATION];

	// Variables for formation change
	int16		m_form;
	int16		m_cntSuspend;

	// Variables for Direction6D.
	int16		m_ds3Ret;
	int16		m_hnave;
	int16vec	m_dvec;
	I16MATRIX	m_hlayout[CSPEC_NUM_FORMATION];
	int16		m_theta;
	int16		m_delta;
	int16		m_hr;
	int16		m_hrhoriz;
	int16		m_ar;
	int16		m_phi180;
	int16		m_phi90;
	int16		m_eta180;
	int16		m_eta90;
	I16MATRIX	m_mat;

// Andy Chuang Added
	// Variables for Acceleration
	int16		m_accx;
	int16		m_accy;
	int16		m_accz;

	// Variables for Geomagnetic Vector
	int16		m_rmvx;
	int16		m_rmvy;
	int16		m_rmvz;
// End Andy Chuang Added

	// Variables for acceleration sensor.
	int16vec	m_avec;

	// This sample application can change the acc sensor type.
	// ALAYOUT may vary according to the sensor type.
	I16MATRIX	m_alayout[CSPEC_NUM_FORMATION];

	// Variables for decimation.
	int16		m_callcnt;

	// Variables for timer counter.
	int16		m_timercnt;

	// Ceritication
	uint8		m_licenser[AKSC_CI_MAX_CHARSIZE+1];	//end with '\0'
	uint8		m_licensee[AKSC_CI_MAX_CHARSIZE+1];	//end with '\0'
	int16		m_key[AKSC_CI_MAX_KEYSIZE];
// Andy Chuang Added
	int		m_Stop;		// Hadle to a stop signal object
	int		m_SlideStop;	/* Handle to a stop signal object of slider detection */
	int		m_hDevice;
	int		m_aDevice;

	pthread_t	m_hThread;	/* Thread handle */
	pthread_t	m_sThread;	/* Thread handle of slider detection */
	int 		compass_chip;
	ACCPRMS		accPrms;
// End Andy Chuang Added
} AK8975PRMS;

#endif
