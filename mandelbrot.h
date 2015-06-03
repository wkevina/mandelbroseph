//
// Created by Kevin Ward on 6/2/15.
//

#ifndef MANDELBROSEPH_MANDELBROT_H
#define MANDELBROSEPH_MANDELBROT_H

#include <array>
#include <vector>

using namespace std;

namespace mandelbrot {
    vector<array<double,3>> plotBrot(unsigned int width, unsigned int height, double zoom);

    void setColorForPoint(double x0, double y0, std::array<double,3> &pixel);
}


#endif //MANDELBROSEPH_MANDELBROT_H
