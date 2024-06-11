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

 /**
* @file rtsvideo.h
* @brief RTStream Video API and Structure
*
* @defgroup total RTStream Video API
* @brief RTStream video API reference
*/

#ifndef _INCLUDE_RTSVIDEO_H
#define _INCLUDE_RTSVIDEO_H
#include <stdint.h>
#include <rtsavdef.h>

#ifdef __cplusplus
extern "C"
{
#endif

/**
* @defgroup common Video Stream
* @brief API and Structure for video stream
* @ingroup total
* @{
*/

/**
 * @brief Create video-in channel
 * @param[in] attr video-in channel attribute
 * @return video-in channel number, minus : fail
 */
int rts_av_create_vin_chn(struct rts_vin_attr *attr);

/**
 * @brief Create h264 channel
 * @param[in] attr h264 channel attribute
 * @return h264 channel number, minus : fail
 */
int rts_av_create_h264_chn(struct rts_h264_attr *attr);

/**
 * @brief Create mjpeg channel
 * @param[in] attr mjpeg channel attribute
 * @return mjpeg channel number, minus : fail
 */
int rts_av_create_mjpeg_chn(struct rts_jpgenc_attr *attr);

/**
 * @brief Create mjpeg decoder channel
 * @param[in] attr mjpeg decoder channel attribute
 * @return mjpeg decoder channel number, minus : fail
 */
int rts_av_create_mjpgdec_chn(struct rts_jpgdec_attr *attr);

/**
 * @brief Create OSD channel
 * @attention OSD channel can't be setted until bind with ISP
 * @return 0 :success, minus : fail
 */
int rts_av_create_osd_chn(void);

/**
 * @brief Create h265 channel
 * @param[in] attr h265 channel attribute
 * @return h265 channel number, minus : fail
 */
int rts_av_create_h265_chn(struct rts_h265_attr *attr);

/**
 * @brief Create video-out channel
 * @param[in] attr video-out channel attribute
 * @return video-out channel number, minus : fail
 */
int rts_av_create_vout_chn(struct rts_vout_attr *attr);

int rts_av_bind_rotate(unsigned int src, unsigned int dst, int rotate);
int rts_av_unbind_rotate(unsigned int src, unsigned int dst);
int rts_av_get_vin_attr(unsigned int chnno, struct rts_vin_attr *attr);
int rts_av_get_h264_attr(unsigned int chnno, struct rts_h264_attr *attr);
int rts_av_get_mjpeg_attr(unsigned int chnno, struct rts_jpgenc_attr *attr);
int rts_av_get_mjpgdec_attr(unsigned int chnno, struct rts_jpgdec_attr *attr);
int rts_av_get_h265_attr(unsigned int chnno, struct rts_h265_attr *attr);

int rts_av_register_vin(void);
int rts_av_register_h264(void);
int rts_av_register_h265(void);
int rts_av_register_osd2(void);
int rts_av_register_mjpeg(void);
int rts_av_register_mjpgdec(void);

/*!@}*/

/**
* @defgroup video_in Video ISP
* @brief API and Structure for ISP configure.
* @details Sets the configure of ISP, such as brightness, contrast, exposure mode,
* white balance mode, color conversion mode and wide dynamic state.
* See \ref RTS_ISP_CTRL_ID explains for id supported by ISP ctrl.
* For ISP channel, the image format, resolution, and frame rate can be queried by \ref rts_av_query_isp_ability.
* The following figure is the ISP workchart of RTStream, which illustrates the working process of IPcamera
* from collecting RAW images from sensor to producing YUV images.
* \htmlonly <style>div.image img[src="isp_flow.png"]{width:600px;}</style> \endhtmlonly
* \image html isp_flow.png "RTStream ISP Flow Diagram"
* @ingroup total
* @{
*/

/**
 * @example example_fov_mode.c
 * @example example_set_sensor_fps.c
 * @example example_day_night_mode.c
 * @example example_isp_ctrl.c
 * @example example_whitebalance.c
 */

/**
 * @brief ISP Control ID
 */
enum RTS_ISP_CTRL_ID {
	RTS_ISP_CTRL_ID_BRIGHTNESS = 1, /**< brightness */
	RTS_ISP_CTRL_ID_CONTRAST, /**< contrast */
	RTS_ISP_CTRL_ID_HUE, /**< hue */
	RTS_ISP_CTRL_ID_SATURATION, /**< saturation */
	RTS_ISP_CTRL_ID_SHARPNESS, /**< sharpness */
	RTS_ISP_CTRL_ID_GAMMA, /**< gamma */
	RTS_ISP_CTRL_ID_AWB_CTRL, /**< auto white balance mode,auto/manual/component */
	RTS_ISP_CTRL_ID_WB_TEMPERATURE, /**< white balance temperature */
	RTS_ISP_CTRL_ID_BLC, /**< back light compensator (only rts3903/3913 support) */
	RTS_ISP_CTRL_ID_GAIN, /**< gain */
	RTS_ISP_CTRL_ID_PWR_FREQUENCY, /**< power liner frequency */
	RTS_ISP_CTRL_ID_EXPOSURE_MODE, /**< exposure mode, auto/manual */
	RTS_ISP_CTRL_ID_EXPOSURE_PRIORITY, /**< exposure priority */
	RTS_ISP_CTRL_ID_EXPOSURE_TIME, /**< exposure time(manual mode) */
	RTS_ISP_CTRL_ID_AF, /**< focus mode(auto/manual) */
	RTS_ISP_CTRL_ID_FOCUS, /**< absolute focus */
	RTS_ISP_CTRL_ID_ZOOM, /**< zoom (only rts3903/3913 support) */
	RTS_ISP_CTRL_ID_PAN, /**< panning (only rts3903/3913 support) */
	RTS_ISP_CTRL_ID_TILT, /**< tilt (only rts3903/3913 support) */
	RTS_ISP_CTRL_ID_ROLL, /**< roll (only rts3903/3913 support) */
	RTS_ISP_CTRL_ID_FLIP, /**< filp (only rts3903/3913 support) */
	RTS_ISP_CTRL_ID_MIRROR, /**< mirror (only rts3903/3913 support) */
	RTS_ISP_CTRL_ID_ROTATE, /**< rotation (only rts3903/3913 support) */
	RTS_ISP_CTRL_ID_GRAY_MODE, /**< gray mode */
	RTS_ISP_CTRL_ID_WDR_MODE, /**< digital wide dynamic range mode */
	RTS_ISP_CTRL_ID_WDR_LEVEL, /**< level of wide dynamic range */
	RTS_ISP_CTRL_ID_GREEN_BALANCE, /**< green component of white balance(in component mode) */
	RTS_ISP_CTRL_ID_RED_BALANCE, /**< red component of white balance(in component mode) */
	RTS_ISP_CTRL_ID_BLUE_BALANCE, /**< blue component of white balance(in component mode) */
	RTS_ISP_CTRL_ID_AE_GAIN, /**< auto exposure gain */
	RTS_ISP_CTRL_ID_3DNR, /**< Three-dimensional noise reduction */
	RTS_ISP_CTRL_ID_DEHAZE, /**< dehaze */
	RTS_ISP_CTRL_ID_IR_MODE, /**< infrared ray mode */
	RTS_ISP_CTRL_ID_SMART_IR_MODE, /**< smart infrared ray mode */
	RTS_ISP_CTRL_ID_SMART_IR_MANUAL_LEVEL, /**< level of manual smart infrared ray */
	RTS_ISP_CTRL_ID_IN_OUT_DOOR_MODE, /**< indoor/outdoor mode (only rts3903/3913 support) */
	RTS_ISP_CTRL_ID_IQ_TABLE,	/**< iq table (only rts3915 support) */
	RTS_ISP_CTRL_ID_NOISE_REDUCTION, /**< noise reduction */
	RTS_ISP_CTRL_ID_DETAIL_ENHANCEMENT, /**< detail enhancement */
	RTS_ISP_CTRL_ID_LDC, /**< Lens Distortion Correction */
	RTS_ISP_CTRL_ID_SNR_CROP_X, /**< sensor crop x */
	RTS_ISP_CTRL_ID_SNR_CROP_Y, /**< sensor crop y */
	RTS_ISP_CTRL_ID_DYNAMIC_FPS, /**< dynamic fps (read only for rts3915) */
	RTS_ISP_CTRL_ID_FOV_MODE, /**< fov mode */
	RTS_ISP_CTRL_ID_CCM_AUTO, /**< ccm auto */
	RTS_ISP_CTRL_ID_CCM_MATRIX, /**< ccm matrix */
	RTS_ISP_CTRL_ID_Y_GAMMA_AUTO, /**< y gamma auto */
	RTS_ISP_CTRL_ID_Y_GAMMA_CURVE, /**< y gamma curve */
	RTS_ISP_CTRL_ID_RGB_GAMMA_AUTO, /**< rgb gamma auto */
	RTS_ISP_CTRL_ID_RGB_GAMMA_CURVE, /**< rgb gamma curve */
	RTS_ISP_CTRL_ID_DAYNIGHT_STATIS, /**< day night statis */
	RTS_ISP_CTRL_ID_HDR_MODE, /**< wide dynamic range mode */
	RTS_ISP_CTRL_ID_WIDE_DYNAMIC_RANGE = RTS_ISP_CTRL_ID_HDR_MODE,
	RTS_ISP_CTRL_ID_AUTO_HDR_RATIO, /**< auto hdr ratio */
	RTS_ISP_CTRL_ID_HDR_RATIO, /**< hdr ratio */
	RTS_ISP_CTRL_ID_RESERVED
};

/**
 * @brief ISP digital wide dynamic range mode
 */
enum RTS_ISP_WDR_MODE {
	RTS_ISP_WDR_DISABLE = 0, /**< digital wdr disable mode */
	RTS_ISP_WDR_MANUAL, /**< digital wdr manual mode */
	RTS_ISP_WDR_AUTO, /**< digital wdr auto mode */
	RTS_ISP_WDR_RESERVED,
};

/**
 * @brief ISP infrared ray mode
 */
enum RTS_ISP_IR_MODE {
	RTS_ISP_IR_DAY = 0, /**< day mode */
	RTS_ISP_IR_NIGHT = 1, /**< night mode */
	RTS_ISP_IR_WHITE_LIGHT = 2 /**< white light mode */
};

/**
 * @brief ISP smart infrared ray mode
 */
enum RTS_ISP_SMART_IR_MODE {
	RTS_ISP_SMART_IR_MODE_DISABLE = 0, /**< disable ir */
	RTS_ISP_SMART_IR_MODE_AUTO = 1, /**< auto mode */
	RTS_ISP_SMART_IR_MODE_HIGH_LIGHT_PRIORITY = 2, /**< high light priority mode */
	RTS_ISP_SMART_IR_MODE_LOW_LIGHT_PRIORITY = 3, /**< low light priority mode */
	RTS_ISP_SMART_IR_MODE_MANUAL = 4 /**< manual mode */
};

/**
 * @brief ISP indoor/outdoor mode
 */
enum RTS_ISP_IN_OUT_DOOR_MODE {
	RTS_ISP_DOOR_MODE_OUT = 0, /**< outdoor mode */
	RTS_ISP_DOOR_MODE_IN = 1, /**< indoor mode */
	RTS_ISP_DOOR_MODE_AUTO = 2 /**< auto mode */
};

/**
 * @brief ISP HDR mode
 */
enum RTS_ISP_HDR_MODE {
	RTS_ISP_HDR_OFF = 0, /**< hdr off mode: only use long frame */
	RTS_ISP_HDR_ON, /**< hdr on mode: use long and short frame */
	RTS_ISP_HDR_AUTO, /**< hdr auto mode: algo to determin on/off */
	RTS_ISP_HDR_RESERVED,
};

/**
 * @brief ISP control attribute
 */
struct rts_isp_control {
	uint32_t type; /**< control type */
	char name[32]; /**< control name */
	int32_t minimum; /**< minimum value */
	int32_t maximum; /**< maximum value */
	int32_t step; /**< step value */
	int32_t default_value; /**< default value */
	int32_t current_value; /**< current value */
	uint32_t flags; /**< flags */
	uint32_t reserved[4];
};


enum RTS_BLK_TYPE {
	RTS_BLK_TYPE_UNDEFINED = 0,
	RTS_BLK_TYPE_RECT,
	RTS_BLK_TYPE_GRID,
};

/**
 * @brief Coordinate description
 */
struct rts_video_coordinate {
	int32_t x; /**< x-axis value */
	int32_t y; /**< y-axis value */
};

/**
 * @brief Resolution description
 */
struct rts_video_size {
	uint32_t width; /**< width */
	uint32_t height; /**< height */
};

/**
 * @brief Rectangle description
 */
struct rts_video_rect {
	union {
		struct {
			struct rts_video_coordinate start; /**< coordinate of the starting point */
			struct rts_video_coordinate end; /**< coordinate of the ending point */
		}; /**< rectangle in coordinate format */
		struct {
			int32_t left; /**< rectangle left value */
			int32_t top; /**< rectangle top value */
			int32_t right; /**< rectangle right value */
			int32_t bottom; /**< rectangle bottom value */
		}; /**< rectangle in other format */
	}; /**< union of rectangle discription in two formats */
};

/**
 * @brief Rectangle description (float)
 */
struct rts_video_rect_float {
	float left; /**< rectangle left value */
	float top; /**< rectangle top value */
	float right; /**< rectangle right value */
	float bottom; /**< rectangle bottom value */
};

/**
 * @brief Grid cell description
 */
struct rts_video_grid_cell {
	uint32_t width; /**< width of grid cell */
	uint32_t height; /**< height of grid cell */
};

/**
 * @brief Grid size description
 */
struct rts_video_grid_size {
	uint32_t rows; /**< number of grid rows */
	uint32_t columns; /**< number of grid columns */
};

/**
 * @brief Bitmap description
 */
struct rts_video_grid_bitmap {
	uint8_t *vm_addr; /**< bitmap buffer addr */
	uint32_t length; /**< bitmap length */
	uint32_t reserved[4];
};

/**
 * @brief Grid description
 */
struct rts_video_grid {
	struct rts_video_coordinate start; /**< coordinate of the starting point */
	struct rts_video_grid_cell cell; /**< width and heigth of the cell */
	struct rts_video_grid_size size; /**< raw and column number of the cell */

	struct rts_video_grid_bitmap bitmap; /**< grid bitmap data */

	uint32_t reserved[4];
};

/*!@}*/

/**
* @defgroup auto 3A Ctrl
* @brief API and Structure for auto exposure/auto white
* balance/auto focus/vendor white balance
* @ingroup total
* @{
*/

/**
 * @brief ISP auto exposure mode
 */
enum RTS_ISP_AE_MODE {
	RTS_ISP_AE_MANUAL = 0, /**< manual */
	RTS_ISP_AE_AUTO = 1 /**< auto */
};

/**
 * @brief ISP auto exposure priority
 */
enum RTS_ISP_AE_PRIORITY {
	RTS_ISP_AE_PRIORITY_MANUAL = 0, /**< manual */
	RTS_ISP_AE_PRIORITY_AUTO = 1 /**< auto */
};

/**
 * @brief ISP auto white balance mode
 */
enum RTS_ISP_AWB_MODE {
	RTS_ISP_AWB_TEMPERATURE = 0, /**< temperature */
	RTS_ISP_AWB_AUTO = 1, /**< auto */
	RTS_ISP_AWB_COMPONENT /**< component mode */
};

/**
 * @brief The exposure properties of ISP
 */
struct rts_isp_ae_ctrl {
	const struct rts_video_size window_size; /**< size of the window */
	const uint32_t window_num; /**< number of the window */
	const uint32_t histogram_num; /**< number of the histogram */

	int mode; /**< mode: manual, auto. see \ref RTS_ISP_AE_MODE */

	struct {
		uint16_t total_gain; /**< total gain */
		struct {
			uint16_t analog; /**< analog gain */
			uint16_t digital; /**< digital gain */
			uint16_t isp_digital; /**< ISP digital gain */
		} gain; /**< gain */
		uint32_t exposure_time; /**< exposure time */

		uint32_t reserved[4];
	} _manual; /**< manual mode */

	struct {
		uint8_t * const win_weights; /**< weight */

		int target_delta; /**< parameter delta */
		uint16_t gain_max; /**< max gain */
		float min_fps; /**< min fps */
		float exposure_max; /**< max exposure(us) */

		uint32_t reserved[4];
	} _auto; /**< automatic mode */

	const struct {
		uint16_t y_mean; /**< y means */
		uint16_t *win_y_means; /**< window y means */
		uint32_t *histogram_info; /**< information of the histogram */

		uint32_t reserved[4];
	} statis; /**< statis value */

	uint32_t reserved[4];
};

/**
 * @brief The white balance properties of ISP
 */
struct rts_isp_awb_ctrl {
	const struct rts_video_size window_size; /**< size of the window */
	const uint32_t window_num; /**< number of the window */

	int mode; /**< mode: manual, auto, component. see \ref RTS_ISP_AWB_MODE */

	struct {
		uint16_t r_gain; /**< red gain */
		uint16_t b_gain; /**< blue gain */

		uint32_t reserved[4];
	} _auto; /**< automatic mode */

	struct {
		uint32_t temperature; /**< color temperature */

		uint32_t reserved[4];
	} _manual; /**< manual mode */

	struct {
		uint16_t red; /**< red component */
		uint16_t green; /**< green component */
		uint16_t blue; /**< blue component */

		uint32_t reserved[4];
	} _component; /**< component mode */

	const struct {
		uint16_t *r_means; /**< red mean value */
		uint16_t *g_means; /**< green mean value */
		uint16_t *b_means; /**< blue mean value */

		uint32_t reserved[4];
	} statis; /**< statis value */

	uint32_t reserved[4];
};

/**
 * @brief The vendor white balance properties of ISP
 */
struct rts_isp_vendor_awb_ctrl {
	const struct rts_video_size window_size; /**< size of the window */
	const uint32_t window_num; /**< number of the window */

	int enable; /**< switch */

	struct {
		uint16_t r_gain; /**< red gain */
		uint16_t g_gain; /**< green gain */
		uint16_t b_gain; /**< blue gain */
	} gain; /**< gain */

	struct {
		uint8_t update_flag; /**< update flag */
		uint8_t bright_min; /**< minimum brightness */
		uint8_t bright_max; /**< maximal brightness */
		uint8_t r_min; /**< minimum r-component */
		uint8_t r_max; /**< maximal r-component */
		uint8_t g_min; /**< minimum g-component */
		uint8_t g_max; /**< maximal g-component */
		uint8_t b_min; /**< minimum b-component */
		uint8_t b_max; /**< maximal b-component */
		/**
		 * minimum value for r/g, 8 bit precision,
		 * the hardware only supports 5 bit precision.
		 */
		uint16_t r_g_ratio_min;
		/**
		 * maximum value for r/g, 8 bit precision,
		 * the hardware only supports 5 bit precision.
		 */
		uint16_t r_g_ratio_max;
		/**
		 * minimum value for b/g, 8 bit precision,
		 * the hardware only supports 5 bit precision.
		 */
		uint16_t b_g_ratio_min;
		/**
		 * maximum value for b/g, 8 bit precision,
		 * the hardware only supports 5 bit precision.
		 */
		uint16_t b_g_ratio_max;
	} rough_limit; /**< rough limit */

	struct {
		uint8_t update_flag; /**< update flag */
		uint8_t bright_min; /**< minimum brightness */
		uint8_t bright_max; /**< maximal brightness */
		/**
		 * minimum value for r/g, 8 bit precision,
		 * the hardware only supports 5 bit precision.
		 */
		uint16_t r_g_ratio_min;
		/**
		 * maximum value for r/g, 8 bit precision,
		 * the hardware only supports 5 bit precision.
		 */
		uint16_t r_g_ratio_max;
		/**
		 * minimum value for b/g, 8 bit precision,
		 * the hardware only supports 5 bit precision.
		 */
		uint16_t b_g_ratio_min;
		/**
		 * maximum value for b/g, 8 bit precision,
		 * the hardware only supports 5 bit precision.
		 */
		uint16_t b_g_ratio_max;
	} fine_limit; /**< fine limit */

	struct {
		uint16_t r_gain; /**< red gain */
		uint16_t b_gain; /**< blue gain */
	} rough_gain; /**< rough gain */

	const uint32_t current_temperature; /**< current temperature */

	const struct {
		uint8_t *r_means; /**< red means */
		uint8_t *g_means; /**< green means */
		uint8_t *b_means; /**< blue means */
		uint8_t *weight; /**< normalized value (0~64) */
		struct {
			uint16_t g_r_ratio; /**< g_sum/r_sum, 8 bit precision */
			uint16_t g_b_ratio; /**< g_sum/b_sum, 8 bit precision */
			uint32_t white_count; /**< white point number */
		} fine_tune; /**< fine tune */

		uint32_t reserved[4];
	} statis; /**< statis value */

	uint32_t reserved[4];
};

/**
 * @brief ISP color temperature
 */
enum RTS_ISP_CT {
	RTS_ISP_CT_2800K = 0, /**< A */
	RTS_ISP_CT_3000K, /**< U30 */
	RTS_ISP_CT_4000K, /**< CWF */
	RTS_ISP_CT_5000K, /**< D50 */
	RTS_ISP_CT_6500K, /**< D65 */
	RTS_ISP_CT_7500K, /**< D75 */
	RTS_ISP_CT_RESERVED
};

/**
 * @brief The focus properties of ISP
 */
struct rts_isp_af_ctrl {
	const struct rts_video_size window_size; /**< size of the window */
	const uint32_t window_num; /**< number of the window */

	const struct {
		uint16_t *y_mean; /** y mean */
		uint16_t *high_light_cnt; /** high light point count */
		uint32_t *gr_focus_value; /** gr focus value */
		uint32_t *gb_focus_value; /** gb focus value */

		uint32_t reserved[4];
	} statis; /**< statis value */

	uint32_t reserved[4];
};

/*!@}*/

/**
* @addtogroup video_in
* @{
*/

/**
 * @brief Crop position
 */
struct rts_isp_snr_crop {
	struct rts_video_coordinate minimum; /**< minimum coordinate */
	struct rts_video_coordinate maximum; /**< maximum coordinate */
	struct rts_video_coordinate step; /**< coordinate step */
	struct rts_video_coordinate default_value; /**< default coordinate */
	struct rts_video_coordinate current_value; /**< current coodinate */
};

/**
 * @brief ISP gamma curve
 */
struct rts_isp_gamma {
	int mode; /**< mode, 1 : manual, 0 : auto */
	const int len; /**< length of gamma curve */
	uint8_t *curve; /**< gamma curve */
};

/**
 * @brief ISP color correction matrix
 */
struct rts_isp_ccm {
	int mode; /**< mode, 1 : manual, 0 : auto */
	const int len; /**< length of matrix */
	int32_t *matrix; /**< matrix */
};

/**
 * @brief Set bitmap for motion detect or private mask
 * @param[in] bitmap pointer to bitmap
 * @param[in] length length of bitmap
 * @param[in] index index of bitmap
 * @return 0 : success, minus : fail
 */
int rts_set_isp_bitmap(uint8_t *bitmap, int length, int index);

/**
 * @brief Clear bitmap for motion detect or private mask
 * @param[in] bitmap pointer to bitmap
 * @param[in] length length of bitmap
 * @param[in] index index of bitmap
 * @return 0 : success, minus : fail
 */
int rts_clear_isp_bitmap(uint8_t *bitmap, int length, int index);

/**
 * @brief Get bitmap for motion detect or private mask
 * @param[in] bitmap pointer to bitmap
 * @param[in] length length of bitmap
 * @param[in] index index of bitmap
 * @return 1 : set, 0 : clear, minus : fail
 */
int rts_get_isp_bitmap(uint8_t *bitmap, int length, int index);

/**
 * @brief Set all bitmap for motion detect or private mask
 * @param[in] bitmap pointer to bitmap
 * @param[in] length length of bitmap
 * @return 0 : success, minus : fail
 */
int rts_set_all_isp_bitmap(uint8_t *bitmap, int length);

/**
 * @brief Clear all bitmap for motion detect or private mask
 * @param[in] bitmap pointer to bitmap
 * @param[in] length length of bitmap
 * @return 0 : success, minus : fail
 */
int rts_clear_all_isp_bitmap(uint8_t *bitmap, int length);

/**
 * @brief Set ISP crop information
 * @param[in] chnno video-in channel number
 * @param[in] crop crop information
 * @return 0 : success, minus : fail
 */
int rts_av_set_isp_crop(unsigned int chnno, struct rts_video_rect *crop);

/**
 * @brief Get ISP crop information
 * @param[in] chnno video-in channel number
 * @param[out] crop crop information
 * @return 0 : success, minus : fail
 */
int rts_av_get_isp_crop(unsigned int chnno, struct rts_video_rect *crop);

/**
 * @brief Obtain ISP control attribute
 * @param[in] id rts video control id, see \ref RTS_ISP_CTRL_ID
 * @param[out] pctrl pointer to rts_isp_control
 * @return 0 : success, minus : fail
 * @note RTS_ISP_CTRL_ID_WDR_MODE refer to \ref RTS_ISP_WDR_MODE\n
 * RTS_ISP_CTRL_ID_IR_MODE refer to \ref RTS_ISP_IR_MODE\n
 * RTS_ISP_CTRL_ID_SMART_IR_MODE refer to \ref RTS_ISP_SMART_IR_MODE\n
 * RTS_ISP_CTRL_ID_IN_OUT_DOOR_MODE refer to \ref RTS_ISP_IN_OUT_DOOR_MODE\n
 * RTS_ISP_CTRL_ID_EXPOSURE_PRIORITY refer to \ref RTS_ISP_AE_PRIORITY\n
 * RTS_ISP_CTRL_ID_HDR_MODE refer to \ref RTS_ISP_HDR_MODE
 */
int rts_av_get_isp_ctrl(uint32_t id, struct rts_isp_control *pctrl);

/**
 * @brief Set ISP control attribute
 * @param[in] id ISP control id, see \ref RTS_ISP_CTRL_ID
 * @param[in] pctrl pointer to rts_isp_control
 * @return 0 : success, minus : fail
 */
int rts_av_set_isp_ctrl(uint32_t id, struct rts_isp_control *pctrl);

/*!@}*/

/**
* @addtogroup auto
* @{
*/
/**
 * @example example_af.c
 * @example example_ae.c
 * @example example_awb.c
 */

/**
 * @brief Initialize and obtain the exposure properties of ISP
 * @param[out] ae pointer to the address of rts_isp_ae_ctrl
 * @return 0 : success, minus : fail
 */
int rts_av_query_isp_ae(struct rts_isp_ae_ctrl **ae);

/**
 * @brief Release the exposure properties of ISP
 * @param[in] ae pointer to rts_isp_ae_ctrl
 * @attention After using rts_av_query_isp_ae, rts_av_release_isp_ae
 * must be called to release the resources.
 */
void rts_av_release_isp_ae(struct rts_isp_ae_ctrl *ae);

/**
 * @brief Get the exposure properties of ISP
 * @param[out] ae pointer to rts_isp_ae_ctrl
 * @return 0 : success, minus : fail
 */
int rts_av_get_isp_ae(struct rts_isp_ae_ctrl *ae);

/**
 * @brief Set the exposure properties of ISP
 * @param[in] ae pointer to rts_isp_ae_ctrl
 * @return 0 : success, minus : fail
 */
int rts_av_set_isp_ae(struct rts_isp_ae_ctrl *ae);

/**
 * @brief Refresh the statis value of the exposure
 * @param[out] ae pointer to rts_isp_ae_ctrl
 * @return 0 : success, minus : fail
 */
int rts_av_refresh_isp_ae_statis(struct rts_isp_ae_ctrl *ae);

/**
 * @brief Initialize and obtain the white balance properties of ISP
 * @param[out] awb pointer to the address of rts_isp_awb_ctrl
 * @return 0 : success, minus : fail
 */
int rts_av_query_isp_awb(struct rts_isp_awb_ctrl **awb);

/**
 * @brief Release the white balance properties of ISP
 * @param[in] awb pointer to rts_isp_awb_ctrl
 * @attention After using rts_av_query_isp_awb, rts_av_release_isp_awb
 * must be called to release the resources.
 * @return 0 : success, minus : fail
 */
void rts_av_release_isp_awb(struct rts_isp_awb_ctrl *awb);

/**
 * @brief Get the white balance properties of ISP
 * @param[out] awb pointer to rts_isp_awb_ctrl
 * @return 0 : success, minus : fail
 */
int rts_av_get_isp_awb(struct rts_isp_awb_ctrl *awb);

/**
 * @brief Set the white balance properties of ISP
 * @param[in] awb pointer to rts_isp_awb_ctrl
 * @return 0 : success, minus : fail
 */
int rts_av_set_isp_awb(struct rts_isp_awb_ctrl *awb);

/**
 * @brief Refresh the statis value of the white balance
 * @param[out] awb pointer to rts_isp_awb_ctrl
 * @return 0 : success, minus : fail
 */
int rts_av_refresh_isp_awb_statis(struct rts_isp_awb_ctrl *awb);

/**
 * @brief Initialize and obtain the vendor white balance properties of ISP
 * @param[out] awb pointer to the address of rts_isp_vendor_awb_ctrl
 * @return 0 : success, minus : fail
 */
int rts_av_query_isp_awb_vendor(struct rts_isp_vendor_awb_ctrl **awb);

/**
 * @brief Release the vendor white balance properties of ISP
 * @param[in] awb pointer to rts_isp_vendor_awb_ctrl
 * @attention After using rts_av_query_isp_awb_vendor,
 * rts_av_release_isp_awb_vendor must be called to release the resources.
 * @return 0 : success, minus : fail
 */
void rts_av_release_isp_awb_vendor(struct rts_isp_vendor_awb_ctrl *awb);

/**
 * @brief Get the vendor white balance properties of ISP
 * @param[out] awb pointer to rts_isp_vendor_awb_ctrl
 * @return 0 : success, minus : fail
 */
int rts_av_get_isp_awb_vendor(struct rts_isp_vendor_awb_ctrl *awb);

/**
 * @brief Set the vendor white balance properties of ISP
 * @param[in] awb pointer to rts_isp_vendor_awb_ctrl
 * @return 0 : success, minus : fail
 */
int rts_av_set_isp_awb_vendor(struct rts_isp_vendor_awb_ctrl *awb);

/**
 * @brief Refresh the statis value of the vendor white balance
 * @param[out] awb pointer to rts_isp_vendor_awb_ctrl
 * @return 0 : success, minus : fail
 */
int rts_av_refresh_isp_awb_vendor_statis(struct rts_isp_vendor_awb_ctrl *awb);

/**
 * @brief Get the gain value at different color temperature
 * @param[in] ct ISP color temperature, see \ref RTS_ISP_CT
 * @param[out] r_gain red gain
 * @param[out] b_gain blue gain
 * @return 0 : success, minus : fail
 */
int rts_av_get_isp_awb_ct_gain(uint8_t ct, uint16_t *r_gain, uint16_t *b_gain);

/**
 * @brief Initialize and obtain the focus properties of ISP
 * @param[out] af pointer to the address of rts_isp_af_ctrl
 * @return 0 : success, minus : fail
 */
int rts_av_query_isp_af(struct rts_isp_af_ctrl **af);

/**
 * @brief Release the focus properties of ISP
 * @param[in] af pointer to rts_isp_af_ctrl
 * @attention After using rts_av_query_isp_af, rts_av_release_isp_af
 * must be called to release the resources.
 */
void rts_av_release_isp_af(struct rts_isp_af_ctrl *af);

/**
 * @brief Get the focus properties of ISP
 * @param[out] af pointer to rts_isp_af_ctrl
 * @return 0 : success, minus : fail
 */
int rts_av_get_isp_af(struct rts_isp_af_ctrl *af);

/**
 * @brief Set the focus properties of ISP
 * @param[in] af pointer to rts_isp_af_ctrl
 * @return 0 : success, minus : fail
 */
int rts_av_set_isp_af(struct rts_isp_af_ctrl *af);

/**
 * @brief Refresh the statis value of the focus
 * @param[out] af pointer to rts_isp_af_ctrl
 * @return 0 : success, minus : fail
 */
int rts_av_refresh_isp_af_statis(struct rts_isp_af_ctrl *af);

/*!@}*/

/**
* @addtogroup video_in
* @{
*/

/**
 * @brief Get the current value of fov mode for the named channel
 * @attention If stream format of the channel is RTS_V_FMT_RGB/RTS_V_FMT_BGR/RTS_V_FMT_Y_ONLY, default fov is 1
 * @attention For other formats, default fov is 0
 * @param[in] chnno channel index, getting by create ISP channel
 * @param[out] val fov mode value, 1 : enable, 0 : disable
 * @return 0 : success, minus : fail
 */
int rts_av_get_isp_fov_mode(unsigned int chnno, int *val);

/**
 * @brief Enable fov mode for named channel
 * @attention If stream format of the channel is RTS_V_FMT_RGB/RTS_V_FMT_BGR/RTS_V_FMT_Y_ONLY, default fov is 1
 * @attention For other formats, default fov is 0
 * @param[in] chnno channel index, getting by create ISP channel
 * @param[in] val 1: enable fov mode, 0: disbale fov mode
 * @return 0 : success, minus : fail
 */
int rts_av_set_isp_fov_mode(unsigned int chnno, int val);

/**
 * @brief Obtain ablity of ISP channel, including supported format/resolution/fps
 * @param[in] chnno ISP channel index, getting by create channel
 * @param[out] isp_ability pointer to the adderss of rts_isp_ability,
 * must released by rts_av_release_isp_ability.
 * @return 0 : success, minus : fail
 */
int rts_av_query_isp_ability(unsigned int chnno,
			struct rts_isp_ability **isp_ability);

/**
 * @brief release rts_isp_ability obtained by rts_av_query_isp_ability
 * @param[in] isp_ability pointer to rts_isp_ability, get from rts_av_query_isp_ability
 */
void rts_av_release_isp_ability(struct rts_isp_ability *isp_ability);

/**
 * @brief Set actual fps value of sensor
 * @param[in] fps framerate
 * @attention auto exposure must change to manual mode before calling this API.
 * For changing fps, rts_av_set_profile is much more recommended than this API.
 * @return 0 : success, minus : fail
 * @par sample:
 * @code
 * //set sensor fps to 20
 * uint32_t id = RTS_ISP_CTRL_ID_EXPOSURE_PRIORITY;
 * struct rts_isp_control ctrl;
 *
 * ctrl.current_value = RTS_ISP_AE_PRIORITY_MANUAL;
 * rts_av_set_isp_ctrl(id, &ctrl);
 * rts_av_set_isp_dynamic_fps(20);
 * @endcode
 */
int rts_av_set_isp_dynamic_fps(float fps);

/**
 * @brief Get actual fps value of sensor
 * @return sensor fps, minus : fail
 */
float rts_av_get_isp_dynamic_fps(void);

/**
 * @brief get crop position
 * @param[out] crop pointer to rts_isp_snr_crop
 * @return 0 : success, minus : fail
 */
int rts_av_get_isp_snr_crop(struct rts_isp_snr_crop *crop);

/**
 * @brief set crop position
 * @param[in] crop pointer to rts_isp_snr_crop
 * @attention The crop range that can be set depends on the sensor setting.
 * You can get reasonable setting range by return value of the minimum/maximum member of input parameter.
 * If it is not allowed to set, the sensor configuration may need to be adjusted.
 * @return 0 : success, minus : fail
 */
int rts_av_set_isp_snr_crop(struct rts_isp_snr_crop *crop);

int rts_av_cvrt_point_res(struct rts_point_res *src,
	struct rts_point_res *dst, struct rts_point_con *constraint);

/**
 * @brief get supported sensor name
 * @return sensor name, NULL : fail
 */
const char *rts_av_get_supported_snr_name(void);

/**
 * @brief alloc buffer for y gamma, and get the length of y gamma curve
 * @param[out] gamma pointer to the address of rts_isp_gamma
 * @return 0 : success, minus : fail
 */
int rts_av_query_y_gamma(struct rts_isp_gamma **gamma);

/**
 * @brief get current y gamma curve and mode
 * @param[out] gamma rts_isp_gamma, get from rts_av_query_y_gamma
 * @return 0 : success, minus : fail
 */
int rts_av_get_y_gamma(struct rts_isp_gamma *gamma);

/**
 * @brief set y gamma curve and mode
 * @param[in] gamma rts_isp_gamma, get from rts_av_query_y_gamma
 * @attention Mode must set to manual(1) before calling this API.
 * After calling, the hardware will do frame sync,
 * setting will work after one frame.
 * @return 0 : success, minus : fail
 */
int rts_av_set_y_gamma(struct rts_isp_gamma *gamma);

/**
 * @brief alloc buffer for rgb gamma, and get the length of rgb gamma curve
 * @param[out] gamma pointer to the adderss of rts_isp_gamma
 * @return 0 : success, minus : fail
 */
int rts_av_query_rgb_gamma(struct rts_isp_gamma **gamma);

/**
 * @brief get current rgb gamma curve and mode
 * @param[out] gamma rts_isp_gamma, get from rts_av_query_rgb_gamma
 * @return 0 : success, minus : fail
 */
int rts_av_get_rgb_gamma(struct rts_isp_gamma *gamma);

/**
 * @brief set rgb gamma curve and mode
 * @param[in] gamma rts_isp_gamma, get from rts_av_query_rgb_gamma
 * @attention Mode must set to manual(1) before calling this API.
 * After calling, the hardware will do frame sync,
 * setting will work after one frame.
 * @return 0 : success, minus : fail
 */
int rts_av_set_rgb_gamma(struct rts_isp_gamma *gamma);

/**
 * @brief release rts_isp_gamma
 * @param[in] gamma rts_isp_gamma, get from rts_av_query_y_gamma
 * or rts_av_query_rgb_gamma
 */
void rts_av_release_gamma(struct rts_isp_gamma *gamma);

/**
 * @brief alloc buffer for color correction matrix,
 * and get the length of color correction matrix
 * @param[out] ccm pointer to the address of rts_isp_ccm
 * @return 0 : success, minus : fail
 */
int rts_av_query_ccm(struct rts_isp_ccm **ccm);

/**
 * @brief release rts_isp_ccm
 * @param[in] ccm rts_isp_ccm, get from rts_av_query_ccm
 */
void rts_av_release_ccm(struct rts_isp_ccm *ccm);

/**
 * @brief get current color correction matrix and mode.
 * @param[out] ccm rts_isp_ccm, get from rts_av_query_ccm.
 * @return 0 : success, minus : fail
 */
int rts_av_get_ccm(struct rts_isp_ccm *ccm);

/**
 * @brief set color correction matrix and mode.
 * @param[in] ccm rts_isp_ccm, get from rts_av_query_ccm
 * @attention mode must set to manual(1) before calling this API.
 * the diagonal of matrix must be positive.
 * @return 0 : success, minus : fail
 */
int rts_av_set_ccm(struct rts_isp_ccm *ccm);

/**
 * @brief get firmware information.
 * @return information string, NULL : fail
 */
const char *rts_av_get_isp_fw_info(void);

/**
 * @brief get daynight statistic.
 * @return statistic value
 */
int rts_av_get_isp_daynight_statis(void);

enum {
    RTS_QUAN_TYPE_DFP = 0, /**< dynamic_fixed_point-8 quantization */
    RTS_QUAN_TYPE_AA   = 1, /**< asymmetric uint8 quantization */
};

/**
 * @brief The RGB normalization control
 */
struct rts_rgb_norm_quan_ctrl {
	/**
	 * enable rgb normalization function, 0: disable, 1: enable
	 * @sa @ref hw_norm
	 */
	int enable;

	/**
	 * structure of R, G and B channel means
	 * @sa @ref hw_norm
	 */
	struct {
		/** normalization mean of R channel */
		uint8_t r_mean;
		/** normalization mean of G channel */
		uint8_t g_mean;
		/** normalization mean of B channel */
		uint8_t b_mean;
		/** normalization scale */
                float scale;
	} norm;

	struct {
		/**
		 * quantization type
		 * @sa @ref hw_norm
		 */
		uint32_t type;

		union {
			struct {
				/**
				 * fixed point position
				 * of dynamic_fixed_point-8 quantization
				 * @sa @ref hw_norm
				 */
				int fp;
			};
			struct {
				/**
				 * zero point of asymmetric uint8 quantization
				 * @sa @ref hw_norm
				 */
				int zp;
				/**
				 * scale of asymmetric uint8 quantization
				 * @sa @ref hw_norm
				 */
				float scale;
			};
		};
	} quan;
};

/**
 * @brief Set RGB normalization control
 * @param[in] ctrl pointer to rts_rgb_norm_quan_ctrl
 * @return 0 : success, minus : fail
 */
int rts_av_set_rgb_norm_quan_ctrl(struct rts_rgb_norm_quan_ctrl *ctrl);

/**
 * @brief Get RGB normalization control
 * @param[out] ctrl pointer to rts_rgb_norm_quan_ctrl
 * @return 0 : success, minus : fail
 */
int rts_av_get_rgb_norm_quan_ctrl(struct rts_rgb_norm_quan_ctrl *ctrl);

/**
 * @brief Convert rect parameter to isp coordinate by stream id
 * @param[in] isp_id stream id
 * @param[in] src src pointer to rts_video_rect_float
 * @param[out] dst dst pointer to rts_video_rect
 * @return 0 : success, minus : fail
 */
int rts_av_cvrt_rect_to_isp_by_stream(int isp_id,
		struct rts_video_rect_float *src, struct rts_video_rect *dst);

/**
 * @brief Convert rect parameter from isp coordinate by stream id
 * @param[in] isp_id stream id
 * @param[in] src src pointer to rts_video_rect
 * @param[out] dst dst pointer to rts_video_rect_float
 * @return 0 : success, minus : fail
 */
int rts_av_cvrt_rect_from_isp_by_stream(int isp_id, struct rts_video_rect *src,
		struct rts_video_rect_float *dst);

/**
 * @brief Convert rect parameter to isp coordinate by channel number
 * @param[in] chnno channel number
 * @param[in] src src pointer to rts_video_rect_float
 * @param[out] dst dst pointer to rts_video_rect
 * @return 0 : success, minus : fail
 */
int rts_av_cvrt_rect_to_isp_by_chn(int chnno, struct rts_video_rect_float *src,
		struct rts_video_rect *dst);

/**
 * @brief Convert rect parameter from isp coordinate by channel number
 * @param[in] chnno channel number
 * @param[in] src src pointer to rts_video_rect
 * @param[out] dst dst pointer to rts_video_rect_float
 * @return 0 : success, minus : fail
 */
int rts_av_cvrt_rect_from_isp_by_chn(int chnno, struct rts_video_rect *src,
		struct rts_video_rect_float *dst);

/**
 * @brief get color range.
 * @param[in] isp_id Specify get full range of which isp stream,limited to [0-3]
 * @param[out] matrix_coef Color coefficient e type,
 * detail in @ref RTS_COLOR_COEF_E
 * @param[out] full_range Color range,detail in @ref RTS_COLOR_RANGE
 * @return 0 : success, minus : fail
 */
int rts_av_get_color_range(int isp_id, int *matrix_coef, int *full_range);

/**
 * @brief set color range.
 * @param[in] isp_id Specify which isp stream to set full range, limited to [0-3]
 * @param[in] matrix_coef Color coefficient e type,
 * detail in @ref RTS_COLOR_COEF_E
 * @param[in] full_range Color range,detail in @ref RTS_COLOR_RANGE
 * @return 0 : success, minus : fail
 */
int rts_av_set_color_range(int isp_id, int matrix_coef, int full_range);
/*!@}*/
/**
* @defgroup sys Video System Mem
* @brief API and Structure for video system mem
* @ingroup total
* @{
*/
/* sys video api -- vmem */
/**
 * @brief Set configuration for video pre-allocated memory
 * @param[in] cfg pointer to rts_sys_vmem_cfg
 * @attention Configuration is not effective until
 * \ref rts_av_sys_vmem_init called.
 * @return 0 : success, minus : fail
 */
int rts_av_sys_vmem_set_conf(struct rts_sys_vmem_cfg *cfg);

/**
 * @brief Get configuration for video pre-allocated memory
 * @param[out] cfg pointer to rts_sys_vmem_cfg
 * @attention It will be failed if it is called before
 * \ref rts_av_sys_vmem_init.
 * @return 0 : success, minus : fail
 */
int rts_av_sys_vmem_get_conf(struct rts_sys_vmem_cfg *cfg);

/**
 * @brief Initialize configuration for video pre-allocated memory
 * @attention This API should be called before start any video
 * channel which will use pre-allocated memory.
 * @return 0 : success, minus : fail
 */
int rts_av_sys_vmem_init(void);

/**
 * @brief Release configuration for video pre-allocated memory
 * @attention After using \ref rts_av_sys_vmem_init, this API
 * can be called to release the resources. Please stop every
 * video channel which is using pre-allocated memory before
 * calling this API.
 * @return 0 : success, minus : fail
 */
int rts_av_sys_vmem_release(void);

/**
 * @brief Get status of video pre-allocated memory
 * @return 1 : on, 2 : off, others : fail
 */
int rts_av_sys_vmem_status(void);
int rts_av_sys_vmem_get_outbuf(int streamid, int memid, int idx, struct rts_av_buffer *mem);

/* sys video api -- vrm */
/**
 * @brief Allocate buffer from video reserved memory
 * @attention The allocated buffer is cacheable and needs to be
 * used together with rts_av_sys_vrm_flush_cache and
 * rts_av_sys_vrm_sync_cache interfaces.
 * @param[out] buffer pointer to rts_av_buffer
 * @return 0 : success, minus : fail
 */
int rts_av_sys_vrm_alloc(struct rts_av_buffer *buffer);

/**
 * @brief Release buffer from video reserved memory
 * @param[in] buffer pointer to rts_av_buffer
 * @return 0 : success, minus : fail
 */
int rts_av_sys_vrm_free(struct rts_av_buffer *buffer);

/**
 * @brief Flush buffer from cache to DDR
 * @param[in] buffer pointer to rts_av_buffer
 * @return 0 : success, minus : fail
 */
int rts_av_sys_vrm_flush_cache(struct rts_av_buffer *buffer);

/**
 * @brief Sync buffer from DDR to cache
 * @param[in] buffer pointer to rts_av_buffer
 * @return 0 : success, minus : fail
 */
int rts_av_sys_vrm_sync_cache(struct rts_av_buffer *buffer);

/* sys video api -- rcm */
/**
 * @brief Remove video CMA memory
 * @return 0 : success, minus : fail
 */
int rts_av_sys_remove_cma_memory(void);
/*!@}*/

/**
* @defgroup h264 Video H.264
* @brief API and Structure for H.264 Encoder
* @ingroup total
* @{
*/

#define RTS_H264_MAX_PS_SIZE	64

/**
 * @brief H.264 information description
 */
struct rts_h264_info {
	int sps_pps_len; /**< length of parameter information */
	char sps_pps[RTS_H264_MAX_PS_SIZE]; /**< parameter information */

	uint32_t reserved[4];
};

/**
 * @brief H.264 control description
 */
struct rts_h264_ctrl {
	const uint32_t supported_bitrate_mode; /**< supported bitrate mode */
	const uint32_t supported_gop_mode; /**< supported GOP mode */
	uint32_t bitrate_mode; /**< bitrate mode */
	uint32_t gop_mode; /**< GOP mode */

	uint32_t bitrate; /**< CBR bitrate, 16K ~ 20M, 1M as default */
	uint32_t max_bitrate; /**< CVBR max bitrate */
	uint32_t min_bitrate; /**< CVBR min bitrate */

	int32_t qp; /**< VBR quantization parameter, 0 ~51, 30 as default */
	uint32_t max_qp; /**< CBR/CVBR max QP, 0 ~ 51, 51 as default */
	uint32_t min_qp; /**< CBR/CVBR min QP, 0 ~ 51, 8 as default */
	uint32_t intra_max_qp; /**< CBR/CVBR I frame max qp, 0~51, 51 as default, only for RTS3915 */
	uint32_t intra_min_qp; /**< CBR/CVBR I frame min qp, 0~51, 8 as default, only for RTS3915 */
	int32_t intra_qp_delta; /**< QP delta value between I and P, -12~12, -4 as default */

	uint32_t gop; /**< GOP, 0 ~ 32767, 30 as default */

	uint32_t constrained_intra_prediction; /**< switch for const intra prediction */
	uint32_t disable_deblocking_filter; /**< disable deblock filter */
	uint32_t enable_cabac; /**< enable CABAC */
	uint32_t transform8x8mode; /**< enable 8x8 transform mode */

	uint32_t super_p_period; /**< period of long reference frame */

	int mbrc_en; /**< enable MBRC, 1 as default */
	float mbrc_qp_gain; /**< coefficient of MBRC, 1.6 as default */
	int32_t mbrc_qp_delta_range; /**< range of MBRC, 0 ~ 12, 4 as default */

	int cb_qp_offset; /**< chroma cb QpOffset, -12 ~ 12, 0 as default, only for RTS3915 */
	int cr_qp_offset; /**< chroma cr QpOffset, -12 ~ 12, 0 as default, only for RTS3915 */

	/* rts3903 ctrl */
	uint32_t slice_size; /**< size of every slice in a frame, only for RTS3903 */
	uint32_t sei_messages; /**< enable to add SEI messages, only for RTS3903 */
	uint32_t video_full_range; /**< quantization range for brightness and chroma, only for RTS3903 */
	uint32_t cabac_init_idc; /**< initial index for CABAC, only for RTS3903 */
	uint32_t gdr; /**< gradual decoding refresh, only for RTS3903 */
	uint32_t hrd; /**< hypothetical reference decoder, only for RTS3903 */
	uint32_t hrd_cpb_size; /**< size of CPB for HRD, only for RTS3903 */
	int32_t longterm_pic_rate;
	uint32_t br_level; /**< CVBR rate curve slope, 0 ~ 100, 50 as default, only for RTS3903 */

	/* rts3915 ctrl */
	uint32_t forced_idr_header_enable; /**< force idr header, only for RTS3915 */
	int scaling_list_enable; /**< scaling list, only for RTS3915 */
	int mb_level_rc_enable; /**< MB level rate control, only for RTS3915 */
	int bg_detect_level; /**< background detect level control, 0 ~ 3, 0 as default, only for RTS3915 */

	int max_pic_size; /**< restrict size of every frame, which may reduce picture quality */

	uint32_t reserved[4];
};

/**
 * @brief H.264 ROI attribution
 */
struct rts_h264_roi_ctrl {
	const int index; /**< ROI index */
	int enable; /**< switch for ROI */
	struct rts_video_rect area; /**< area of ROI */
	int32_t value; /**< -15 ~ 0 */

	const int32_t min; /**< minimum value */
	const int32_t max; /**< maximum value */
	const int32_t step; /**< step */

	uint32_t reserved[4];
};

/**
 * @brief ROI attribution
 */
struct rts_h264_roi {
	struct rts_h264_roi_ctrl *roi; /**< ROI control */
	const int count; /**< ROI count */

	uint32_t reserved[4];
};

/**
 * @brief ROI map
 */
struct rts_h264_roi_map {
	const uint32_t x_mbs; /**< MB number in each row */
	const uint32_t y_mbs; /**< MB number in each column */
	const uint8_t mb_width; /**< MB width */
	const uint8_t mb_height; /**< MB height */

	int roi_map_enable; /**< enable ROI map */
	uint8_t *map; /**< QP map */

	const int qp_offset_num; /**< QP offset number, default 3 */
	int qp_offset[3]; /**< QP offset, range [-8~7][-127~127][-127~127] */

	uint32_t reserved[4];
};

/**
 * @brief MB mode map
 */
struct rts_h264_mb_mode_map {
	const uint32_t x_mbs; /**< MB number in each row */
	const uint32_t y_mbs; /**< MB number in each column */
	const uint8_t mb_width; /**< MB width */
	const uint8_t mb_height; /**< MB height */

	int enable; /**< enable MB mode map */
	uint8_t *map; /**< MB mode map */

	uint32_t reserved[4];
};

/**
 * @brief H.264 motion vector description
 */
struct rts_h264_mb_mv {
	uint8_t mvcol[4]; /**< motion vector in MB */
	uint8_t flag; /**< encoding type intra(0) or inter(1) */
	int16_t mv_x[4]; /**< mv_x for subMB8x8 */
	int16_t mv_y[4]; /**< mv_y for subMB8x8 */
};

/**
 * @brief H.264 motion vector buffer
 */
struct rts_h264_mv_buffer {
	const uint32_t number; /**< number of MB in each frame */
	uint32_t index; /**< frame index */
	struct rts_h264_mb_mv *mv_info; /**< motion vector information of each frame */
};

/**
 * @brief H.264 background detection description
 */
struct rts_h264_bg_detect {
	int enable; /**< enable background detection */
	int bg_th_diff; /**< the threshold of max difference that is used in s2me block */
	int bg_th_mean_diff; /**< the threshold of mean difference that is used in s2me block */
	int bg_lambda_qp; /**< the minimum lambda QP value to be used in the background area */
	int bg_delta_qp; /**< the difference between the lambda QP value of background and the lambda QP value of foreground */
};

/**
 * @brief H.264 crop description
 */
struct rts_h264_crop {
	uint32_t start_x; /**< x coordinate of start pixel */
	uint32_t start_y; /**< y coordinate of start pixel */
	uint32_t end_x; /**< x coordinate of end pixel */
	uint32_t end_y; /**< y coordinate of end pixel */
};

/**
 * @brief H.264 VUI description
 */
struct rts_h264_vui {
	uint32_t vui_parameters_present_flag; /**< vui parameter present flag */

	uint32_t aspect_ratio_info_present_flag; /**< aspect ratio info present flag */
	uint16_t aspect_ratio_idc; /**< aspect ratio idc */
	uint16_t sar_width; /**< sar width */
	uint16_t sar_height; /**< sar height */

	uint32_t video_signal_type_present_flag; /**< video signal type present flag */
	int video_full_range_flag; /**< video full range flag */
	uint8_t video_format; /**< video format */

	uint32_t colour_description_present_flag; /**< colour description present flag */
	uint8_t colour_primaries; /**< colour primaries */
	uint8_t transfer_characteristics; /**< transfer characteristics */
	uint8_t matrix_coeffs; /**< matrix coeffs */

	uint32_t timing_info_present_flag; /**< timing information present flag */
	uint32_t num_units_in_tick; /**< number of units in tick */
	uint32_t time_scale; /**< time scale */
	uint32_t fixed_frame_rate_flag; /**< fixed frame rate flag */

	uint32_t reserved[4];
};

/**
 * @brief H.264 HRD description
 */
struct rts_h264_hrd {
	uint32_t encode_hrd_in_vui; /**< enable hrd encoding */
	uint32_t nal_hrd_parameters_present_flag; /**< nal hrd parameters present flag */
	uint32_t vcl_hrd_parameters_present_flag; /**< vcl hrd parameters present flag */

	uint32_t cpb_cnt_minus1; /**< cpb cnt minus1 */
	uint32_t bit_rate_scale; /**< bitrate scale */
	uint32_t cpb_size_scale; /**< cpb size scale */

	uint32_t bit_rate_value_minus1; /**< bitrate value minus */
	uint32_t cpb_size_value_minus1; /**< cpb size value minus1 */
	uint32_t cbr_flag; /**< cbr flag */

	uint32_t initial_cpb_removal_delay_length_minus1; /**< initial cpb removal delay length minu1 */
	uint32_t cpb_removal_delay_length_minus1; /**< cpb removal delay length minus1 */
	uint32_t dpb_output_delay_length_minus1; /**< dpb output delay length minus1 */
	uint32_t time_offset_length; /**< time offset length */
	uint32_t low_delay_hrd_flag; /**< low delay hrd flag */

	uint32_t reserved[4];
};

/**
 * @brief Obtain H.264 media information
 * @param[in] chnno H.264 channel number
 * @param[out] info pointer to rts_h264_info
 * @return 0 : success, minus : fail
 */
int rts_av_get_h264_mediainfo(unsigned int chnno,
			struct rts_h264_info *info);

/* to delete */
int rts_av_get_h264_profile(unsigned int chnno, int *profile);
int rts_av_set_h264_color_conversion(unsigned int chnno, int color_type,
			struct rts_color_coef_t *coef);

/**
 * @brief Request a H.264 key frame
 * @param[in] chnno H.264 channel number
 * @return 0 : success, minus : fail
 * @attention The next frame is not necessarily a key frame.
 */
int rts_av_request_h264_key_frame(unsigned int chnno);

/**
 * @brief Initialize and obtain the H.264 control
 * @param[in] chnno H.264 channel number
 * @param[out] ppctrl pointer to the address of rts_h264_ctrl
 * @return 0 : success, minus : fail
 */
int rts_av_query_h264_ctrl(unsigned int chnno,
			struct rts_h264_ctrl **ppctrl);

/**
 * @brief Release the H.264 control
 * @param[in] ctrl pointer to rts_h264_ctrl
 * @attention After using rts_av_query_h264_ctrl, rts_av_release_h264_ctrl
 * must be called to release the resources.
 */
int rts_av_release_h264_ctrl(struct rts_h264_ctrl *ctrl);

/**
 * @brief Set the H.264 control
 * @param[in] ctrl pointer to rts_h264_ctrl
 * @return 0 : success, minus : fail
 */
int rts_av_set_h264_ctrl(struct rts_h264_ctrl *ctrl);

/**
 * @brief Get the H.264 control
 * @param[out] ctrl pointer to rts_h264_ctrl
 * @return 0 : success, minus : fail
 */
int rts_av_get_h264_ctrl(struct rts_h264_ctrl *ctrl);

/**
 * @brief Initialize and obtain the ROI properties
 * @param[in] chnno H.264 channel number
 * @param[out] attr pointer to the address of rts_h264_roi
 * @return 0 : success, minus : fail
 */
int rts_av_query_h264_roi(unsigned int chnno, struct rts_h264_roi **attr);

/**
 * @brief Release the ROI properties
 * @param[in] attr pointer to rts_h264_roi
 * @attention After using rts_av_query_h264_roi, rts_av_release_h264_roi
 * must be called to release the resources.
 */
int rts_av_release_h264_roi(struct rts_h264_roi *attr);

/**
 * @brief Set the ROI properties
 * @param[in] attr pointer to rts_h264_roi
 * @return 0 : success, minus : fail
 */
int rts_av_set_h264_roi(struct rts_h264_roi *attr);

/**
 * @brief Get the ROI properties
 * @param[out] attr pointer to rts_h264_roi
 * @return 0 : success, minus : fail
 */
int rts_av_get_h264_roi(struct rts_h264_roi *attr);

/**
 * @brief Initialize and obtain the ROI map
 * @param[in] chnno H.264 channel number
 * @param[out] ppmap pointer to the address of rts_h264_roi_map
 * @attention Please call it after rts_av_enable_chn
 * @return 0 : success, minus : fail
 */
int rts_av_query_h264_roi_map(unsigned int chnno,
			struct rts_h264_roi_map **ppmap);

/**
 * @brief Release the ROI map
 * @param[in] pmap pointer to rts_h264_roi_map
 * @attention After using rts_av_query_h264_roi_map, rts_av_release_h264_roi_map
 * must be called to release the resources.
 */
int rts_av_release_h264_roi_map(struct rts_h264_roi_map *pmap);

/**
 * @brief Get the ROI map
 * @param[in] pmap pointer to rts_h264_roi_map
 * @return 0 : success, minus : fail
 */
int rts_av_get_h264_roi_map(struct rts_h264_roi_map *pmap);

/**
 * @brief Set the ROI map
 * @param[in] pmap pointer to rts_h264_roi_map
 * @return 0 : success, minus : fail
 */
int rts_av_set_h264_roi_map(struct rts_h264_roi_map *pmap);

/**
 * @brief Initialize and obtain the H.264 MB mode map
 * @param[in] chnno H.264 channel number
 * @param[out] ppmap pointer to the address of \ref rts_h264_mb_mode_map
 * @attention Please call it after \ref rts_av_enable_chn
 * @return 0 : success, minus : fail
 */
int rts_av_query_h264_mode_map(unsigned int chnno,
			struct rts_h264_mb_mode_map **ppmap);

/**
 * @brief Release the H.264 MB mode map
 * @param[in] pmap pointer to \ref rts_h264_mb_mode_map
 * @attention After using \ref rts_av_query_h264_mode_map, \ref rts_av_release_h264_mode_map
 * must be called to release the resources.
 */
int rts_av_release_h264_mode_map(struct rts_h264_mb_mode_map *pmap);

/**
 * @brief Set the H.264 MB mode map
 * @param[in] pmap pointer to rts_h264_mb_mode_map
 * @return 0 : success, minus : fail
 */
int rts_av_set_h264_mode_map(struct rts_h264_mb_mode_map *pmap);

/**
 * @brief Initialize and obtain the H.264 crop properties
 * @param[in] chnno H.264 channel number
 * @param[out] ppcrop pointer to the address of rts_h264_crop
 * @return 0 : success, minus : fail
 */
int rts_av_query_h264_crop(unsigned int chnno,
			struct rts_h264_crop **ppcrop);

/**
 * @brief Release the H.264 crop properties
 * @param[in] pcrop pointer to rts_h264_crop
 * @attention After using rts_av_query_h264_crop, rts_av_release_h264_crop
 * must be called to release the resources.
 */
int rts_av_release_h264_crop(struct rts_h264_crop *pcrop);

/**
 * @brief Set the H.264 crop properties
 * @param[in] pcrop pointer to rts_h264_crop
 * @return 0 : success, minus : fail
 */
int rts_av_set_h264_crop(struct rts_h264_crop *pcrop);

/**
 * @brief Get the H.264 crop properties
 * @param[out] pcrop pointer to rts_h264_crop
 * @return 0 : success, minus : fail
 */
int rts_av_get_h264_crop(struct rts_h264_crop *pcrop);

/**
 * @brief Initialize and obtain H.264 motion vector information
 * @param[in] chnno H.264 channel number
 * @param[out] ppbuf pointer to the address of rts_h264_mv_buffer
 * @return 0 : success, minus : fail
 */
int rts_av_query_h264_mv_info(unsigned int chnno,
			struct rts_h264_mv_buffer **ppbuf);

/**
 * @brief Release the H.264 motion vector information
 * @param[in] pbuf pointer to rts_h264_mv_buffer
 * @attention After using rts_av_query_h264_mv_info, rts_av_release_h264_mv_info
 * must be called to release the resources.
 */
int rts_av_release_h264_mv_info(struct rts_h264_mv_buffer *pbuf);

/**
 * @brief Get the H.264 motion vector information
 * @param[out] pbuf pointer to rts_h264_mv_buffer
 * @return 0 : success, minus : fail
 */
int rts_av_get_h264_mv_info(struct rts_h264_mv_buffer *pbuf);

/**
 * @brief Initialize and obtain the H.264 VUI information
 * @param[in] chnno H.264 channel number
 * @param[out] ppvui pointer to the address of rts_h264_vui
 * @return 0 : success, minus : fail
 */
int rts_av_query_h264_vui(unsigned int chnno,
		struct rts_h264_vui **ppvui);

/**
 * @brief Release the H.264 VUI information
 * @param[in] pvui pointer to rts_h264_vui
 * @attention After using rts_av_query_h264_vui, rts_av_release_h264_vui
 * must be called to release the resources.
 * @return 0 : success, minus : fail
 */
int rts_av_release_h264_vui(struct rts_h264_vui *pvui);

/**
 * @brief Set the H.264 VUI information
 * @param[in] pvui pointer to rts_h264_vui
 * @return 0 : success, minus : fail
 */
int rts_av_set_h264_vui(struct rts_h264_vui *pvui);

/**
 * @brief Get the H.264 VUI information
 * @param[out] pvui pointer to rts_h264_vui
 * @return 0 : success, minus : fail
 */
int rts_av_get_h264_vui(struct rts_h264_vui *pvui);

/**
 * @brief Initialize and obtain the H.264 HRD information
 * @param[in] chnno H.264 channel number
 * @param[out] pphrd pointer to the address of rts_h264_hrd
 * @return 0 : success, minus : fail
 */
int rts_av_query_h264_hrd(unsigned int chnno,
		struct rts_h264_hrd **pphrd);

/**
 * @brief Release the H.264 HRD information
 * @param[in] phrd pointer to rts_h264_hrd
 * @attention After using rts_av_query_h264_hrd, rts_av_release_h264_hrd
 * must be called to release the resources.
 * @return 0 : success, minus : fail
 */
int rts_av_release_h264_hrd(struct rts_h264_hrd *phrd);

/**
 * @brief Set the H.264 HRD information
 * @param[in] phrd pointer to rts_h264_hrd
 * @return 0 : success, minus : fail
 */
int rts_av_set_h264_hrd(struct rts_h264_hrd *phrd);

/**
 * @brief Get the H.264 HRD information
 * @param[out] phrd pointer to rts_h264_hrd
 * @return 0 : success, minus : fail
 */
int rts_av_get_h264_hrd(struct rts_h264_hrd *phrd);

/**
 * @brief Initialize and obtain H.264 background detection control
 * @param[in] chnno H.264 channel number
 * @param[out] ppbgdetect pointer to the address of rts_h264_bg_detect
 * @return 0 : success, minus : fail
 */
int rts_av_query_h264_bg_detect(unsigned int chnno,
		struct rts_h264_bg_detect **ppbgdetect);

/**
 * @brief Release the H.264 background detection control
 * @param[in] pbgdetect pointer to rts_h264_bg_detect
 * @attention After using rts_av_query_h264_bg_detect,
 * rts_av_release_h264_bg_detect must be called to release the resources.
 * @return 0 : success, minus : fail
 */
int rts_av_release_h264_bg_detect(struct rts_h264_bg_detect *pbgdetect);

/**
 * @brief Set the H.264 background detection control
 * @param[in] pbgdetect pointer to rts_h264_bg_detect
 * @return 0 : success, minus : fail
 */
int rts_av_set_h264_bg_detect(struct rts_h264_bg_detect *pbgdetect);

/**
 * @brief Get the H.264 background detection control
 * @param[out] pbgdetect pointer to rts_h264_bg_detect
 * @return 0 : success, minus : fail
 */
int rts_av_get_h264_bg_detect(struct rts_h264_bg_detect *pbgdetect);
/*!@}*/
/**
* @defgroup h265 Video H.265
* @brief API and Structure for H.265 Encoder
* @ingroup total
* @{
*/

/**
 * @example example_h265_crop.c
 * @example example_h265_ctrl.c
 * @example example_h265_roi.c
 */

#define RTS_H265_MAX_PS_SIZE	1024

/**
 * @brief H.265 information description
 */
struct rts_h265_info {
	int vps_sps_pps_len; /**< length of parameter information */
	char vps_sps_pps[RTS_H265_MAX_PS_SIZE]; /**< parameter information */

	uint32_t reserved[4];
};

/**
 * @brief H.265 control description
 */
struct rts_h265_ctrl {
	const uint32_t supported_bitrate_mode; /**< supported bitrate mode */
	const uint32_t supported_gop_mode; /**< supported GOP mode */
	uint32_t bitrate_mode; /**< bitrate mode */
	uint32_t gop_mode; /**< GOP mode */

	uint32_t bitrate; /**< CBR bitrate, 16K ~ 20M, 1M as default */
	uint32_t max_bitrate; /**< CVBR max bitrate */
	uint32_t min_bitrate; /**< CVBR min bitrate */

	int32_t qp; /**< VBR quantization parameter, 0~51, 30 as default */
	uint32_t gop; /**< GOP, 0 ~ 32767, 30 as default */

	uint32_t intra_min_qp; /**< min qp for i, 0 ~ 51, 8 as default */
	uint32_t intra_max_qp; /**< max QP for I, 0 ~ 51, 51 as default */
	uint32_t min_qp; /**< min QP, 0 ~ 51, 8 as default */
	uint32_t max_qp; /**< max QP, 0 ~ 51, 51 as default */
	uint32_t max_delta_qp; /**< QP delta value between each CU, 0 ~ 12, 10 as default */
	int32_t intra_qp_offset; /**< QP delta value between I and P, -12 ~ 12, -4 as default */

	int cu_level_rc_enable; /**< enable rate control in CTU level */
	int hvs_qp_enable; /**< enable rate control in subCTU level */
	int hvs_qp_scale; /**< QP coefficient for HVS */
	int initial_delay; /**< initial CPB delay in msec */
	int init_buf_level;  /**< encoder initial delay, only for RTS3913 */
	int gop_preset_idx; /**< preset struction for GOP */
	int gop_size; /**< size for GOP, only for RTS3915 */
	int bit_alloc_mode; /**< mode for bit allocation */
	int fixed_bit_ratio[8]; /**< fixed bit ratio, 1 ~ 255 */

	uint32_t super_p_period; /**< period of long reference frame */

	int const_intra_pred_flag; /**< switch for const intra prediction */
	int forced_idr_header_enable; /**< enable to add PS before every IDR */

	int use_recommend_enc_param; /**< recommended encoder parameter presets */
	int scaling_list_enable; /**< enable scaling list */
	int tmvp_enable; /**< enable temporal mv prediction */
	int max_num_merge; /**< maximum number of PU to merge motion vector */
	int dynamic_merge8x8_enable; /**< enable to merge CU8x8, only for RTS3913 */
	int dynamic_merge16x16_enable; /**< enable to merge CU16x16, only for RTS3913 */
	int dynamic_merge32x32_enable; /**< enable to merge CU32x32, only for RTS3913 */
	int disable_deblk; /**< disable deblock filter */
	int beta_offset_div2; /**< BetaOffsetDiv2 for deblock filter */
	int tc_offset_div2; /**< TcOffsetDiv2 for deblock filter */
	int skip_intra_trans; /**< enable transform skip for intra */
	int sao_enable; /**< enable SAO */
	int intra_in_inter_slice_enable; /**< enable intra in P silce, only for RTS3913 */
	int intra_NxN_enable; /**< enable intra NXN PUs */
	int monochrome_enable; /**< enable mono chrome, only for RTS3915 */
	int cb_qp_offset; /**< QP offset in Cb, only for RTS3915 */
	int cr_qp_offset; /**< QP offset in Cr, only for RTS3915 */
	int bg_detect_level; /**< background detect level control, 0 ~ 3, 0 as default, only for RTS3915 */
	int denoise_level; /**< noise reduction level control, 0 ~ 5, 2 as default, only for RTS3915 */

	int max_pic_size; /**< restrict size of every frame, which may reduce picture quality */

	uint32_t reserved[4];
};

/**
 * @brief ROI map
 */
struct rts_h265_roi_map {
	const uint32_t x_cus; /**< CTU number in each row */
	const uint32_t y_cus; /**< CTU number in each column */
	const uint8_t cu_width; /**< CTU width */
	const uint8_t cu_height; /**< CTU height */

	int enable; /**< enable ROI map */
	uint8_t *map; /**< CTU level map, 0 ~ 8 */
	uint8_t roi_delta_qp; /**< QP delta value, only for RTS3913 */

	uint32_t reserved[4];
};

/**
 * @brief CTU mode map
 */
struct rts_h265_ctu_mode_map {
	const uint32_t x_ctus; /**< CTU number in each row */
	const uint32_t y_ctus; /**< CTU number in each column */
	const uint8_t ctu_width; /**< CTU width */
	const uint8_t ctu_height; /**< CTU height */

	int enable; /**< enable CTU mode map */
	uint8_t *map; /**< CTU mode map */

	uint32_t reserved[4];
};

/**
 * @brief CTU QP map
 */
struct rts_h265_ctu_qp_map {
	const uint32_t x_ctus; /**< CTU number in each row */
	const uint32_t y_ctus; /**< CTU number in each column */
	const uint8_t ctu_width; /**< CTU width */
	const uint8_t ctu_height; /**< CTU height */

	int enable; /**< enable CTU QP map */
	uint8_t *map; /**< CTU QP map */

	uint32_t reserved[4];
};

/**
 * @brief H.265 crop description
 */
struct rts_h265_crop {
	uint32_t start_x; /**< x coordinate of start pixel */
	uint32_t start_y; /**< y coordinate of start pixel */
	uint32_t end_x; /**< x coordinate of end pixel */
	uint32_t end_y; /**< y coordinate of end pixel */
};

/**
 * @brief H.265 VUI description
 */
struct rts_h265_vui {
	uint32_t vui_parameters_present_flag; /**< vui parameter present flag */

	uint32_t aspect_ratio_info_present_flag; /**< aspect ratio info present flag */
	uint16_t aspect_ratio_idc; /**< aspect ratio idc */
	uint16_t sar_width; /**< sar width */
	uint16_t sar_height; /**< sar height */

	uint32_t video_signal_type_present_flag; /**< video signal type present flag */
	int video_full_range_flag; /**< video full range flag */
	uint8_t video_format; /**< video format */

	uint32_t colour_description_present_flag; /**< colour description present flag */
	uint8_t colour_primaries; /**< colour primaries */
	uint8_t transfer_characteristics; /**< transfer characteristics */
	uint8_t matrix_coeffs; /**< matrix coeffs */

	uint32_t vui_timing_info_present_flag; /**< vui timing info present flag */
	uint32_t vui_num_units_in_tick; /**< vui num units in tick */
	uint32_t vui_time_scale; /**< vui time scale */

	uint32_t reserved[4];
};

/**
 * @brief H.265 HRD description
 */
struct rts_h265_hrd {
	uint32_t encode_hrd_in_vui; /**< encode hrd in vui */

	uint32_t nal_hrd_parameters_present_flag; /**< nal hrd parameters present flag */
	uint32_t vcl_hrd_parameters_present_flag; /**< vcl hrd parameters present flag */

	uint32_t bit_rate_scale; /**< bit rate scale */
	uint32_t cpb_size_scale; /**< cpb size scale */

	uint32_t initial_cpb_removal_delay_length_minus1; /**< initial cpb removal delay length minus1 */
	uint32_t cpb_removal_delay_length_minus1; /**< cpb removal delay length minus */
	uint32_t dpb_output_delay_length_minus1; /**< dpb output delay length minus1 */

	uint32_t fixed_pic_rate_general_flag; /**< fixed pic rate general falg */
	uint32_t fixed_pic_rate_within_cvs_flag; /**< fixed pic rate within cvs flag */
	uint32_t elemental_duration_in_tc_minus1; /**< elemental duration in tc minus1 */
	uint32_t low_delay_hrd_flag; /**< low delay hrd flag */
	uint32_t cpb_cnt_minus1; /**< cpb cnt minus1, to be zero currently*/

	uint32_t bit_rate_value_minus1; /**< bit rate value minus1 */
	uint32_t cpb_size_value_minus1; /**< cpb size value minus1 */
	uint32_t cbr_flag; /**< cbr flag */

	uint32_t reserved[4];
};

/**
 * @brief H.265 motion vector description
 */
struct rts_h265_ctu_mv {
	uint8_t type[16]; /**< CTU type */
	int16_t mv_x[16]; /**< motion vector in X-axis for CU16x16 */
	int16_t mv_y[16]; /**< motion vector in Y-axis for CU16x16 */
};

/**
 * @brief H.265 motion vector buffer
 */
struct rts_h265_mv_buffer {
	const uint32_t number; /**< number of CTU in each frame */
	uint32_t index; /**< frame index */
	struct rts_h265_ctu_mv *mv_info; /**< motion vector information of each frame */
};

/**
 * @brief H.265 background detection description
 */
struct rts_h265_bg_detect {
	int enable; /**< enable background detection */
	int bg_th_diff; /**< the threshold of max difference that is used in s2me block */
	int bg_th_mean_diff; /**< the threshold of mean difference that is used in s2me block */
	int bg_lambda_qp; /**< the minimum lambda QP value to be used in the background area */
	int bg_delta_qp; /**< the difference between the lambda QP value of background and the lambda QP value of foreground */
};

/**
 * @brief H.265 noise reduction description
 */
struct rts_h265_3dnr {
	int en_y; /**< enable noise reduction algorithm to Y component */
	int en_cb; /**< enable noise reduction algorithm to Cb component */
	int en_cr; /**< enable noise reduction algorithm to Cr component */
	/**
	 * enable noise estimation for noise reduction,
	 * when this is disabled, host carries out noise estimation
	 * with Sigma Y/Cb/Cr.
	 */
	int en_est;

	uint8_t sigma_y; /**< Y noise standard deviation when en_est is 0 */
	uint8_t sigma_cb; /**< Cb noise standard deviation when en_est is 0 */
	uint8_t sigma_cr; /**< Cr noise standard deviation when en_est is 0 */

	uint8_t intra_weight_y; /**< weight to Y noise level for intra picture (0 ~ 31) */
	uint8_t intra_weight_cb; /**< weight to Cb noise level for intra picture (0 ~ 31) */
	uint8_t intra_weight_cr; /**< weight to Cr noise level for intra picture (0 ~ 31) */
	uint8_t inter_weight_y; /**< weight to Y noise level for inter picture (0 ~ 31) */
	uint8_t inter_weight_cb; /**< weight to Cb noise level for inter picture (0 ~ 31) */
	uint8_t inter_weight_cr; /**< weight to Cr noise level for inter picture (0 ~ 31) */
};

/**
 * @brief Obtain H.265 media information
 * @param[in] chnno H.265 channel number
 * @param[out] info pointer to rts_h265_info
 * @return 0 : success, minus : fail
 */
int rts_av_get_h265_mediainfo(unsigned int chnno,
			struct rts_h265_info *info);

/**
 *@brief Enable H.265 Lossless Encoding (Debug API)
 *@param[in] chnno H.265 channel number
 *@param[in] enable flag: 0 : disable, 1 : enable
 *@return 0 : success, minus : fail
 *@attention This API must be used before enable channel.
 */
int rts_av_set_h265_lossless_encoding(unsigned int chnno, int enable);

/**
 * @brief Initialize and obtain the H.265 control
 * @param[in] chnno H.265 channel number
 * @param[out] ppctrl pointer to the address of rts_h265_ctrl
 * @return 0 : success, minus : fail
 */
int rts_av_query_h265_ctrl(unsigned int chnno,
			struct rts_h265_ctrl **ppctrl);

/**
 * @brief Release the H.265 control
 * @param[in] ctrl pointer to rts_h265_ctrl
 * @attention After using rts_av_query_h265_ctrl, rts_av_release_h265_ctrl
 * must be called to release the resources.
 */
int rts_av_release_h265_ctrl(struct rts_h265_ctrl *ctrl);

/**
 * @brief Get the H.265 control
 * @param[out] ctrl pointer to rts_h265_ctrl
 * @return 0 : success, minus : fail
 */
int rts_av_get_h265_ctrl(struct rts_h265_ctrl *ctrl);

/**
 * @brief Set the H.265 control
 * @param[in] ctrl pointer to rts_h265_ctrl
 * @return 0 : success, minus : fail
 */
int rts_av_set_h265_ctrl(struct rts_h265_ctrl *ctrl);

/**
 * @brief Request a H.265 key frame
 * @param[in] chnno H.265 channel number
 * @return 0 : success, minus : fail
 * @attention The next frame is not necessarily a key frame.
 */
int rts_av_request_h265_key_frame(unsigned int chnno);

/**
 * @brief Initialize and obtain the ROI map
 * @param[in] chnno H.265 channel number
 * @param[out] ppmap pointer to the address of rts_h265_roi_map
 * @return 0 : success, minus : fail
 */
int rts_av_query_h265_roi_map(unsigned int chnno,
			struct rts_h265_roi_map **ppmap);

/**
 * @brief Release the ROI map
 * @param[in] pmap pointer to rts_h265_roi_map
 * @attention After using rts_av_query_h265_roi_map, rts_av_release_h265_roi_map
 * must be called to release the resources.
 */
int rts_av_release_h265_roi_map(struct rts_h265_roi_map *pmap);

/**
 * @brief Set the ROI map
 * @param[in] pmap pointer to rts_h265_roi_map
 * @return 0 : success, minus : fail
 */
int rts_av_set_h265_roi_map(struct rts_h265_roi_map *pmap);

/**
 * @brief Get the ROI map
 * @param[out] pmap pointer to rts_h265_roi_map
 * @return 0 : success, minus : fail
 */
int rts_av_get_h265_roi_map(struct rts_h265_roi_map *pmap);

/**
 * @brief Initialize and obtain the CTU mode map
 * @param[in] chnno H.265 channel number
 * @param[out] ppmap pointer to the address of rts_h265_ctu_mode_map
 * @return 0 : success, minus : fail
 */
int rts_av_query_h265_ctu_mode_map(unsigned int chnno,
			struct rts_h265_ctu_mode_map **ppmap);

/**
 * @brief Release the CTU mode map
 * @param[in] pmap pointer to rts_h265_ctu_mode_map
 * @attention After using rts_av_query_h265_ctu_mode_map, rts_av_release_h265_ctu_mode_map
 * must be called to release the resources.
 */
int rts_av_release_h265_ctu_mode_map(struct rts_h265_ctu_mode_map *pmap);

/**
 * @brief Set the CTU mode map
 * @param[in] pmap pointer to rts_h265_ctu_mode_map
 * @return 0 : success, minus : fail
 */
int rts_av_set_h265_ctu_mode_map(struct rts_h265_ctu_mode_map *pmap);

/**
 * @brief Get the CTU mode map
 * @param[out] pmap pointer to rts_h265_ctu_mode_map
 * @return 0 : success, minus : fail
 */
int rts_av_get_h265_ctu_mode_map(struct rts_h265_ctu_mode_map *pmap);

/**
 * @brief Initialize and obtain the CTU QP map
 * @param[in] chnno H.265 channel number
 * @param[out] ppmap pointer to the address of rts_h265_ctu_qp_map
 * @return 0 : success, minus : fail
 */
int rts_av_query_h265_ctu_qp_map(unsigned int chnno,
			struct rts_h265_ctu_qp_map **ppmap);

/**
 * @brief Release the CTU QP map
 * @param[in] pmap pointer to rts_h265_ctu_qp_map
 * @attention After using rts_av_query_h265_ctu_qp_map, rts_av_release_h265_ctu_qp_map
 * must be called to release the resources.
 */
int rts_av_release_h265_ctu_qp_map(struct rts_h265_ctu_qp_map *pmap);

/**
 * @brief Set the CTU QP map
 * @param[in] pmap pointer to rts_h265_ctu_qp_map
 * @return 0 : success, minus : fail
 */
int rts_av_set_h265_ctu_qp_map(struct rts_h265_ctu_qp_map *pmap);

/**
 * @brief Get the CTU QP map
 * @param[out] pmap pointer to rts_h265_ctu_qp_map
 * @return 0 : success, minus : fail
 */
int rts_av_get_h265_ctu_qp_map(struct rts_h265_ctu_qp_map *pmap);

/**
 * @brief Initialize and obtain the H.265 crop properties
 * @param[in] chnno H.265 channel number
 * @param[out] ppcrop pointer to the address of rts_h265_crop
 * @return 0 : success, minus : fail
 */
int rts_av_query_h265_crop(unsigned int chnno,
			struct rts_h265_crop **ppcrop);

/**
 * @brief Release the H.265 crop properties
 * @param[in] pcrop pointer to rts_h265_crop
 * @attention After using rts_av_query_h265_crop, rts_av_release_h265_crop
 * must be called to release the resources.
 */
int rts_av_release_h265_crop(struct rts_h265_crop *pcrop);

/**
 * @brief Set the H.265 crop properties
 * @param[in] pcrop pointer to rts_h265_crop
 * @return 0 : success, minus : fail
 */
int rts_av_set_h265_crop(struct rts_h265_crop *pcrop);

/**
 * @brief Get the H.265 crop properties
 * @param[out] pcrop pointer to rts_h265_crop
 * @return 0 : success, minus : fail
 */
int rts_av_get_h265_crop(struct rts_h265_crop *pcrop);

/**
 * @brief Initialize and obtain the H.265 VUI information
 * @param[in] chnno H.265 channel number
 * @param[out] ppvui pointer to the address of rts_h265_vui
 * @return 0 : success, minus : fail
 */
int rts_av_query_h265_vui(unsigned int chnno,
			struct rts_h265_vui **ppvui);

/**
 * @brief Release the H.265 VUI information
 * @param[in] pvui pointer to rts_h265_vui
 * @attention After using rts_av_query_h265_vui, rts_av_release_h265_vui
 * must be called to release the resources.
 */
int rts_av_release_h265_vui(struct rts_h265_vui *pvui);

/**
 * @brief Set the H.265 VUI information
 * @param[in] pvui pointer to rts_h265_vui
 * @return 0 : success, minus : fail
 */
int rts_av_set_h265_vui(struct rts_h265_vui *pvui);

/**
 * @brief Get the H.265 VUI information
 * @param[out] pvui pointer to rts_h265_vui
 * @return 0 : success, minus : fail
 */
int rts_av_get_h265_vui(struct rts_h265_vui *pvui);

/**
 * @brief Initialize and obtain the H.265 HRD information
 * @param[in] chnno H.265 channel number
 * @param[out] pphrd pointer to the address of rts_h265_hrd
 * @return 0 : success, minus : fail
 */
int rts_av_query_h265_hrd(unsigned int chnno,
			struct rts_h265_hrd **pphrd);

/**
 * @brief Release the H.265 HRD information
 * @param[in] phrd pointer to rts_h265_hrd
 * @attention After using rts_av_query_h265_hrd, rts_av_release_h265_hrd
 * must be called to release the resources.
 */
int rts_av_release_h265_hrd(struct rts_h265_hrd *phrd);

/**
 * @brief Set the H.265 HRD information
 * @param[in] phrd pointer to rts_h265_hrd
 * @return 0 : success, minus : fail
 */
int rts_av_set_h265_hrd(struct rts_h265_hrd *phrd);

/**
 * @brief Get the H.265 HRD information
 * @param[out] phrd pointer to rts_h265_hrd
 * @return 0 : success, minus : fail
 */
int rts_av_get_h265_hrd(struct rts_h265_hrd *phrd);

/**
 * @brief Initialize and obtain H.265 motion vector information
 * @param[in] chnno H.265 channel number
 * @param[out] ppbuf pointer to the address of rts_h265_mv_buffer
 * @return 0 : success, minus : fail
 */
int rts_av_query_h265_mv_info(unsigned int chnno,
			struct rts_h265_mv_buffer **ppbuf);

/**
 * @brief Release the H.265 motion vector information
 * @param[in] pbuf pointer to rts_h265_mv_buffer
 * @attention After using rts_av_query_h265_mv_info, rts_av_release_h265_mv_info
 * must be called to release the resources.
 * @return 0 : success, minus : fail
 */
int rts_av_release_h265_mv_info(struct rts_h265_mv_buffer *pbuf);

/**
 * @brief Get the H.265 motion vector information
 * @param[out] pbuf pointer to rts_h265_mv_buffer
 * @return 0 : success, minus : fail
 */
int rts_av_get_h265_mv_info(struct rts_h265_mv_buffer *pbuf);

/**
 * @brief Initialize and obtain H.265 background detection control
 * @param[in] chnno H.265 channel number
 * @param[out] ppbgdetect pointer to the address of rts_h265_bg_detect
 * @return 0 : success, minus : fail
 */
int rts_av_query_h265_bg_detect(unsigned int chnno,
		struct rts_h265_bg_detect **ppbgdetect);

/**
 * @brief Release the H.265 background detection control
 * @param[in] pbgdetect pointer to rts_h265_bg_detect
 * @attention After using rts_av_query_h265_bg_detect,
 * rts_av_release_h265_bg_detect must be called to release the resources.
 * @return 0 : success, minus : fail
 */
int rts_av_release_h265_bg_detect(struct rts_h265_bg_detect *pbgdetect);

/**
 * @brief Set the H.265 background detection control
 * @param[in] pbgdetect pointer to rts_h265_bg_detect
 * @return 0 : success, minus : fail
 */
int rts_av_set_h265_bg_detect(struct rts_h265_bg_detect *pbgdetect);

/**
 * @brief Get the H.265 background detection control
 * @param[out] pbgdetect pointer to rts_h265_bg_detect
 * @return 0 : success, minus : fail
 */
int rts_av_get_h265_bg_detect(struct rts_h265_bg_detect *pbgdetect);

/**
 * @brief Initialize and obtain H.265 noise reduction control
 * @param[in] chnno H.265 channel number
 * @param[out] pp3dnr pointer to the address of rts_h265_3dnr
 * @return 0 : success, minus : fail
 */
int rts_av_query_h265_3dnr(unsigned int chnno,
		struct rts_h265_3dnr **pp3dnr);

/**
 * @brief Release the H.265 noise reduction control
 * @param[in] p3dnr pointer to rts_h265_3dnr
 * @attention After using rts_av_query_h265_3dnr,
 * rts_av_release_h265_3dnr must be called to release the resources.
 * @return 0 : success, minus : fail
 */
int rts_av_release_h265_3dnr(struct rts_h265_3dnr *p3dnr);

/**
 * @brief Get the H.265 noise reduction control
 * @param[out] p3dnr pointer to rts_h265_3dnr
 * @return 0 : success, minus : fail
 */
int rts_av_get_h265_3dnr(struct rts_h265_3dnr *p3dnr);

/**
 * @brief Set the H.265 noise reduction control
 * @param[out] p3dnr pointer to rts_h265_3dnr
 * @return 0 : success, minus : fail
 */
int rts_av_set_h265_3dnr(struct rts_h265_3dnr *p3dnr);
/*!@}*/
/**
* @defgroup osd Video OSD
* @brief API and Structure for OSD
* @details Before setting OSD, OSD channel must be created firstly, and then connected after ISP channel.\n
* OSD supports setting 32 blocks at the same time, and also supports setting a single block separately.
* It only supports display image, and the supported image formats are 1bpp, argb1111, argb2222,
* argb4444, argb1555, argb8888 and so on. It no longer supports loading font library.
* Display date and time require the user to generate the corresponding image in advance.
* @ingroup total
* @{
*/

/**
 * @example example_osd2_pict.c
 * @example example_osd2_freetype.c
 */

/**
 * @brief enumerate value of OSD block fmt
 */
enum RTS_OSD2_BLK_FMT {
	RTS_OSD2_BLK_FMT_1BPP = RTS_PIX_FMT_1BPP, /**< 1bpp format */
	RTS_OSD2_BLK_FMT_RGBA1111 = RTS_PIX_FMT_RGBA1111, /**< rgba1111 format */
	RTS_OSD2_BLK_FMT_RGBA2222 = RTS_PIX_FMT_RGBA2222, /**< rgba2222 format */
	RTS_OSD2_BLK_FMT_RGBA5551 = RTS_PIX_FMT_RGBA5551, /**< rgba5551 format */
	RTS_OSD2_BLK_FMT_RGBA4444 = RTS_PIX_FMT_RGBA4444, /**< rgba4444 format */
	RTS_OSD2_BLK_FMT_RGBA8888 = RTS_PIX_FMT_RGBA8888 /**< rgba8888 format */
};

/**
 * @brief detail OSD block information
 */
struct rts_osd2_block {
	struct rts_video_rect rect; /**< rectangle */

	struct {
		uint32_t pixel_fmt; /**< OSD block fmt, see \ref RTS_OSD2_BLK_FMT */
		void *pdata; /**< picture data */
		uint32_t length; /**< picture data length */
		uint32_t pure_color; /**< set pure color rgb */
	} picture; /**< picture configure*/

	struct {
		int flick_enable; /**< enable flick */
		uint32_t show_time; /**< show time for flik */
		uint32_t hide_time; /**< hide tim efor flick */
	} flick; /**< flick configure*/

	uint8_t enable; /**< enable show block */
	uint32_t fixed_buf_len; /**< the least block buffer size */

	uint32_t reserved[4];
};

/**
 * @brief OSD attribute
 */
struct rts_osd2_attr {
	const int number; /**< OSD block number */
	struct rts_osd2_block *blocks; /**< detail block message */

	uint32_t reserved[4];
};

struct rts_osd2_scfg {
	uint8_t uv_disable;
	uint8_t bypass;
	uint8_t y_incr_enable;
	uint16_t y_incr;
	uint16_t y_incr_thd;
};

/**
 * @brief Initialize and obtain the OSD attribute
 * @param[in] chnno OSD channel number
 * @param[out] attr pointer to the address of rts_osd2_attr
 * @return 0 : success, minus : fail
 */
int rts_av_query_osd2(unsigned int chnno, struct rts_osd2_attr **attr);

/**
 * @brief Set attribute for the named block
 * @param[in] attr pointer to rts_osd2_attr
 * @param[in] blkidx index of OSD block
 * @return 0 : success, minus : fail
 */
int rts_av_set_osd2_single(struct rts_osd2_attr *attr, int blkidx);

/**
 * @brief Get attribute of the named block
 * @param[out] attr pointer to rts_osd2_attr
 * @param[in] blkidx index of OSD block
 * @return 0 : success, minus : fail
 */
int rts_av_get_osd2_single(struct rts_osd2_attr *attr, int blkidx);

/**
 * @brief Set attribute for every block
 * @param[in] attr pointer to rts_osd2_attr
 * @return 0 : success, minus : fail
 */
int rts_av_set_osd2(struct rts_osd2_attr *attr);

/**
 * @brief Get attribute of every block
 * @param[out] attr pointer to rts_osd2_attr
 * @return 0 : success, minus : fail
 */
int rts_av_get_osd2(struct rts_osd2_attr *attr);

/**
 * @brief Resume the setting for named block
 * @param[in] attr pointer to rts_osd2_attr
 * @param[in] blkidx index of block
 * @return 0 : success, minus : fail
 */
int rts_av_resume_osd2_single(struct rts_osd2_attr *attr, int blkidx);

/**
 * @brief Pause the setting for named OSD block
 * @param[in] attr pointer to rts_osd2_attr
 * @param[in] blkidx index of block
 * @return 0 : success, minus : fail
 */
int rts_av_pause_osd2_single(struct rts_osd2_attr *attr, int blkidx);

/**
 * @brief Set OSD color table
 * @param[in] attr pointer to rts_osd2_attr
 * @param[in] fmt color format for adjusting color table
 * @param[in] val setting value of specified place in color table
 * @param[in] r specified index of red in color table
 * @param[in] g specified index of green in color table
 * @param[in] b specifoed index of blue in color table
 * @param[in] a specified index of alpha in color table
 * @return 0 : success, minus : fail
 * @par sample:
 * @code
 *   //change the mapping value of index 0x1b in color table
 *     to opaque blue(0x0000ffff) for formatRTS_PIX_FMT_RGBA2222
 *   ret = rts_av_set_osd2_color_table(attr, RTS_PIX_FMT_RGBA2222, 0x0000ffff, 3, 2, 1, 0);
 * @endcode
 */
int rts_av_set_osd2_color_table(struct rts_osd2_attr *attr,
			int fmt, uint32_t val,
			uint8_t r, uint8_t g, uint8_t b, uint8_t a);

/**
 * @brief Get OSD color table
 * @param[in] attr pointer to rts_osd2_attr
 * @param[in] fmt color format for adjusting color table
 * @param[out] val pointer to get value of specified place in color table
 * @param[in] r index of red in color table
 * @param[in] g index of green in color table
 * @param[in] b index of blue in color table
 * @param[in] a index of alpha in color table
 * @return 0 : success, minus : fail
 */
int rts_av_get_osd2_color_table(struct rts_osd2_attr *attr,
			int fmt, uint32_t *val,
			uint8_t r, uint8_t g, uint8_t b, uint8_t a);

/**
 * @brief release attribute
 * @param attr pointer to rts_osd2_attr
 */
void rts_av_release_osd2(struct rts_osd2_attr *attr);

int rts_av_set_osd2_special_config(struct rts_osd2_attr *attr,
			struct rts_osd2_scfg *scfg, int blkidx);
int rts_av_get_osd2_special_config(struct rts_osd2_attr *attr,
			struct rts_osd2_scfg *scfg, int blkidx);

/*!@}*/
/**
* @defgroup osd Video OSD
* @brief API and Structure for OSD
* @details Before setting OSD, OSD channel must be created firstly, and then connected after ISP channel.\n
* OSD supports setting 32 blocks at the same time, and also supports setting a single block separately.
* It only supports display image, and the supported image formats are 1bpp, argb1111, argb2222,
* argb4444, argb1555, argb8888 and so on. It no longer supports loading font library.
* Display date and time require the user to generate the corresponding image in advance.
* @ingroup total
* @{
*/

/**
 * @example example_osdi_pict.c
 * @example example_osdi_freetype.c
 */

#define RTSOSDI_MAX_BLK_NUM	6

/**
 * @brief enumerate value of OSD block fmt
 */
enum RTS_OSDI_BLK_FMT {
	RTS_OSDI_BLK_FMT_1BPP = RTS_PIX_FMT_1BPP, /**< 1bpp format */
	RTS_OSDI_BLK_FMT_RGBA1111 = RTS_PIX_FMT_RGBA1111, /**< rgba1111 format */
	RTS_OSDI_BLK_FMT_RGBA2222 = RTS_PIX_FMT_RGBA2222, /**< rgba2222 format */
	RTS_OSDI_BLK_FMT_RGBA5551 = RTS_PIX_FMT_RGBA5551, /**< rgba5551 format */
	RTS_OSDI_BLK_FMT_RGBA4444 = RTS_PIX_FMT_RGBA4444, /**< rgba4444 format */
	RTS_OSDI_BLK_FMT_RGBA8888 = RTS_PIX_FMT_RGBA8888 /**< rgba8888 format */
};

/**
 * @brief detail OSD block information
 */
struct rts_osdi_block {
	struct rts_video_rect rect; /**< rectangle */

	struct {
		uint32_t pixel_fmt; /**< OSD block fmt, see \ref RTS_OSDI_BLK_FMT */
		void *pdata; /**< picture data */
		uint32_t length; /**< picture data length */
	} picture; /**< picture configure*/

	uint8_t enable; /**< enable show block */
	uint32_t fixed_buf_len; /**< the least block buffer size */

	uint32_t reserved[4];
};

/**
 * @brief OSD attribute
 */
struct rts_osdi_attr {
	const int number; /**< OSD block number */
	struct rts_osdi_block *blocks; /**< detail block message */

	uint32_t reserved[4];
};

/**
 * @brief Initialize and obtain the OSD attribute
 * @param[in] vin_chnno video-in channel number
 * @param[out] attr pointer to the address of rts_osdi_attr
 * @return 0 : success, minus : fail
 */
int rts_av_query_osdi(unsigned int vin_chnno, struct rts_osdi_attr **attr);

/**
 * @brief Set attribute for the named block
 * @param[in] attr pointer to rts_osdi_attr
 * @param[in] blkidx index of OSD block
 * @return 0 : success, minus : fail
 */
int rts_av_set_osdi_single(struct rts_osdi_attr *attr, int blkidx);

/**
 * @brief Get attribute of the named block
 * @param[out] attr pointer to rts_osdi_attr
 * @param[in] blkidx index of OSD block
 * @return 0 : success, minus : fail
 */
int rts_av_get_osdi_single(struct rts_osdi_attr *attr, int blkidx);

/**
 * @brief Set attribute for every block
 * @param[in] attr pointer to rts_osdi_attr
 * @return 0 : success, minus : fail
 */
int rts_av_set_osdi(struct rts_osdi_attr *attr);

/**
 * @brief Get attribute of every block
 * @param[out] attr pointer to rts_osdi_attr
 * @return 0 : success, minus : fail
 */
int rts_av_get_osdi(struct rts_osdi_attr *attr);

/**
 * @brief Resume the setting for named block
 * @param[in] attr pointer to rts_osdi_attr
 * @param[in] blkidx index of block
 * @return 0 : success, minus : fail
 */
int rts_av_resume_osdi_single(struct rts_osdi_attr *attr, int blkidx);

/**
 * @brief Pause the setting for named OSD block
 * @param[in] attr pointer to rts_osdi_attr
 * @param[in] blkidx index of block
 * @return 0 : success, minus : fail
 */
int rts_av_pause_osdi_single(struct rts_osdi_attr *attr, int blkidx);

/**
 * @brief Set OSD color table, need stop all OSD
 * @param[in] fmt color format for adjusting color table
 * @param[in] val setting value of specified place in color table
 * @param[in] r specified index of red in color table
 * @param[in] g specified index of green in color table
 * @param[in] b specifoed index of blue in color table
 * @param[in] a specified index of alpha in color table
 * @return 0 : success, minus : fail
 * @par sample:
 * @code
 *   //change the mapping value of index 0x1b in color table
 *     to opaque blue(0x0000ffff) for format RTS_OSDI_BLK_FMT_RGBA2222
 *   ret = rts_av_set_osdi_color_table(attr, RTS_OSDI_BLK_FMT_RGBA2222, 0x0000ffff, 3, 2, 1, 0);
 * @endcode
 */
int rts_av_set_osdi_color_table(int fmt, uint32_t val,
			uint8_t r, uint8_t g, uint8_t b, uint8_t a);

/**
 * @brief Get OSD color table
 * @param[in] fmt color format for adjusting color table
 * @param[in] val pointer to value of specified place in color table
 * @param[in] r index of red in color table
 * @param[in] g index of green in color table
 * @param[in] b index of blue in color table
 * @param[in] a index of alpha in color table
 * @return 0 : success, minus : fail
 */
int rts_av_get_osdi_color_table(int fmt, uint32_t *val,
			uint8_t r, uint8_t g, uint8_t b, uint8_t a);

/**
 * @brief release attribute
 * @param attr pointer to rts_osdi_attr
 */
void rts_av_release_osdi(struct rts_osdi_attr *attr);

/*!@}*/
/**
* @defgroup mjpeg Video MJPEG
* @brief API and Structure for MJPEG
* @ingroup total
* @{
*/

/**
* @example example_mjpeg.c
*/

struct rts_mjpeg_ctrl {
	uint16_t normal_compress_rate:8;
	const uint16_t ncr_max;
	const uint16_t ncr_min;
	const uint16_t ncr_step;

	uint32_t reserved[4];
};

int rts_av_query_mjpeg_ctrl(unsigned int chnno,
			struct rts_mjpeg_ctrl **ppctrl);
void rts_av_release_mjpeg_ctrl(struct rts_mjpeg_ctrl *ctrl);
int rts_av_get_mjpeg_ctrl(struct rts_mjpeg_ctrl *ctrl);
int rts_av_set_mjpeg_ctrl(struct rts_mjpeg_ctrl *ctrl);

enum {
        RTS_MJPEG_LOW_QUALITY = 0,
        RTS_MJPEG_MEDIAN_QUALITY,
        RTS_MJPEG_HIGH_QUALITY
};

int rts_av_set_mjpeg_ncr_level(unsigned int chnno, int level);

/**
 * @brief Set the MJPEG quality
 * @attention This API should call before enable MJPEG channel
 * This API is supported in RTS3915
 * @param[in] chnno MJPEG channel number
 * @param[in] quality Quality value, support 1-100, default 60, MJPEG
 * quality will be better as the value be higher
 * @return 0 : success, minus : fail
 */
int rts_av_set_mjpeg_quality(unsigned int chnno, int quality);

struct rts_jpgenc_ctrl {
	uint32_t fmt;
	uint32_t width;
	uint32_t height;
	uint16_t normal_compress_rate:8;
};

void *rts_av_sip_jpg_init(struct rts_jpgenc_ctrl *pctrl);
int rts_av_sip_jpg_encode(void *handle,
			struct rts_av_buffer *inbuf,
			struct rts_av_buffer *outbuf);
void rts_av_sip_jpg_release(void *handle);
/*!@}*/
/**
* @defgroup md2 Motion Detection for RTS3917
* @brief API and Structure for Motion Detection of RTS3917
* @ingroup total
* @{
*/
/**
 * @example example_md2.c
 */
/**
 * @brief Sample region of motion detection 2
 */
struct rts_md2_sample_region {
	uint32_t x; /**< start x */
	uint32_t y; /**< start y */
	uint32_t w; /**< width */
	uint32_t h; /**< height */
	/**
	 * scale of width
	 * pixel sample interval of motion detection in x-direction
	 * sample_image_width = w * scale_x
	 */
	uint32_t scale_x;
	/**
	 * scale of height
	 * pixel sample interval of motion detection in y-direction
	 * sample_image_height = h * scale_y
	 */
	uint32_t scale_y;
};

/**
 * @brief Bin bits of motion detection 2, data bits of a bin of a pixel sample
 */
enum RTS_MD2_BIN_BITS {
	RTS_MD2_BIN_BITS_2 = 0, /**< bin bits is 2 */
	RTS_MD2_BIN_BITS_4, /**< bin bits is 4 */
	RTS_MD2_BIN_BITS_MAX, /**< reserved */
};

/**
 * @brief Bins number of motion detection 2, number of bins of a pixel sample
 */
enum RTS_MD2_NR_BINS {
	RTS_MD2_NR_BINS_16 = 0, /**< bins number is 16 */
	RTS_MD2_NR_BINS_32, /**< bins number is 32 */
	RTS_MD2_NR_BINS_MAX, /**< reserved */
};

/**
 * @brief Attribution of motion detection 2
 */
struct rts_md2_attr {
	struct rts_md2_sample_region sample; /**< sample region */
	enum RTS_MD2_BIN_BITS bin_bits; /**< bin bits */
	enum RTS_MD2_NR_BINS nr_bins; /**< bins number */
	int skip_frames; /**< skip frame count, sample interval of isp frames*/
};

/**
 * @brief Roi(region of interest) map of motion detection 2
 */
struct rts_md2_roi_map {
	const uint32_t width; /**< roi width */
	const uint32_t height; /**< roi height */
	const uint32_t length; /**< roi map buffer length */

	uint8_t *const map; /**< roi map buffer, pixfmt is yonly*/
};

/**
 * @brief Control description for motion detection 2
 * must turn on RTS_MD2_RESULT_FL_ENABLE_CC_FILTER,
 * to make nr_cc_thd&max_ar&min_ar&cc_ratio effective
 */
struct rts_md2_ctrl {
	struct rts_md2_roi_map roi; /**< roi map*/

	/**
	 * sensitivity, 0 ~ 7.
	 * 1 ~ 7 automatic mode, will automatic set nr_cc_thd & back_thd,
	 *  (which means nr_cc_thd & back_thd settings will be ignored).
	 * 0 mannual mode, nr_cc_thd & back_thd is effective.
	 * default value: 6
	 **/
	int sensitivity;

	int train_enable; /**< train enable*/
	uint32_t train_frames; /**< train frames*/
	/**
	 * scene change threshold
	 * if current frame contains more motion pixels, will trigger trainning.
	 * default value: attr->sample.w * attr->sample.h * 0.5
	 */
	uint32_t scene_change_thd;

	/**
	 * background threshold, 0 ~ 15, thd to determind if it's background or foregound.
	 * if sensitivity is 1 ~ 7, back_thd setting is ignored.
	 */
	uint8_t back_thd;
	uint8_t learn_thd; /**< learn threshold, 0 ~ 255, learn_thd/255 is the learn probabilty for each frame*/
	uint8_t forget_thd; /**< forget threshold, 0 ~ 255, learn_thd/255 is the forget probabilty for each frame*/

	/**
	 * minimum pixel number of connect domain
	 * connect domain which cotains less pixels will be filter out.
	 * if sensitivity is 1 ~ 7, nr_cc_thd setting is ignored.
	 */
	uint32_t nr_cc_thd;
	/**
	 * max aspect ratio, compute by cc_w/cc_h, cc ar larger will be filter out.
	 * default value: 1.5
	 */
	float max_ar;
	/**
	 * min aspect ratio, cc ar smaller will be filter out.
	 * default value: 0.05
	 */
	float min_ar;
	/**
	 * connected domain ratio, 0 <= cc_ratio < 1, compute by pixel_count/(cc_w*cc_h), cc_ratio smaller will be filter out.
	 * default value: 0.3
	 */
	float cc_ratio;
};

/**
 * @brief Connected domain of motion detection 2
 */
struct rts_md2_cc {
	uint16_t u; /**< up of connected domain*/
	uint16_t b; /**< bottom of connected domain*/
	uint16_t l; /**< left of connected domain*/
	uint16_t r; /**< right of connected domain*/
	uint32_t pixel_cnt; /**< pixel count of connected domain*/
};

#define RTS_MD2_MAX_CC_NUM 20

/**
 * @brief Connected domain info of motion detection 2
 */
struct rts_md2_cc_info {
	struct rts_md2_cc cc[RTS_MD2_MAX_CC_NUM]; /**< connected domain*/
	uint32_t cc_len; /**< effective connected domain count*/
};

#define RTS_MD2_RESULT_FL_ENABLE_POST_PROCESS	(1) /**<turn on post process*/
#define RTS_MD2_RESULT_FL_ENABLE_CC_INFO	(1 << 1) /**<turn on cc_info, must turn on postprocess*/
#define RTS_MD2_RESULT_FL_ENABLE_CC_FILTER	(1 << 2) /**<turn on cc filter fucntion, must turn on cc_info*/
#define RTS_MD2_RESULT_FL_ENABLE_MOTION_MAP	(1 << 3) /**<turn on motion_map output*/

/**
 * @brief Result of Motion detection 2
 */
struct rts_md2_result {
	uint32_t flags; /**< md2 result flags, control result type*/

	uint32_t motion_cnt; /**< motion count*/
	uint8_t *motion_map; /**< motion map*/
	struct rts_md2_cc_info cc_info; /**< connected domain info*/
};

/**
 * @brief Initialize and obtain the motion detection 2 ctrl
 * @param[out] ctrl pointer to rts_md2_ctrl
 * @param[in] attr pointer to rts_md2_attr
 * @return 0 : success, minus : fail
 */
int rts_av_query_md2(struct rts_md2_ctrl **ctrl,
			struct rts_md2_attr *attr);

/**
* @brief release motion detection 2 ctrl
* @param ctrl pointer to rts_md2_ctrl
*/
void rts_av_release_md2(struct rts_md2_ctrl *ctrl);

/**
 * @brief Set ctrl for motion detection 2
 * @param[in] ctrl pointer to rts_md2_ctrl
 * @return 0 : success, minus : fail
 */
int rts_av_set_md2(struct rts_md2_ctrl *ctrl);

/**
 * @brief Get ctrl for motion detection 2
 * @param[out] ctrl pointer to rts_md2_ctrl
 * @return 0 : success, minus : fail
 */
int rts_av_get_md2(struct rts_md2_ctrl *ctrl);

int rts_av_poll_md2(struct rts_md2_ctrl *ctrl, int timeout_ms);

/**
 * @brief Check if data is ready for motion detection 2
 * @param[in] ctrl pointer to rts_md2_ctrl
 * @param[in] timeout_ms timeout(ms)
 * @return 0 : success, minus : fail
 */
int rts_av_poll_md2_result(struct rts_md2_ctrl *ctrl, int timeout_ms);

/**
 * @brief Get the result of motion detection 2
 * @param[in] ctrl pointer to rts_md2_ctrl
 * @param[out] res pointer to rts_md2_result
 * @return 0 : success, minus : fail
 */
int rts_av_get_md2_result(struct rts_md2_ctrl *ctrl,
				struct rts_md2_result *res);
/*!@}*/
/**
 * @defgroup mask Video Mask
 * @brief API and Structure for Private Mask
 * @details First, it needs to get the properties of mask through \ref rts_av_query_mask,
 * and then call \ref rts_av_release_mask to release it after using. Reference resolution
 * is required when querying the mask property.\n
 * The area of the mask supports the ways of rectangle and grid.
 * @ingroup total
 * @{
 */

/**
 * @example example_mask.c
 */

/**
 * @brief Block of private mask
 */
struct rts_mask_block {
	const int type; /**< block type, 1-rectangle, 2-grid */
	const uint32_t supported_grid_num; /**< supported grid number */
	int enable; /**< switch of private mask */
	union {
		struct rts_video_grid area; /**< grid area of private mask */
		struct rts_video_rect rect; /**< rectangle of private mask */
	}; /**< union of grid/rectangle */
	struct rts_video_size res_size; /**< reference resolution */

	uint32_t reserved[4];
};

/**
 * @brief Attribution of private mask
 */
struct rts_mask_attr {
	uint32_t color; /**< rgb24 */
	const int number; /**< block number of private mask */
	struct rts_mask_block *blocks; /**< pointer to rts_video_mask_block */

	uint32_t reserved[4];
};

/**
 * @brief Initialize and obtain the properties of ISP for private mask
 * @param[out] attr pointer to the address of rts_mask_attr
 * @param[in] res_width resolution width, block area in rts_mask_attr is relative to this.
 * @param[in] res_height resolution height, block area in rts_mask_attr is relative to this.
 * @return 0 : success, minus : fail
 */
int rts_av_query_mask(struct rts_mask_attr **attr,
			uint32_t res_width, uint32_t res_height);

/**
 * @brief Release the properties of ISP for private mask
 * @param[in] attr pointer to rts_mask_attr
 * @attention After using rts_av_query_mask, rts_av_release_mask
 * must be called to release the resources.
 */
void rts_av_release_mask(struct rts_mask_attr *attr);

/**
 * @brief Get the properties of ISP for private mask
 * @param[out] attr pointer to rts_mask_attr
 * @return 0 : success, minus : fail
 */
int rts_av_get_mask(struct rts_mask_attr *attr);

/**
 * @brief Set the properties of ISP for private mask
 * @param[out] attr pointer to rts_mask_attr
 * @return 0 : success, minus : fail
 */
int rts_av_set_mask(struct rts_mask_attr *attr);
/*!@}*/

#ifdef __cplusplus
}
#endif
#endif