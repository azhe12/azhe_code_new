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

#include <sys/stat.h>
#include "AccSensorFunction.h"
#include "DispMessage.h"
#include "CustomerSpec.h"
#include "FileIO.h"

#include "IOMessage.h"
#include "ak8975_log.h"

#include <math.h>

extern int get_debug_flag(void);

//==========================================================================
//
//  FUNCTION:  SetDefaultPRMSAcc()
//
//  PURPOSE:   Initialize the parameter of accelerometer(float)
//
//  DESCRIPTION:
//
//==========================================================================
void SetDefaultPRMSAcc(
	ACCPRMS*		prms //(i/o)Pointer to parameters of AK8975
)
{
	// Set an acceleration measurement result.
	prms->AS[0] = 256.0f;//0.35555556f;
	prms->AS[1] = 256.0f;//0.35555556f;
	prms->AS[2] = 256.0f;//0.35555556f;
	prms->AO[0] = 0.0f;
	prms->AO[1] = 0.0f;
	prms->AO[2] = 0.0f;
}

//==========================================================================
//
//  FUNCTION: GetAccVec
//
//  PURPOSE:
//
//  DESCRIPTION:
//
//==========================================================================
void GetAccVec(
	AK8975PRMS*	prms,		// (i)Pointer to parameters of AK8975
	ACCPRMS*	accprms,	// (i/o)Pointer to ACC parameters of AK8975
	float*		avecf
)
{
	int	i;
	int16	acc[3];

	//AKD_GetAccelerationData(acc);
	if(!SendIOMessage(prms->m_aDevice, BMA_READ_ACCELERATION, NULL, acc)){
		AKM_LOGD("GetAccVec: ACCELERATION ERROR\n");
	}

	// Debug
	LOGV("%s: acc(x, y, z) = (%d, %d, %d)\n",
		__PRETTY_FUNCTION__, acc[0], acc[1], acc[2]);

	acc[0] = acc[0] + accprms->offset[0];
	acc[1] = acc[1] + accprms->offset[1];
	acc[2] = acc[2] + accprms->offset[2];

	// Debug, After calibration
	LOGV("%s: Calibrated acc(x, y, z) = (%d, %d, %d)\n",
		__PRETTY_FUNCTION__, acc[0], acc[1], acc[2]);

	// Convert format
	for(i=0; i<3; i++){
		LOGV("%s: acc[%d] = %d, accprms->AO[%d] = %f, "
			"accprms->AS[%d] = %f)\n",
			__PRETTY_FUNCTION__, i, acc[i],
			i, accprms->AO[i], i, accprms->AS[i]);
		avecf[i] = (acc[i] - accprms->AO[i]) / accprms->AS[i];
	}

	// Debug
	LOGV("%s: avecf(x, y, z) = (%f, %f, %f)\n",
		__PRETTY_FUNCTION__, avecf[0], avecf[1], avecf[2]);

}

//==========================================================================
//
//  FUNCTION:  ACalibration()
//
//  PURPOSE:
//
//  DESCRIPTION:
//
//==========================================================================
int ACalibration(
			ACCPRMS*	prms	// (i/o)Pointer to parameters of AK8975
)
{
	int	i, j;
	int16	acc[3];
	float	vec[3][3];
	float	tmpASX1, tmpASX2;
	float	tmpASY1, tmpASY2;

	memset(acc, 0, sizeof(int16)*3);

	for(i=0; i<3; i++) {
		// Show 1st-3rd message and wait for user input.
		switch(i){
			case 0:
				DispMessage(MSG_LEVEL0, "[01] Hold the sensor box horizontally.\n");
				break;
			case 1:
				DispMessage(MSG_LEVEL0, "[02] Tilt +90 degrees in pitch direction.\n");
				break;
			case 2:
				DispMessage(MSG_LEVEL0, "[03] Tilt +90 degrees in roll direction.\n");
				break;
			default:
				DispMessage(MSG_LEVEL0, "Unknown error.\n");
		}
		Prmpt_Kbhit();

		// Acquire 3rd data.
		vec[i][0] = 0.0f;
		vec[i][1] = 0.0f;
		vec[i][2] = 0.0f;
		for(j=0; j<ACALIB_MEASURE; j++) {
			// Acquire the latest acceleration sensor measurement data.
			//AKD_GetAccelerationData(acc);

			vec[i][0] += acc[0];
			vec[i][1] += acc[1];
			vec[i][2] += acc[2];
		}
		vec[i][0] = vec[i][0] / (float)ACALIB_MEASURE;
		vec[i][1] = vec[i][1] / (float)ACALIB_MEASURE;
		vec[i][2] = vec[i][2] / (float)ACALIB_MEASURE;
	}

	// Calculate offset and sense.
	prms->AO[0] = vec[0][0];
	prms->AO[1] = vec[0][1];
	prms->AO[2] = vec[1][2];
	prms->AS[2] = fabs(vec[0][2] - prms->AO[2]);
	tmpASX1 = fabs(vec[1][0] - prms->AO[0]);
	tmpASX2 = fabs(vec[2][0] - prms->AO[0]);
	tmpASY1 = fabs(vec[1][1] - prms->AO[1]);
	tmpASY2 = fabs(vec[2][1] - prms->AO[1]);

	if(tmpASX1 >= tmpASX2) {
		prms->AS[0] = tmpASX1;
		prms->AS[1] = tmpASY2;
	}
	else {
		prms->AS[0] = tmpASX2;
		prms->AS[1] = tmpASY1;
	}

	// Show final message
	DispMessage(MSG_LEVEL0, "Calibration is finished.\n\n");
	DispMessage(MSG_LEVEL0, "%-10s","AOFFSET:");
	DispMessage(MSG_LEVEL0, "x=%6.2f, y=%6.2f, z=%6.2f\n", prms->AO[0], prms->AO[1], prms->AO[2]);
	DispMessage(MSG_LEVEL0, "%-10s","ASENSE:");
	DispMessage(MSG_LEVEL0, "x=%6.2f, y=%6.2f, z=%6.2f\n", prms->AS[0], prms->AS[1], prms->AS[2]);
	DispMessage(MSG_LEVEL0, "\n");

	Prmpt_Kbhit();

	return 1;
}

//==========================================================================
//
//  FUNCTION: LoadParametersAcc
//
//  PURPOSE:  Load data from file named "AccPrmsF.ini"
//
//  DESCRIPTION:
//
//==========================================================================
int LoadParametersAcc(
		ACCPRMS*	prms //(i/o)Pointer to parameters of AK8975
)
{
	int16 ret;
	FILE* fp;

	//Open setting file for read.
	if((fp = fopen(SETTING_ACC_FILE_NAME, "r")) == NULL) {
		return 0;
	}

	ret = 1;

	//Load an acceleration measurement result.
	ret = ret && LoadFvec(fp, "AS", prms->AS);
	ret = ret && LoadFvec(fp, "AO", prms->AO);

	fclose(fp);
	return ret;
}

//==========================================================================
//
//  FUNCTION: LoadFloat
//
//  PURPOSE:  Load float data
//
//  DESCRIPTION:
//
//==========================================================================
int LoadFloat(
			FILE*		fp,
	const	char*		lpKeyName,
			float*		val
)
{
	float tmp;
	char buf_read[KEYNAME_SIZE] = {0};
	char del[KEYNAME_SIZE] = {0};

	if(fscanf(fp, "%s %s %f", buf_read, del, &tmp) != 3) {
		if(remove("/data/misc/AccPrmsF.ini"))
			LOGE("Remove %s Error", "/data/misc/AccPrmsF.ini");
		LOGD("AK8975: remove AccPrmsF.ini OK!.\n");
		return 0;
	}
	else {
		if(strcmp(buf_read, lpKeyName) != 0) {
			return 0;
		}
		else {
			*val = tmp;
		}
	}

	return 1;
}

//==========================================================================
//
//  FUNCTION:  LoadFvec
//
//  PURPOSE:  Load fvec data
//
//  DESCRIPTION:
//
//==========================================================================
int LoadFvec(
			FILE*		fp,
	const	char*		lpKeyName,
			float		vec[]
)
{
	char keyName[KEYNAME_SIZE];

	sprintf(keyName, "%s.x", lpKeyName);
	if(LoadFloat(fp, keyName, &vec[0]) == 0) {
		return 0;
	}

	sprintf(keyName, "%s.y", lpKeyName);
	if(LoadFloat(fp, keyName, &vec[1]) == 0) {
		return 0;
	}

	sprintf(keyName, "%s.z", lpKeyName);
	if(LoadFloat(fp, keyName, &vec[2]) == 0) {
		return 0;
	}

	return 1;
}

//==========================================================================
//
//  FUNCTION: SaveParametersAcc
//
//  PURPOSE:  Save AK8975 Parameters at the file named "AccPrmsF.ini"
//
//  DESCRIPTION:
//
//==========================================================================
int SaveParametersAcc(
	ACCPRMS*  prms //(i)Pointer to parameters of AK8975
)
{
	FILE* fp;

	//Open setting file for write.
	if((fp = fopen(SETTING_ACC_FILE_NAME, "w")) == NULL) {
		return 0;
	}

	//Save an acceleration measurement result.
	SaveFvec(fp, "AS", prms->AS);
	SaveFvec(fp, "AO", prms->AO);

	chmod(SETTING_ACC_FILE_NAME, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);

	fclose(fp);
	return 1;
}

//==========================================================================
//
//  FUNCTION: SaveFloat
//
//  PURPOSE:  Save float data
//
//  DESCRIPTION:
//
//==========================================================================
void SaveFvec(
			FILE*		fp,
	const	char*		lpKeyName,
	const	float		vec[]
)
{
	fprintf(fp, "%s.x %s %f\n", lpKeyName, DELIMITER, vec[0]);
	fprintf(fp, "%s.y %s %f\n", lpKeyName, DELIMITER, vec[1]);
	fprintf(fp, "%s.z %s %f\n", lpKeyName, DELIMITER, vec[2]);
}

//==========================================================================
//
//  FUNCTION:  InitAccBuffer()
//
//  PURPOSE:
//      Initializes buffers.
//
//
//  DESCRIPTION:
//
//==========================================================================
void InitAccBuffer(
	INT16 adata[][3]
)
{
	int	i, j;

	for(i = 0; i < CSPEC_ADATA_SIZE; i++){
		for(j = 0; j < 3; j++){
			adata[i][j] = ACC_INIT_VALUE;
		}
	}
}
