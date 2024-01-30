#pragma once

#include <stdint.h>

typedef struct BMPHeader {		// Total: 54 Bytes
	uint16_t type;				// Magic Identifier: 0x4d42
	uint32_t size;
	uint16_t reserved1;			// Not used
	uint16_t reserved2;			// Not used
	uint32_t offset;			// Offset to image data in bytes
	uint32_t dib_header_size;	// DIB header size in bytes
	int32_t  width_px;			// Width of the image
	int32_t  height_px;			// Height of the image
	uint32_t num_planes;		// Number of color planes
	uint16_t bits_per_pixel;
	uint32_t compression;
	uint32_t image_size_bytes;	// Image Size in Bytes
	int32_t  x_resolution_ppm;
	int32_t  y_resolution_ppm;
	uint32_t num_colors;		// Number of colors
	uint32_t important_colors;
} BMPHeader;


typedef struct BMPImage {
	BMPHeader header;
	unsigned char* data;
} BMPImage;
