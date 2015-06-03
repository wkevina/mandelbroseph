#include <iostream>
#include <pngwriter.h>
#include <cxxopts.hpp>
#include <array>
#include "mandelbrot.h"

using namespace std;
using namespace cxxopts;

typedef unsigned int uint;

int main(int argc, char** argv) {



    Options option(argv[0], " - example command line options");

    double zoom;

    option.add_options()
            ("w,width", "Image width", cxxopts::value<int>()
                    ->default_value("400"), "N")
            ("h,height", "Image height", cxxopts::value<int>()
                    ->default_value("400"), "N")
            ("z,zoom", "Zoom multiplier", cxxopts::value<double>(zoom), "N");

    option.parse(argc, argv);

    uint width = option["width"].as<int>();
    uint height = option["height"].as<int>();

    vector< array<double,3> > data = mandelbrot::plotBrot(width, height, zoom);

    cout << "Width: " << width << " height: " << height << endl;

    pngwriter image(width, height, 0.0, "out.png");

    for (uint x = 0; x < width; ++x) {
        for (uint y = 0; y < height; ++y) {
            const uint index = x + y*width;
            const auto pixel = data.at(index);
            image.plot(x, y, pixel[0], pixel[1], pixel[2]);
        }
    }

    image.close();

    return 0;
}

