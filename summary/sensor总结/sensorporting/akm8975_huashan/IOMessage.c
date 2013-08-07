/*************************************************************************
 *
 *  $Workfile: AKDBMessage.cpp $
 *
 *  $Author: Weirx $
 *  $Date: 07/12/06 10:26 $
 *  $Revision: 5 $
 *
 *  Developped by AsahiKASEI EMD Corporation
 *  Provided by AsahiKASEI Microsystems
 *  Copyright (C) 2005 AsahiKASEI EMD Corporation, All rights reserved
 *
 *************************************************************************/
#include "IOMessage.h"
#include "ak8975_log.h"

/*==========================================================================
 *
 *  FUNCTION:  SendAKDBMessage()
 *
 *  PURPOSE:   Send message to Demoboard
 *
 *  DESCRIPTION:
 *
 *==========================================================================*/
#ifndef NULL
#define NULL ((void *)0)
#endif

int16 SendIOMessage(
	int	hDevice,
	const	int16	message,
	const	int16	hParam,
	int16*	lParam
)
{
	/* Number of chars to be read*/
/*	long charsRead = 0;*/
	/* loop counter for AKDBMES_GETDATA*/
	int i, j, k;
	char msg[AKSC_BDATA_SIZE+1];
	int status;
	char rwbuf[5];
	short delay,buf[7];
	char  project_name[64] = "bahamas";
	short layouts[4][3][3];
	int   ret = 0;
	short cali_mode = 0;
	short cali_update = 0;
	signed char *cali_values;

	/* Only for debug*/
	LOGV("SendIOMessage = %d\n", message);

	if (get_operation_mode())
		return 0; /*SIMULATOR*/

	/* For safety*/
	memset(msg, 0, sizeof(msg));
	memset(rwbuf, 0, sizeof(rwbuf));

	switch(message)
	{
		case AKDBMES_WRITE_REGISTER:
			/* Write data*/
			rwbuf[0] = 2;
			rwbuf[1] = (char)hParam;
			rwbuf[2] = (char)*lParam;
			if (ioctl(hDevice, ECS_IOCTL_WRITE, rwbuf) < 0) {
				goto SENDAKDBMES_ERROR;
			}
			break;

		case AKDBMES_READ_REGISTER:
			LOGV("%s: AKDBMES_READ_REGISTER\n", __PRETTY_FUNCTION__);
			LOGV("%s: ECS_IOCTL_READ = 0x%x\n",
				__PRETTY_FUNCTION__, ECS_IOCTL_READ);
			/* Read data*/
			rwbuf[0] = 1;
			rwbuf[1] = (char)hParam;

			LOGV("%s: hParam = 0x%x\n",
				__PRETTY_FUNCTION__, hParam);

			ret = ioctl(hDevice, ECS_IOCTL_READ, rwbuf);
			if (ret < 0) {
				LOGV("%s: AKDBMES_READ_REGISTER error, ret = %d\n",
					__PRETTY_FUNCTION__, ret);
				goto SENDAKDBMES_ERROR;
			}
			*lParam = rwbuf[1];
			LOGV("%s: AKDBMES_READ_REGISTER success, rwbuf[1] = 0x%x\n",
				__PRETTY_FUNCTION__, rwbuf[1]);
			break;

		case AKDBMES_RESET:
			/*aaa if(ioctl(hDevice, ECS_IOCTL_RESET, msg)< 0){*/
			if (ioctl(hDevice, ECS_IOCTL_RESET, NULL) < 0) {
				goto SENDAKDBMES_ERROR;
			}
			break;

		case AKDBMES_SET_MODE:
			LOGV("%s: AKDBMES_SET_MODE\n", __PRETTY_FUNCTION__);
			LOGV("%s: ECS_IOCTL_SET_MODE = 0x%x\n",
				__PRETTY_FUNCTION__, ECS_IOCTL_SET_MODE);
			/* Set single measurement mode*/
			msg[0] = 1;
			msg[1] = hParam;

			LOGV("%s: hParam = 0x%x\n",
				__PRETTY_FUNCTION__, hParam);

			ret = ioctl(hDevice, ECS_IOCTL_SET_MODE, &hParam);
			if (ret < 0) {
				LOGV("%s: AKDBMES_SET_MODE error, ret = %d\n",
					__PRETTY_FUNCTION__, ret);
				goto SENDAKDBMES_ERROR;
			}
			LOGV("%s: AKDBMES_SET_MODE success\n", __PRETTY_FUNCTION__);
			break;

		case AKDBMES_GETDATA:
			LOGV("%s: AKDBMES_GETDATA\n", __PRETTY_FUNCTION__);
			LOGV("%s: ECS_IOCTL_GETDATA = 0x%x\n",
				__PRETTY_FUNCTION__, ECS_IOCTL_GETDATA);
			msg[0] = AKSC_BDATA_SIZE;
			ret = ioctl(hDevice, ECS_IOCTL_GETDATA, msg);
			if (ret < 0) {
				LOGV("%s: AKDBMES_SET_MODE error, ret = %d\n",
					__PRETTY_FUNCTION__, ret);
				goto SENDAKDBMES_ERROR;
			}
			for (i = 0; i < AKSC_BDATA_SIZE + 1; i++) {
				lParam[i] = msg[i];
			}
			LOGV("%s: AKDBMES_GETDATA success\n", __PRETTY_FUNCTION__);
			break;

		case AKDBMES_SET_VECTOR:
			/* Write data*/
			rwbuf[0] = 4;
			rwbuf[1] = (char)hParam;
			rwbuf[2] = (char)lParam[0];
			rwbuf[3] = (char)lParam[1];
			rwbuf[4] = (char)lParam[2];
			if (ioctl(hDevice, ECS_IOCTL_WRITE, rwbuf) < 0) {
				goto SENDAKDBMES_ERROR;
			}
			break;

		case AKDBMES_GET_VECTOR:
			/* Read data*/
			rwbuf[0] = 3;
			rwbuf[1] = (char)hParam;
			if (ioctl(hDevice, ECS_IOCTL_READ, rwbuf) < 0) {
				goto SENDAKDBMES_ERROR;
			}
			lParam[0] = rwbuf[1];
			lParam[1] = rwbuf[2];
			lParam[2] = rwbuf[3];
			break;

		case AKDBMES_SET_YPR:
			if (ioctl(hDevice, ECS_IOCTL_SET_YPR, lParam) < 0) {
				goto SENDAKDBMES_ERROR;
			}
			break;

		case AKDBMES_GET_OPEN_STATUS:
			LOGV("%s: AKDBMES_GET_OPEN_STATUS\n", __PRETTY_FUNCTION__);
			LOGV("%s: ECS_IOCTL_GET_OPEN_STATUS = 0x%x\n",
				__PRETTY_FUNCTION__, ECS_IOCTL_GET_OPEN_STATUS);
			ret = ioctl(hDevice, ECS_IOCTL_GET_OPEN_STATUS, &status);
			if (ret < 0) {
				LOGV("%s: AKDBMES_GET_OPEN_STATUS error, ret = %d\n",
					__PRETTY_FUNCTION__, ret);
				goto SENDAKDBMES_ERROR;
			}
			LOGV("%s: AKDBMES_GET_OPEN_STATUS success\n", __PRETTY_FUNCTION__);
			lParam[0] = (int16)status;
			break;

		case AKDBMES_GET_CLOSE_STATUS:
			if (ioctl(hDevice, ECS_IOCTL_GET_CLOSE_STATUS, &status) < 0) {
				goto SENDAKDBMES_ERROR;
			}
			lParam[0] = (int16) status;
			break;

		case AKDBMES_GET_DELAY:
			if (ioctl(hDevice, ECS_IOCTL_GET_DELAY, &delay) < 0) {
				goto SENDAKDBMES_ERROR;
			}
			lParam[0] = delay;
			break;

		case AKDBMES_GET_PROJECT_NAME:
			if (ioctl(hDevice, ECS_IOCTL_GET_PROJECT_NAME, &project_name) < 0) {
				goto SENDAKDBMES_ERROR;
			}
			strncpy((char *)lParam, project_name, 64);
			break;

		case AKDBMES_GET_MATRIX:
			if (ioctl(hDevice, ECS_IOCTL_GET_MATRIX, layouts) < 0) {
				goto SENDAKDBMES_ERROR;
			}
			for (i = 0; i < 4; i++)
				for (j = 0; j < 3; j++)
					for (k = 0; k < 3; k++) {
						LOGV("layouts[%d][%d][%d] = %d", i, j, k, layouts[i][j][k]);
						lParam[i*9+j*3+k] = layouts[i][j][k];
					}
			break;

		case BMA_INT_STATUS:
			if (ioctl(hDevice, BMA_IOCTL_INIT, NULL) < 0) {
				goto SENDAKDBMES_ERROR;
			}
			break;

		case BMA_WRITE_REGISTER:
			/* Write data*/
			rwbuf[0] = 2;
			rwbuf[1] = (char)hParam;
			rwbuf[2] = (char)*lParam;
			if (ioctl(hDevice, BMA_IOCTL_WRITE, rwbuf) < 0) {
				goto SENDAKDBMES_ERROR;
			}
			break;

		case BMA_READ_REGISTER:
			/* Read data*/
			rwbuf[0] = 1;
			rwbuf[1] = (char)hParam;
			if (ioctl(hDevice, BMA_IOCTL_READ, rwbuf) < 0) {
				goto SENDAKDBMES_ERROR;
			}
			*lParam = rwbuf[1];
			break;
		case BMA_READ_ACCELERATION:
			/*Read x,y,z acceleration data*/
			if (ioctl(hDevice, BMA_IOCTL_READ_ACCELERATION, buf) < 0) {
				goto SENDAKDBMES_ERROR;
			}
			for (i = 0; i < 3; i++) {
				lParam[i] = buf[i];
			}
			break;
		case BMA_READ_CALI_VALUE:
			/*Read x,y,z calibration data*/
			if (ioctl(hDevice, BMA_IOCTL_READ_CALI_VALUE, rwbuf) < 0) {
				goto SENDAKDBMES_ERROR;
			}

			cali_values = (signed char *)lParam;
			for (i = 0; i < 3; i++)
				cali_values[i] = rwbuf[i];

			break;
		case BMA_SET_MODE:
			if (ioctl(hDevice, BMA_IOCTL_SET_MODE, &hParam) < 0) {
				goto SENDAKDBMES_ERROR;
			}
			break;
		case BMA_GET_CALI_MODE:
			if (ioctl(hDevice, BMA_IOCTL_GET_CALI_MODE, &cali_mode) < 0) {
				LOGE("%s: BMA_GET_CALI_MODE Error, cali_mode = %d\n",
					__PRETTY_FUNCTION__, cali_mode);
				goto SENDAKDBMES_ERROR;
			}
			*lParam = cali_mode;
			break;
		case BMA_GET_UPDATE_USER_CALI_DATA:
			if (ioctl(hDevice, BMA_IOCTL_GET_UPDATE_USER_CALI_DATA, &cali_update) < 0) {
				/*LOGE("%s: BMA_GET_UPDATE_USER_CALI_DATA Error, cali_update = %d\n",
					__PRETTY_FUNCTION__, cali_update);*/
				return 0;
				//goto SENDAKDBMES_ERROR;
			}
			*lParam = cali_update;
			break;
		case BMA_SET_UPDATE_USER_CALI_DATA:
			if (ioctl(hDevice, BMA_IOCTL_SET_UPDATE_USER_CALI_DATA, &hParam) < 0) {
				LOGE("ERROR: BMA_IOCTL_SET_UPDATE_USER_CALI_DATA\n");
				goto SENDAKDBMES_ERROR;
			}
			break;
		default:
			LOGE("Sent message is not supported by SendAKDBMessage.");
			return 0;
	}
	return 1;

SENDAKDBMES_ERROR:
	LOGE("DeviceIOControl %d failed. \n", message);
	return 0;
}
