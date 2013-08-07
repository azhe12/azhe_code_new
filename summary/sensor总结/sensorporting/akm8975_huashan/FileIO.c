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
#include <sys/stat.h>
#include "FileIO.h"
#include "ak8975_log.h"


/* Load parameters from file named with #SETTING_FILE_NAME.
 * This function reads data from a beginning of the file line by line, and
 * check parameter name sequentially. In otherword, this function depends on
 * the order of eache parameter described in the file.
 *
 * @return When function fails, the return value is 0. In that case, it can not
 * be known that which parameter has failed. So it is recommended that fill
 * each parameters with initial value.
 */
int16 LoadParameters(
			AK8975PRMS	*prms	/*< A pointer to AK8975PRMS structure. Loaded
						  < parameter is stored to the member of this
						  < structure.*/
)
{
	int16 tmp, ret;
	FILE *fp;

	/*Open setting file for read.*/
	fp = fopen(SETTING_FILE_NAME, "r");
	if (fp == NULL)
		return 0;

	ret = 1;
	/*Set loaded data to HDST, HO, HREF, THRE*/
	/*Form 0*/
	tmp = 0;
	ret = ret && LoadInt16(fp, "HSUC_HDST_SLIDER_OPEN", &tmp);
	prms->HSUC_HDST[0] = (AKSC_HDST)tmp;
	ret = ret && LoadInt16vec(fp, "HSUC_HO_SLIDER_OPEN", &prms->HSUC_HO[0]);
	ret = ret && LoadInt16vec(fp, "HFLUCV_HREF_SLIDER_OPEN", &prms->HFLUCV_HREF[0]);

	/*Form 1*/
	tmp = 0;
	ret = ret && LoadInt16(fp, "HSUC_HDST_SLIDER_CLOSE", &tmp);
	prms->HSUC_HDST[1] = (AKSC_HDST)tmp;
	ret = ret && LoadInt16vec(fp, "HSUC_HO_SLIDER_CLOSE", &prms->HSUC_HO[1]);
	ret = ret && LoadInt16vec(fp, "HFLUCV_HREF_SLIDER_CLOSE", &prms->HFLUCV_HREF[1]);

	fclose(fp);
	return ret;
}


/* Load \c int16 type value from file. The name of parameter is specified with
 * \a lpKeyName. If the name matches the beginning of read line, the string
 * after #DELIMITER will converted to \c int16 type value.
 * When this function fails, the \a *val is not updated.
 */
int16 LoadInt16(
	FILE		*fp,        /* < Pointer to \c FILE structure.*/
	const char	*lpKeyName, /* < The name of parameter.*/
	int16		*val        /* < Pointer to \c int16 type value.*/
)
{
	int tmp;
	char buf_read[KEYNAME_SIZE] = {0};
	char del[KEYNAME_SIZE] = {0};

	/* NOTE: The format should be changed according to the value of KEYNAME_SIZE.*/
	if (fscanf(fp, "%63s %63s %d", buf_read, del, &tmp) != 3) {
		return 0;
	} else {
		if (strcmp(buf_read, lpKeyName) != 0) {
			return 0;
		} else {
			*val = (int16)tmp;
		}
	}

	return 1;
}


/* Load \c int16vec type value from file.
 * @return When function fails, the return value is 0. In that case, it can not
 * be known that which element has failed. So it is recommended that fill each
 * parameters with initial value.
 */
int16 LoadInt16vec(
	FILE		*fp,
	const	char	*lpKeyName,
	int16vec	* vec
)
{
	char keyName[KEYNAME_SIZE];
	int16 ret = 1;

	sprintf(keyName, "%s.x", lpKeyName);
	ret = ret && LoadInt16(fp, keyName, &vec->u.x);

	sprintf(keyName, "%s.y", lpKeyName);
	ret = ret && LoadInt16(fp, keyName, &vec->u.y);

	sprintf(keyName, "%s.z", lpKeyName);
	ret = ret && LoadInt16(fp, keyName, &vec->u.z);

	return ret;
}


/* Save parameter to file named with #SETTING_FILE_NAME.
 * This function saves variables when the offsets of magnetic sensor estimated
 * successfully.
 * @return When function fails, the return value is 0. When this function
 * success, the return value is 1.
 */
int16 SaveParameters(
		AK8975PRMS *prms /*[in] Pointer to parameters of AK8975*/
)
{
	FILE *fp;

	AKM_LOGD("%s: prms->m_iStatusCurrent = %d\n",
		__PRETTY_FUNCTION__, prms->m_iStatusCurrent);

	prms->HSUC_HDST[prms->m_iStatusCurrent]  = prms->m_hdst;
	prms->HSUC_HO[prms->m_iStatusCurrent]  = prms->m_ho;
	prms->HFLUCV_HREF[prms->m_iStatusCurrent] = prms->m_hflucv.href;

	AKM_LOGD("%s: Ready to save the following data!\n", __PRETTY_FUNCTION__);
	AKM_LOGD("HSUC_HDST = 0x%x\n",  prms->m_hdst);
	AKM_LOGD("HSUC_HO(x, y, z) = (0x%x, 0x%x, 0x%x)\n",
		prms->m_ho.u.x, prms->m_ho.u.y, prms->m_ho.u.z);

	AKM_LOGD("prms->HSUC_HDST[0] = 0x%x\n", prms->HSUC_HDST[0]);
	AKM_LOGD("prms->HSUC_HO[0](x, y, z) = (0x%x, 0x%x, 0x%x)\n",
		prms->HSUC_HO[0].u.x, prms->HSUC_HO[0].u.y, prms->HSUC_HO[0].u.z);

	AKM_LOGD("prms->HSUC_HDST[1] = 0x%x\n", prms->HSUC_HDST[1]);
	AKM_LOGD("prms->HSUC_HO[1](x, y, z) = (0x%x, 0x%x, 0x%x)\n",
		prms->HSUC_HO[1].u.x, prms->HSUC_HO[1].u.y, prms->HSUC_HO[1].u.z);

	/*Open setting file with write permission.*/
	fp = fopen(SETTING_FILE_NAME, "w");
	if (fp == NULL)
		return 0;

	/*SLIDER OPEN*/
	SaveInt16(fp, "HSUC_HDST_SLIDER_OPEN", (int16)prms->HSUC_HDST[0]);
	SaveInt16vec(fp, "HSUC_HO_SLIDER_OPEN", &prms->HSUC_HO[0]);
	SaveInt16vec(fp, "HFLUCV_HREF_SLIDER_OPEN", &prms->HFLUCV_HREF[0]);

	/*SLIDER CLOSE*/
	SaveInt16(fp, "HSUC_HDST_SLIDER_CLOSE", (int16)prms->HSUC_HDST[1]);
	SaveInt16vec(fp, "HSUC_HO_SLIDER_CLOSE", &prms->HSUC_HO[1]);
	SaveInt16vec(fp, "HFLUCV_HREF_SLIDER_CLOSE", &prms->HFLUCV_HREF[1]);

	chmod(SETTING_FILE_NAME, S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP);

	fclose(fp);
	return 1;
}


/* Save \c int16 type value to file. The name of parameter is specified with
 * \a lpKeyName.
 */
void SaveInt16(
	FILE		*fp,		/*< Pointer to \c FILE structure.*/
	const	char	*lpKeyName,	/*< The name of paraemter.*/
	const	int16	val		/*< Pointer to \c int16 type value.*/
)
{
	fprintf(fp, "%s %s %d\n", lpKeyName, DELIMITER, val);
}


/* Save \c int16vec type value to file.*/
void SaveInt16vec(
	FILE			*fp,		/*< Pointer to \c FILE structure.*/
	const	char		*lpKeyName,	/*< The name of paraemter.*/
	const	int16vec	* vec		/*< Pointer to \c int16 type value.*/
)
{
	fprintf(fp, "%s.x %s %d\n", lpKeyName, DELIMITER, vec->u.x);
	fprintf(fp, "%s.y %s %d\n", lpKeyName, DELIMITER, vec->u.y);
	fprintf(fp, "%s.z %s %d\n", lpKeyName, DELIMITER, vec->u.z);
}
