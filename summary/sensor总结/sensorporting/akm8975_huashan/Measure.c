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
#include <linux/input.h>
#include <sys/stat.h>
#include "TestLimit.h"

#include "FileIO.h"
#include "DispMessage.h"
#include "Measure.h"

#include "IOMessage.h"
#include "ECS_PDD.h"
#include "ak8975_log.h"

#include "akmd_slider.h"

short cspec_Hlayout[3][3];
short cspec_Alayout[3][3];

short m_Hlayout[3][3];
short m_Alayout[3][3];

#define test_bit(bit, array)    (array[bit/8] & (1<<(bit%8)))

extern int get_debug_flag(void);
extern void set_debug_flag(int flag);

/*==========================================================================
 *
 *  FUNCTION:  WaitForDRDY
 *
 *  PURPOSE:
 *
 *  DESCRIPTION:
 *
 *==========================================================================*/
int16 WaitForDRDY(void)
{
	int16 i;

	/* Wait for DRDY PIN high*/
	for (i = 0; i < 1000; i++) {
		/*if (g_DRDYIsHigh == TRUE) {*/
		/*	return 1;          */
		/*}                        */
		/* Wait 1 millisecond. */
		usleep(1000);
	}

	/* DRDY pin did not changed to HIGH.*/
	return 1;
}

/*==========================================================================
 *
 *  FUNCTION:  getFormation
 *
 *  PURPOSE:
 *
 *  DESCRIPTION:
 *
 *==========================================================================*/
int16 getFormation(void)
{
	return 1;/*g_Form;*/
}

/*==========================================================================
 *
 *  FUNCTION:  InitAK8975PRMS()
 *
 *  PURPOSE:   Initialize AK8975PRMS structure
 *
 *  DESCRIPTION:
 *
 *==========================================================================*/
void InitAK8975PRMS(
	AK8975PRMS	*prms /*(i/o)Pointer to parameters of AK8975*/
)
{
	/* Set 0 to the AK8975PRMS structure. */
	/*memset(prms, 0, sizeof(AK8975PRMS));*/

	/* Sensitivity*/
	prms->m_hs.u.x = AKSC_HSENSE_TARGET;
	prms->m_hs.u.y = AKSC_HSENSE_TARGET;
	prms->m_hs.u.z = AKSC_HSENSE_TARGET;

	/* HDOE*/
	prms->m_hdst = AKSC_HDST_UNSOLVED;

	prms->HSUC_HDST[0] = 0;
	prms->HSUC_HDST[1] = 0;

	/* Set counter*/
	prms->m_cntSuspend = 0;

	/* (m_hdata is initialized with AKSC_InitDecomp8975)*/
	prms->m_hnave = CSPEC_HNAVE;
	prms->m_dvec.u.x = CSPEC_DVEC_X;
	prms->m_dvec.u.y = CSPEC_DVEC_Y;
	prms->m_dvec.u.z = CSPEC_DVEC_Z;

	/*************************************************/
	/* Set HLAYOUT                                   */
	/*************************************************/

	/* Form 0*/
	prms->m_hlayout[0].u._11 = (int16) cspec_Hlayout[0][0];
	prms->m_hlayout[0].u._12 = (int16) cspec_Hlayout[0][1];
	prms->m_hlayout[0].u._13 = (int16) cspec_Hlayout[0][2];
	prms->m_hlayout[0].u._21 = (int16) cspec_Hlayout[1][0];
	prms->m_hlayout[0].u._22 = (int16) cspec_Hlayout[1][1];
	prms->m_hlayout[0].u._23 = (int16) cspec_Hlayout[1][2];
	prms->m_hlayout[0].u._31 = (int16) cspec_Hlayout[2][0];
	prms->m_hlayout[0].u._32 = (int16) cspec_Hlayout[2][1];
	prms->m_hlayout[0].u._33 = (int16) cspec_Hlayout[2][2];

	/* Form 1*/
	prms->m_hlayout[1].u._11 = (int16) cspec_Hlayout[0][0];
	prms->m_hlayout[1].u._12 = (int16) cspec_Hlayout[0][1];
	prms->m_hlayout[1].u._13 = (int16) cspec_Hlayout[0][2];
	prms->m_hlayout[1].u._21 = (int16) cspec_Hlayout[1][0];
	prms->m_hlayout[1].u._22 = (int16) cspec_Hlayout[1][1];
	prms->m_hlayout[1].u._23 = (int16) cspec_Hlayout[1][2];
	prms->m_hlayout[1].u._31 = (int16) cspec_Hlayout[2][0];
	prms->m_hlayout[1].u._32 = (int16) cspec_Hlayout[2][1];
	prms->m_hlayout[1].u._33 = (int16) cspec_Hlayout[2][2];


	/*************************************************/
	/* Set ALAYOUT                                   */
	/*************************************************/
/*
	// Form 0
	prms->m_alayout[0].u._11 = CSPEC_FORM0_ALAYOUT_11;
	prms->m_alayout[0].u._12 = CSPEC_FORM0_ALAYOUT_12;
	prms->m_alayout[0].u._13 = CSPEC_FORM0_ALAYOUT_13;
	prms->m_alayout[0].u._21 = CSPEC_FORM0_ALAYOUT_21;
	prms->m_alayout[0].u._22 = CSPEC_FORM0_ALAYOUT_22;
	prms->m_alayout[0].u._23 = CSPEC_FORM0_ALAYOUT_23;
	prms->m_alayout[0].u._31 = CSPEC_FORM0_ALAYOUT_31;
	prms->m_alayout[0].u._32 = CSPEC_FORM0_ALAYOUT_32;
	prms->m_alayout[0].u._33 = CSPEC_FORM0_ALAYOUT_33;

	// Form 1
	prms->m_alayout[1].u._11 = CSPEC_FORM1_ALAYOUT_11;
	prms->m_alayout[1].u._12 = CSPEC_FORM1_ALAYOUT_12;
	prms->m_alayout[1].u._13 = CSPEC_FORM1_ALAYOUT_13;
	prms->m_alayout[1].u._21 = CSPEC_FORM1_ALAYOUT_21;
	prms->m_alayout[1].u._22 = CSPEC_FORM1_ALAYOUT_22;
	prms->m_alayout[1].u._23 = CSPEC_FORM1_ALAYOUT_23;
	prms->m_alayout[1].u._31 = CSPEC_FORM1_ALAYOUT_31;
	prms->m_alayout[1].u._32 = CSPEC_FORM1_ALAYOUT_32;
	prms->m_alayout[1].u._33 = CSPEC_FORM1_ALAYOUT_33;*/
}

/*==========================================================================
 *
 *  FUNCTION:  SetDefaultPRMS()
 *
 *  PURPOSE:   Initialize the parameter of HDOE
 *
 *  DESCRIPTION:
 *
 *==========================================================================*/
void SetDefaultPRMS(
	AK8975PRMS *prms /*(i/o)Pointer to parameters of AK8975*/
)
{
	/* Set parameter to HDST, HO, HREF, THRE*/
	/* Form 0*/
	prms->HSUC_HDST[0] = AKSC_HDST_UNSOLVED;
	prms->HSUC_HO[0].u.x = 0;
	prms->HSUC_HO[0].u.y = 0;
	prms->HSUC_HO[0].u.z = 0;
	prms->HFLUCV_HREF[0].u.x = 0;
	prms->HFLUCV_HREF[0].u.y = 0;
	prms->HFLUCV_HREF[0].u.z = 0;

	/* Form 1*/
	prms->HSUC_HDST[1] = AKSC_HDST_UNSOLVED;
	prms->HSUC_HO[1].u.x = 0;
	prms->HSUC_HO[1].u.y = 0;
	prms->HSUC_HO[1].u.z = 0;
	prms->HFLUCV_HREF[1].u.x = 0;
	prms->HFLUCV_HREF[1].u.y = 0;
	prms->HFLUCV_HREF[1].u.z = 0;
}

/*==========================================================================
 *
 *  FUNCTION:  ReadAK8975FUSEROM()
 *
 *  PURPOSE:
 *
 *  DESCRIPTION:
 *
 *==========================================================================*/
void ReadAK8975FUSEROM(
	AK8975PRMS	*prms	/*(o)Pointer to parameters of AK8975*/
)
{
	BYTE		i2cData[6];

	/* Set to PowerDown mode*/
	/*i2cData[0] = AK8975_CNTL_POWER_DOWN;*/
	/*AKD_TxData(AK8975_REG_CNTL, i2cData, 1);****/
	if (!SendIOMessage(prms->m_hDevice,
			AKDBMES_SET_MODE,
			AK8975_CNTL_POWER_DOWN,
			NULL))
		LOGE("%s: AKDBMES_SET_MODE error1\n", __PRETTY_FUNCTION__);

	/* Wait over 100 us*/
	usleep(1);

	/* Set to FUSE ROM access mode*/
	/*i2cData[0] = AK8975_CNTL_FUSE_ACCESS;*/
	/*AKD_TxData(AK8975_REG_CNTL, i2cData, 1);*/
	if (!SendIOMessage(prms->m_hDevice,
			AKDBMES_SET_MODE,
			AK8975_CNTL_FUSE_ACCESS,
			NULL))
		LOGE("%s: AKDBMES_SET_MODE error2\n", __PRETTY_FUNCTION__);

	/* Wait over 100 us*/
	usleep(1);

	/* Read values. ASAX*/
	/*AKD_RxData(AK8975_FUSE_ASAX, i2cData, 1);*/
	/*prms->m_asa.u.x = (int16)i2cData[0];*/
	if (!SendIOMessage(prms->m_hDevice,
			AKDBMES_READ_REGISTER,
			AK8975_FUSE_ASAX,
			i2cData))
		LOGE("%s: AKDBMES_READ_REGISTER error1\n", __PRETTY_FUNCTION__);

	prms->m_asa.u.x = (int16)i2cData[0];
	/* Set keywords for SmartCompassLibrary certification*/
	prms->m_key[2] = (int16)i2cData[0];

	/* Read values. ASAY*/
	/*AKD_RxData(AK8975_FUSE_ASAY, i2cData, 1);*/
	/*prms->m_asa.u.y = (int16)i2cData[0];*/
	if (!SendIOMessage(prms->m_hDevice,
			AKDBMES_READ_REGISTER,
			AK8975_FUSE_ASAY,
			i2cData))
		LOGE("%s: AKDBMES_READ_REGISTER error1\n", __PRETTY_FUNCTION__);

	prms->m_asa.u.y = (int16)i2cData[0];
	/* Set keywords for SmartCompassLibrary certification*/
	prms->m_key[3] = (int16)i2cData[0];

	/* Read values. ASAZ*/
	/*AKD_RxData(AK8975_FUSE_ASAZ, i2cData, 1);*/
	/*prms->m_asa.u.z = (int16)i2cData[0];*/
	if (!SendIOMessage(prms->m_hDevice,
			AKDBMES_READ_REGISTER,
			AK8975_FUSE_ASAZ,
			i2cData))
		LOGE("%s: AKDBMES_READ_REGISTER error1\n", __PRETTY_FUNCTION__);

	prms->m_asa.u.z = (int16)i2cData[0];
	/* Set keywords for SmartCompassLibrary certification*/
	prms->m_key[4] = (int16)i2cData[0];

	/* Set to PowerDown mode*/
	/*i2cData[0] = AK8975_CNTL_POWER_DOWN;*/
	/*AKD_TxData(AK8975_REG_CNTL, i2cData, 1);*/
	if (!SendIOMessage(prms->m_hDevice,
			AKDBMES_SET_MODE,
			AK8975_CNTL_POWER_DOWN,
			NULL))
		LOGE("%s: AKDBMES_SET_MODE error3\n", __PRETTY_FUNCTION__);

	/* Wait over 100 us*/
	usleep(1);

	/* Set keywords for SmartCompassLibrary certification*/
	/*AKD_RxData(AK8975_REG_WIA, i2cData, 1);*/
	if (!SendIOMessage(prms->m_hDevice,
			AKDBMES_READ_REGISTER,
			AK8975_REG_WIA,
			i2cData))
		LOGE("%s: AKDBMES_READ_REGISTER error1\n", __PRETTY_FUNCTION__);

	prms->m_key[1] = (int16)i2cData[0];
	strncpy((char *)prms->m_licenser, CSPEC_CI_LICENSER, AKSC_CI_MAX_CHARSIZE);
	strncpy((char *)prms->m_licensee, CSPEC_CI_LICENSEE, AKSC_CI_MAX_CHARSIZE);
	prms->m_key[0] = CSPEC_CI_AK_DEVICE;

	AKM_LOGD("%s: prms->m_key(0, 1, 2, 3, 4) = "
		"(%4d, %4d, %4d, %4d, %4d)\n",
		__PRETTY_FUNCTION__, prms->m_key[0], prms->m_key[1], prms->m_key[2]
		, prms->m_key[3], prms->m_key[4]);
}

/*==========================================================================
 *
 *  FUNCTION:  InitAK8975_Measure()
 *
 *  PURPOSE:   Initialize AK8975
 *
 *  DESCRIPTION: This function never returns 0.
 *
 *==========================================================================*/
int16 InitAK8975_Measure(
	AK8975PRMS	*prms	/* (i/o)Pointer to parameters of AK8975*/
)
{
	int 	fd;
	BYTE	i2cData[AKSC_BDATA_SIZE+1];
	uint8_t	sw_bitmask[(SW_MAX+1)/8];

	/* Get initial slider status*/
	fd = scan_slider_device();
	if (fd < 0) {
		AKM_LOGD("could not detect slider event\n");
		AKM_LOGD("assume that keypad is closed.\n");
		prms->m_iStatusCurrent = SLIDER_CLOSE_STATUS;
		prms->m_iStatusNew = prms->m_iStatusCurrent;
		prms->m_hdst = prms->HSUC_HDST[SLIDER_CLOSE_STATUS];
		prms->m_ho = prms->HSUC_HO[SLIDER_CLOSE_STATUS];
		prms->m_hflucv.href = prms->HFLUCV_HREF[SLIDER_CLOSE_STATUS];
	} else {
		memset(sw_bitmask, 0, sizeof(sw_bitmask));
		if (ioctl(fd, EVIOCGSW(sizeof(sw_bitmask)), sw_bitmask) < 0) {
			AKM_LOGE("slider event ioctl failed\n");
			close(fd);
			return AKRET_PROC_KILL;
		}
		if (test_bit(SW_LID, sw_bitmask)) {
			AKM_LOGD("Initial STATUS: Lid closed\n");
			prms->m_iStatusCurrent = SLIDER_CLOSE_STATUS;
			prms->m_iStatusNew = prms->m_iStatusCurrent;
			prms->m_hdst = prms->HSUC_HDST[SLIDER_CLOSE_STATUS];
			prms->m_ho = prms->HSUC_HO[SLIDER_CLOSE_STATUS];
			prms->m_hflucv.href = prms->HFLUCV_HREF[SLIDER_CLOSE_STATUS];
		} else {
			AKM_LOGD("Initial STATUS: Lid opened\n");
			prms->m_iStatusCurrent = SLIDER_OPEN_STATUS;
			prms->m_iStatusNew = prms->m_iStatusCurrent;
			prms->m_hdst = prms->HSUC_HDST[SLIDER_OPEN_STATUS];
			prms->m_ho = prms->HSUC_HO[SLIDER_OPEN_STATUS];
			prms->m_hflucv.href = prms->HFLUCV_HREF[SLIDER_OPEN_STATUS];
		}
		close(fd);
	} /* else*/

	/* Set to PowerDown mode*/
	i2cData[0] = AK8975_CNTL_POWER_DOWN;
	/*AKD_TxData(AK8975_REG_CNTL, i2cData, 1);*/

	/* Wait over 100 us*/
	usleep(1);

	/* Initialize the decompose parameters*/
	AKSC_InitDecomp8975(prms->m_hdata);

	/* Initialize HDOE parameters*/
	AKSC_InitHDOEProcPrmsS3(
		&prms->m_hdoev,
		1,
		&prms->m_ho,
		prms->m_hdst
	);

	AKSC_InitHFlucCheck(
		&(prms->m_hflucv),
		&(prms->HFLUCV_HREF[prms->m_iStatusCurrent]),
		CSPEC_HFLUCV_TH
	);

	/* Reset counter*/
	prms->m_cntSuspend = 0;
	prms->m_callcnt = 0;

	return 1;
}

/*==========================================================================
 *
 *  FUNCTION:  SwitchSlider()
 *
 *  PURPOSE:
 *
 *  DESCRIPTION:
 *
 *==========================================================================*/
int16 SwitchSlider(
	AK8975PRMS *prms	/* (i/o)Pointer to parameters of AK8975*/
)
{
	AKM_LOGD("SwitchSlider is called!\n");

	/* Restore the value when succeeding in estimating of HOffset.*/
	prms->HSUC_HDST[prms->m_iStatusCurrent] = prms->m_hdst;
	prms->HSUC_HO[prms->m_iStatusCurrent] = prms->m_ho;

	AKM_LOGD("Current = %d, New = %d\n", prms->m_iStatusCurrent, prms->m_iStatusNew);

	AKM_LOGD("Old values:\n");
	AKM_LOGD("HSUC_HDST = 0x%x\n",	prms->m_hdst);
	AKM_LOGD("HSUC_HO(x, y, z) = (0x%x, 0x%x, 0x%x)\n",
		prms->m_ho.u.x, prms->m_ho.u.y, prms->m_ho.u.z);

	/*Load new parameters*/
	prms->m_hdst = prms->HSUC_HDST[prms->m_iStatusNew];
	prms->m_ho = prms->HSUC_HO[prms->m_iStatusNew];
	prms->m_iStatusCurrent = prms->m_iStatusNew;

	AKM_LOGD("New values:\n");
	AKM_LOGD("HSUC_HDST = 0x%x\n",	prms->m_hdst);
	AKM_LOGD("HSUC_HO(x, y, z) = (0x%x, 0x%x, 0x%x)\n",
		prms->m_ho.u.x, prms->m_ho.u.y, prms->m_ho.u.z);

	/* Initialize the decompose parameters*/
	AKSC_InitDecomp8975(prms->m_hdata);

	/* Initialize HDOE parameters*/
	AKSC_InitHDOEProcPrmsS3(
		&prms->m_hdoev,
		1,
		&prms->m_ho,
		prms->m_hdst
	);

	AKSC_InitHFlucCheck(
		&(prms->m_hflucv),
		&(prms->HFLUCV_HREF[prms->m_iStatusCurrent]),
		CSPEC_HFLUCV_TH
	);

	/* Reset counter*/
	prms->m_callcnt = 0;

	return 1;
}

/*==========================================================================
 *
 *  FUNCTION:  FctShipmntTest_Body
 *
 *  PURPOSE:
 *
 *  DESCRIPTION:
 *			1;  pass
 *			-1; fail
 *			0;  error
 *
 *==========================================================================*/
int16 FctShipmntTest_Body(
	AK8975PRMS *prms	/* (i/o)Pointer to parameters of AK8975*/
)
{
	int16		pf_total;
	int16		pf;

	DispMessage(MSG_LEVEL1,
		"Hold the sensor box stable. \n"
		"Confirm that there is no strong magnetic object around the sensor box.\n\n"
	);
	Prmpt_Kbhit();

	/*************************************************/
	/*	Reset Test Result*/
	/*************************************************/
	pf_total = 1;	/*pass*/
	TEST_DATA(NULL, "START", 0, 0, 0, &pf_total);

	/*************************************************/
	/*	Step 1 to 2*/
	/*************************************************/
	pf = FctShipmntTestProcess_Body(prms);
	if (pf == 0) {
		/* Error*/
		DispMessage(MSG_LEVEL0, "Factory shipment test was ABORTED.\n");
		return 0;
	}
	if (pf_total != 1 || pf != 1) {
		pf_total = -1;
	}

	/*************************************************/
	/*	Judge Test Result*/
	/*************************************************/
	TEST_DATA(NULL, "END", 0, 0, 0, &pf_total);

	Prmpt_Kbhit();

	return pf_total;
}

/*==========================================================================
 *
 *  FUNCTION:  FctShipmntTestProcess_Body
 *
 *  PURPOSE:
 *
 *  DESCRIPTION:
 *			1;  pass
 *			-1; fail
 *			0;  error
 *
 *==========================================================================*/
int16 FctShipmntTestProcess_Body(
	AK8975PRMS *prms		/* (i/o)Pointer to parameters of AK8975.*/
)
{
	int16		pf_total;	/*p/f flag for this subtest*/
	BYTE		i2cData[AKSC_BDATA_SIZE];
	int16		hdata[3];
	int16		asax;
	int16		asay;
	int16		asaz;
	int16		sngHX;
	int16		sngHY;
	int16		sngHZ;
	BYTE		tmp;

	/* initialize i2cData*/
	memset(i2cData, 0, AKSC_BDATA_SIZE);

	/*************************************************/
	/*	Reset Test Result                        */
	/*************************************************/
	pf_total = 1;

	/**************************************************/
	/**	Step1                                    */
	/**************************************************/

	/* Set to PowerDown mode*/
	i2cData[0] = AK8975_CNTL_POWER_DOWN;
	/*AKD_TxData(AK8975_REG_CNTL, i2cData, 1);*/

	/* Wait over 100 us*/
	usleep(1);

	/* When the serial interface is SPI,                      */
	/* write 00011011 to I2CDIS register(to disable I2C,).*/
	if (CSPEC_SPI_USE == 1) {
		i2cData[0] = 0x1B;
		/*AKD_TxData(AK8975_REG_I2CDIS, i2cData, 1);*/
	}

	/* Read values. WIA                      */
	/*AKD_RxData(AK8975_REG_WIA, i2cData, 1);*/

	/* TEST*/
	TEST_DATA(TLIMIT_NO_RST_WIA, TLIMIT_TN_RST_WIA, (int16)i2cData[0], TLIMIT_LO_RST_WIA, TLIMIT_HI_RST_WIA, &pf_total);

	/* Read values. INFO                      */
	/*AKD_RxData(AK8975_REG_INFO, i2cData, 1);*/

	/* TEST*/
	TEST_DATA(TLIMIT_NO_RST_INFO, TLIMIT_TN_RST_INFO, (int16)i2cData[0], TLIMIT_LO_RST_INFO, TLIMIT_HI_RST_INFO, &pf_total);

	/* Read values. ST1*/
	/*AKD_RxData(AK8975_REG_ST1, i2cData, 1);*/

	/* TEST*/
	TEST_DATA(TLIMIT_NO_RST_ST1, TLIMIT_TN_RST_ST1, (int16)i2cData[0], TLIMIT_LO_RST_ST1, TLIMIT_HI_RST_ST1, &pf_total);

	/* Read values. HXL*/
	/*AKD_RxData(AK8975_REG_HXL, i2cData, 1);*/

	/* TEST*/
	TEST_DATA(TLIMIT_NO_RST_HXL, TLIMIT_TN_RST_HXL, (int16)i2cData[0], TLIMIT_LO_RST_HXL, TLIMIT_HI_RST_HXL, &pf_total);

	/* Read values. HXH*/
	/*AKD_RxData(AK8975_REG_HXH, i2cData, 1);*/

	/* TEST*/
	TEST_DATA(TLIMIT_NO_RST_HXH, TLIMIT_TN_RST_HXH, (int16)i2cData[0], TLIMIT_LO_RST_HXH, TLIMIT_HI_RST_HXH, &pf_total);

	/* Read values. HYL                      */
	/*AKD_RxData(AK8975_REG_HYL, i2cData, 1);*/

	/* TEST*/
	TEST_DATA(TLIMIT_NO_RST_HYL, TLIMIT_TN_RST_HYL, (int16)i2cData[0], TLIMIT_LO_RST_HYL, TLIMIT_HI_RST_HYL, &pf_total);

	/* Read values. HYH                      */
	/*AKD_RxData(AK8975_REG_HYH, i2cData, 1);*/

	/* TEST*/
	TEST_DATA(TLIMIT_NO_RST_HYH, TLIMIT_TN_RST_HYH, (int16)i2cData[0], TLIMIT_LO_RST_HYH, TLIMIT_HI_RST_HYH, &pf_total);

	/* Read values. HZL*/
	/*AKD_RxData(AK8975_REG_HZL, i2cData, 1);*/

	/* TEST*/
	TEST_DATA(TLIMIT_NO_RST_HZL, TLIMIT_TN_RST_HZL, (int16)i2cData[0], TLIMIT_LO_RST_HZL, TLIMIT_HI_RST_HZL, &pf_total);

	/* Read values. HZH                      */
	/*AKD_RxData(AK8975_REG_HZH, i2cData, 1);*/

	/* TEST*/
	TEST_DATA(TLIMIT_NO_RST_HZH, TLIMIT_TN_RST_HZH, (int16)i2cData[0], TLIMIT_LO_RST_HZH, TLIMIT_HI_RST_HZH, &pf_total);

	/* Read values. ST2                      */
	/*AKD_RxData(AK8975_REG_ST2, i2cData, 1);*/

	/* TEST*/
	TEST_DATA(TLIMIT_NO_RST_ST2, TLIMIT_TN_RST_ST2, (int16)i2cData[0], TLIMIT_LO_RST_ST2, TLIMIT_HI_RST_ST2, &pf_total);

	/* Read values. CNTL                      */
	/*AKD_RxData(AK8975_REG_CNTL, i2cData, 1);*/

	/* TEST*/
	TEST_DATA(TLIMIT_NO_RST_CNTL, TLIMIT_TN_RST_CNTL, (int16)i2cData[0], TLIMIT_LO_RST_CNTL, TLIMIT_HI_RST_CNTL, &pf_total);

	/* Read values. ASTC                      */
	/*AKD_RxData(AK8975_REG_ASTC, i2cData, 1);*/

	/* TEST*/
	TEST_DATA(TLIMIT_NO_RST_ASTC, TLIMIT_TN_RST_ASTC, (int16)i2cData[0], TLIMIT_LO_RST_ASTC, TLIMIT_HI_RST_ASTC, &pf_total);

	/* Read values. I2CDIS                      */
	/*AKD_RxData(AK8975_REG_I2CDIS, i2cData, 1);*/

	/* TEST*/
	if (CSPEC_SPI_USE == 1) {
		TEST_DATA(TLIMIT_NO_RST_I2CDIS, TLIMIT_TN_RST_I2CDIS, (int16)i2cData[0], TLIMIT_LO_RST_I2CDIS_USESPI, TLIMIT_HI_RST_I2CDIS_USESPI, &pf_total);
	} else {
		TEST_DATA(TLIMIT_NO_RST_I2CDIS, TLIMIT_TN_RST_I2CDIS, (int16)i2cData[0], TLIMIT_LO_RST_I2CDIS_USEI2C, TLIMIT_HI_RST_I2CDIS_USEI2C, &pf_total);
	}

	/* Set to FUSE ROM access mode*/
	i2cData[0] = AK8975_CNTL_FUSE_ACCESS;
	/*AKD_TxData(AK8975_REG_CNTL, i2cData, 1);*/

	/* Wait over 100 us*/
	usleep(1);

	/* Read values. ASAX                       */
	/*AKD_RxData(AK8975_FUSE_ASAX, i2cData, 1);*/
	asax = (int16)i2cData[0];

	/* TEST*/
	TEST_DATA(TLIMIT_NO_ASAX, TLIMIT_TN_ASAX, asax, TLIMIT_LO_ASAX, TLIMIT_HI_ASAX, &pf_total);

	/* Read values. ASAY                       */
	/*AKD_RxData(AK8975_FUSE_ASAY, i2cData, 1);*/
	asay = (int16)i2cData[0];

	/* TEST*/
	TEST_DATA(TLIMIT_NO_ASAY, TLIMIT_TN_ASAY, asay, TLIMIT_LO_ASAY, TLIMIT_HI_ASAY, &pf_total);

	/* Read values. ASAZ                       */
	/*AKD_RxData(AK8975_FUSE_ASAZ, i2cData, 1);*/
	asaz = (int16)i2cData[0];

	/* TEST*/
	TEST_DATA(TLIMIT_NO_ASAZ, TLIMIT_TN_ASAZ, asaz, TLIMIT_LO_ASAZ, TLIMIT_HI_ASAZ, &pf_total);

	/* Read values. CNTL                      */
	/*AKD_RxData(AK8975_REG_CNTL, i2cData, 1);*/

	/* Set to PowerDown mode*/
	tmp = AK8975_CNTL_POWER_DOWN;
	/*AKD_TxData(AK8975_REG_CNTL, &tmp, 1);*/

	/* Wait over 100 us*/
	usleep(1);

	/* TEST*/
	TEST_DATA(TLIMIT_NO_WR_CNTL, TLIMIT_TN_WR_CNTL, (int16)i2cData[0], TLIMIT_LO_WR_CNTL, TLIMIT_HI_WR_CNTL, &pf_total);

	/*************************************************/
	/*	Step2                                    */
	/*************************************************/

	/* Set to SNG measurement pattern (Set CNTL register)*/
	i2cData[0] = AK8975_CNTL_SNG_MEASURE;
	/*AKD_TxData(AK8975_REG_CNTL, i2cData, 1);*/

	/* Wait for DRDY pin changes to HIGH.*/
	if (WaitForDRDY() == 0) {
		DispMessage(MSG_LEVEL0, "Failed to detect DRDY pin transition to High.\n");
		return 0;	/*error*/
	}

	/* Reset flag.         */
	/*g_DRDYIsHigh = FALSE;*/

	/* Get measurement data from AK8975                    */
	/* ST1 + (HXL + HXH) + (HYL + HYH) + (HZL + HZH) + ST2 */
	/* = 1 + (1 + 1) + (1 + 1) + (1 + 1) + 1 = 8Byte       */
	/*AKD_RxData(AK8975_REG_ST1, i2cData, AKSC_BDATA_SIZE);*/

	/* TEST*/
	TEST_DATA(TLIMIT_NO_SNG_ST1, TLIMIT_TN_SNG_ST1, (int16)i2cData[0], TLIMIT_LO_SNG_ST1, TLIMIT_HI_SNG_ST1, &pf_total);

	hdata[0] = (int16)((((uint16)(i2cData[2]))<<8)+(uint16)(i2cData[1]));
	hdata[1] = (int16)((((uint16)(i2cData[4]))<<8)+(uint16)(i2cData[3]));
	hdata[2] = (int16)((((uint16)(i2cData[6]))<<8)+(uint16)(i2cData[5]));

	sngHX = hdata[0];
	sngHY = hdata[1];
	sngHZ = hdata[2];

	/* TEST*/
	TEST_DATA(TLIMIT_NO_SNG_HX, TLIMIT_TN_SNG_HX, hdata[0], TLIMIT_LO_SNG_HX, TLIMIT_HI_SNG_HX, &pf_total);
	TEST_DATA(TLIMIT_NO_SNG_HY, TLIMIT_TN_SNG_HY, hdata[1], TLIMIT_LO_SNG_HY, TLIMIT_HI_SNG_HY, &pf_total);
	TEST_DATA(TLIMIT_NO_SNG_HZ, TLIMIT_TN_SNG_HZ, hdata[2], TLIMIT_LO_SNG_HZ, TLIMIT_HI_SNG_HZ, &pf_total);

	/* TEST*/
	TEST_DATA(TLIMIT_NO_SNG_ST2, TLIMIT_TN_SNG_ST2, (int16)i2cData[7], TLIMIT_LO_SNG_ST2, TLIMIT_HI_SNG_ST2, &pf_total);

	/* Generate magnetic field for self-test (Set ASTC register)*/
	i2cData[0] = 0x40;
	/*AKD_TxData(AK8975_REG_ASTC, i2cData, 1);*/

	/* Set to Self-test mode (Set CNTL register)*/
	i2cData[0] = AK8975_CNTL_SELF_TEST;
	/*AKD_TxData(AK8975_REG_CNTL, i2cData, 1);*/

	/* Wait for DRDY pin changes to HIGH.*/
	if (WaitForDRDY() == 0) {
		DispMessage(MSG_LEVEL0, "Failed to detect DRDY pin transition to High.\n");
		return 0;	/*error*/
	}

	/* Reset flag.         */
	/*g_DRDYIsHigh = FALSE;*/

	/* Get measurement data from AK8975                    */
	/* ST1 + (HXL + HXH) + (HYL + HYH) + (HZL + HZH) + ST2 */
	/* = 1 + (1 + 1) + (1 + 1) + (1 + 1) + 1 = 8Byte       */
	/*AKD_RxData(AK8975_REG_ST1, i2cData, AKSC_BDATA_SIZE);*/

	/* TEST*/
	TEST_DATA(TLIMIT_NO_SLF_ST1, TLIMIT_TN_SLF_ST1, (int16)i2cData[0], TLIMIT_LO_SLF_ST1, TLIMIT_HI_SLF_ST1, &pf_total);

	hdata[0] = (int16)((((uint16)(i2cData[2]))<<8)+(uint16)(i2cData[1]));
	hdata[1] = (int16)((((uint16)(i2cData[4]))<<8)+(uint16)(i2cData[3]));
	hdata[2] = (int16)((((uint16)(i2cData[6]))<<8)+(uint16)(i2cData[5]));

	/* TEST*/
	TEST_DATA(TLIMIT_NO_SLF_HX, TLIMIT_TN_SLF_HX, hdata[0], TLIMIT_LO_SLF_HX, TLIMIT_HI_SLF_HX, &pf_total);
	TEST_DATA(
		TLIMIT_NO_SLF_DFHX,
		TLIMIT_TN_SLF_DFHX,
		(hdata[0] - sngHX)*((asax - 128)*0.5/128 + 1),
		TLIMIT_LO_SLF_DFHX,
		TLIMIT_HI_SLF_DFHX,
		&pf_total
	);

	TEST_DATA(TLIMIT_NO_SLF_HY, TLIMIT_TN_SLF_HY, hdata[1], TLIMIT_LO_SLF_HY, TLIMIT_HI_SLF_HY, &pf_total);
	TEST_DATA(
		TLIMIT_NO_SLF_DFHY,
		TLIMIT_TN_SLF_DFHY,
		(hdata[1] - sngHY)*((asay - 128)*0.5/128 + 1),
		TLIMIT_LO_SLF_DFHY,
		TLIMIT_HI_SLF_DFHY,
		&pf_total
	);

	TEST_DATA(TLIMIT_NO_SLF_HZ, TLIMIT_TN_SLF_HZ, hdata[2], TLIMIT_LO_SLF_HZ, TLIMIT_HI_SLF_HZ, &pf_total);
	TEST_DATA(
		TLIMIT_NO_SLF_DFHZ,
		TLIMIT_TN_SLF_DFHZ,
		(hdata[2] - sngHZ)*((asaz - 128)*0.5/128 + 1),
		TLIMIT_LO_SLF_DFHZ,
		TLIMIT_HI_SLF_DFHZ,
		&pf_total
	);

	/* TEST*/
	TEST_DATA(TLIMIT_NO_SLF_ST2, TLIMIT_TN_SLF_ST2, (int16)i2cData[7], TLIMIT_LO_SLF_ST2, TLIMIT_HI_SLF_ST2, &pf_total);

	/* Set to Normal mode for self-test.*/
	i2cData[0] = 0x00;
	/*AKD_TxData(AK8975_REG_ASTC, i2cData, 1);*/

	return pf_total;
}

/*==========================================================================
 *
 *  FUNCTION:  MeasureSNGLoop()
 *
 *  PURPOSE:   This is the main routine of measurement.
 *
 *  DESCRIPTION:
 *
 *==========================================================================*/
void MeasureSNGLoop(
	AK8975PRMS *prms,	/* (i/o)Pointer to parameters of AK8975*/
	ACCPRMS * accprms
)
{
	BYTE		i2cData[AKSC_BDATA_SIZE];
	int16		i;
	int16		bData[AKSC_BDATA_SIZE];	/* Measuring block data*/
	float		avec[3];
	int16		ret;
	int32		ch;

	/* Reset flags         */
	/*g_DRDYIsHigh = FALSE;*/

	/* Initialize*/
	if (InitAK8975_Measure(prms) == 0) {
		DispMessage(MSG_LEVEL0, "Failed to initialize AK8975.\n\n");
		return;
	}

	/* Initialize Acceleration buffer*/
	InitAccBuffer(accprms->adata);

	while (TRUE) {
		/* Set to SNG measurement pattern (Set CNTL register)*/
		i2cData[0] = AK8975_CNTL_SNG_MEASURE;
		/*AKD_TxData(AK8975_REG_CNTL, i2cData, 1);*/

		/* Wait*/
		if (WaitForDRDY() == 1) {
			/* Reset flag.                                         */
			/*g_DRDYIsHigh = FALSE;                                */

			/* Get measurement data from AK8975                    */
			/* ST1 + (HXL + HXH) + (HYL + HYH) + (HZL + HZH) + ST2 */
			/* = 1 + (1 + 1) + (1 + 1) + (1 + 1) + 1 = 8Byte       */
			/*AKD_RxData(AK8975_REG_ST1, i2cData, AKSC_BDATA_SIZE);*/

			/* Copy to local variable*/
			for (i = 0; i < AKSC_BDATA_SIZE; i++) {
				bData[i] = i2cData[i];
			}

			/*	Acceleration sensor specific process.     */
			/*  Get acceelration sensor's measurement data    */
			/*  ,and subtract offset and normalize the vector.*/
			GetAccVec(prms, accprms, avec);
			prms->m_avec.u.x = (int16)(avec[0] * ASENSE_TARGET);
			prms->m_avec.u.y = (int16)(avec[1] * ASENSE_TARGET);
			prms->m_avec.u.z = (int16)(avec[2] * ASENSE_TARGET);

			ret = MeasuringEventProcess(
					bData,
					prms,
					getFormation(),
					CSPEC_HDECIMATOR_SNG,
					CSPEC_CNTSUSPEND_SNG
				  );

			/* Check the return value*/
			if (ret == AKRET_PROC_SUCCEED) {
				if (prms->m_cntSuspend > 0) {
					/* Show message*/
					DispMessage(MSG_LEVEL1, "Suspend cycle count = %d\n", prms->m_cntSuspend);
				}

				/* Display the result.*/
				Disp_MeasurementResult(prms);
			} else if (ret == AKRET_FORMATION_CHANGED) {
				/* Switch formation.*/
				SwitchSlider(prms);
			} else if (ret == AKRET_DATA_READERROR) {
				DispMessage(MSG_LEVEL0, "Data read error occurred.\n\n");
			} else if (ret == AKRET_DATA_OVERFLOW) {
				DispMessage(MSG_LEVEL0, "Data overflow occurred.\n\n");
			} else if (ret == AKRET_HFLUC_OCCURRED) {
				DispMessage(MSG_LEVEL0, "AKSC_HFlucCheck did not return 1.\n\n");
			} else {
				/* Does not reach here*/
				;
			}

			/* Adjust sampling frequency*/
			usleep(CSPEC_INTERVAL_SNG);
		} else {
			DispMessage(MSG_LEVEL0, "Failed to detect DRDY pin transition to High.\n\n");
			break;
		} /*if (WaitForDRDY() == 1)*/
	}
	/* Set to PowerDown mode*/
	i2cData[0] = AK8975_CNTL_POWER_DOWN;
	/*AKD_TxData(AK8975_REG_CNTL, i2cData, 1);*/

	/* Wait over 100 us*/
	usleep(1);
}

/*==========================================================================
 *
 *  FUNCTION:  MeasureSNGWithoutDRDYLoop()
 *
 *  PURPOSE:   This is the main routine of measurement.
 *
 *  DESCRIPTION:
 *
 *==========================================================================*/
void MeasureSNGWithoutDRDYLoop(
	AK8975PRMS *prms	/* (i/o)Pointer to parameters of AK8975*/
)
{
	BYTE	i2cData[AKSC_BDATA_SIZE+1];
	int16	i;
	int16	bData[AKSC_BDATA_SIZE];	/* Measuring block data*/
	float	avec[3];
	int16	ret;
	int32	ch;
	int16	data[12];
	int16	delay = 0;
	int16	cali_mode = 0, current_cali_mode = 0;
	signed char	cali_values[3];
	int16	cali_update = 0;
	int 	warning_printed = 0;

	/* initialize i2cData*/
	memset(i2cData, 0, AKSC_BDATA_SIZE);

	/* Initialize Acceleration buffer*/
	InitAccBuffer(prms->accPrms.adata);

	AKM_LOGD("%s: accprms->AO[%d] = %f, "
		"accprms->AS[%d] = %f)\n",
		__PRETTY_FUNCTION__,
		i, prms->accPrms.AO[i], i, prms->accPrms.AS[i]);

	if (!SendIOMessage(prms->m_aDevice, BMA_SET_MODE, BMA_MODE_NORMAL, NULL))
		LOGE("Enable BMA150 fail!!\n");
	else
		AKM_LOGD("Enable BMA150 successful!!\n");

	/* Initialize*/
	if (InitAK8975_Measure(prms) == 0) {
		DispMessage(MSG_LEVEL0, "Failed to initialize AK8975.\n\n");
		return;
	}
	AKM_LOGD("InitAK8975_Measure complete\n");

	while (TRUE) {

		/* Get the calibration data */
		if (!SendIOMessage(prms->m_aDevice, BMA_READ_CALI_VALUE, NULL,
		    cali_values)) {
			LOGE("Get calibration data ERROR!!\n");
			prms->accPrms.offset[0] = 0;
			prms->accPrms.offset[1] = 0;
			prms->accPrms.offset[2] = 0;
		} else {
			prms->accPrms.offset[0] = cali_values[0];
			prms->accPrms.offset[1] = cali_values[1];
			prms->accPrms.offset[2] = cali_values[2];
		}

		AKM_LOGD("prms->accPrms.offset[0], (offset_x) = %d\n",
			prms->accPrms.offset[0]);
		AKM_LOGD("prms->accPrms.offset[1], (offset_x) = %d\n",
			prms->accPrms.offset[1]);
		AKM_LOGD("prms->accPrms.offset[2], (offset_x) = %d\n",
			prms->accPrms.offset[2]);

		/* Get the calibration update status which is set by calibration tool */
		if (!SendIOMessage(prms->m_aDevice, BMA_GET_UPDATE_USER_CALI_DATA, NULL, &cali_update))
			AKM_LOGD("Get cali_update ERROR!!\n");
		AKM_LOGD("cali_update = %d\n", cali_mode);

		if (cali_update == 1) {
			LOGD("G_SENSOR_CALIBRATION_USER executed!\n");
			/*	Read Parameters from file.*/
			if (LoadParametersAcc(&(prms->accPrms)) == 0)
				SetDefaultPRMSAcc(&(prms->accPrms));

			if (!SendIOMessage(prms->m_aDevice, BMA_SET_UPDATE_USER_CALI_DATA, 0, NULL))
				LOGE("Set cali_update to 0 ERROR!!\n");

			LOGD("prms->accPrms.AO[0] = %lf\n",
				prms->accPrms.AO[0]);
			LOGD("prms->accPrms.AO[1] = %lf\n",
				prms->accPrms.AO[1]);
			LOGD("prms->accPrms.AO[2] = %lf\n",
				prms->accPrms.AO[2]);
		}


		/*Check Phone Status*/
		if (prms->m_iStatusCurrent != prms->m_iStatusNew)
			SwitchSlider(prms);

		/* Get the calibration mode which is set by calibration tool */
		if (!SendIOMessage(prms->m_aDevice, BMA_GET_CALI_MODE, NULL, &cali_mode))
			LOGE("Get cali_mode ERROR!!\n");
		AKM_LOGD("cali_mode = %d\n", cali_mode);

		if (cali_mode == 1 && current_cali_mode == 0) {
			chmod(SETTING_ACC_FILE_NAME, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH | S_IWOTH);
			current_cali_mode = 1;
		} else if (cali_mode == 0 && current_cali_mode == 1) {
			chmod(SETTING_ACC_FILE_NAME, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);
			current_cali_mode = 0;
		}

		/* Get the DELAY which is set by AP*/
		if (!SendIOMessage(prms->m_hDevice, AKDBMES_GET_DELAY, NULL, &delay)) {
			LOGE("MeasureLoop_GETDELAY ERROR\n");
			ret = AKRET_PROC_KILL;
			goto MESTHREAD_EXIT;
		}

		if (prms->m_Stop)
		{
			AKM_LOGD("Thread is going to finish! \n");

			/* Set return code;*/
			ret = AKRET_PROC_QUIT;

			/* Exit thread loop*/
			goto MESTHREAD_EXIT;
		}

		/* Set to SNG measurement pattern (Set CNTL register)*/
		/*i2cData[0] = AK8975_CNTL_SNG_MEASURE;              */
		/*AKD_TxData(AK8975_REG_CNTL, i2cData, 1);           */

		/*usleep(CSPEC_TIME_MEASUREMENTDRDY);*/

		/* Get measurement data from AK8975                    */
		/* ST1 + (HXL + HXH) + (HYL + HYH) + (HZL + HZH) + ST2 */
		/* = 1 + (1 + 1) + (1 + 1) + (1 + 1) + 1 = 8Byte       */
		/*AKD_RxData(AK8975_REG_ST1, i2cData, AKSC_BDATA_SIZE);*/

		i2cData[8] = 0; /* set debug flag to 0 per loop */

		if (prms->compass_chip) {
			/* Set to SNG measurement pattern (Set CNTL register)*/
			if (!SendIOMessage(prms->m_hDevice,
					AKDBMES_SET_MODE,
					AK8975_CNTL_SNG_MEASURE,
					NULL)) {
				LOGE("MeasureLoop SET MEASUREMENT ERROR\n");
				ret = AKRET_PROC_KILL;
				goto MESTHREAD_EXIT;
			}

			/* Get measurement data from AK8975                   */
			/* ST1 + (HXL + HXH) + (HYL + HYH) + (HZL + HZH) + ST2*/
			/* = 1 + (1 + 1) + (1 + 1) + (1 + 1) + 1 = 8Byte      */
			if (!SendIOMessage(prms->m_hDevice, AKDBMES_GETDATA, NULL, i2cData)) {
				LOGE("Measuring: GET DATA ERROR\n");
				continue;
			}
		}
		AKM_LOGD("GET MEASUREMENT DATA\n");
		AKM_LOGD("%s: i2cData(x1, x2, y1, y2, z1, z2) = "
			"(0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x)\n",
			__PRETTY_FUNCTION__, i2cData[1], i2cData[2]
			, i2cData[3], i2cData[4], i2cData[5], i2cData[6]);
		AKM_LOGD("%s: i2cData(ST1, x1, x2, y1, y2, z1, z2, ST2, debug) = "
			"(0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x, 0x%x)\n",
			__PRETTY_FUNCTION__, i2cData[0], i2cData[1], i2cData[2]
			, i2cData[3], i2cData[4], i2cData[5], i2cData[6], i2cData[7], i2cData[8]);

		set_debug_flag(i2cData[8]);

		/* Copy to local variable*/
		for (i = 0; i < AKSC_BDATA_SIZE; i++) {
			bData[i] = i2cData[i];
		}

		/*	Acceleration sensor specific process.     */
		/*  Get acceelration sensor's measurement data    */
		/*  ,and subtract offset and normalize the vector.*/
		GetAccVec(prms, &(prms->accPrms), avec);
		prms->m_avec.u.x = (int16)(avec[0] * ASENSE_TARGET);
		prms->m_avec.u.y = (int16)(avec[1] * ASENSE_TARGET);
		prms->m_avec.u.z = (int16)(avec[2] * ASENSE_TARGET);
		AKM_LOGD("%s: prms->m_avec(x, y, z) = "
			"(%4d, %4d, %4d)\n",
			__PRETTY_FUNCTION__, prms->m_avec.u.x,
			prms->m_avec.u.y, prms->m_avec.u.z);

		ret = MeasuringEventProcess(
				bData,
				prms,
				getFormation(),
				CSPEC_HDECIMATOR_SNGWITHOUTDRDY,
				CSPEC_CNTSUSPEND_SNGWITHOUTDRDY
			  );

		/* Check the return value*/
		if (ret == AKRET_PROC_SUCCEED) {
			if (prms->m_cntSuspend > 0) {
				/* Show message*/
				DispMessage(MSG_LEVEL1, "Suspend cycle count = %d\n", prms->m_cntSuspend);
			}

			/* Display the result.*/
			Disp_MeasurementResult(prms);

			/* Transform the matrix to Android framework*/
			data[0] = prms->m_theta / 64;
			data[1] = (prms->m_phi180) / 64;
			data[2] = (prms->m_eta90) / 64;
			data[3] = 0; /* AKM8975 does not have temperature*/
			data[4] = prms->m_hdst;
			data[5] = 0;

			/* Acceleration data transformation*/
			data[6]  = (prms->m_accx)*m_Alayout[0][0] +
			           (prms->m_accy)*m_Alayout[0][1] +
			           (prms->m_accz)*m_Alayout[0][2];
			data[7]  = (prms->m_accx)*m_Alayout[1][0] +
			           (prms->m_accy)*m_Alayout[1][1] +
			           (prms->m_accz)*m_Alayout[1][2];
			data[8]  = (prms->m_accx)*m_Alayout[2][0] +
			           (prms->m_accy)*m_Alayout[2][1] +
			           (prms->m_accz)*m_Alayout[2][2];

			/* Magnetic data transformation*/
			data[9]  = (prms->m_rmvx)*m_Hlayout[0][0] +
			           (prms->m_rmvy)*m_Hlayout[0][1] +
			           (prms->m_rmvz)*m_Hlayout[0][2];
			data[10] = (prms->m_rmvx)*m_Hlayout[1][0] +
			           (prms->m_rmvy)*m_Hlayout[1][1] +
			           (prms->m_rmvz)*m_Hlayout[1][2];
			data[11] = (prms->m_rmvx)*m_Hlayout[2][0] +
			           (prms->m_rmvy)*m_Hlayout[2][1] +
			           (prms->m_rmvz)*m_Hlayout[2][2];
/*
void Show_G_Sensor_Raw()
*/
			/* For modify alyouts of the CSPEC_ALAYOUT_** and M_ALAYOUT_** of G-Sensor*/
			AKM_LOGD("G_Sensor Raw: (accx, accy, accz) = (%4d, %4d, %4d)\n", prms->m_accx, prms->m_accy, prms->m_accz);

			AKM_LOGD("M_Sensor: (y, p, r) = (%4d, %4d, %4d), Status = %d\n", data[0], data[1], data[2], data[4]);
			AKM_LOGD("G_Sensor: (x, y, z)=(%4d, %4d, %4d)\n", data[6], data[7], data[8]);
			AKM_LOGD("Temperature: %d\n", data[3]);
			AKM_LOGD("M_Sensor Vec: (x, y, z)=(%d, %d, %d)\n", data[9], data[10], data[11]);

			if ((data[6] == 0) &&
			    (data[7] == 0) &&
			    (data[8] == 0) &&
			    (warning_printed == 0)) {
				LOGW("G_Sensor All Zero, please check!!\n");
				warning_printed = 1;
			}

			SendIOMessage(prms->m_hDevice, AKDBMES_SET_YPR, NULL, data );

			if (delay)
				usleep(delay*1000);

		} else if (ret == AKRET_FORMATION_CHANGED) {
			/* Switch formation.*/
			SwitchSlider(prms);
		} else if (ret == AKRET_DATA_READERROR) {
			DispMessage(MSG_LEVEL0, "Data read error occurred.\n\n");
		} else if (ret == AKRET_DATA_OVERFLOW) {
			DispMessage(MSG_LEVEL0, "Data overflow occurred.\n\n");
		} else if (ret == AKRET_HFLUC_OCCURRED) {
			DispMessage(MSG_LEVEL0, "AKSC_HFlucCheck did not return 1.\n\n");
		} else {
			/* Does not reach here*/
			;
		}

		/* Adjust sampling frequency*/
		usleep(CSPEC_INTERVAL_SNGWITHOUTDRDY);
	}
	/* Set to PowerDown mode*/
	i2cData[0] = AK8975_CNTL_POWER_DOWN;
	/*AKD_TxData(AK8975_REG_CNTL, i2cData, 1);*/

	/* Wait over 100 us*/
	usleep(1);

MESTHREAD_EXIT:
	AKM_LOGD("Exit Message=%d \n",ret);
	if (!SendIOMessage(prms->m_aDevice, BMA_SET_MODE, BMA_MODE_SLEEP, NULL))
		LOGE("Disable BMA150 fail!!\n");
	else
		AKM_LOGD("Disable BMA150 successful!!\n");
	pthread_exit((void*)ret);
}

/*==========================================================================
 *
 *  FUNCTION:  MeasuringEventProcess()
 *
 *  PURPOSE:   This function will be processed when DRDY pin event is occured
 *
 *  DESCRIPTION:
 *
 *==========================================================================*/
int16 MeasuringEventProcess(
	int16		bData[],	/* (i)  Measuring block data           */
	AK8975PRMS	*prms,		/* (i/o)Pointer to parameters of AK8975*/
	int16		curForm,	/* (i)  current formation     */
	int16		hDecimator,	/* (i)  decimator             */
	int16		cntSuspend	/* (i)	the counter of suspend*/
)
{
	int16vec	have;
	int16		dor, derr, hofl;
	int16		isOF;
	int16		hdSucc;
	int16		preThe;

	short log_raw_x, log_raw_y, log_raw_z;

	dor = 0;
	derr = 0;
	hofl = 0;

	AKM_LOGD("%s: bData(0, 1, 2, 3, 4, 5, 6, 7) = "
		"(%4d, %4d, %4d, %4d, %4d, %4d, %4d, %4d)\n",
		__PRETTY_FUNCTION__, bData[0], bData[1], bData[2]
		, bData[3], bData[4], bData[5], bData[6], bData[7]);
	AKM_LOGD("%s: prms->m_asa(x, y, z) = "
		"(%4d, %4d, %4d)\n",
		__PRETTY_FUNCTION__, prms->m_asa.u.x,
		prms->m_asa.u.y, prms->m_asa.u.z);

	/* Decompose one block data into each Magnetic sensor's data*/
	AKSC_Decomp8975(
		bData,
		prms->m_hnave,
		&prms->m_asa,
		prms->m_hdata,
		&prms->m_hn,
		&have,
		&dor,
		&derr,
		&hofl
	);
	AKM_LOGD("%s: have(x, y, z) = (%4d, %4d, %4d)\n",
		__PRETTY_FUNCTION__, have.u.x, have.u.y, have.u.z);

	log_raw_x = bData[2] << 8 | bData[1];
	log_raw_y = bData[4] << 8 | bData[3];
	log_raw_z = bData[6] << 8 | bData[5];

	/*LOGD("%s: HXH&HXL, HYH&HYL, HZH&HZL, hdata[0].u.x, hdata[0].u.y, hdata[0].u.z, asax, asay, asaz = %d, %d, %d, %d, %d, %d, %d, %d, %d",__PRETTY_FUNCTION__, log_raw_x, log_raw_y, log_raw_z, prms->m_hdata[0].u.x, prms->m_hdata[0].u.y, prms->m_hdata[0].u.z, prms->m_asa.u.x, prms->m_asa.u.y, prms->m_asa.u.z);*/

	/* Check the formation change*/
	if (prms->m_form != curForm) {
		/* Set counter*/
		prms->m_cntSuspend = cntSuspend;

		prms->m_form = curForm;

		return AKRET_FORMATION_CHANGED;
	}

	if (derr == 1) {
		return AKRET_DATA_READERROR;
	}

	if (prms->m_cntSuspend > 0) {
		prms->m_cntSuspend--;
	} else {
		/* Detect a fluctuation of magnetic field.*/
		isOF = AKSC_HFlucCheck(&(prms->m_hflucv), &(prms->m_hdata[0]));
		AKM_LOGD("AKSC_HFlucCheck return = %d, hofl = %d\n", isOF, hofl);

		if (hofl == 1) {
			/* Set a HDOE level as "HDST_UNSOLVED"*/
			AKSC_SetHDOELevel(
				&prms->m_hdoev,
				&prms->m_ho,
				AKSC_HDST_UNSOLVED,
				1
			);
			prms->m_hdst = AKSC_HDST_UNSOLVED;
			prms->HSUC_HDST[SLIDER_OPEN_STATUS] = AKSC_HDST_UNSOLVED;
			prms->HSUC_HDST[SLIDER_CLOSE_STATUS] = AKSC_HDST_UNSOLVED;

			log_raw_x = bData[2] << 8 | bData[1];
			log_raw_y = bData[4] << 8 | bData[3];
			log_raw_z = bData[6] << 8 | bData[5];

			LOGW("%s: Overflow: HXH&HXL, HYH&HYL, HZH&HZL, hdata[0].u.x, "
				"hdata[0].u.y, hdata[0].u.z, asax, asay, asaz = %d, "
				"%d, %d, %d, %d, %d, %d, %d, %d, %d",
				__PRETTY_FUNCTION__, log_raw_x, log_raw_y, log_raw_z,
				prms->m_hdata[0].u.x, prms->m_hdata[0].u.y, prms->m_hdata[0].u.z,
				prms->m_asa.u.x, prms->m_asa.u.y, prms->m_asa.u.z);

			return AKRET_DATA_OVERFLOW;
		} else if (isOF == 1) {
			/* Set a HDOE level as "HDST_UNSOLVED" 0->3, 3 is complete*/
			AKSC_SetHDOELevel(
				&prms->m_hdoev,
				&prms->m_ho,
				AKSC_HDST_UNSOLVED,
				1
			);
			prms->m_hdst = AKSC_HDST_UNSOLVED;
			prms->HSUC_HDST[SLIDER_OPEN_STATUS] = AKSC_HDST_UNSOLVED;
			prms->HSUC_HDST[SLIDER_CLOSE_STATUS] = AKSC_HDST_UNSOLVED;

			log_raw_x = bData[2] << 8 | bData[1];
			log_raw_y = bData[4] << 8 | bData[3];
			log_raw_z = bData[6] << 8 | bData[5];

			LOGW("%s: Fluctuation: HXH&HXL, HYH&HYL, HZH&HZL, hdata[0].u.x, "
				"hdata[0].u.y, hdata[0].u.z, asax, asay, asaz = %d, "
				"%d, %d, %d, %d, %d, %d, %d, %d, %d",
				__PRETTY_FUNCTION__, log_raw_x, log_raw_y, log_raw_z,
				prms->m_hdata[0].u.x, prms->m_hdata[0].u.y, prms->m_hdata[0].u.z,
				prms->m_asa.u.x, prms->m_asa.u.y, prms->m_asa.u.z);

			return AKRET_HFLUC_OCCURRED;
		} else {
			AKM_LOGD("%s: Go to HDOE\n", __PRETTY_FUNCTION__);
			prms->m_callcnt--;
			if (prms->m_callcnt <= 0) {
				AKM_LOGD("%s: prms->m_licenser = %s\n",
					__PRETTY_FUNCTION__, (char *)prms->m_licenser);
				AKM_LOGD("%s: prms->m_licensee = %s\n",
					__PRETTY_FUNCTION__, (char *)prms->m_licensee);
				AKM_LOGD("%s: prms->m_key(0, 1, 2, 3, 4) = "
					"(%4d, %4d, %4d, %4d, %4d)\n",
					__PRETTY_FUNCTION__, prms->m_key[0], prms->m_key[1],
					prms->m_key[2], prms->m_key[3], prms->m_key[4]);
				/*Calculate Magnetic sensor's offset by DOE*/
				hdSucc = AKSC_HDOEProcessS3(
							prms->m_licenser,
							prms->m_licensee,
							prms->m_key,
							&prms->m_hdoev,
							prms->m_hdata,
							prms->m_hn,
							&prms->m_ho,
							&prms->m_hdst
						 );
				AKM_LOGD("AKSC_HDOEProcessS3 return = 0x%x\n", hdSucc);
				AKM_LOGD("AKSC_HDOEProcessS3 return prms->m_hdst = %d", prms->m_hdst);

				if (hdSucc > 0) {
					prms->HSUC_HO[prms->m_iStatusCurrent] = prms->m_ho;
					prms->HSUC_HDST[prms->m_iStatusCurrent] = prms->m_hdst;
					prms->HFLUCV_HREF[prms->m_iStatusCurrent] = prms->m_hflucv.href;
				}
				prms->m_callcnt = hDecimator;
			}
		}
	}

	/* Subtract offset and normalize magnetic field vector.*/
	AKSC_VNorm(
		&have,
		&prms->m_ho,
		&prms->m_hs,
		AKSC_HSENSE_TARGET,
		&prms->m_hvec
	);
	AKM_LOGD("M_SENSOR NORMALIZE\n");

	/* Calculate Azimuth, Pitch angle, Roll angle, and etc..*/
	/* Calculate filterd vector data.                       */
	preThe = prms->m_theta;

	AKM_LOGD("%s: prms->m_hvec(x, y, z) = (%4d, %4d, %4d)\n",
		__PRETTY_FUNCTION__, prms->m_hvec.u.x,
		prms->m_hvec.u.y, prms->m_hvec.u.z);

	/**************************************************/
	/*	Acceleration sensor specific process.     */
	/**************************************************/

	/* Subtract offset and normalize the vector.*/
	/* Shoud no necessary                       */
	/*AKSC_VNorm(&tmpA, &(accprms->AO), &(accprms->AS), AKSC_ASENSE_TARGET, &tmpNA);
	AKM_LOGD("G_SRNSOR NORMALIZE\n");*/
	AKM_LOGD("%s: prms->m_avec(x, y, z) = "
		"(%4d, %4d, %4d)\n",
		__PRETTY_FUNCTION__, prms->m_avec.u.x, prms->m_avec.u.y,
		prms->m_avec.u.z);

	/**************************************************/
	/*	Acceleration sensor specific process END. */
	/**************************************************/

	/* Debug: check the matrix*/
	AKM_LOGD("hlayout0: %d, %d, %d\n", prms->m_hlayout[0].m[0][0],
					prms->m_hlayout[0].m[0][1],
					prms->m_hlayout[0].m[0][2]);
	AKM_LOGD("          %d, %d, %d\n", prms->m_hlayout[0].m[1][0],
					prms->m_hlayout[0].m[1][1],
					prms->m_hlayout[0].m[1][2]);
	AKM_LOGD("          %d, %d, %d\n", prms->m_hlayout[0].m[2][0],
					prms->m_hlayout[0].m[2][1],
					prms->m_hlayout[0].m[2][2]);
	/* Debug: check the matrix*/
	AKM_LOGD("hlayout1: %d, %d, %d\n", prms->m_hlayout[1].m[0][0],
					prms->m_hlayout[1].m[0][1],
					prms->m_hlayout[1].m[0][2]);
	AKM_LOGD("          %d, %d, %d\n", prms->m_hlayout[1].m[1][0],
					prms->m_hlayout[1].m[1][1],
					prms->m_hlayout[1].m[1][2]);
	AKM_LOGD("          %d, %d, %d\n", prms->m_hlayout[1].m[2][0],
					prms->m_hlayout[1].m[2][1],
					prms->m_hlayout[1].m[2][2]);

	AKM_LOGD("%s: prms->m_dvec(x, y, z) = (%4d, %4d, %4d)\n",
		__PRETTY_FUNCTION__, prms->m_dvec.u.x,
		prms->m_dvec.u.y, prms->m_dvec.u.z);

	prms->m_ds3Ret = AKSC_DirectionS3(
						prms->m_licenser,
						prms->m_licensee,
						prms->m_key,
						&prms->m_hvec,
						&prms->m_avec,
						&prms->m_dvec,
						&prms->m_hlayout[prms->m_form],
						&prms->m_alayout[prms->m_form],
						&prms->m_theta,
						&prms->m_delta,
						&prms->m_hr,
						&prms->m_hrhoriz,
						&prms->m_ar,
						&prms->m_phi180,
						&prms->m_phi90,
						&prms->m_eta180,
						&prms->m_eta90,
						&prms->m_mat
					);

	prms->m_theta =	AKSC_ThetaFilter(
						prms->m_theta,
						preThe,
						CSPEC_THETAFILTER_SCALE
					);

	AKM_LOGD("%s: prms->m_theta = 0x%x\n", __PRETTY_FUNCTION__, prms->m_theta);

	AKM_LOGD("AKSC_DirectionS3 return = 0x%x\n", prms->m_ds3Ret);

	AKM_LOGI("MATRIX==[%4d,%4d,%4d]\n", prms->m_mat.m[0][0], prms->m_mat.m[0][1], prms->m_mat.m[0][2]);
	AKM_LOGI("MATRIX==[%4d,%4d,%4d]\n", prms->m_mat.m[1][0], prms->m_mat.m[1][1], prms->m_mat.m[1][2]);
	AKM_LOGI("MATRIX==[%4d,%4d,%4d]\n", prms->m_mat.m[2][0], prms->m_mat.m[2][1], prms->m_mat.m[2][2]);

	/* store Acceleration vector*/
	prms->m_accx = prms->m_avec.u.x;
	prms->m_accy = prms->m_avec.u.y;
	prms->m_accz = prms->m_avec.u.z;
	/* store Geomagnetic vector*/
	prms->m_rmvx = prms->m_hvec.u.x;
	prms->m_rmvy = prms->m_hvec.u.y;
	prms->m_rmvz = prms->m_hvec.u.z;

	AKM_LOGD("prms->m_accx = %d\n", prms->m_accx);
	AKM_LOGD("prms->m_accy = %d\n", prms->m_accy);
	AKM_LOGD("prms->m_accz = %d\n", prms->m_accz);

	AKM_LOGD("prms->m_rmvx = %d\n", prms->m_rmvx);
	AKM_LOGD("prms->m_rmvy = %d\n", prms->m_rmvy);
	AKM_LOGD("prms->m_rmvz = %d\n", prms->m_rmvz);

	return AKRET_PROC_SUCCEED;
}

/*==========================================================================
 *
 *  FUNCTION:  HDOECalibrationLoop()
 *
 *  PURPOSE:
 *
 *  DESCRIPTION:
 *
 *==========================================================================*/
void HDOECalibrationLoop(
	AK8975PRMS *prms		/* (i/o)Pointer to parameters of AK8975*/
)
{
	BYTE		i2cData[AKSC_BDATA_SIZE];
	AKSC_HDST	preHDST;
	int16		i;
	int16		bData[AKSC_BDATA_SIZE];	/* Measuring block data*/
	int16		ret = 0;
	int32		ch;

	/* Show message to start HDOE calibration.*/
	DispMessage(MSG_LEVEL1,
		"Please turn the sensor box like the character of 8.\n\n");
	Prmpt_Kbhit();

	/* Reset flags         */
	/*g_DRDYIsHigh = FALSE;*/

	/* Reset counter*/
	prms->m_timercnt = 0;

	/* Reset HDOE LEVEL*/
	prms->HSUC_HDST[prms->m_form] = AKSC_HDST_UNSOLVED;

	/* Initialize*/
	if (InitAK8975_Measure(prms) == 0) {
		DispMessage(MSG_LEVEL0, "Failed to initialization of AK8975 parameters.\n\n");
		return;
	}

	/* Show HDOE level.*/
	Disp_HDOECalibResult(prms);

	while (TRUE) {
		/* Set to SNG measurement pattern (Set CNTL register)*/
		i2cData[0] = AK8975_CNTL_SNG_MEASURE;
		/*AKD_TxData(AK8975_REG_CNTL, i2cData, 1);*/

		preHDST = prms->m_hdst;

		/* Wait*/
		if (WaitForDRDY() == 1) {
			/* Reset flag.         */
			/*g_DRDYIsHigh = FALSE;*/

			prms->m_timercnt++;

			/* Get measurement data from AK8975                    */
			/* ST1 + (HXL + HXH) + (HYL + HYH) + (HZL + HZH) + ST2 */
			/* = 1 + (1 + 1) + (1 + 1) + (1 + 1) + 1 = 8Byte       */
			/*AKD_RxData(AK8975_REG_ST1, i2cData, AKSC_BDATA_SIZE);*/

			/* Copy to local variable*/
			for (i = 0; i < AKSC_BDATA_SIZE; i++) {
				bData[i] = i2cData[i];
			}

			ret = HDOECalibrationEventProcess(
					bData,
					prms,
					getFormation(),
					CSPEC_HDECIMATOR_HDOECALIB
				  );

			/* Check the return value*/
			if (ret == AKRET_PROC_SUCCEED) {
				if (prms->m_hdst != preHDST) { /* HDOE LEVEL change?*/
					/* Display the result.*/
					Disp_HDOECalibResult(prms);
				}
			} else if (ret == AKRET_FORMATION_CHANGED) {
				/* Error*/
				DispMessage(MSG_LEVEL0, "Do not change formation during calibration.\n\n");
				break;
			} else if (ret == AKRET_DATA_READERROR) {
				DispMessage(MSG_LEVEL0, "Data read error occurred.\n\n");
			} else if (ret == AKRET_DATA_OVERFLOW) {
				DispMessage(MSG_LEVEL0, "Data overflow occurred.\n\n");
			} else if (ret == AKRET_HFLUC_OCCURRED) {
				DispMessage(MSG_LEVEL0, "A fluctuation of magnetic field occurred.\n\n");
			} else {
				/* Does not reach here*/
				;
			}

			if (prms->m_timercnt >= CSPEC_TIMEOUT_CALLCNT_HDOECALIB) {
				DispMessage(MSG_LEVEL1, "HDOECalibration is finished.\n\n");
				break;
			}

			/* Adjust sampling frequency*/
			usleep(CSPEC_INTERVAL_SNG);
		} /*if (WaitForDRDY() == 1)*/
	}

	if (ret != AKRET_FORMATION_CHANGED) {
		if (prms->m_hdst == AKSC_HDST_UNSOLVED) {
			DispMessage(MSG_LEVEL0, "No magnetic offset data is determined. \n\n");
		} else {
			Disp_HDOELevel(prms);
		}
	}

	/* Set to PowerDown mode*/
	i2cData[0] = AK8975_CNTL_POWER_DOWN;
	/*AKD_TxData(AK8975_REG_CNTL, i2cData, 1);*/

	/* Wait over 100 us*/
	usleep(1);

	Prmpt_Kbhit();
}

/*==========================================================================
 *
 *  FUNCTION:  HDOECalibrationEventProcess()
 *
 *  PURPOSE:
 *
 *  DESCRIPTION:
 *
 *==========================================================================*/
int16 HDOECalibrationEventProcess(
	int16		bData[],	/* (i)  Measuring block data*/
	AK8975PRMS	*prms,		/* (i/o)Pointer to parameters of AK8975*/
	int16		curForm,	/* (i)  current formation              */
	int16		hDecimator	/* (i)  decimator                      */
)
{
	int16vec	have;
	int16		dor, derr, hofl;
	int16		isOF;
	int16		hdSucc;

	dor = 0;
	derr = 0;
	hofl = 0;

	/* Decompose one block data into each Magnetic sensor's data*/
	AKSC_Decomp8975(
		bData,
		prms->m_hnave,
		&prms->m_asa,
		prms->m_hdata,
		&prms->m_hn,
		&have,
		&dor,
		&derr,
		&hofl
	);

	/* Check the formation change*/
	if (prms->m_form != curForm) {
		return AKRET_FORMATION_CHANGED;
	}

	if (derr == 1) {
		return AKRET_DATA_READERROR;
	}

	/* Detect a fluctuation of magnetic field.*/
	isOF = AKSC_HFlucCheck(&(prms->m_hflucv), &(prms->m_hdata[0]));

	if (hofl == 1) {
		/* Set a HDOE level as "HDST_UNSOLVED"*/
		AKSC_SetHDOELevel(
			&prms->m_hdoev,
			&prms->m_ho,
			AKSC_HDST_UNSOLVED,
			1
		);
		prms->m_hdst = AKSC_HDST_UNSOLVED;
		return AKRET_DATA_OVERFLOW;
	} else if (isOF == 1) {
		/* Set a HDOE level as "HDST_UNSOLVED"*/
		AKSC_SetHDOELevel(
			&prms->m_hdoev,
			&prms->m_ho,
			AKSC_HDST_UNSOLVED,
			1
		);
		prms->m_hdst = AKSC_HDST_UNSOLVED;
		return AKRET_HFLUC_OCCURRED;
	} else {
		prms->m_callcnt--;
		if (prms->m_callcnt <= 0) {
			/*Calculate Magnetic sensor's offset by DOE*/
			hdSucc = AKSC_HDOEProcessS3(
						prms->m_licenser,
						prms->m_licensee,
						prms->m_key,
						&prms->m_hdoev,
						prms->m_hdata,
						prms->m_hn,
						&prms->m_ho,
						&prms->m_hdst
					 );

			if (hdSucc > 0) {
				prms->HSUC_HO[prms->m_form] = prms->m_ho;
				prms->HSUC_HDST[prms->m_form] = prms->m_hdst;
				prms->HFLUCV_HREF[prms->m_form] = prms->m_hflucv.href;
			}

			prms->m_callcnt = hDecimator;
		}
	}

	return AKRET_PROC_SUCCEED;
}

/*==========================================================================
 *
 *  FUNCTION:  HCalibration()
 *
 *  PURPOSE:  The function dispatched from HOffsetCal()
 *
 *  DESCRIPTION:
 *
 *==========================================================================*/
int16 HCalibration(
	AK8975PRMS	*prms		/*(i/o)Pointer to parameters of AK8975*/
)
{
	int16		i, j, k;
	BYTE		i2cData[AKSC_BDATA_SIZE+1];
	int16		bData[AKSC_BDATA_SIZE];
	int16vec	have;
	int16vec	vec[3];
	int16		dor, derr, hofl;

	dor = 0;
	derr = 0;
	hofl = 0;

	for (i = 0; i < 3; i++) {
		AKSC_InitDecomp8975(prms->m_hdata);

		/* Reset flags         */
		/*g_DRDYIsHigh = FALSE;*/

		/* Show 1st-3rd message and wait for user input.*/
		switch (i) {
		case 0:
			DispMessage(MSG_LEVEL0, "[01] Hold the sensor box horizontally.\n");
			break;
		case 1:
			DispMessage(MSG_LEVEL0, "[02] Rotate 180 degrees in a horizontal plane.\n");
			break;
		case 2:
			DispMessage(MSG_LEVEL0, "[03] Turn over the sensor box.\n");
			break;
		default:
			DispMessage(MSG_LEVEL0, "Unknown error.\n");
			break;
		}
		Prmpt_Kbhit();

		for (j = 0; j < CSPEC_MESNUM_HCALIB; j++) {
			/* Set to SNG measurement pattern (Set CNTL register)*/
			i2cData[0] = AK8975_CNTL_SNG_MEASURE;
			/*AKD_TxData(AK8975_REG_CNTL, i2cData, 1);*/

			/* Wait*/
			if (WaitForDRDY() == 1) {
				/* Reset flag.         */
				/*g_DRDYIsHigh = FALSE;*/

				/* Get measurement data from AK8975                    */
				/* ST1 + (HXL + HXH) + (HYL + HYH) + (HZL + HZH) + ST2 */
				/* = 1 + (1 + 1) + (1 + 1) + (1 + 1) + 1 = 8Byte       */
				/*AKD_RxData(AK8975_REG_ST1, i2cData, AKSC_BDATA_SIZE);*/

				/* Copy to local variable*/
				for (k = 0; k < AKSC_BDATA_SIZE; k++) {
					bData[k] = i2cData[k];
				}

				/* Decompose one block data into each Magnetic sensor's data*/
				AKSC_Decomp8975(
					bData,
					prms->m_hnave,
					&prms->m_asa,
					prms->m_hdata,
					&prms->m_hn,
					&have,
					&dor,
					&derr,
					&hofl
				);
				/* Adjust sampling frequency*/
				usleep(CSPEC_INTERVAL_SNG);
			} /* if (WaitForDRDY() == 1)*/
		} /* for(j=0; j<CSPEC_MESNUM_HCALIB; j++)*/

		vec[i] = have;
	} /* for(i=0; i<3; i++)*/

	/* Calculates offsets of X,Y and Z axis Hall sensor by manual operation.*/
	AKSC_HOffsetCal(vec, &prms->HSUC_HO[prms->m_form]);

	/* Set a HDOE level as 3*/
	prms->m_hdst = AKSC_HDST_L2;
	prms->HSUC_HDST[prms->m_form] = prms->m_hdst;

	/* Show final message*/
	DispMessage(MSG_LEVEL0, "Calibration is finished.\n\n");
	DispMessage(MSG_LEVEL0, "FORMATION=%2d, LEVEL=%2d.\n",
		prms->m_form,
		prms->HSUC_HDST[prms->m_form]
	);
	DispMessage(MSG_LEVEL0, "HOFFSET:  x=%5d, y=%5d, z=%5d\n",
		prms->HSUC_HO[prms->m_form].u.x,
		prms->HSUC_HO[prms->m_form].u.y,
		prms->HSUC_HO[prms->m_form].u.z);
	DispMessage(MSG_LEVEL0, "\n");

	/* Set to PowerDown mode*/
	i2cData[0] = AK8975_CNTL_POWER_DOWN;
	/*AKD_TxData(AK8975_REG_CNTL, i2cData, 1);*/

	/* Wait over 100 us*/
	usleep(100);

	Prmpt_Kbhit();

	return 1;
}

