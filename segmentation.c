#include "segmentation.h"

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "queue.h"
#include "pixel.h"
#include "image.h"
#include "color.h"

bool invalid_cell(unsigned x, unsigned y, unsigned width, unsigned height, bool** visited) {
    return x < 0 || width <= x || y < 0 || height <= y;
}

bool is_boundary(GrayPixel gray_pixel, unsigned char boundaries_detection_strength) {
    return gray_pixel.color >= boundaries_detection_strength;
}

bool is_near_boundary(GrayPixel** source,
                      unsigned width,
                      unsigned height,
                      unsigned init_x,
                      unsigned init_y,
                      bool** visited,
                      unsigned char boundaries_detection_strength,
                      unsigned char boundaries_radius
) {
    if (is_boundary(source[init_x][init_y], boundaries_detection_strength)) {
        return true;
    }
    int cnt = 0;
    for (int i = -boundaries_radius; i <= boundaries_radius; ++i) {
        for (int j = -boundaries_radius; j <= boundaries_radius; ++j) {
            unsigned x = init_x + i;
            unsigned y = init_y + j;
            if (invalid_cell(x, y, width, height, visited)) {
                continue;
            }
            cnt += is_boundary(source[x][y], boundaries_detection_strength);
        }
    }
    return cnt > boundaries_radius;
}

void bfs(Pixel** image,
         GrayPixel** source,
         unsigned width,
         unsigned height,
         unsigned init_x,
         unsigned init_y,
         bool** visited,
         unsigned char boundaries_detection_strength,
         unsigned char boundaries_radius,
         Pixel color,
         Pixel boundary_color
) {
    Queue* queue = create_queue();
    push(queue, init_x, init_y);
    while (queue_size(queue)) {
        Coords coords = pop(queue);
        for (int i = -1; i <= 1; ++i) {
            for (int j = -1; j <= 1; ++j) {
                unsigned x = coords.x + i;
                unsigned y = coords.y + j;
                if (invalid_cell(x, y, width, height, visited) || i == 0 && j == 0 || visited[x][y]) {
                    continue;
                }
                if (is_near_boundary(source, width, height, x, y, visited, boundaries_detection_strength, boundaries_radius)) {
                    image[x][y] = boundary_color;
                } else {
                    image[x][y] = color;
                    push(queue, x, y);
                }
                visited[x][y] = true;
            }
        }
    }
    return;
}

Pixel** segment_image(GrayPixel** source,
                      unsigned width,
                      unsigned height,
                      unsigned char boundaries_detection_strength,
                      unsigned char boundaries_radius
) {
    Pixel** image = malloc_image(width, height);
    bool** visited = malloc(width * sizeof(char*));
    for (unsigned x = 0; x < width; ++x) {
        visited[x] = calloc(height, sizeof(char));
    }
    Pixel boundary_color = {0, 0, 0, 255};
    unsigned number_of_segments = 0;
    for (unsigned x = 0; x < width; ++x) {
        for (unsigned y = 0; y < height; ++y) {
            if (is_boundary(source[x][y], boundaries_detection_strength)) {
                image[x][y] = boundary_color;
                visited[x][y] = true;
            }
            if (!visited[x][y]) {
                bfs(
                    image,
                    source,
                    width,
                    height,
                    x,
                    y,
                    visited,
                    boundaries_detection_strength,
                    boundaries_radius,
                    generate_random_color(),
                    boundary_color
                );
                ++number_of_segments;
            }
        }
    }
    printf("Number of segments: %u\n", number_of_segments);
    return image;
}
