#include "sobel_filter.h"

#include <stdlib.h>
#include <math.h>

#include "config.h"
#include "pixel.h"
#include "image.h"

unsigned char clamp_sum(double sum) {
    if (sum < 0.0) {
        return 0;
    }
    if (sum > 255.0) {
        return 255;
    }
    return round(sum);
}

void get_3x3_kernels(char* shift, char* kernel_size, char*** horizontal_destination, char*** vertical_destination) {
    *shift = 1;
    *kernel_size = *shift * 2 + 1;
    const char horizontal_kernel[3][3] = {
        {+1, +2, +1},
        {+0, +0, +0},
        {-1, -2, -1}
    };
    const char vertical_kernel[3][3] = {
        {-1, +0, +1},
        {-2, +0, +2},
        {-1, +0, +1}
    };
    *horizontal_destination = malloc((*kernel_size) * (*kernel_size) * sizeof(double*));
    *vertical_destination = malloc((*kernel_size) * (*kernel_size) * sizeof(double*));
    for (int i = 0; i < *kernel_size; ++i) {
        (*horizontal_destination)[i] = malloc((*kernel_size) * sizeof(double));
        (*vertical_destination)[i] = malloc((*kernel_size) * sizeof(double));
        for (int j = 0; j < *kernel_size; ++j) {
            (*horizontal_destination)[i][j] = horizontal_kernel[i][j];
            (*vertical_destination)[i][j] = vertical_kernel[i][j];
        }
    }
    return;
}

void get_5x5_kernels(char* shift, char* kernel_size, char*** horizontal_destination, char*** vertical_destination) {
    *shift = 2;
    *kernel_size = *shift * 2 + 1;
    const char horizontal_kernel[5][5] = {
        {+2, +2, +4, +2, +2},
        {+1, +1, +2, +1, +1},
        {+0, +0, +0, +0, +0},
        {-1, -1, -2, -1, -1},
        {-2, -2, -4, -2, -2}
    };
    const char vertical_kernel[5][5] = {
        {+2, +1, 0, -1, -2},
        {+2, +1, 0, -1, -2},
        {+4, +2, 0, -2, -4},
        {+2, +1, 0, -1, -2},
        {+2, +1, 0, -1, -2}
    };
    *horizontal_destination = malloc((*kernel_size) * (*kernel_size) * sizeof(double*));
    *vertical_destination = malloc((*kernel_size) * (*kernel_size) * sizeof(double*));
    for (int i = 0; i < *kernel_size; ++i) {
        (*horizontal_destination)[i] = malloc((*kernel_size) * sizeof(double));
        (*vertical_destination)[i] = malloc((*kernel_size) * sizeof(double));
        for (int j = 0; j < *kernel_size; ++j) {
            (*horizontal_destination)[i][j] = horizontal_kernel[i][j];
            (*vertical_destination)[i][j] = vertical_kernel[i][j];
        }
    }
    return;
}

void get_kernels(char* shift, char* kernel_size, char*** horizontal_destination, char*** vertical_destination, SobelKernels kernel_type) {
    switch (kernel_type) {
        case SobelKernel_3x3:
            get_3x3_kernels(shift, kernel_size, horizontal_destination, vertical_destination);
            break;
        case SobelKernel_5x5:
            get_5x5_kernels(shift, kernel_size, horizontal_destination, vertical_destination);
            break;
        default:
            get_5x5_kernels(shift, kernel_size, horizontal_destination, vertical_destination);
            break;
    }
    return;
}

GrayPixel** sobel_filter(GrayPixel** source, unsigned width, unsigned height, SobelKernels kernel_type) {
    char shift, kernel_size;
    char** horizontal_kernel;
    char** vertical_kernel;
    get_kernels(&shift, &kernel_size, &horizontal_kernel, &vertical_kernel, kernel_type);
    GrayPixel** image = malloc_gray_image(width, height);
    blacken_boundaries(image, width, height, shift);
    for (unsigned x = shift; x < width - shift; ++x) {
        for (unsigned y = shift; y < height - shift; ++y) {
            int horizontal_sum = 0, vertical_sum = 0;
            for (int i = 0; i < kernel_size; ++i) {
                for (int j = 0; j < kernel_size; ++j) {
                    horizontal_sum += source[x + i - shift][y + j - shift].color * horizontal_kernel[i][j];
                    vertical_sum += source[x + i - shift][y + j - shift].color * vertical_kernel[i][j];
                }
            }
            image[x][y].color = clamp_sum(sqrt(horizontal_sum * horizontal_sum + vertical_sum * vertical_sum));
            image[x][y].alpha = 255;
        }
    }
    return image;
}