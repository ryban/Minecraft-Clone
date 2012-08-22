#ifndef PERLIN_H
#define PERLIN_H

#include "Module.h"
#include "NoiseModule.h"

// the basic perlin noise module
// uses some prime number psuedo random number generator magic
// to get a random number based on coordinates and bi/tri linear
// interpolation to generate a noise vale for a given position

namespace Noise
{

    class PerlinModule : public NoiseModule
    {
        protected:
            double noise2d(int x, int y);
            double noise3d(int x, int y, int z);
            double noise2d_grad(double x, double y);
            double noise3d_grad(double x, double y, double z);
        public:
            PerlinModule(int s);
            PerlinModule(int seed, int oct, double scale, double pers, double low, double high);
            ~PerlinModule();

            virtual double getValue(double x, double y);
            virtual double getValue(double x, double y, double z);
    };

} // end namespace Noise

#endif