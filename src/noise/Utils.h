#ifndef UTILS_H
#define UTILS_H

#include <cmath>

namespace Noise
{
namespace Utils
{
    double lerp(double x0, double x1, double t);

    double blend_hermite(double x);

    double blend_quintic(double x);

    double bias(double b, double x);

    double gain(double gain, double x);

    double easeCurve(double t);

    double bilerp(double x0y0, double x1y0, double x0y1, double x1y1, double x, double y);

    double trilerp(double v000, double v100, double v010, double v110,
                   double v001, double v101, double v011, double v111,
                   double x, double y, double z);

    double contour(double v);

    double bound(double high, double low, double n);
} // end namespace Utils
} // end namespace Noise

#endif