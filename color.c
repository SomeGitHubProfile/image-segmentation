#include "color.h"

#include <math.h>

#include "pixel.h"
#include "random.h"

#define number_of_colors 20

unsigned char index = 0;

Pixel get_next_color() {
    Pixel colors[number_of_colors] = {
        {255, 0, 0, 255},
        {0, 255, 0, 255},
        {0, 0, 255, 255},
        {233, 30, 99, 255},
        {255, 0, 255, 255},
        {156, 39, 176, 255},
        {29, 233, 182, 255},
        {0, 230, 118, 255},
        {238, 255, 65, 255},
        {33, 150, 243, 255},
        {248, 187, 208, 255},
        {41, 182, 246, 255},
        {76, 175, 80, 255},
        {100, 221, 23, 255},
        {121, 85, 72, 255},
        {26, 35, 126, 255},
        {0, 137, 123, 255},
        {0, 188, 212, 255},
        {105, 240, 174, 255},
        {255, 171, 0, 255}
    };
    return colors[index++ % number_of_colors];
}

double convert_hue(double p, double q, double t) {
    if (t < 0) {
        t += 1;
    } else if (t > 1) {
        t -= 1;
    }
    if (t < 1.0 / 6.0) {
        return p + (q - p) * 6.0 * t;
    }
    if (t < 0.5) {
        return q;
    }
    if (t < 2.0 / 3.0) {
        return p + (q - p) * (2.0 / 3.0 - t) * 6.0;
    }
    return p;
}

// hsl: [360, 100, 100]
// rgb: [255, 255, 255]
Pixel hsl_to_rgba(unsigned hue, unsigned saturation, unsigned lightness) {
    double h = hue / 360.0;
    double s = saturation / 100.0;
    double l = lightness / 100.0;
    Pixel color;
    color.alpha = 255;
    if (saturation == 0) {
        color.red = color.green = color.blue = round(l * 255);
        return color;
    }
    const double q = lightness < 50 ? l * (1.0 + s) : l + s - l * s;
    const double p = 2 * l - q;
    color.red = round(convert_hue(p, q, h + 1.0 / 3.0) * 255);
    color.green = round(convert_hue(p, q, h) * 255);
    color.blue = round(convert_hue(p, q, h - 1.0 / 3.0) * 255);
    return color;
}

Pixel generate_random_color() {
    if (!randint_between(0, 2)) {
        return get_next_color();
    }
    const unsigned hue = unsigned_randint_between(0, 361);
    const unsigned saturation = unsigned_randint_between(60, 101);
    const unsigned lightness = unsigned_randint_between(50, 101);
    return hsl_to_rgba(hue, saturation, lightness);
}