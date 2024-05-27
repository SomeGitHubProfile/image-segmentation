#pragma once

#include "config.h"
#include "pixel.h"

#ifndef GAUSSIAN_FILTER
#define GAUSSIAN_FILTER
GrayPixel** gaussian_filter(GrayPixel** source, unsigned width, unsigned height, GaussianKernels kernel_type);
#endif
