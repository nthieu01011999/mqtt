#ifndef __RTS_IO_ERRNO_H__
#define __RTS_IO_ERRNO_H__

enum {
	ERR_IO_GPIO			= 0x03010000,
	ERR_IO_GPIO_OPENDEV_FAIL	= 0x03010001,
	ERR_IO_GPIO_READ_FAIL		= 0x03010002,
	ERR_IO_GPIO_WRITE_FAIL		= 0x03010003,
	ERR_IO_GPIO_NOMEM		= 0x03010004,
	ERR_IO_GPIO_INVAL		= 0x03010005,
	ERR_IO_GPIO_OPENISPCTL_FAIL	= 0x03010006,
	ERR_IO_GPIO_ISPCMD_FAIL		= 0x03010007,
	ERR_IO_GPIO_MAP_FAIL		= 0x03010008,
	ERR_IO_GPIO_NOT_SUPPORT		= 0x03010009,

	ERR_IO_I2C			= 0x03020000,
	ERR_IO_I2C_OPENDEV_FAIL		= 0x03020001,
	ERR_IO_I2C_NOMEM		= 0x03020002,
	ERR_IO_I2C_IOCTL_FAIL		= 0x03020003,

	ERR_IO_ADC			= 0x03030000,
	ERR_IO_ADC_OPENDEV_FAIL		= 0x03030001,
	ERR_IO_ADC_READ_FAIL		= 0x03030002,
	ERR_IO_ADC_NOT_MATCH		= 0x03030003,

	ERR_IO_PTZ			= 0x03040000,
	ERR_IO_PTZ_OPENDEV_FAIL		= 0x03040001,
	ERR_IO_PTZ_WRITE_FAIL		= 0x03040002,
	ERR_IO_PTZ_NOMEM		= 0x03040003,
	ERR_IO_PTZ_INVAL		= 0x03040004,
	ERR_IO_PTZ_PARITY_FAIL		= 0x03040005
};

#endif
