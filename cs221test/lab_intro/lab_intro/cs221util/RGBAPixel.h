/**
 * @file RGBA.h
 */

#ifndef CS221UTIL_RGBAPixel_H
#define CS221UTIL_RGBAPixel_H

using namespace std;

namespace cs221util {
    class RGBAPixel{
        public:
        unsigned char r;
        unsigned char g;
        unsigned char b;
        double a;

        public:

        RGBAPixel();
        RGBAPixel(int red, int green, int blue);
        RGBAPixel(int red, int green, int blue, double alpha);
    };
}

#endif