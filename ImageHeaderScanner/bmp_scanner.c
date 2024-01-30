#define  _CRT_SECURE_NO_WARNINGS


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "image_structs.h"


#define NEXTBYTE() getc(infile)


/*

									Notes on BMP Headers:

 Modern BMP headers all follow the same format, which is 14 bytes of metadata about the file,
 and then 40 bytes of information about the image itself. We iterate through this header 
 similar to how IJG does in libjpeg. We start at the very beginning, and go byte by byte.


 BMP headers are little endian, so we have to do some bit manipulation to get the proper values.
 Each time more than one byte of data is read at a time, we shift the bits to the left and add the
 results.


 Every byte beyond one, we need to shift the bits by 8 * x, where x is their position in the byte sequence. 
 So if we are reading 4 bytes:

		int bytes[] = { byte1, byte2, byte3, byte4 }

		result = bytes[0] + (bytes[1] << 8) + (bytes[2] << 16) + (bytes[3] << 24);


 This little snippet is used in our read_4_bytes() function.


 This script doesn't go into the image data at this time, but with the information gathered, it
 wouldn't be too much of a stretch to do so.

*/


static int identify_bmp();
static int read_1_byte();
static int read_2_bytes();
static int read_4_bytes();
static int get_file_size();
static int get_offset();
static int get_dib_header_size();
static int populate_dib_information(struct BMPHeader* p_bmp);


FILE* infile;


/*

	This function is fed a pointer to a BMPHeader struct created in the main.c code, who
	it directly modifies. All error codes are -1 for now.

*/
extern int scan_bmp_header(char* file_name, struct BMPHeader* p_bmp)
{
	infile = fopen(file_name, "rb");
	if (!infile)
	{
		return -1;
	}


	// Step 1: Look for Magic Identifier
	// Step 2: Get File Size
	// Step 3: Skip both reserved blocks
	// Step 4: Get the Offset to the image data
	// Step 5: Get the DIB Header size
	// Step 6: Get Height/Width of the Image
	// Step 7: Get the number of color planes
	// Step 8: get the number of bits per pixel
	// Step 9: Get the compression method, if any
	// Step 10: Get the size of the raw bitmap data
	// Step 11: Get the Horizontal PPM
	// Step 12: Get the Vertical PPM
	// Step 13: Get the number of Colors in the Color Pallete
	// Step 14: Get the Number of Important Colors


		
	if (identify_bmp() != 0)			// Step 1
	{
		return -1;
	}


	
	int file_size = get_file_size();	// Step 2
	if (file_size == -1)
	{
		return -1;
	}
	p_bmp->size = file_size;


	
	int header_offset = get_offset();	// Step 3 and 4 (we skipped the reserved blocks by using fseek)
	if (header_offset == -1)
	{
		return -1;
	}
	p_bmp->offset = header_offset;



	int dib_header_size = get_dib_header_size();		// Step 5 (this should always be 40)
	if (dib_header_size == -1)
	{
		printf("Non-normal DIB header size detected. Exiting...\n");
		return -1;
	}
	p_bmp->dib_header_size = dib_header_size;


	/* 
	
		At this point, we are iterating the DIB header. Since the cursor is
		sitting on the width after calling get_dib_header_size(), we can
		just call our read_X_bytes functions to get the values we need instead of
		making 7 new functions. 

	*/

	populate_dib_information(p_bmp);



	return 0;
}


/* Helper Functions */
static int read_1_byte()
{
	int c;
	c = NEXTBYTE();


	return c;
}

static int read_2_bytes()
{
	int c1;
	int c2;

	c1 = NEXTBYTE();
	c2 = NEXTBYTE();


	return (uint32_t)c1 + ((uint32_t)c2 << 8);
}

static int read_4_bytes()
{
	int c1, c2, c3, c4;
	c1 = NEXTBYTE();
	c2 = NEXTBYTE();
	c3 = NEXTBYTE();
	c4 = NEXTBYTE();

	int bytes[] = { c1 , c2, c3, c4 };

	for (int i = 0; i < 5; i++)
	{
		if (bytes[i] == EOF)
		{
			return -1;
		}
	}
	int value = bytes[0] + (bytes[1] << 8) + (bytes[2] << 16) + (bytes[3] << 24);


	return (uint32_t)value;
}

static int identify_bmp()
{
	int c1;
	int c2;

	c1 = NEXTBYTE();
	c2 = NEXTBYTE();

	if (c1 == 0x42 || c2 == 0x4D)
	{
		return 0;
	}
	else
	{
		printf("BMP not detected...\n");
		printf("Exiting...\n");
		return -1;
	}


}

static int get_file_size()
{
	int c1;

	if (fseek(infile, 2, SEEK_SET) != 0)
	{
		return -1;
	}
	c1 = read_4_bytes();


	return c1;
}

static int get_offset()
{
	if (fseek(infile, 10, SEEK_SET) != 0)
	{
		return -1;
	}


	return read_4_bytes();
}

static int get_dib_header_size()
{
	if (fseek(infile, 14, SEEK_SET) != 0)
	{
		return -1;
	}
	int c = read_4_bytes();


	return c;
}

static int populate_dib_information(struct BMPHeader* p_bmp)
{
	if (fseek(infile, 18, SEEK_SET) != 0)
	{
		return -1;
	}

	// Step 6-14
	p_bmp->width_px = read_4_bytes();
	p_bmp->height_px = read_4_bytes();
	p_bmp->num_planes = read_2_bytes();
	p_bmp->bits_per_pixel = read_2_bytes();
	p_bmp->compression = read_4_bytes();
	p_bmp->image_size_bytes = read_4_bytes();
	p_bmp->x_resolution_ppm = read_4_bytes();
	p_bmp->y_resolution_ppm = read_4_bytes();
	p_bmp->num_colors = read_4_bytes();
	p_bmp->important_colors = read_4_bytes();

	return 0;
}