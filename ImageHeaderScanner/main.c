#include <stdio.h>
#include <string.h>
#include <math.h>
#include "headers\\image_structs.h"
#include "headers\bmp_scanner.h"


int main(void)
{
	char* file_name = "pictures\\snail.bmp";

	
	struct BMPHeader bmp_header;
	struct BMPHeader* p_bmp_header = &bmp_header;
	if (scan_bmp_header(file_name, p_bmp_header) != 0)
	{
		printf("Something went wrong while scanning the BMP header...");
		return -1;
	}

	printf("--------%s---------\n\n", file_name);
	printf("File Size: %i Bytes\n", p_bmp_header->size);
	printf("Height: %ipx\n", p_bmp_header->height_px);
	printf("Width: %ipx\n", p_bmp_header->width_px);
	printf("Compression Method: %i", p_bmp_header->compression);
	switch (p_bmp_header->compression)
	{
		case 0:
			printf(" (no compression)\n");
			break;

		case 1:
			printf(" (RLE 8-bit/pixel)\n");
			break;
		
		case 2:
			printf(" (RLE 4-bit/pixel)\n");
			break;

		default:
			printf(" (Unknown/Other)\n");
			break;
	}
	printf("Number of bits per pixel: %i\n", p_bmp_header->bits_per_pixel);
	printf("Number of Colors: %i", p_bmp_header->num_colors);
	if (p_bmp_header->num_colors == 0)
	{
		printf(" (placeholder zero detected, number of colors is %.00lf)\n", pow(2, p_bmp_header->bits_per_pixel));
	}
	else
	{
		printf("\n");
	}
	printf("Image Size in Bytes: %i", p_bmp_header->image_size_bytes);
	if (p_bmp_header->image_size_bytes == 0)
	{
		printf(" (placeholder zero detected, bitmap is BI_RGB)\n");
	}
	else
	{
		printf("\n");
	}



	return 0;
}