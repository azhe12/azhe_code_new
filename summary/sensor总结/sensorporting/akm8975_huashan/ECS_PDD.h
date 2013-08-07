/*------------------------------------------------------------------------------
 *
 *  Header:  ECS_PDD.h
 *
 *  Provides definitions for AK8975 module
 *
 *------------------------------------------------------------------------------*/
#ifndef AKSC_INC_ECSPDD_H
#define AKSC_INC_ECSPDD_H


#define INT16  signed short int		/*< 16-bit signed integer type.  */
#define UINT16 unsigned short int	/*< 16-bit unsigned integer type.*/

#define AKD_SUCCESS			1	/*< The return value. It represents success.           */
#define AKD_ERROR			0	/*< The return value. It represents error.             */
#define AKD_FAIL			-1	/*< The return value. It represents the function fails.*/


#ifndef AK8975_REGISTER_MAP_DEFINED
#define AK8975_REGISTER_MAP_DEFINED
/*! \name AK8975 register address
\anchor AK8975_REG
Defines a register address of the AK8975.*/
/*@{*/
#define AK8975_REG_WIA		0x00
#define AK8975_REG_INFO		0x01
#define AK8975_REG_ST1		0x02
#define AK8975_REG_HXL		0x03
#define AK8975_REG_HXH		0x04
#define AK8975_REG_HYL		0x05
#define AK8975_REG_HYH		0x06
#define AK8975_REG_HZL		0x07
#define AK8975_REG_HZH		0x08
#define AK8975_REG_ST2		0x09
#define AK8975_REG_CNTL		0x0A
#define AK8975_REG_RSV		0x0B
#define AK8975_REG_ASTC		0x0C
#define AK8975_REG_TS1		0x0D
#define AK8975_REG_TS2		0x0E
#define AK8975_REG_I2CDIS	0x0F
/*@}*/

/*! \name AK8975 fuse-rom address
\anchor AK8975_FUSE
Defines a read-only address of the fuse ROM of the AK8975.*/
/*@{*/
#define AK8975_FUSE_ASAX	0x10
#define AK8975_FUSE_ASAY	0x11
#define AK8975_FUSE_ASAZ	0x12
/*@}*/

/*! \name AK8975 register value
\anchor AK8975_CNTL
Defines a value to be set in the Control Registers (\c CNTL) of AK8975. */
/*@{*/
#define AK8975_CNTL_SNG_MEASURE		0x01
#define	AK8975_CNTL_CONT_MEASURE	0x02
#define	AK8975_CNTL_TRIG_MEASURE	0x04
#define	AK8975_CNTL_SELF_TEST		0x08
#define	AK8975_CNTL_FUSE_ACCESS		0x0F
#define	AK8975_CNTL_POWER_DOWN		0x00
/*@}*/

#endif

#define RBUFF_SIZE_8975		8		/* Rx buffer size (must be same as AKSC_BDATA_SIZE)*/

#endif
