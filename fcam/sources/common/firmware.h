#ifndef __FIRMWARE_H__
#define __FIRMWARE_H__

#include <stdint.h>
#include <string> // Include this for std::string
#include "app_data.hpp"

using std::string; // Add this line if you want to use `string` without `std::`

typedef struct {
    uint32_t bin_len;
    std::string checksum; // Use std::string
} fileInfo_t;

extern int firmware_get_info(fileInfo_t *fh, const char *bin_file_path);
extern int firmware_read(uint8_t* data, uint32_t cursor, uint32_t size, const char* bin_file_path);

#endif //__FIRMWARE_H__
