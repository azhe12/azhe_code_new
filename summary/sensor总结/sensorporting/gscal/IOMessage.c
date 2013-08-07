#include "IOMessage.h"

#include "gscal_log.h"
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
	int i, j, k;
	int kbuf;
	char rwbuf[5];
	short delay,buf[7];
	short chip_layout;

	// For safety
	memset(rwbuf, 0, sizeof(rwbuf));

	switch(message)
	{
		case BMA_GET_CHIP_LAYOUT:
			if (ioctl(hDevice, BMA_IOCTL_GET_CHIP_LAYOUT,
					&chip_layout) < 0)
				goto SENDAKDBMES_ERROR;
			*lParam = chip_layout;

			break;

		case BMA_INT_STATUS:
			if(ioctl(hDevice, BMA_IOCTL_INIT, NULL)< 0){
				goto SENDAKDBMES_ERROR;
			}
			break;

		case BMA_WRITE_REGISTER:
			// Write data
			rwbuf[0] = 2;
			rwbuf[1] = (char)hParam;
			rwbuf[2] = (char)*lParam;
			if(ioctl(hDevice, BMA_IOCTL_WRITE, rwbuf)< 0){
				goto SENDAKDBMES_ERROR;
			}
			break;

		case BMA_WRITE_CALI_VALUE:
			/* Write calibration data */
			kbuf = (hParam << 16) | (*lParam & 0xFFFF);
			if (ioctl(hDevice, BMA_IOCTL_WRITE_CALI_VALUE, &kbuf) < 0)
				goto SENDAKDBMES_ERROR;
			break;

		case BMA_READ_REGISTER:
			// Read data
			rwbuf[0] = 1;
			rwbuf[1] = (char)hParam;
			if(ioctl(hDevice, BMA_IOCTL_READ, rwbuf)< 0){
				goto SENDAKDBMES_ERROR;
			}
			*lParam = rwbuf[1];
			break;
		case BMA_READ_ACCELERATION:
			//Read x,y,z acceleration data
			if(ioctl(hDevice, BMA_IOCTL_READ_ACCELERATION, buf)< 0){
				goto SENDAKDBMES_ERROR;
			}
			for(i=0; i<3; i++){
				lParam[i] = buf[i];
			}
			break;
		case BMA_SET_MODE:
			if(ioctl(hDevice, BMA_IOCTL_SET_MODE, &hParam)< 0){
				LOGE("ERROR: SET MODE\n");
				goto SENDAKDBMES_ERROR;
			}
			break;
		default:
			return 0;
	}
	return 1;

SENDAKDBMES_ERROR:
	return 0;
}
