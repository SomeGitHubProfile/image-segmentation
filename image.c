#include "image.h"

#include <stdlib.h>
#include <math.h>

#include "lodepng.h"

#include "pixel.h"

Pixel** decode_image(unsigned char* source, unsigned width, unsigned height) {
    Pixel** image = malloc(width * sizeof(Pixel*));
    for (unsigned x = 0; x < width; ++x) {
        image[x] = malloc(height * sizeof(Pixel));
    }
    for (int i = 0; i < width * height; ++i) {
        image[i % width][i / width].red = source[i * 4];
        image[i % width][i / width].green = source[i * 4 + 1];
        image[i % width][i / width].blue = source[i * 4 + 2];
        image[i % width][i / width].alpha = source[i * 4 + 3];
    }
    return image;
}

Pixel** malloc_image(signed width, unsigned height) {
    Pixel** image = malloc(width * sizeof(Pixel*));
    for (unsigned x = 0; x < width; ++x) {
        image[x] = malloc(height * sizeof(Pixel));
    }
    return image;
}

GrayPixel** malloc_gray_image(unsigned width, unsigned height) {
    GrayPixel** image = malloc(width * sizeof(GrayPixel*));
    for (unsigned x = 0; x < width; ++x) {
        image[x] = malloc(height * sizeof(GrayPixel));
    }
    return image;
}

void free_gray_image(GrayPixel** image, unsigned width) {
    for (unsigned x = 0; x < width; ++x) {
        free(image[x]);
    }
    free(image);
    return;
}

void free_image(Pixel** image, unsigned width) {
    for (unsigned x = 0; x < width; ++x) {
        free(image[x]);
    }
    free(image);
    return;
}

void save_gray_image(GrayPixel** image, unsigned width, unsigned height, const char* path) {
    unsigned char* encoded = encode_gray_image(image, width, height);
    lodepng_encode32_file(path, encoded, width, height);
    free(encoded);
    return;
}

void save_image(Pixel** image, unsigned width, unsigned height, const char* path) {
    unsigned char* encoded = encode_image(image, width, height);
    lodepng_encode32_file(path, encoded, width, height);
    free(encoded);
    return;
}

GrayPixel** to_gray(Pixel** source, unsigned width, unsigned height) {
    GrayPixel** image = malloc_gray_image(width, height);
    for (unsigned x = 0; x < width; ++x) {
        for (unsigned y = 0; y < height; ++y) {
            double red = source[x][y].red / 255.0;
            double green = source[x][y].green / 255.0;
            double blue = source[x][y].blue / 255.0;
            double c = 0.2126 * red + 0.7152 * green + 0.0722 * blue;
            if (c <= 0.0031308) {
                image[x][y].color = (char)(12.92 * 255 * c);
            } else {
                image[x][y].color = (char)((1.055 * pow(c, 0.4166666666666667) - 0.055) * 255);
            }
            image[x][y].alpha = source[x][y].alpha;
        }
    }
    return image;
}

void blacken_boundaries(GrayPixel** image, unsigned width, unsigned height, int shift) {
    for (unsigned x = 0; x < width; ++x) {
        for (int y = 0; y < shift; ++y) {
            image[x][y].color = image[x][height - y - 1].color = 0;
            image[x][y].alpha = image[x][height - y - 1].alpha = 255;
        }
    }
    for (int x = 0; x < shift; ++x) {
        for (unsigned y = 0; y < height; ++y) {
            image[x][y].color = image[width - x - 1][y].color = 0;
            image[x][y].alpha = image[width - x - 1][y].alpha = 255;
        }
    }
    return;
}

unsigned char* encode_gray_image(GrayPixel** image, unsigned width, unsigned height) {
    unsigned char* encoded = malloc(4 * width * height * sizeof(unsigned char));
    for (int i = 0; i < width * height; ++i) {
        encoded[i * 4] = image[i % width][i / width].color;
        encoded[i * 4 + 1] = image[i % width][i / width].color;
        encoded[i * 4 + 2] = image[i % width][i / width].color;
        encoded[i * 4 + 3] = image[i % width][i / width].alpha;
    }
    return encoded;
}

unsigned char* encode_image(Pixel** image, unsigned width, unsigned height) {
    unsigned char* encoded = malloc(4 * width * height * sizeof(unsigned char));
    for (int i = 0; i < width * height; ++i) {
        encoded[i * 4] = image[i % width][i / width].red;
        encoded[i * 4 + 1] = image[i % width][i / width].green;
        encoded[i * 4 + 2] = image[i % width][i / width].blue;
        encoded[i * 4 + 3] = image[i % width][i / width].alpha;
    }
    return encoded;
}