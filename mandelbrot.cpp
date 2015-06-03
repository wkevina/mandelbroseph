//
// Created by Kevin Ward on 6/2/15.
//

#include <complex>
#include <iostream>
#include "mandelbrot.h"

using namespace mandelbrot;

const unsigned int MAX_ITERATIONS = 100;

static int highest_iter = 0;

static double highest_scaled_c = 0.0;

vector<array<double,3>> mandelbrot::plotBrot(unsigned int width, unsigned int height, double zoom) {
    // try to fit 2x2 box

    double imageAspect = height / (double)width;
    double x_min, x_max, y_min, y_max;

    if (imageAspect > 0) { // taller than wide
        x_min = -2;
        x_max = 2;

        y_max = imageAspect*2;
        y_min = -y_max;
    } else {
        y_min = -2;
        y_max = 2;

        x_max = imageAspect*2;
        x_min = -x_max;
    }

    vector<std::array<double,3>> data(width*height);

    for (auto x = 0; x < width; ++x) {
        double x_coord = (x_max - x_min) * x / width + x_min;
        for (auto y = 0; y < height; ++y) {
            double y_coord = (y_max - y_min) * y / height + y_min;

            setColorForPoint(x_coord, y_coord, data.at(x + y*width));
        }
    }

    cout << "Highest iteration: " << highest_iter << endl;

    cout << "Highest scaled c: " << highest_scaled_c << endl;

    return data;
}


void mandelbrot::setColorForPoint(double x0, double y0, std::array<double,3> &pixel) {
    unsigned int iterations = 0;

    complex<double> z{0,0}, z0{x0, y0};

    do {
        z = pow(z, 2) + z0;
        ++iterations;
    } while (abs(z) < 2.0 && iterations < MAX_ITERATIONS);

    std::array<int, 3> color{0};

    if (iterations > highest_iter && iterations < MAX_ITERATIONS)
        highest_iter = iterations;

    if (iterations == MAX_ITERATIONS) {
        pixel[0] = 0;
        pixel[1] = 0;
        pixel[2] = 0;
    } else {
        double c = iterations / (double)MAX_ITERATIONS;

        if (c > highest_scaled_c)
            highest_scaled_c = c;

        if (iterations < MAX_ITERATIONS / 4.0) {
            pixel[0] = c*4.0;
        } else if (iterations < MAX_ITERATIONS/2.0) {
            double scaled_c = 4.0*(c - 1/4.0);
            pixel[0] = 1.0 - scaled_c;
            pixel[2] = scaled_c;
        } else if (iterations < MAX_ITERATIONS*3.0/4.0) {
            double scaled_c = 4.0*(c - 0.5);
            pixel[2] = 1.0 - scaled_c;
            pixel[1] = scaled_c;
        } else {
            double scaled_c = 4.0*(c - 3.0/4.0);
            pixel[1] = scaled_c;
        }
    }
}