#pragma once

#include <stdio.h>
#include <stdbool.h>

#ifndef CONFIG
#define CONFIG

typedef enum MedianFilterStates {
    MedianFilter_enabled,
    MedianFilter_disabled
} MedianFilterStates;

typedef enum GaussianKernels {
    GaussianKernel_3x3,
    GaussianKernel_5x5,
    GaussianKernel_5x5_low_value
} GaussianKernels;

typedef enum SobelKernels {
    SobelKernel_3x3,
    SobelKernel_5x5
} SobelKernels;

enum Boundaries {
    Boundaries_min_value = 0,
    Boundaries_max_value = 255
} Boundaries;

typedef struct Config {
    char* config_name;
    MedianFilterStates median_filter;
    GaussianKernels gaussian_kernel;
    SobelKernels sobel_kernel;
    int boundaries_detection_strength;
    int boundaries_radius;
} Config;

#define default_config_name "default.cfg"
Config load_config(const char* path);
void print_config(Config config, FILE* const stream);
#endif
