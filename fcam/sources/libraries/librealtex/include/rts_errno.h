/*
 * Copyright (c) 2022 Realtek Semiconductor Corp. All rights reserved.
 *
 * SPDX-License-Identifier: LicenseRef-Realtek-Proprietary
 *
 * This software component is confidential and proprietary to Realtek
 * Semiconductor Corp. Disclosure, reproduction, redistribution, in whole
 * or in part, of this work and its derivatives without express permission
 * is prohibited.
 */

#ifndef _RTS_ERRNO_H
#define _RTS_ERRNO_H

#ifndef RTS_RETURN
#define RTS_RETURN(e)		(-(e))
#endif

#ifndef RTS_ERRNO
#define RTS_ERRNO(r)	((r) < 0 ? (-(r)) : (r))
#endif

#ifndef RTS_IS_ERR_VALUE
#define RTS_IS_ERR_VALUE(r)	((r) < RTS_OK)
#endif

enum RTS_ERRNO {
	RTS_OK = 0,
	RTS_FAIL,
	RTS_E_NULL_POINT = 10,
	RTS_E_NO_MEMORY,
	RTS_E_NOT_REALIZED,
	RTS_E_EXIST,
	RTS_E_NOT_EXIST,
	RTS_E_NOT_FOUND,
	RTS_E_NOT_REGISTERED,
	RTS_E_NOT_READY,
	RTS_E_EMPTY,
	RTS_E_NOT_EMPTY,
	RTS_E_FULL,
	RTS_E_INVALID_ARG,
	RTS_E_INVALID_TYPE,
	RTS_E_NOT_MATCH,
	RTS_E_OPEN_FAIL,
	RTS_E_CLOSE_FAIL,
	RTS_E_NOT_OPEN,
	RTS_E_GET_FAIL,
	RTS_E_SET_FAIL,
	RTS_E_NOT_SUPPORT,
	RTS_E_INITIALIZED,
	RTS_E_NOT_INITIALIZED,
	RTS_E_INUSE,
	RTS_E_WRITE_FAIL,
	RTS_E_READ_FAIL,
	RTS_E_LOCK_FAIL,
	RTS_E_INVALID_LENGTH,
	RTS_E_TIMEOUT,
	RTS_E_THREAD_FAIL,
	RTS_E_OVERFLOW,
	RTS_E_BIG,
	RTS_E_PERM,
	RTS_E_NO_ENT,
	RTS_E_IO,
	RTS_E_AGAIN,
	RTS_E_NO_DEV,
	RTS_E_NO_SYS,
	RTS_E_IOCTL,
	RTS_E_LESS_DATA,
	RTS_E_OUT_OF_RANGE,
	RTS_E_MMAP_FAIL,
	RTS_E_MUNMAP_FAIL,
	RTS_E_INVALID_DATA,
	RTS_E_NO_REALIZED,
	RTS_E_INVALID_VERSION,
	RTS_E_UNKNOWN,
	RTS_E_RECEIVE_FAIL,
	RTS_E_SEND_FAIL,
	RTS_E_DISCONNECT,
	RTS_E_SAVE_FAIL,
	RTS_E_CMP_FAIL,
	RTS_E_ERASE_FAIL,
	RTS_E_RESET_FAIL,
	RTS_E_DISABLE,
	RTS_E_NOT_EQUAL,
	RTS_E_EQUAL,
	RTS_E_CMD_ERROR,
	RTS_E_INVALID_CMD,
	RTS_E_MISMATCH,
	RTS_E_BUF_OVERFLOW,
	RTS_E_NOT_CROSS,
	RTS_E_NOT_PARALLEL,
	RTS_E_PARALLEL,
	RTS_E_CONFILCT,
	RTS_E_BUSY,
	RTS_E_CHANGED,
};

char *rts_strerrno(int errnum);

int RTS_IS_ERR(int ret);

#endif
