#pragma once

#include "config.h"
#include "pixel.h"

#ifndef SOBEL_FILTER
#define SOBEL_FILTER
GrayPixel** sobel_filter(GrayPixel** source, unsigned width, unsigned height, SobelKernels kernel_type);
#endif
