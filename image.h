#pragma once

#include "pixel.h"

#ifndef IMAGE
#define IMAGE
Pixel** decode_image(unsigned char* source, unsigned width, unsigned height);
Pixel** malloc_image(signed width, unsigned height);
GrayPixel** malloc_gray_image(unsigned width, unsigned height);
GrayPixel** to_gray(Pixel** source, unsigned width, unsigned height);
void blacken_boundaries(GrayPixel** image, unsigned width, unsigned height, int shift);
unsigned char* encode_gray_image(GrayPixel** image, unsigned width, unsigned height);
unsigned char* encode_image(Pixel** image, unsigned width, unsigned height);
void free_gray_image(GrayPixel** image, unsigned width);
void free_image(Pixel** image, unsigned width);
#endif