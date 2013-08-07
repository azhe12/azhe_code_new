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
#include "DispMessage.h"
#include "ak8975_log.h"
/* Include file for user definition.*/
#include "CustomerSpec.h"

#define AKMD_VERSION  "1.1.0-HUA"

/*==========================================================================
 *
 *  FUNCTION: Disp_StartMessage
 *
 *  PURPOSE:  Display AK8975 library software version.
 *
 *  DESCRIPTION:
 *
 *==========================================================================*/
void Disp_StartMessage(void)
{
	char ver[64] = "";

	strncat (ver, AKMD_VERSION, 64);

	LOGD("AK8975 daemon %s Start\n(Library version : %d.%d.%d.%d)\n",
		ver,
		AKSC_GetVersion_Major(),
		AKSC_GetVersion_Minor(),
		AKSC_GetVersion_Revision(),
		AKSC_GetVersion_DateCode());

	DispMessage(MSG_LEVEL0, "SampleConsole for AK8975 v1.0.1.1023 (Library version : %d.%d.%d.%d)\n",
		AKSC_GetVersion_Major(),
		AKSC_GetVersion_Minor(),
		AKSC_GetVersion_Revision(),
		AKSC_GetVersion_DateCode());
	DispMessage(MSG_LEVEL0, "Provided by Asahi KASEI Microdevices. All rights reserved.\n");
	DispMessage(MSG_LEVEL0, "This program is compiled for ");
#if defined(AKD_ACCSENSOR_ST)
	DispMessage(MSG_LEVEL0, "LIS302DL by STMicroelectronics.\n\n");
#elif defined(AKD_ACCSENSOR_BOSCH)
	DispMessage(MSG_LEVEL0, "SMB380/BMA150 by Bosch Sensortec.\n\n");
#endif
}

/*==========================================================================
 *
 *  FUNCTION: Disp_ErrorMessage
 *
 *  PURPOSE:
 *
 *  DESCRIPTION:
 *
 *==========================================================================*/
void Disp_ErrorMessage(ERROR_MESSAGE_ID errID)
{
	switch(errID){
	case ERMES_DEVNAME_INVALID:
		LOGE("Input device name is invalid.\n\n");
		break;

	case ERMES_INIT_DEVICE_FAILED:
		LOGE("Device initialization failed.\n\n");
		break;

	case ERMES_TMPFILEOPEN_FAILED:
		LOGE("Failed to open the temporary file.\n");
		break;

	case ERMES_LOAD_PARAMS_FAILED:
		LOGE("Failed to load parameters from file.\n\n");
		break;

	case ERMES_FCTSHIPMNTTEST_ABORTED:
		LOGE("Factory shipment test was ABORTED.\n");
		break;

	case ERMES_NO_OPERATION_SELECTED:
		LOGE("Selected operation mode is invalid.\n\n");
		break;

	case ERMES_INIT_AK8973_FAILED:
		LOGE("Failed to initialize AK8973.\n\n");
		break;
	case ERMES_MEASURING_FAILED:
		LOGE("Measuring process was failed with some reason.\n\n");
		break;

	default:
		LOGE("Unknown Error ID(0x%X).\n\n", errID);
		break;
	}
}

/*==========================================================================
 *
 *  FUNCTION: DispMessage
 *
 *  PURPOSE:
 *
 *  DESCRIPTION:
 *
 *==========================================================================*/
void DispMessage(
	const MSGLEVELS msgLevel,
	const char *format,
	...
)
{
	/*va_list va;

	if(msgLevel <= DISPMESSAGE_LEVEL){
		va_start(va, format);
		vprintf(format, va);
		va_end(va);
	}*/
}

/*==========================================================================
 *
 *  FUNCTION: Disp_MeasurementResult
 *
 *  PURPOSE:
 *
 *  DESCRIPTION:
 *
 *==========================================================================*/
void Disp_MeasurementResult(AK8975PRMS *prms)
{
	DispMessage(MSG_LEVEL0, "FORMATION = %d\n", prms->m_form);

	if (prms->m_ds3Ret & 0x1)
		DispMessage(MSG_LEVEL0, "THETA=%6.1f, ", prms->m_theta/64.);
	else
		DispMessage(MSG_LEVEL0, "THETA= -    , ");

	if (prms->m_ds3Ret & 0x2) {
		DispMessage(MSG_LEVEL0, "PITCH=%6.1f(%6.1f), ROLL=%6.1f(%6.1f)\n",
			prms->m_phi180/64.,
			prms->m_phi90/64.,
			prms->m_eta180/64.,
			prms->m_eta90/64.
		);
	} else {
		DispMessage(MSG_LEVEL0, "PITCH= -    ( -    ), ROLL= -    ( -    )\n");
	}

	if (prms->m_hdoev.hthIdx == AKSC_HDFI_SMA)	/* Small*/
		DispMessage(MSG_LEVEL0, "HDOE Parameter Set:Small\n");
	else if (prms->m_hdoev.hthIdx == AKSC_HDFI_NOR) /* Normal*/
		DispMessage(MSG_LEVEL0, "HDOE Parameter Set:Normal\n");

	DispMessage(MSG_LEVEL0, "LEVEL=%2d\n", prms->m_hdst);
	DispMessage(MSG_LEVEL0, "HR=%3.1f\n", prms->m_hr*0.06);

	/* 0.06 = 1/5 * 0.3
	 * hr is quintupled format (x5) .
	 * 1LSB = 0.3uT*/
	DispMessage(MSG_LEVEL0, "HOFFSET:  x=%5d,y=%5d,z=%5d\n",
			prms->m_ho.u.x, prms->m_ho.u.y, prms->m_ho.u.z);
	DispMessage(MSG_LEVEL0, "DOE HR=%3.1f\n", prms->m_hdoev.hrdoeHR*0.06);
	DispMessage(MSG_LEVEL0, "INCLINATION=%6.1f\n", prms->m_delta/64.);

	DispMessage(MSG_LEVEL0, "\n");

}

/*==========================================================================
 *
 *  FUNCTION: Disp_HDOECalibResult
 *
 *  PURPOSE:
 *
 *  DESCRIPTION:
 *
 *==========================================================================*/
void Disp_HDOECalibResult(AK8975PRMS *prms)
{
	if (prms->m_hdst == AKSC_HDST_UNSOLVED)
		DispMessage(MSG_LEVEL0, "FORMATION=%2d, LEVEL= 0/3\n", prms->m_form);
	else {
		DispMessage(MSG_LEVEL0, "FORMATION=%2d, LEVEL=%2d/3, PARAMETER= %s\n",
			prms->m_form,
			prms->m_hdst,
			(prms->m_hdoev.hthIdx == AKSC_HDFI_NOR) ? ("Normal") : ("Small"));
	}
}

/*==========================================================================
 *
 *  FUNCTION: Disp_HDOELevel
 *
 *  PURPOSE:
 *
 *  DESCRIPTION:
 *
 *==========================================================================*/
void Disp_HDOELevel(AK8975PRMS *prms)
{
	DispMessage(MSG_LEVEL0, "FORMATION=%2d, LEVEL=%2d.\n\n",
		prms->m_form,
		prms->HSUC_HDST[prms->m_form]
	);
}

/*==========================================================================
 *
 *  FUNCTION: Menu_ACalibration
 *
 *  PURPOSE:
 *
 *  DESCRIPTION:
 *
 *==========================================================================*/
int16 Menu_ACalibration(void)
{
	DispMessage(MSG_LEVEL0, "\n");
	DispMessage(MSG_LEVEL0, " ------------ Acceleration sensor offset calibration------------ \n");
	DispMessage(MSG_LEVEL0, "  Execute acceleration sensor offset calibration?\n\n");
	DispMessage(MSG_LEVEL0, "   Y/y : Yes, start the calibration.\n");
	DispMessage(MSG_LEVEL0, "   N/n : No, the calibration DOES NOT need to be executed.\n");
	DispMessage(MSG_LEVEL0, " --------------------------------------------------------------- \n\n");

	return Menu_YesNo();
}

/*==========================================================================
 *
 *  FUNCTION: Menu_FctShipmntTest
 *
 *  PURPOSE:
 *
 *  DESCRIPTION:
 *
 *==========================================================================*/
int16 Menu_FctShipmntTest(void)
{
	DispMessage(MSG_LEVEL0, "\n");
	DispMessage(MSG_LEVEL0, " -------------------- Factory shipment test -------------------- \n");
	DispMessage(MSG_LEVEL0, "  Execute factory shipment test ?\n\n");
	DispMessage(MSG_LEVEL0, "   Y/y : Yes, start factory shipment test.\n");
	DispMessage(MSG_LEVEL0, "   N/n : No, factory shipment test DOES NOT need to be executed.\n");
	DispMessage(MSG_LEVEL0, " --------------------------------------------------------------- \n\n");

	return Menu_YesNo();
}

/*==========================================================================
 *
 *  FUNCTION: Menu_Main
 *
 *  PURPOSE:
 *
 *  DESCRIPTION:
 *
 *==========================================================================*/
MODE Menu_Main(void)
{
	char msg[20];
	memset(msg, 0, sizeof(msg));

	DispMessage(MSG_LEVEL0, " --------------------  AK8975 Console Application -------------------- \n");
	DispMessage(MSG_LEVEL0, "   T. Start Factory Shipment Test. \n");
	DispMessage(MSG_LEVEL0, "   1. Start Continuous Measurement. \n");
	DispMessage(MSG_LEVEL0, "   2. Start Single     Measurement. \n");
	DispMessage(MSG_LEVEL0, "   3. Start Single     Measurement  without DRDY. \n");
	DispMessage(MSG_LEVEL0, "   4. Start Trigger    Measurement. \n");
	DispMessage(MSG_LEVEL0, "   5. Optional magnetic sensor offset calibration. (HDOE) \n");
	DispMessage(MSG_LEVEL0, "   6. Optional magnetic sensor offset calibration. (3 posture) \n");
	DispMessage(MSG_LEVEL0, "   7. Optional acceleration sensor offset calibration. \n");
	DispMessage(MSG_LEVEL0, "   Q. Quit application. \n");
	DispMessage(MSG_LEVEL0, " --------------------------------------------------------------------- \n\n");

	DispMessage(MSG_LEVEL0, " Please select a number.\n");
	DispMessage(MSG_LEVEL0, "   ---> ");
	gets(msg);
	DispMessage(MSG_LEVEL0, "\n");

	/* BUG : If 2-digits number is input,
	 *	only the first character is compared.*/
	if (strncmp(msg, "T", 1) == 0 || strncmp(msg, "t", 1) == 0) {
		return MODE_FctShipmntTestBody;
	} else if (strncmp(msg, "1", 1) == 0) {
		return MODE_MeasureCONT;
	} else if (strncmp(msg, "2", 1) == 0) {
		return MODE_MeasureSNG;
	} else if (strncmp(msg, "3", 1) == 0) {
		return MODE_MeasureSNGWithoutDRDY;
	} else if (strncmp(msg, "4", 1) == 0) {
		return MODE_MeasureTrigger;
	} else if (strncmp(msg, "5", 1) == 0) {
		return MODE_HDOECalibration;
	} else if (strncmp(msg, "6", 1) == 0) {
		return MODE_HCalibration;
	} else if (strncmp(msg, "7", 1) == 0) {
		return MODE_ACalibration;
	} else if (strncmp(msg, "Q", 1) == 0 || strncmp(msg, "q", 1) == 0) {
		return MODE_Quit;
	} else {
		return MODE_ERROR;
	}
}

/*==========================================================================
 *
 *  FUNCTION: Menu_YesNo
 *
 *  PURPOSE:  Ask user to input Y or N.
 *
 *  DESCRIPTION: return value: 0 means No. 1 means Yes.
 *
 *==========================================================================*/
int16 Menu_YesNo(void)
{
	char msg[20];
	memset(msg, 0, sizeof(msg));

	while (1) {
		DispMessage(MSG_LEVEL0, " Please input Y[y] or N[n]. \n");
		DispMessage(MSG_LEVEL0, "   ---> ");
		gets(msg);
		DispMessage(MSG_LEVEL0, "\n");

		if (!strncmp(msg, "y", 1) || !strncmp(msg, "Y", 1)) {
			DispMessage(MSG_LEVEL0, "\n");
			return 1;
		} else if (!strncmp(msg, "n", 1) || !strncmp(msg, "N", 1)) {
			DispMessage(MSG_LEVEL0, "\n");
			return 0;
		}

		/* Try again.*/
		DispMessage(MSG_LEVEL0, " The input value is invalid!!\n\n");
	}
}

/*==========================================================================
 *
 *  FUNCTION: Prmpt_Kbhit
 *
 *  PURPOSE:
 *
 *  DESCRIPTION:
 *
 *==========================================================================*/
void Prmpt_Kbhit(void)
{
	char msg[20];
	memset(msg, 0, sizeof(msg));

	DispMessage(MSG_LEVEL0, "Please hit ENTER key.");
	gets(msg);
	DispMessage(MSG_LEVEL0, "\n");
}

/*==========================================================================
 *
 *  FUNCTION: Prmpt_ComPort
 *
 *  PURPOSE:  COM port input menu
 *
 *  DESCRIPTION:
 *
 *==========================================================================*/
int16 Prmpt_ComPort(
	char *strCom	/*(i)Serial Port*/
)
{
	int16 ret;
	char buf[4];

	DispMessage(MSG_LEVEL0, " Please input the Number of COM port. \n");
	DispMessage(MSG_LEVEL0, "   ---> ");
	gets(buf);
	DispMessage(MSG_LEVEL0, "\n");

	DispMessage(MSG_LEVEL0, " COM port is \"COM%s\" ? ", buf);

	ret = Menu_YesNo();

	if (ret == 1) {
		sprintf(strCom, "COM%s", buf);
	}

	return ret;
}

/*==========================================================================
 *
 *  FUNCTION: TEST_DATA
 *
 *  PURPOSE:
 *
 *  DESCRIPTION:
 *			1;  Pass
 *			-1; Fail
 *
 *
 *==========================================================================*/
int16 TEST_DATA(
	const	char	testno[],
	const	char	testname[],
	const	int16	testdata,
	const	int16	lolimit,
	const	int16	hilimit,
	int16		*pf_total
)
{
	int16	pf;	/*Pass;1, Fail;-1*/

	if (testno == NULL && strcmp(testname, "START") == 0) {	/* Display header*/
		DispMessage(MSG_LEVEL0, "--------------------------------------------------------------------\n");
		DispMessage(MSG_LEVEL0, " Test No. Test Name    Fail    Test Data    [      Low         High]\n");
		DispMessage(MSG_LEVEL0, "--------------------------------------------------------------------\n");

		pf = 1;
	} else if (testno == NULL && strcmp(testname, "END") == 0) {	/* Display result*/
		printf("--------------------------------------------------------------------\n");
		if (*pf_total == 1) {
			DispMessage(MSG_LEVEL0, "Factory shipment test was passed.\n\n");
		} else {
			DispMessage(MSG_LEVEL0, "Factory shipment test was failed.\n\n");
		}

		pf = 1;
	} else {
		if (lolimit <= testdata && testdata <= hilimit) {
			pf = 1;	/*Pass*/
		} else {
			pf = -1;	/*Fail*/
		}

		/*display result*/
		DispMessage(MSG_LEVEL0, " %7s  %-10s      %c     %10d    [%10d    %10d]\n",
			testno, testname, (pf == 1) ? ('.') : ('F'), testdata, lolimit, hilimit);
	}

	/*Pass/Fail check*/
	if (*pf_total != 0) {
		if (*pf_total == 1 && pf == 1) {
			*pf_total = 1;	/*Pass*/
		} else {
			*pf_total = -1;	/*Fail*/
		}
	}
	return pf;
}

