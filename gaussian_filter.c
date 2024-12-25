#include "gaussian_filter.h"

#include <stdlib.h>

#include "config.h"
#include "pixel.h"
#include "image.h"

void get_3x3_kernel(unsigned char* shift, unsigned char* kernel_size, double*** destination) {
    *shift = 1;
    *kernel_size = *shift * 2 + 1;
    /*
    kernel: 1/16*matrix
    1 2 1
    2 4 2
    1 2 1
    */
    const double kernel[3][3] = {
        {0.0625, 0.125, 0.0625},
        {0.125, 0.25, 0.125},
        {0.0625, 0.125, 0.062}
    };
    *destination = malloc((*kernel_size) * sizeof(double*));
    for (int i = 0; i < *kernel_size; ++i) {
        (*destination)[i] = malloc((*kernel_size) * sizeof(double));
        for (int j = 0; j < *kernel_size; ++j) {
            (*destination)[i][j] = kernel[i][j];
        }
    }
    return;
}

void get_5x5_kernel(unsigned char* shift, unsigned char* kernel_size, double*** destination) {
    *shift = 2;
    *kernel_size = *shift * 2 + 1;
    /*
    kernel: 1/273*matrix
    1 4  7  4  1
    4 16 26 16 4
    7 26 41 26 7
    4 16 26 16 4
    1 4  7  4  1
    */
    const double kernel[5][5] = {
        {0.003663003663003663, 0.014652014652014652, 0.02564102564102564, 0.014652014652014652, 0.003663003663003663},
        {0.014652014652014652, 0.05860805860805861, 0.09523809523809523, 0.05860805860805861, 0.014652014652014652},
        {0.02564102564102564, 0.09523809523809523, 0.15018315018315018, 0.09523809523809523, 0.02564102564102564},
        {0.014652014652014652, 0.05860805860805861, 0.09523809523809523, 0.05860805860805861, 0.014652014652014652},
        {0.003663003663003663, 0.014652014652014652, 0.02564102564102564, 0.014652014652014652, 0.003663003663003663},
    };
    *destination = malloc((*kernel_size) * sizeof(double*));
    for (int i = 0; i < *kernel_size; ++i) {
        (*destination)[i] = malloc((*kernel_size) * sizeof(double));
        for (int j = 0; j < *kernel_size; ++j) {
            (*destination)[i][j] = kernel[i][j];
        }
    }
    return;
}

void get_5x5_low_value_kernel(unsigned char* shift, unsigned char* kernel_size, double*** destination) {
    *shift = 2;
    *kernel_size = *shift * 2 + 1;
    /*
    kernel: 1/159*matrix
    2 4  5  4  2
    4 9  12 9  4
    5 12 15 12 5
    4 9  12 9  4
    2 4  5  4  2
    */
    const double kernel[5][5] = {
        {0.012578616352201259, 0.025157232704402517, 0.031446540880503145, 0.025157232704402517, 0.012578616352201259},
        {0.025157232704402517, 0.05660377358490566, 0.07547169811320754, 0.05660377358490566, 0.025157232704402517},
        {0.031446540880503145, 0.07547169811320754, 0.09433962264150944, 0.07547169811320754, 0.031446540880503145},
        {0.025157232704402517, 0.05660377358490566, 0.07547169811320754, 0.05660377358490566, 0.025157232704402517},
        {0.012578616352201259, 0.025157232704402517, 0.031446540880503145, 0.025157232704402517, 0.012578616352201259}
    };
    *destination = malloc((*kernel_size) * sizeof(double*));
    for (int i = 0; i < *kernel_size; ++i) {
        (*destination)[i] = malloc((*kernel_size) * sizeof(double));
        for (int j = 0; j < *kernel_size; ++j) {
            (*destination)[i][j] = kernel[i][j];
        }
    }
    return;
}

void free_kernel(double** kernel, unsigned char kernel_size) {
    for (unsigned char i = 0; i < kernel_size; ++i) {
        free(kernel[i]);
    }
    free(kernel);
    return;
}

void get_kernel(unsigned char* shift, unsigned char* kernel_size, double*** destination, GaussianKernels kernel_type) {
    switch (kernel_type) {
        case GaussianKernel_3x3:
            get_3x3_kernel(shift, kernel_size, destination);
            break;
        case GaussianKernel_5x5:
            get_5x5_kernel(shift, kernel_size, destination);
            break;
        case GaussianKernel_5x5_low_value:
            get_5x5_low_value_kernel(shift, kernel_size, destination);
            break;
        default:
            get_5x5_kernel(shift, kernel_size, destination);
            break;
    }
    return;
}

GrayPixel** gaussian_filter(GrayPixel** source, unsigned width, unsigned height, GaussianKernels kernel_type) {
    unsigned char shift, kernel_size;
    double** kernel;
    get_kernel(&shift, &kernel_size, &kernel, kernel_type);
    GrayPixel** image = malloc_gray_image(width, height);
    blacken_boundaries(image, width, height, shift);
    for (unsigned x = shift; x < width - shift; ++x) {
        for (unsigned y = shift; y < height - shift; ++y) {
            double sum = 0.0;
            for (int i = 0; i < kernel_size; ++i) {
                for (int j = 0; j < kernel_size; ++j) {
                    sum += source[x + i - shift][y + j - shift].color * kernel[j][i];
                }
            }
            image[x][y].color = (unsigned char)sum;
            image[x][y].alpha = 255;
        }
    }
    free_kernel(kernel, kernel_size);
    return image;
}