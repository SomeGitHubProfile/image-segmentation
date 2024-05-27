#pragma once

#ifndef PIXEL
#define PIXEL
typedef struct Pixel {
    unsigned char red, green, blue, alpha;
} Pixel;

typedef struct GrayPixel {
    unsigned char color;
    unsigned char alpha;
} GrayPixel;
#endif