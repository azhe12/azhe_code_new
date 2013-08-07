/*************************************************************************
 *
 *  $Workfile: akmd_slider $
 *
 *  $Author: Andy Chuang $
 *  $Department: SSD $
 *  $Date: 2009/12/29 20:13 $
 *  $Version: 0.0.1 $
 *
 *  Developped by HTC Corporation
 *  Copyright (C) 2009 HTC Corporation, All rights reserved
 *
 *************************************************************************/

#include <fcntl.h>
#include <pthread.h>
#include <sys/poll.h>
#include <utils/Log.h>
#include <errno.h>
#include <linux/input.h>
#include <dirent.h>
#include "akmd_slider.h"
#include "ak8975_log.h"

pthread_mutex_t	m_hSMutex;
static int	g_fd;

void ChangHOffHdac(int16 status, AK8975PRMS *prms)
{
	AKM_LOGD("ChangHOffHdac is called!\n");

	if (0 <= status && status < SLIDER_STATUS_NUM)
		prms->m_iStatusNew = status;
}

void *SliderDetectThread(void *pParam)
{
	fd_set rfds;
	struct timeval tv;
	struct input_event iev;
	unsigned int ret;

	AK8975PRMS *prms = (AK8975PRMS *)pParam;

	while (!prms->m_SlideStop) {
		FD_ZERO(&rfds);
		FD_SET(g_fd, &rfds);

		/*Set timeout as 1 seconds, need to re-consider the value*/
		tv.tv_sec = 0;
		tv.tv_usec = 500000;

		select(g_fd + 1, &rfds, NULL, NULL, &tv);

		if (prms->m_SlideStop)
			goto SDTHREAD_END;

		if (FD_ISSET(g_fd, &rfds)) {
			ret = read(g_fd, &iev, sizeof(iev));
			LOGV("%s: Read done\n", __PRETTY_FUNCTION__);
			if (ret < sizeof(iev)) {
				LOGE("Could not get event\n");
				goto SDTHREAD_END;
			} else if (ret == sizeof(iev)) {
				LOGV("Got event device = %d, type = %d, value = %d \n", iev.type, iev.code, iev.value);
				if (iev.type == EV_SW && iev.code == 0 && !prms->m_SlideStop) {
					LOGD("sliding keypad status changed: %d (0: open, 1: close)\n", iev.value);
					ChangHOffHdac(iev.value, prms);
				}
			}
		}
	}
SDTHREAD_END:
	AKM_LOGD("SliderDetectThread exit \n");
	close(g_fd);
	pthread_exit((void *)NULL);
	return NULL;
}

/* scan all input drivers and look for "trout-keypad" */
int scan_slider_device()
{
	int fd = -1;
	const char *dirname = "/dev/input";
	char devname[PATH_MAX];
	char *filename;
	DIR *dir;
	struct dirent *de;

	LOGV("scan_slider_device called!\n");

	dir = opendir(dirname);
	if (dir == NULL)
		return -1;

	strcpy(devname, dirname);
	filename = devname + strlen(devname);
	*filename++ = '/';
	while ((de = readdir(dir))) {
		if (de->d_name[0] == '.' &&
			(de->d_name[1] == '\0' ||
			(de->d_name[1] == '.' && de->d_name[2] == '\0'))
		)
			continue;

		strcpy(filename, de->d_name);
		fd = open(devname, O_RDONLY);
		if (fd >= 0) {
			char name[80];
			if (ioctl(fd, EVIOCGNAME(sizeof(name) - 1), &name) < 1)
				name[0] = '\0';
			if (strstr(name, "-keypad")) {
				LOGV("Slider use %s (name=%s)\n", devname, name);
				break;
			}
			close(fd);
			fd = -1;
		}
	}
	LOGV("closedir\n");
	closedir(dir);
	return fd;
}

int open_slider_detect(AK8975PRMS *prms)
{
	int ret;

	prms->m_SlideStop = 0;

	AKM_LOGD("open_slider_detect is called!\n");

	g_fd = scan_slider_device();
	if (g_fd < 0) {
		LOGE("could not find slider input event \n");
		return -1;
	}

	ret = pthread_create(&prms->m_sThread, NULL, SliderDetectThread, (void *)prms);

	return ret;
}

int close_slider_detect(AK8975PRMS *prms)
{
	AKM_LOGD("close_slider_detect is called!\n");
	if (!prms->m_SlideStop)
		prms->m_SlideStop = 1;

	return 0;
}
