/*
 * Copyright (C) 2011 <fwhacking|gmail:com>
 *
 * This is free software, licensed under the GNU General Public License v2.
 * See /LICENSE for more information.
 *
 */

#ifndef _GSIMG_H_
#define _GSIMG_H_

#include <byteswap.h>
#include <endian.h>

#define PACKED __attribute__ ((__packed__))

#ifdef __BIG_ENDIAN__
# define GS_BIG_ENDIAN 1
# define GS_LITTLE_ENDIAN 0
#elif __BYTE_ORDER == __BIG_ENDIAN
# define GS_BIG_ENDIAN 1
# define GS_LITTLE_ENDIAN 0
#else
# define GS_BIG_ENDIAN 0
# define GS_LITTLE_ENDIAN 1
#endif

#if GS_BIG_ENDIAN
#define SWAP_BE16(x) (x)
#define SWAP_BE32(x) (x)
#else
#define SWAP_BE16(x) bswap_16(x)
#define SWAP_BE32(x) bswap_32(x)
#endif

typedef struct _GS_HEADER
{
	uint32_t size;
	uint16_t checksum;
	uint8_t version1;
	uint8_t version2;
	uint8_t version3;
	uint8_t version4;
	uint16_t build_year;
	uint8_t build_month;
	uint8_t build_day;
	uint8_t build_hour;
	uint8_t build_minute;
	char name[16];
} GS_HEADER;

#endif // _GSIMG_H_
