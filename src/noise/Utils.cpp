#include "Utils.h"

namespace Noise
{
namespace Utils
{
    // linear interpolation
	double lerp(double x0, double x1, double t)
    {
        return x0 + (x1-x0) * t;
    }
    // a blending function
    double blend_hermite(double x)
    {
        return (x*x*(3-2*x));
    }
    // another blending function
    double blend_quintic(double x)
    {
        return x*x*x*(x*(x*6-15)+10);
    }
    // bias a value x towards b
    double bias(double b, double x)
    {
        return pow(x, log(b)/log(0.5));
    }
    // apply a gain to x
    double gain(double gain, double x)
    {
        if(x < 0.5)
            return bias(1.0-gain, 2.0*x)/2.0;
        else
            return 1.0 - bias(1.0-gain, 2.0-2.0*x)/2.0;
    }
    // a blending function
    double easeCurve(double t)
    {
        return 6 * pow(t, 5) - 15 * pow(t, 4) + 10 * pow(t, 3);
    }
    // bilinear interpolation
    double bilerp(double x0y0, double x1y0, double x0y1, double x1y1, double x, double y)
    {
        double tx = easeCurve(x);
        double ty = easeCurve(y);

        double u = lerp(x0y0, x1y0, tx);
        double v = lerp(x0y1, x1y1, tx);

        return lerp(u, v, ty);
    }
    // trilinear interpolation
    double trilerp(double v000, double v100, double v010, double v110,
                   double v001, double v101, double v011, double v111,
                   double x, double y, double z)
    {
        double tx = x;
        double ty = y;
        double tz = z;

        return (
                v000*(1-tx)*(1-ty)*(1-tz) +
                v100*tx*(1-ty)*(1-tz) +
                v010*(1-tx)*ty*(1-tz) +
                v110*tx*ty*(1-tz) +
                v001*(1-tx)*(1-ty)*tz +
                v101*tx*(1-ty)*tz +
                v011*(1-tx)*ty*tz +
                v111*tx*ty*tz
                );
    }
    // blending function
    double contour(double v)
    {
        v = fabs(v);
        if(v >= 1.0)
            return 0.0;
        return 1.0 - v;
    }
    // bounds an input value n (assumed to be originally bounded to -1 to 1)
    // to low to high.
    double bound(double high, double low, double n)
    {
        return n * (high - low) / 2.0 + (high + low) / 2.0;
    }
} // endname space Utils
} // end namespace Noise