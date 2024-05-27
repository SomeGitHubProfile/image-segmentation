#pragma once

#include "pixel.h"

#ifndef MEDIAN_FILTER
#define MEDIAN_FILTER
GrayPixel** median_filter(GrayPixel** source, unsigned width, unsigned height);
#endif