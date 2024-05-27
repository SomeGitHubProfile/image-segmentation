#include "median_filter.h"

#include "pixel.h"
#include "image.h"

void sort_pair(unsigned char* a, unsigned char* b) {
    *a ^= *b;
    *b ^= *a;
    *a ^= *b;
    return;
}

unsigned char get_median(unsigned char* array) {
    sort_pair(array + 1, array + 2); sort_pair(array + 4, array + 5); sort_pair(array + 7, array + 8);
    sort_pair(array + 0, array + 1); sort_pair(array + 3, array + 4); sort_pair(array + 6, array + 7);
    sort_pair(array + 1, array + 2); sort_pair(array + 4, array + 5); sort_pair(array + 7, array + 8);
    sort_pair(array + 0, array + 3); sort_pair(array + 5, array + 8); sort_pair(array + 4, array + 7);
    sort_pair(array + 3, array + 6); sort_pair(array + 1, array + 4); sort_pair(array + 2, array + 5);
    sort_pair(array + 4, array + 7); sort_pair(array + 4, array + 2); sort_pair(array + 6, array + 4);
    sort_pair(array + 4, array + 2);
    return array[4];
}

GrayPixel** median_filter(GrayPixel** source, unsigned width, unsigned height) {
    int shift = 1;
    unsigned char buffer[9];
    GrayPixel** image = malloc_gray_image(width, height);
    blacken_boundaries(image, width, height, shift);
    for (unsigned x = shift; x < width - shift; ++x) {
        for (unsigned y = shift; y < height - shift; ++y) {
            int cnt = 0;
            for (int i = -1; i <= 1; ++i) {
                for (int j = -1; j <= 1; ++j) {
                    buffer[cnt++] = source[x + i][y + j].color;
                }
            }
            image[x][y].color = get_median(buffer);
            image[x][y].alpha = 255;
        }
    }
    return image;
}