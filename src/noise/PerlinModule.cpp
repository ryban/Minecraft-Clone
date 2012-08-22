#include "PerlinModule.h"
#include "Utils.h"

#include <cmath>

namespace Noise
{

    const int PRIME_X = 1619;
    const int PRIME_Y = 31337;
    const int PRIME_Z = 52591;
    const int PRIME_SEED = 1013;

    PerlinModule::PerlinModule(int s) : NoiseModule(s)
    {
    }

    PerlinModule::PerlinModule(int seed, int oct, double scale, double pers, double low, double high)
    : NoiseModule(seed, oct, scale, pers, low, high)
    {
    }

    PerlinModule::~PerlinModule()
    {
    }

    double PerlinModule::noise2d(int x, int y)
    {
        int n = PRIME_X * x + PRIME_Y * y + PRIME_SEED * m_seed;
        n &= 0x7fffffff;
        n = (n >> 13) ^ n;
        n = (n * (n*n*60493+19990303) + 1376312589) & 0x7fffffff;
        return (1.0 - (double)n/1073741824.0);
    }

    double PerlinModule::noise3d(int x, int y, int z)
    {
        int n = PRIME_X * x + PRIME_Y * y + PRIME_Z * z + PRIME_SEED * m_seed;
        n &= 0x7fffffff;
        n = (n >> 13) ^ n;
        n = (n * (n*n*60493+19990303) + 1376312589) & 0x7fffffff;
        return (1.0 - (double)n/1073741824.0);
    }

    double PerlinModule::noise2d_grad(double x, double y)
    {
        int x0 = x > 0.0 ? (int)x : (int)x-1;
        int y0 = y > 0.0 ? (int)y : (int)y-1;

        double x1 = x - (double)x0;
        double y1 = y - (double)y0;

        double v00 = noise2d(x0, y0);
        double v10 = noise2d(x0+1, y0);
        double v01 = noise2d(x0, y0+1);
        double v11 = noise2d(x0+1, y0+1);

        return Utils::bilerp(v00, v10, v01, v11, x1, y1);
    }

    double PerlinModule::noise3d_grad(double x, double y, double z)
    {
        int x0 = x > 0.0 ? (int)x : (int)x-1;
        int y0 = y > 0.0 ? (int)y : (int)y-1;
        int z0 = z > 0.0 ? (int)z : (int)z-1;

        double x1 = x - (double)x0;
        double y1 = y - (double)y0;
        double z1 = z - (double)z0;

        double v000 = noise3d(x0, y0, z0);
        double v100 = noise3d(x0+1, y0, z0);
        double v010 = noise3d(x0, y0+1, z0);
        double v110 = noise3d(x0+1, y0+1, z0);
        double v001 = noise3d(x0, y0, z0+1);
        double v101 = noise3d(x0+1, y0, z0+1);
        double v011 = noise3d(x0, y0+1, z0+1);
        double v111 = noise3d(x0+1, y0+1, z0+1);

        return Utils::trilerp(v000, v100, v010, v110, v001, v101, v011, v111, x1, y1, z1);
    }

    double PerlinModule::getValue(double x, double y)
    {
        x *= m_scale;
        y *= m_scale;

        double n = 0.0;
        double f = 1.0;
        double amp = 1.0;

        for(int i = 0; i < m_octaves; i++)
        {
            n += amp * noise2d_grad(x*f, y*f);
            f *= 2.0;
            amp *= m_persitence;
        }
        return Utils::bound(m_lowBound, m_highBound, n);
    }

    double PerlinModule::getValue(double x, double y, double z)
    {
        x *= m_scale;
        y *= m_scale;
        z *= m_scale;

        double n = 0.0;
        double f = 1.0;
        double amp = 1.0;

        for(int i = 0; i < m_octaves; i++)
        {
            n += amp * noise3d_grad(x*f, y*f, z*f);
            f *= 2.0;
            amp *= m_persitence;
        }
        return Utils::bound(m_lowBound, m_highBound, n);
    }

} // end namespace Noise