/*
 * Copyright (C) 2011 <fwhacking|gmail:com>
 *
 * This is free software, licensed under the GNU General Public License v2.
 * See /LICENSE for more information.
 *
 */

#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "gsimg.h"

static void print_usage(const char *name)
{
	printf("Usage: %s firmware\n", name);
}

int main(int argc, char **argv)
{
	FILE *fd;
	GS_HEADER *hdr;
	unsigned char *fp;
	long size;

	if (argc != 2)
	{
		print_usage(argv[0]);
		exit(1);
	}

	fd = fopen(argv[1], "rb");
	if (fd == NULL)
	{
		printf("Could not read the firmware file '%s'\n", argv[1]);
		print_usage(argv[0]);
		exit(1);
	}

	size = fseek(fd, 0L, SEEK_END);
	size = ftell(fd);
	//~ printf("Firmware file size : %ld bytes\n\n", size);
	fseek(fd, 0L, SEEK_SET);

	fp = malloc(size);
	fread(fp, size, 1, fd);
	fclose(fd);

	hdr = (GS_HEADER *) fp;

	printf("HEADER\n");
	printf("-------------------------------------\n");
	printf("size\t\t%d\n", SWAP_BE32(hdr->size) * 2);
	printf("checksum\t0x%04X\n", SWAP_BE16(hdr->checksum));
	printf("version\t\t%d.%d.%d.%d\n", hdr->version1, hdr->version2, hdr->version3, hdr->version4);
	printf("build date\t%d-%02d-%02d %02d:%02d\n", SWAP_BE16(hdr->build_year), hdr->build_month, hdr->build_day, hdr->build_hour, hdr->build_minute);
	printf("name\t\t%s\n", hdr->name);
	printf("-------------------------------------\n\n");

	free(fp);

	exit(0);
}
