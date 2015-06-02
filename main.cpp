#include <iostream>
#include <pngwriter.h>
#include <cxxopts.hpp>

using namespace std;

int main() {
    pngwriter image(800, 600, 0.0, "out.png");

    image.plot(400, 300, 1.0, 0.0, 0.0);

    image.close();

    cout << "Hello, World!" << endl;
    return 0;
}