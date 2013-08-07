/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
Copyright (c) 2008 High Tech Computer Corporation
Module Name:
    bma150_MFG_calibration  - G-sensor calibration tool
Abstract:
Auther:
    viral wang 	Dec, 2008
Notes:
------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <utils/Log.h>
#include <fcntl.h>
#include <cutils/properties.h>
#include "FileIO.h"
#include "IOMessage.h"
#include "gscal_log.h"
#include "../../lib/headers/partition.h"

#define DEBUG
#define REAL_WRITE

#define CALIBRATE_MAX_COUNT	10

/* mode settings */
#define BMA_MODE_NORMAL		0
#define BMA_MODE_SLEEP		1

#define GSR_DEVICE_NAME	  "/dev/bma150"
#define RESULT_FILE       "/data/misc/gscal_result.txt"
#define VERSION_INFO      "Calibration MFG SW 0.6"
#define AK8973PRMS        "/data/misc/AK8973Prms.txt"
#define AK8975PRMS        "/data/misc/AccPrmsF.ini"

#define TEST_TIMES              (20)
#define MAX_VARIATION           (15)

#define PRE_CHECK_X		51
#define PRE_CHECK_Y		51
#define PRE_CHECK_Z		65

int OFFSET = 0x3410;

int partition_status = 1;

int readMfgOffsetInt(int offset)
{
	PARTITION pn;

	int ret = -2, *ptr;

	if (partition_open(&pn, "mfg") < 0)
	{
		partition_status = -1;//open mfg failed
		printf("cannot open MFG partition\n");
		goto end;
	}

	if (partition_read(&pn, offset, sizeof(int), &ret) < 0)
	{
		partition_status = -2;//read mfg failed
		printf("cannot read MFG partition\n");
		goto end;
	}

end:;
	partition_close(&pn);
	return ret;
}

int writeMfgOffsetInt(int offset, int value)
{
	PARTITION pn;

	int ret = -1, *ptr;

	if (partition_open(&pn, "mfg") < 0)
		goto end;

	if (partition_write(&pn, offset, sizeof(int), &value) < 0)
		goto end;

	ret = 0;

end:;
	partition_close(&pn);
	return ret;
}

int check_nand_info()
{
	char *NANDINFO = "/sys/module/msm_nand/parameters/info";
	FILE *pFile;
	long lSize;
	char *buffer, *pos_start, *pos_end;
	char size[8], block_c[8], page_c[8];
	size_t result;
	int page = 0 , size_int, block_int, page_int;

	/*LOGD("check_nand_info+\n");*/
	pFile = fopen(NANDINFO , "rb");
	if (pFile == NULL) {
		fputs("File error", stderr);
		exit(1);
	}

	/* obtain file size:*/
	fseek(pFile, 0, SEEK_END);
	lSize = ftell(pFile);
	rewind(pFile);

	/* allocate memory to contain the whole file:*/
	buffer = (char *) malloc(sizeof(char)*lSize);
	if (buffer == NULL) {
		fputs("Memory error", stderr);
		exit(2);
	}

	/* copy the file into the buffer:*/
	result = fread(buffer, 1, lSize, pFile);
	/*LOGD("result:[%d], lSize:[%d]\n", result, lSize);*/

	/* the whole file is now loaded in the memory buffer. */
	/*LOGD("buffer:[%s]\n", buffer);*/
	/*========== decision of 2k/4k ==============*/
	memset(size, 0, sizeof(size));
	memset(block_c, 0, sizeof(block_c));
	memset(page_c, 0, sizeof(page_c));

	pos_start = strstr(buffer, "size");
	pos_start = strstr(pos_start, "=") + 1;
	pos_end = strstr(pos_start, "\n") - 3;
	strncpy(size, pos_start, pos_end-pos_start);
	LOGD("nand_size:[%s]\n", size);
	size_int = atoi(size);

	pos_start = strstr(buffer, "block");
	pos_start = strstr(pos_start, "=") + 1;
	pos_end = strstr(pos_start, "\n");
	strncpy(block_c, pos_start, pos_end - pos_start);
	LOGD("block count:[%s]\n", block_c);
	block_int = atoi(block_c);

	pos_start = strstr(buffer, "page");
	pos_start = strstr(pos_start, "=") + 1;
	pos_end = strstr(pos_start, "\n");
	strncpy(page_c, pos_start, pos_end-pos_start);
	LOGD("page count:[%s]\n", page_c);
	page_int = atoi(page_c);
	/*===========================================*/
	page = size_int * 1024 / block_int / page_int;

	/* terminate */
	fclose(pFile);
	free(buffer);

	return page;
}

void check_pagesize()
{
	char buf [PROPERTY_VALUE_MAX];
	int page_size;

	memset (buf, 0, sizeof (buf));
	property_get ("ro.pagesize", buf, "0");
	if (buf[0] == '2')
	{
		LOGD("\nUsing ro.pagesize 2k. OFFSET = 0x3410.\n");
		OFFSET = 0x3410;
	}
	else if (buf[0] == '4')
	{
		LOGD("\nUsing ro.pagesize 4k. OFFSET = 0x6410.\n");
		OFFSET = 0x6410;
	}
	else
	{
		printf("Can't get [ro.pagesize]:%s\n",buf);

		memset (buf, 0, sizeof (buf));
		property_get ("ro.emmc", buf, "0");

		if (buf [0] == '1')
		{
			LOGD("\nUsing emmc 4k. OFFSET = 0x6410.\n");
			OFFSET = 0x6410;
		}
		else if (buf [0] == '0')
		{
			page_size = check_nand_info();
			if (page_size == 2)
			{
				LOGD("\nUsing nand 2k. OFFSET = 0x3410.\n");
				OFFSET = 0x3410;
			}
			else if (page_size == 4)
			{
				LOGD("\nUsing nand 4k. OFFSET = 0x6410.\n");
				OFFSET = 0x6410;
			}
		}
		else
		{
			LOGD("Can't get [ro.emmc]:%s\n",buf);
		}
	}
}

void write_kvalue(int m_aDevice, int value)
{
	LOGD("%s: value = 0x%x, (value >> 16) & 0xFFFF = 0x%x\n",
		__PRETTY_FUNCTION__, value, (value >> 16) & 0xFFFF);
	if (!SendIOMessage(m_aDevice, BMA_WRITE_CALI_VALUE, (value >> 16) & 0xFFFF, &value)) {
		LOGE("write_kvalue, BMA_WRITE_CALI_VALUE ERROR");
		return 37;
	}

	LOGD("write gs_kvalue done\n");
}

int StoreOffsetXYZtoResultFile(int fd, int value)
{
	char string[256];
	signed char offset_x;
	signed char offset_y;
	signed char offset_z;

	offset_x = value >> 16 & 0xFF;
	offset_y = value >>  8 & 0xFF;
	offset_z = value       & 0xFF;

	//write to bma_result.txt
	sprintf(string, "offset_x = %d\n", offset_x);
	LOGD("%s", string);
	write(fd, string, strlen(string));

	sprintf(string, "offset_y = %d\n", offset_y);
	LOGD("%s", string);
	write(fd, string, strlen(string));

	sprintf(string, "offset_z = %d\n", offset_z);
	LOGD("%s", string);
	write(fd, string, strlen(string));

	return 0;
}

/** verifies the accerleration values to be good enough for
    calibration calculations
  \param min takes the minimum measured value
  \param max takes the maximum measured value
  \return 1: min,max values are in range, 0: not in range
*/
int check_variation(int16vec min, int16vec max)
{
	short dx, dy, dz;
	int veri_ok = 1;

	dx =  max.u.x - min.u.x;    /* calc delta max-min */
	dy =  max.u.y - min.u.y;
	dz =  max.u.z - min.u.z;

	LOGV("min(x, y, z) = (%d, %d, %d)\n", min.u.x, min.u.y, min.u.z);
	LOGV("max(x, y, z) = (%d, %d, %d)\n", max.u.x, max.u.y, max.u.z);
	LOGD("d(x, y, z) = (%d, %d, %d)\n", dx, dy, dz);

	if (dx > MAX_VARIATION || dx < -MAX_VARIATION)
		veri_ok = 0;

	if (dy > MAX_VARIATION || dy < -MAX_VARIATION)
		veri_ok = 0;

	if (dz > MAX_VARIATION || dz < -MAX_VARIATION)
		veri_ok = 0;

	return veri_ok;
}

int offset_calc(int16 accel, int pivot)
{
	int offset = 0;

	offset = accel - pivot;

	return offset;
}

int pre_check_range(int16 x, int16 y, int16 z, short  chip_layout)
{
	LOGD("x = %d, y = %d, z = %d, chip_layout = %d\n", x, y, z, chip_layout);

	if (chip_layout) {
		if (x < -PRE_CHECK_X || x > PRE_CHECK_X || y < -PRE_CHECK_Y || y > PRE_CHECK_Y ||
				z < 256 - PRE_CHECK_Z || z > 256 + PRE_CHECK_Z) {
			LOGD("x < %d || x > %d || y < %d || y > %d || z < %d || z > %d\n",
				-PRE_CHECK_X, PRE_CHECK_X, -PRE_CHECK_Y, PRE_CHECK_Y,
				256 - PRE_CHECK_Z, 256 + PRE_CHECK_Z);
			return -1;
		}
	} else {
		if (x < -PRE_CHECK_X || x > PRE_CHECK_X || y < -PRE_CHECK_Y || y > PRE_CHECK_Y ||
				z < -256 - PRE_CHECK_Z || z > -256 + PRE_CHECK_Z) {
			LOGD("x < %d || x > %d || y < %d || y > %d || z < %d || z > %d\n",
				-PRE_CHECK_X, PRE_CHECK_X, -PRE_CHECK_Y, PRE_CHECK_Y,
				-256 - PRE_CHECK_Z, -256 + PRE_CHECK_Z);
			return -1;
		}
	}
	return 0;
}

int main(int argc, char **argv)
{
	int16vec tmpA, Aoff, min, max;
	int m_aDevice, retry_times=1, fd;
	int16 i2cData[7];
	char	string[256];
	int     i;
	int     check_veri_ok = 0;
	int16 offset_x = 0, offset_y = 0, offset_z = 0;
	char   ver[64] = "";
	short  chip_layout = -1;
	int ret = 0;
	int value;

	if (remove(AK8975PRMS))
		LOGD("%s does not exist.", AK8975PRMS);

	if (remove(AK8973PRMS))
		LOGD("%s does not exist", AK8973PRMS);

	strncat(ver, VERSION_INFO, 63);
	LOGD("%s\n", ver);

	// Open serial communication device.
	m_aDevice = open(GSR_DEVICE_NAME, 0666);
	while (m_aDevice < 0) {
		LOGE("Open m_aDevice ERROR, m_aDevice= %d\n",m_aDevice);
		return 1;
	}
	LOGV("m_aDevice: %d\n", m_aDevice);

	/* Get G-Sensor chip layout */
	if (!SendIOMessage(m_aDevice,
			BMA_GET_CHIP_LAYOUT, NULL, &chip_layout))
		LOGE("layouts retrieve error!!");
	LOGD("%s: chip_layout = %d\n",
		__PRETTY_FUNCTION__, chip_layout);

	// Create a file to save result
	fd = open(RESULT_FILE, O_CREAT | O_RDWR | O_TRUNC, 0666);
	if (fd == -1) {
		LOGE("bmafct: create /data/misc/bma_result.txt fail \n");
		return 2;
	}

	/* Unexpected values */
	if (chip_layout != 0 && chip_layout != 1) {
		/* show result */
		sprintf(string, "Unknown G-Sensor chip layout!!\n");
		LOGE("%s", string);
		write(fd, string, strlen(string));
		return 0;
	}

	check_pagesize();

	if (!SendIOMessage(m_aDevice, BMA_SET_MODE, BMA_MODE_NORMAL, NULL))
		LOGE("enable BMA150 fail!!\n");
	else
		LOGV("enable BMA150 successful!!\n");

	/* set soft_reset */
	if (!SendIOMessage(m_aDevice, BMA_READ_REGISTER, 0x0a, &i2cData[0])) {
		LOGE("set soft_reset: I2C read from bma150 reg 0x0a ERROR");
		return 20;
	}
	i2cData[0] = (i2cData[0] & 0xfd) | 0x02;
	if (!SendIOMessage(m_aDevice, BMA_WRITE_REGISTER, 0x0a, &i2cData[0])) {
		LOGE("set soft_reset: I2C write to bma150 reg 0x0a ERROR");
		return 21;
	}
	usleep(1000);

	/* Configure the bma150: 2G @25Hz */
	if (!SendIOMessage(m_aDevice, BMA_READ_REGISTER, 0x14, &i2cData[0])) {
		LOGE("Configure the bma150: I2C read from bma150 reg 0x14 ERROR");
		return 3;
	}

	i2cData[0] = i2cData[0]&0xe0;
	if (!SendIOMessage(m_aDevice, BMA_WRITE_REGISTER, 0x14, &i2cData[0])) {
		LOGE("Configure the bma150: I2C write to bma150 reg 0x14 ERROR");
		return 4;
	}

	/* Read the Acceleration data of axis x, y, z and compare with 0, 0 , +/- 1g*/
	Aoff.u.x = Aoff.u.y = Aoff.u.z = 0;
	max.u.x = -512; max.u.y = -512; max.u.z = -512;
	min.u.x = 512; min.u.y = 512; min.u.z = 512;
	retry_times = 0;

/*
___void get_acc_values ()
*/
	while (retry_times < TEST_TIMES) {
		usleep(50000);
		if (!SendIOMessage(m_aDevice, BMA_READ_ACCELERATION, NULL, tmpA.v)) {
			LOGE("READ ACCELERATION ERROR\n");
			return 5;
		}

		LOGV("x=%d\ty=%d\tz=%d\n",
			tmpA.u.x, tmpA.u.y, tmpA.u.z);

		/* Record the Max and Min values */
		if (tmpA.u.x > max.u.x)
			max.u.x = tmpA.u.x;
		if (tmpA.u.x < min.u.x)
			min.u.x = tmpA.u.x;

		if (tmpA.u.y > max.u.y)
			max.u.y = tmpA.u.y;
		if (tmpA.u.y < min.u.y)
			min.u.y = tmpA.u.y;

		if (tmpA.u.z > max.u.z)
			max.u.z = tmpA.u.z;
		if (tmpA.u.z < min.u.z)
			min.u.z = tmpA.u.z;

		Aoff.u.x += tmpA.u.x;
		Aoff.u.y += tmpA.u.y;
		Aoff.u.z += tmpA.u.z;
		retry_times++;
	}

/*
___void check_variate ()
*/
	/* Check the variation to confirm that the device is stable */
	check_veri_ok = check_variation(min, max);
	if (!check_veri_ok) {
		LOGE("Please keep the device STABLE on the platform\n");
		sprintf(string, "Please keep the device "
			"STABLE on the platform\n");
		write(fd, string, strlen(string));
		return 0;
	}
	LOGV("Check variation OK!\n");

	LOGD("Aoff.u.x = %d\n", Aoff.u.x);
	LOGD("Aoff.u.y = %d\n", Aoff.u.y);
	LOGD("Aoff.u.z = %d\n", Aoff.u.z);

	LOGD("(Aoff.u.x / TEST_TIMES) = %d\n", (Aoff.u.x / TEST_TIMES));
	LOGD("(Aoff.u.y / TEST_TIMES) = %d\n", (Aoff.u.y / TEST_TIMES));
	LOGD("(Aoff.u.z / TEST_TIMES) = %d\n", (Aoff.u.z / TEST_TIMES));

	if (Aoff.u.x == 0 && Aoff.u.y == 0 && Aoff.u.z == 0) {
		/* show result */
		sprintf(string, "Reading data all ZERO, something wrong!!\nNo calibration is done!!\n");
		LOGD("%s", string);
		write(fd, string, strlen(string));

		return 0;
	}

	ret = pre_check_range(Aoff.u.x / TEST_TIMES, Aoff.u.y / TEST_TIMES, Aoff.u.z / TEST_TIMES, chip_layout);
	if (ret) {
		/* show result */
		sprintf(string, "Data out of pre-check range!!\n");
		LOGD("%s", string);
		write(fd, string, strlen(string));
		return 0;
	}

/*
___void calculate_offset ()
*/
	Aoff.u.x = offset_calc(Aoff.u.x / TEST_TIMES, 0);

	Aoff.u.y = offset_calc(Aoff.u.y / TEST_TIMES, 0);

	if (chip_layout == 1)
		Aoff.u.z = offset_calc(Aoff.u.z / TEST_TIMES, 256);
	else
		Aoff.u.z = offset_calc(Aoff.u.z / TEST_TIMES, -256);

	if (Aoff.u.x == 0 && Aoff.u.y == 0 && Aoff.u.z == 0) {
		/* show result */
		sprintf(string, "No calibration is needed!!\n");
		LOGD("%s", string);
		write(fd, string, strlen(string));
		return 0;
	}

	/* show result */
	sprintf(string, "Offset drift setting: x=%d\ty=%d\tz=%d\n",
			Aoff.u.x, Aoff.u.y, Aoff.u.z);
	LOGD("%s", string);
	write(fd, string, strlen(string));

/*
___void set_offset_value ()
*/
	if (Aoff.u.x != 0) {
		offset_x = -Aoff.u.x;
		LOGD("offset_x = %d\n", offset_x);

		if (offset_x > 127)
			offset_x = 127;
		else if (offset_x < -128)
			offset_x = -128;
	}
	if (Aoff.u.y != 0) {
		offset_y = -Aoff.u.y;
		LOGD("offset_y = %d\n", offset_y);

		if (offset_y > 127)
			offset_y = 127;
		else if (offset_y < -128)
			offset_y = -128;
	}
	if (Aoff.u.z != 0) {
		offset_z = -Aoff.u.z;
		LOGD("offset_z = %d\n", offset_z);

		if (offset_z > 127)
			offset_z = 127;
		else if (offset_z < -128)
			offset_z = -128;
	}

/*
___void Verification ()
*/
	/*retry_times = 0;
	LOGD("After calibration: \n");
	while (retry_times < TEST_TIMES) {
		usleep(50000);
		if (!SendIOMessage(m_aDevice, BMA_READ_ACCELERATION, NULL, tmpA.v)) {
			LOGE("READ ACCELERATION ERROR\n");
			return 5;
		}
		LOGD("x=%d\ty=%d\tz=%d\n", tmpA.u.x, tmpA.u.y, tmpA.u.z);

		Aoff.u.x += tmpA.u.x;
		Aoff.u.y += tmpA.u.y;
		Aoff.u.z += tmpA.u.z;
		retry_times++;
	}

	Aoff.u.x /= TEST_TIMES;
	Aoff.u.y /= TEST_TIMES;
	Aoff.u.z /= TEST_TIMES;*/

/*
___void real_write ()
*/
#ifdef REAL_WRITE
	value = readMfgOffsetInt(OFFSET);
	//if (value != -2) {	/* 0xFFFFFFFF==-1, so don't use -1 */
	if (partition_status > 0) {
		LOGD("\nold value in flash: 0x%X 0x%X 0x%X 0x%X\n",
			value >> 24 & 0xFF, value >> 16 & 0xFF,
			value >> 8 & 0xFF, value & 0xFF);
	} else {
		/* show result */
		sprintf(string, "cannot open MFG partition, please use MFG hboot!\n");
		LOGD("%s", string);
		write(fd, string, strlen(string));
		return 0;
	}

	value = 0x67 << 24 | (offset_x & 0xFF) << 16 |
		(offset_y & 0xFF) << 8 | (offset_z & 0xFF);

	/* For settting the calibration data to 0 */
	/*value = 0x67 << 24;*/

	LOGD("Calibrated value: 0x%x\n", value);
	writeMfgOffsetInt(OFFSET, value);
	value = readMfgOffsetInt(OFFSET);
	if ((value & (0x67 << 24)) != (0x67 << 24)) {
		/* show result */
		sprintf(string, "write calibrated value failed!\n");
		LOGD("%s", string);
		write(fd, string, strlen(string));
		return 0;
	}
	write_kvalue(m_aDevice, value);
	LOGD("current value in flash: 0x%X 0x%X 0x%X 0x%X\n",
		value >> 24 & 0xFF, value >> 16 & 0xFF,
		value >> 8 & 0xFF, value & 0xFF);

	ret = StoreOffsetXYZtoResultFile(fd, value);
#endif

	//set soft_reset
	if(!SendIOMessage(m_aDevice, BMA_READ_REGISTER, 0x0a, &i2cData[0])){
		LOGE("set soft_reset: I2C read from bma150 reg 0x0a ERROR");
		return 20;
	}

	i2cData[0]=(i2cData[0]&0xfd)|0x02;
	if(!SendIOMessage(m_aDevice, BMA_WRITE_REGISTER, 0x0a, &i2cData[0])){
		LOGE("set soft_reset: I2C write to bma150 reg 0x0a ERROR");
		return 21;
	}
	usleep(1000);

	//Init BMA150 chip
	if(!SendIOMessage(m_aDevice, BMA_READ_REGISTER, 0x14, &i2cData[0])){
		LOGE("Init BMA150 chip: I2C read from bma150 reg 0x14 ERROR");
		return 22;
	}

	i2cData[0]=i2cData[0]&0xe0;
	if(!SendIOMessage(m_aDevice, BMA_WRITE_REGISTER, 0x14, &i2cData[0])){
		LOGE("Init BMA150 chip: I2C write to bma150 reg 0x14 ERROR");
		return 23;
	}

	if(!SendIOMessage(m_aDevice, BMA_READ_REGISTER, 0x15, &i2cData[0])){
		LOGE("Init BMA150 chip: I2C read from bma150 reg 0x15 ERROR");
		return 24;
	}

	i2cData[0]=(i2cData[0]&0xf7)|1<<3;
	if(!SendIOMessage(m_aDevice, BMA_WRITE_REGISTER, 0x15, &i2cData[0])){
		LOGE("Init BMA150 chip: I2C write to bma150 reg 0x15 ERROR");
		return 25;
	}

	return 0; /* Calibrtion Successed */
}
