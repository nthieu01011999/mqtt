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

#ifndef _LIB_RTSV4L2_H
#define _LIB_RTSV4L2_H

#ifdef __cplusplus
extern "C"
{
#endif

#include <stdint.h>
#include <linux/videodev2.h>
#include <fcntl.h>

#define v4l2pixfmtstr(x)	(x) & 0xff, ((x) >> 8) & 0xff, ((x) >> 16) & 0xff, ((x) >> 24) & 0xff

int rts_v4l2_open(const char *path, int oflag);
int rts_v4l2_close(int fd);
int rts_v4l2_get_selection(int fd, uint32_t *x, uint32_t *y,
		uint32_t *width, uint32_t *height);
int rts_v4l2_set_selection(int fd, uint32_t x, uint32_t y,
		uint32_t width, uint32_t height);
int rts_v4l2_get_fmt(int fd, uint32_t *pfmt, uint32_t *pw, uint32_t *ph);
int rts_v4l2_set_fmt(int fd, uint32_t fmt, uint32_t width, uint32_t height);
int rts_v4l2_get_frmival(int fd, uint32_t *numerator, uint32_t *denominator);
int rts_v4l2_set_frmival(int fd, uint32_t numerator, uint32_t denominator);
int rts_v4l2_enum_fmt(int fd, int index, struct v4l2_fmtdesc *fmtdesc);
int rts_v4l2_enum_frmsizes(int fd, uint32_t fmt, int index,
			   struct v4l2_frmsizeenum *frmsize);
int rts_v4l2_enum_frmival(int fd, uint32_t fmt, uint32_t width,
			  uint32_t height, int index,
			  struct v4l2_frmivalenum *frmival);
int rts_v4l2_request_bufs(int fd, unsigned int num);
int rts_v4l2_query_mmap_buf(int fd,
			    int index, void **ppbuf, uint32_t *plength);
int rts_v4l2_munmap_buf(void *pbuf, uint32_t length);
int rts_v4l2_streamon(int fd);
int rts_v4l2_streamoff(int fd);
int rts_v4l2_query_buffer(int fd, uint32_t index, struct v4l2_buffer *pbuf);
int rts_v4l2_get_buffer(int fd, struct v4l2_buffer *pbuf);
int rts_v4l2_put_buffer(int fd, struct v4l2_buffer *pbuf);
int rts_v4l2_put_buffer_by_index(int fd, int index);
int rts_v4l2_pollin(int fd, int timeout);
int rts_v4l2_check_frame(int fd);

int rts_v4l2_queryctrl(int fd, struct v4l2_queryctrl *pqctrl);
int rts_v4l2_query_next_ctrl(int fd, struct v4l2_queryctrl *pqctrl);
int rts_v4l2_get_ctrl(int fd, struct v4l2_control *pctrl);
int rts_v4l2_set_ctrl(int fd, struct v4l2_control *pctrl);
int rts_v4l2_get_ext_ctrls(int fd, struct v4l2_ext_controls *ctrls);
int rts_v4l2_set_ext_ctrls(int fd, struct v4l2_ext_controls *ctrls);
int rts_v4l2_get_max_frmsize(int fd, uint32_t fmt, uint32_t *w, uint32_t *h);
int rts_v4l2_get_sensor_frmsize(uint32_t *w, uint32_t *h);


int rts_v4l2_enable_vin(int fd);
int rts_v4l2_streamon_without_vin(int fd);
int rts_v4l2_set_vin_mode(int fd, int mode);

#ifdef __cplusplus
}
#endif
#endif
