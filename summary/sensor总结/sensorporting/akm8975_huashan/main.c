/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Copyright (c) 2009 High Tech Computer Corporation
Module Name:
    main.c  - AK8975 Daemon
Abstract:
Auther:
    Andy Chuang Dec, 2009
Notes:
------------------------------------------------------------------*/

#include "ak8975_log.h"
#include "FileIO.h"
#include "DispMessage.h"
#include "Measure.h"
#include "AccSensorFunction.h"
#include "IOMessage.h"
#include "akmd_slider.h"
#include <pthread.h>

#define CSPEC_DEVICE_NAME	"/dev/akm8975_daemon"
#define GSR_DEVICE_NAME		"/dev/bma150"

static int debug_flag = 0;
static int operation_mode = 0;

extern short cspec_Hlayout[3][3];
extern short cspec_Alayout[3][3];
extern short m_Hlayout[3][3];
extern short m_Alayout[3][3];

int get_debug_flag(void)
{
	return debug_flag;
}

void set_debug_flag(int flag)
{
	debug_flag = flag;
}

int get_operation_mode(void)
{
	return operation_mode;
}

int main(void)
{
	AK8975PRMS	AK8975Prms;
/*	ACCPRMS		accPrms;*/
	char		deviceName[16];
	int16		mode, val;
	int		retValue = 1;
	int		mainQuit = 0;
	int		retry_times = 1;

	short		layouts[4][3][3];
	int		i, j, k;

	void		*Measure_thread_ret;
	void		*Slider_thread_ret;

	/***********************************************/
	/*	System Initialization.                 */
	/*	This Section is dependent to target OS.*/
	/***********************************************/
	/* Show the version info of this software.*/
	Disp_StartMessage();

	/* Ask serial communication device name.*/
	/*if (Prmpt_ComPort(deviceName) == 0) {
		DispMessage(MSG_LEVEL0, "Input device name is invalid.\n\n");
		retValue = 0;
		goto THE_END_OF_MAIN_FUNCTION;
	}*/

	/* Open serial communication device.
	if (AKD_InitDevice(deviceName) != AKD_SUCCESS) {
		DispMessage(MSG_LEVEL0, "Device initialization failed.\n\n");
		retValue = 0;
		goto THE_END_OF_MAIN_FUNCTION;
	}*/

	/*	Register callback function.              */
	/*	One is for DRDY interruption event.      */
	/*	The other one is for Timer elapsed event.*/
	/*AKD_RegisterCallback_DRDY((AKD_DRDY_CALLBACK)InterruptEvent);*/

	/* Open serial communication device.*/
	AK8975Prms.m_hDevice = open(CSPEC_DEVICE_NAME, 0666);
	AK8975Prms.m_aDevice = open(GSR_DEVICE_NAME, 0666);
	while ((AK8975Prms.m_hDevice < 0) || (AK8975Prms.m_aDevice < 0)) {
		LOGE("m_hDevice = %d\n", AK8975Prms.m_hDevice);
		LOGE("m_aDevice = %d\n", AK8975Prms.m_aDevice);
		Disp_ErrorMessage(ERMES_INIT_DEVICE_FAILED);
		retry_times++;
		if (retry_times > 3)
			while(1) sleep(10000);
		usleep(50000);
	}

	/* Get layout matrices*/
	if (!SendIOMessage(AK8975Prms.m_hDevice, AKDBMES_GET_MATRIX, NULL, (int16 *)layouts)) {
		LOGE("layouts retrieve error!!");
	}

	/* Judge whether the compass chip exists or not*/
	if (!SendIOMessage(AK8975Prms.m_hDevice, AKDBMES_SET_MODE, AK8975_CNTL_FUSE_ACCESS, NULL)) {
		AK8975Prms.compass_chip = 0;
		LOGE("No Compass chip inside\n");
	} else {
		SendIOMessage(AK8975Prms.m_hDevice, AKDBMES_SET_MODE, AK8975_CNTL_POWER_DOWN, NULL);
		AK8975Prms.compass_chip = 1;
	}

	for (j = 0; j < 3; j++)
		for (k = 0; k < 3; k++) {
			AKM_LOGD("layouts[0][%d][%d] = %d\n", j, k, layouts[0][j][k]);
			cspec_Hlayout[j][k] = layouts[0][j][k];
		}
	for (j = 0; j < 3; j++)
		for (k = 0; k < 3; k++) {
			AKM_LOGD("layouts[1][%d][%d] = %d\n", j, k, layouts[1][j][k]);
			cspec_Alayout[j][k] = layouts[1][j][k];
		}
	for (j = 0; j < 3; j++)
		for (k = 0; k < 3; k++) {
			AKM_LOGD("layouts[2][%d][%d] = %d\n", j, k, layouts[2][j][k]);
			m_Hlayout[j][k] = layouts[2][j][k];
		}
	for (j = 0; j < 3; j++)
		for (k = 0; k < 3; k++) {
			AKM_LOGD("layouts[3][%d][%d] = %d\n", j, k, layouts[3][j][k]);
			m_Alayout[j][k] = layouts[3][j][k];
		}

	/* Variables for acceleration sensor*/
	AK8975Prms.m_alayout[0].u._11 = (int16) cspec_Alayout[0][0];
	AK8975Prms.m_alayout[0].u._12 = (int16) cspec_Alayout[0][1];
	AK8975Prms.m_alayout[0].u._13 = (int16) cspec_Alayout[0][2];
	AK8975Prms.m_alayout[0].u._21 = (int16) cspec_Alayout[1][0];
	AK8975Prms.m_alayout[0].u._22 = (int16) cspec_Alayout[1][1];
	AK8975Prms.m_alayout[0].u._23 = (int16) cspec_Alayout[1][2];
	AK8975Prms.m_alayout[0].u._31 = (int16) cspec_Alayout[2][0];
	AK8975Prms.m_alayout[0].u._32 = (int16) cspec_Alayout[2][1];
	AK8975Prms.m_alayout[0].u._33 = (int16) cspec_Alayout[2][2];

	/* Variables for acceleration sensor*/
	AK8975Prms.m_alayout[1].u._11 = (int16) cspec_Alayout[0][0];
	AK8975Prms.m_alayout[1].u._12 = (int16) cspec_Alayout[0][1];
	AK8975Prms.m_alayout[1].u._13 = (int16) cspec_Alayout[0][2];
	AK8975Prms.m_alayout[1].u._21 = (int16) cspec_Alayout[1][0];
	AK8975Prms.m_alayout[1].u._22 = (int16) cspec_Alayout[1][1];
	AK8975Prms.m_alayout[1].u._23 = (int16) cspec_Alayout[1][2];
	AK8975Prms.m_alayout[1].u._31 = (int16) cspec_Alayout[2][0];
	AK8975Prms.m_alayout[1].u._32 = (int16) cspec_Alayout[2][1];
	AK8975Prms.m_alayout[1].u._33 = (int16) cspec_Alayout[2][2];

	/* Initialize parameters structure.*/
	InitAK8975PRMS(&AK8975Prms);

	while (1) {
		AKM_LOGD("AK8975 PROCESS START\n");

		while (1) { /* Get OPEN STATUS*/
			AKM_LOGD("GET OPEN STATUS START\n");
			if (!SendIOMessage(AK8975Prms.m_hDevice,
					AKDBMES_GET_OPEN_STATUS,
					NULL,
					&mode)) {
				LOGE("AK8975: Get open status ioctl fail.\n");
				return -1;
			}
			AKM_LOGD("AK8975: Get mode = %d.\n", mode);

			/*	Read Parameters from file.*/
			if (LoadParameters(&AK8975Prms) == 0) {
				DispMessage(MSG_LEVEL0, "Failed to load parameters from file.\n\n");
				SaveParameters(&AK8975Prms);
				/*while(1) sleep(10000);*/
			}

			/*	Read Parameters from file.*/
			if (LoadParametersAcc(&(AK8975Prms.accPrms)) == 0) {
				DispMessage(MSG_LEVEL0,
					"Failed to load acc parameters from file.(GET OPEN STATUS)\n\n");
				SetDefaultPRMSAcc(&(AK8975Prms.accPrms));
			}
			AKM_LOGD("%s: (AK8975Prms->accPrms)->AO[%d] = %f, "
				"(AK8975Prms->accPrms)->AS[%d] = %f)\n",
				__PRETTY_FUNCTION__,
				i, (AK8975Prms.accPrms).AO[i], i, (AK8975Prms.accPrms).AS[i]);

			/***********************************************/
			/*	Read FUSE ROM(ASAX, ASAY, ASAZ)        */
			/***********************************************/
			ReadAK8975FUSEROM(&AK8975Prms);

			if (mode == 1) {
				LOGD("Compass Start\n");

				/* Initial flags*/
				AK8975Prms.m_Stop = 0;
				AKM_LOGD("Set m_Stop = 0 in main\n");

				/* Create MeasureLoop thread*/
				pthread_create(
					&AK8975Prms.m_hThread,
					NULL,
					MeasureSNGWithoutDRDYLoop,
					(void *)&AK8975Prms);

				/* Create slider detect thread*/
				if (open_slider_detect(&AK8975Prms) != 0)
					LOGE("slider detect thread create failed \n");

				break;
			} else if (mode == -1) {
				LOGE("Compass driver encountered fatal error. \n");
				sleep(10);
			} else {
				AKM_LOGD("Get mode = %d. \n", mode);
				usleep(200000);
				continue;
			}
		} /* End Get OPEN STATUS*/

		while (1) { /* Get CLOSE STATUS*/
			SendIOMessage(AK8975Prms.m_hDevice, AKDBMES_GET_CLOSE_STATUS, NULL,  &val);
			AKM_LOGD("GET CLOSE STATUS, val=%d\n",val);
			if (val == 0) {
				/* close slider detect thread*/
				close_slider_detect(&AK8975Prms);

				AK8975Prms.m_Stop = 1;
				usleep(200 * 1000);

				/*	Read Parameters from file.*/
				if (LoadParametersAcc(&(AK8975Prms.accPrms)) == 0) {
					DispMessage(MSG_LEVEL0,
						"Failed to load acc parameters from file.(GET CLOSE STATUS)\n\n");
					SetDefaultPRMSAcc(&(AK8975Prms.accPrms));
				}

				/*loadInt16vec(SETTING_APP_NAME, "AOFFSET", &(AK8975Prms.AO), 0, SETTING_FILE_NAME);*/

				/*	Write Parameters to file.*/
				SaveParameters(&AK8975Prms);
				SaveParametersAcc(&(AK8975Prms.accPrms));

				/*SaveParameters(&AK8975Prms);*/
				AKM_LOGD("Parameter saved \n");

				pthread_join(AK8975Prms.m_hThread, &Measure_thread_ret);
				AKM_LOGD("pthread_join m_hThread returned: 0x%x\n", (int16 *)Measure_thread_ret);

				pthread_join(AK8975Prms.m_sThread, &Slider_thread_ret);
				AKM_LOGD("pthread_join m_sThread returned: %d\n", (int16 *)Slider_thread_ret);

				LOGD("Compass CLOSE \n");
				break;
			} else if (val == -1) {	/*Kernel encounters error*/
				LOGE("Compass driver encountered fatal error2. \n");
				sleep(10);
			} else {
				AKM_LOGD("CLOSE STATUS=%d\n",val);
				usleep(200000);
				continue;
			}
		} /* End Get CLOSE STATUS*/
	}

	/*	Read Parameters from file.*/
	/*if (LoadParameters(&AK8975Prms) == 0) {
		DispMessage(MSG_LEVEL0, "Failed to load parameters from file.\n\n");
		SetDefaultPRMS(&AK8975Prms);
	}

	//	Read Parameters from file.
	if (LoadParametersAcc(&accPrms) == 0) {
		DispMessage(MSG_LEVEL0, "Failed to load acc parameters from file.\n\n");
		SetDefaultPRMSAcc(&accPrms);
	}*/

	/***********************************************/
	/*	Read FUSE ROM(ASAX, ASAY, ASAZ)        */
	/***********************************************/
	ReadAK8975FUSEROM(&AK8975Prms);

	/***********************************************/
	/*	Here is the Main Menu                  */
	/***********************************************/
	while (mainQuit == 0) {
		/* Select operation*/
		switch (Menu_Main()) {
		case MODE_FctShipmntTestBody:
			FctShipmntTest_Body(&AK8975Prms);
			break;

		case MODE_MeasureCONT:
			MeasureCONTLoop(&AK8975Prms, &(AK8975Prms.accPrms));
			break;

		case MODE_MeasureSNG:
			MeasureSNGLoop(&AK8975Prms, &(AK8975Prms.accPrms));
			break;

		case MODE_MeasureSNGWithoutDRDY:
			MeasureSNGWithoutDRDYLoop(&AK8975Prms/*, &(AK8975Prms.accPrms)*/);
			break;

		case MODE_MeasureTrigger:
			MeasureTriggerLoop(&AK8975Prms, &(AK8975Prms.accPrms));
			break;

		case MODE_HDOECalibration:
			HDOECalibrationLoop(&AK8975Prms);
			break;

		case MODE_HCalibration:
			HCalibration(&AK8975Prms);
			break;

		case MODE_ACalibration:
			ACalibration(&(AK8975Prms.accPrms));
			break;

		case MODE_Quit:
			/* Change the loop flag.*/
			mainQuit = 1;
			break;

		default:
			DispMessage(MSG_LEVEL0, "Selected operation mode is invalid.\n\n");
			break;
		}
	}

	/*	Write Parameters to file.*/
	SaveParameters(&AK8975Prms);
	SaveParametersAcc(&(AK8975Prms.accPrms));

THE_END_OF_MAIN_FUNCTION:

	/***********************************************/
	/*	Close system resources.                */
	/***********************************************/
	/*AKD_DeinitDevice();*/

	return 0;
}


