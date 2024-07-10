#include <stdio.h>

#include "lodepng.h"

#include "config.h"
#include "random.h"
#include "cstring.h"
#include "pixel.h"
#include "image.h"
#include "gaussian_filter.h"
#include "median_filter.h"
#include "sobel_filter.h"
#include "segmentation.h"

int main() {
    init_random(8);
    mkdir("output_images");
    Config config = load_config(default_config_name);
    printf("Config settings:\n");
    print_config(config, stdout);
    printf("\n");
    char path[100];
    printf("Input path to the png image:\n");
    scan(path);
    unsigned char* encoded_image;
    unsigned error, width, height;
    error = lodepng_decode32_file(&encoded_image, &width, &height, path);
    if (error) {
        printf("Unable to read file, error: %d\n", error);
        return error;
    }
    Pixel** color_image = decode_image(encoded_image, width, height);
    GrayPixel** gray_image = to_gray(color_image, width, height);
    GrayPixel** median_image = gray_image;
    if (config.median_filter == MedianFilter_enabled) {
        median_image = median_filter(gray_image, width, height);
    }
    GrayPixel** gauss_image = gaussian_filter(median_image, width, height, config.gaussian_kernel);
    GrayPixel** sobel_image = sobel_filter(gauss_image, width, height, config.sobel_kernel);
    Pixel** segmented_image = segment_image(sobel_image, width, height, config.boundaries_detection_strength, config.boundaries_radius);

    free_image(color_image, width);
    free_gray_image(gray_image, width);
    if (config.median_filter == MedianFilter_enabled) {
        save_gray_image(median_image, width, height, "output_images/median.png");
        free_gray_image(median_image, width);
    }
    save_gray_image(gauss_image, width, height, "output_images/gauss.png");
    free_gray_image(gauss_image, width);
    save_gray_image(sobel_image, width, height, "output_images/sobel.png");
    free_gray_image(sobel_image, width);
    save_image(segmented_image, width, height, "output_images/segmented.png");
    free_image(segmented_image, width);

    printf("Images saved\n");
    return 0;
}