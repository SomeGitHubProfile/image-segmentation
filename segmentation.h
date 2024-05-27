#pragma once

#include "pixel.h"

#ifndef SEGMENTATION
#define SEGMENTATION
Pixel** segment_image(GrayPixel** source, unsigned width, unsigned height, unsigned char boundaries_detection_strength, unsigned char boundaries_radius);
#endif
