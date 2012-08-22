#ifndef NOISEMODULE_H
#define NOISEMODULE_H

// a virtual base class for noise generators
// most have the common octaves, scale(zoom), persistence, and seed values
// the bounds might eventually get moves to their own Module

#include "Module.h"

namespace Noise
{

    class NoiseModule : public Module
    {
        protected:
            int m_seed;

            int m_octaves;
            double m_scale;
            double m_persitence;
            double m_lowBound;
            double m_highBound;
        public:
            NoiseModule(int seed);
            NoiseModule(int seed, int oct, double scale, double pers, double low, double high);
            ~NoiseModule();

            virtual double getValue(double x, double y) = 0;
            virtual double getValue(double x, double y, double z) = 0;

            virtual void setSeed(int s);
            virtual void setOctaves(int o);
            virtual void setScale(double s);
            virtual void setPersitence(double p);
            virtual void setBounds(double low, double high);
    };

} // end namespace Noise

#endif