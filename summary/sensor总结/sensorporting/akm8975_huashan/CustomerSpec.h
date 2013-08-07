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
#ifndef INC_CUSTOMERSPEC_H
#define INC_CUSTOMERSPEC_H

//***************************
// User defines parameters.
//***************************

// Certification information
#define CSPEC_CI_AK_DEVICE	8975
#define CSPEC_CI_LICENSER	"ASAHIKASEI"
#define CSPEC_CI_LICENSEE	"HTC-Xindian"

// Parameters for Average
//	The number of magnetic data block to be averaged.
//	 NBaveh*(*nh) must be 1, 2, 4, 8 or 16.
#define CSPEC_HNAVE		4

//   parameter for theta filter
#define	CSPEC_THETAFILTER_SCALE			4128

// Parameters for Direction Calculation
#define CSPEC_DVEC_X		0
#define CSPEC_DVEC_Y		0
#define CSPEC_DVEC_Z		0

// Specify the acceleration sensor
#define AKD_ACCSENSOR_BOSCH

// AK8975

// Formation 0
#define CSPEC_FORM0_HLAYOUT_11	0
#define CSPEC_FORM0_HLAYOUT_12	1
#define CSPEC_FORM0_HLAYOUT_13	0
#define CSPEC_FORM0_HLAYOUT_21	-1
#define CSPEC_FORM0_HLAYOUT_22	0
#define CSPEC_FORM0_HLAYOUT_23	0
#define CSPEC_FORM0_HLAYOUT_31	0
#define CSPEC_FORM0_HLAYOUT_32	0
#define CSPEC_FORM0_HLAYOUT_33	1

// Formation 1
#define CSPEC_FORM1_HLAYOUT_11	-1
#define CSPEC_FORM1_HLAYOUT_12	0
#define CSPEC_FORM1_HLAYOUT_13	0
#define CSPEC_FORM1_HLAYOUT_21	0
#define CSPEC_FORM1_HLAYOUT_22	1
#define CSPEC_FORM1_HLAYOUT_23	0
#define CSPEC_FORM1_HLAYOUT_31	0
#define CSPEC_FORM1_HLAYOUT_32	0
#define CSPEC_FORM1_HLAYOUT_33	-1

///////////////////////////////
#if defined(AKD_ACCSENSOR_ST)
// Parameters for ST
#define CSPEC_FORM0_ALAYOUT_11	0
#define CSPEC_FORM0_ALAYOUT_12	-1
#define CSPEC_FORM0_ALAYOUT_13	0
#define CSPEC_FORM0_ALAYOUT_21	1
#define CSPEC_FORM0_ALAYOUT_22	0
#define CSPEC_FORM0_ALAYOUT_23	0
#define CSPEC_FORM0_ALAYOUT_31	0
#define CSPEC_FORM0_ALAYOUT_32	0
#define CSPEC_FORM0_ALAYOUT_33	-1

#define CSPEC_FORM1_ALAYOUT_11	-1
#define CSPEC_FORM1_ALAYOUT_12	0
#define CSPEC_FORM1_ALAYOUT_13	0
#define CSPEC_FORM1_ALAYOUT_21	0
#define CSPEC_FORM1_ALAYOUT_22	-1
#define CSPEC_FORM1_ALAYOUT_23	0
#define CSPEC_FORM1_ALAYOUT_31	0
#define CSPEC_FORM1_ALAYOUT_32	0
#define CSPEC_FORM1_ALAYOUT_33	-1

#elif defined(AKD_ACCSENSOR_BOSCH)
// Parameters for Bosch
#define CSPEC_FORM0_ALAYOUT_11	0
#define CSPEC_FORM0_ALAYOUT_12	-1
#define CSPEC_FORM0_ALAYOUT_13	0
#define CSPEC_FORM0_ALAYOUT_21	1
#define CSPEC_FORM0_ALAYOUT_22	0
#define CSPEC_FORM0_ALAYOUT_23	0
#define CSPEC_FORM0_ALAYOUT_31	0
#define CSPEC_FORM0_ALAYOUT_32	0
#define CSPEC_FORM0_ALAYOUT_33	-1

#define CSPEC_FORM1_ALAYOUT_11	-1
#define CSPEC_FORM1_ALAYOUT_12	0
#define CSPEC_FORM1_ALAYOUT_13	0
#define CSPEC_FORM1_ALAYOUT_21	0
#define CSPEC_FORM1_ALAYOUT_22	-1
#define CSPEC_FORM1_ALAYOUT_23	0
#define CSPEC_FORM1_ALAYOUT_31	0
#define CSPEC_FORM1_ALAYOUT_32	0
#define CSPEC_FORM1_ALAYOUT_33	-1

#else
#error Acceleration sensor is not specified.
#endif

// measurement time + extra time
#define	CSPEC_TIME_MEASUREMENTDRDY	20

// The number of formation
#define CSPEC_NUM_FORMATION		2

// the counter of Suspend
#define CSPEC_CNTSUSPEND_SNG				8	// 1(s)
#define CSPEC_CNTSUSPEND_SNGWITHOUTDRDY		8

// Set Decimator for HDOEProcess( )
// 8-16Hz : 1
//   20Hz : 2
//   30Hz : 3
//   50Hz : 5
//  100Hz : 10
#define CSPEC_HDECIMATOR_SNG				1
#define CSPEC_HDECIMATOR_SNGWITHOUTDRDY		1
#define	CSPEC_HDECIMATOR_HDOECALIB			1

// Calcurate sleep time.
// 7.26ms; time for one measurement
#define CSPEC_INTERVAL_SNG				(125-7.26)	// ms
#define CSPEC_INTERVAL_SNGWITHOUTDRDY	(125-CSPEC_TIME_MEASUREMENTDRDY)	// ms

#define CSPEC_HFLUCV_TH			2500		//*5 format

// Parameters for HDOECalibration
// 8Hz x 80 = 1/8 x 80 = 10(s)
#define CSPEC_TIMEOUT_CALLCNT_HDOECALIB 80

// Parameters for HCalibration
#define CSPEC_MESNUM_HCALIB		16

// Parameters for FctShipmntTest
//  1 : USE SPI
//  0 : NOT USE SPI(I2C)
#define CSPEC_SPI_USE			0

#define CSPEC_ADATA_SIZE		32

/* Slider detection */
#define SLIDER_STATUS_NUM 2
#define SLIDER_OPEN_STATUS 0
#define SLIDER_CLOSE_STATUS 1

#endif
