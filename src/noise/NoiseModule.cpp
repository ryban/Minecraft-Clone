#include "NoiseModule.h"

namespace Noise
{

    NoiseModule::NoiseModule(int seed)
    {
        m_seed = seed;
        m_octaves = 1;
        m_scale = 1.0;
        m_persitence = 1.0;
        m_highBound = 1.0;
        m_lowBound = -1.0;
    }

    NoiseModule::NoiseModule(int seed, int oct, double scale, double pers, double low, double high)
    {
        m_seed = seed;
        m_octaves = oct;
        m_scale = scale;
        m_persitence = pers;
        m_highBound = high;
        m_lowBound = low;
    }

    NoiseModule::~NoiseModule()
    {
    }

    void NoiseModule::setSeed(int s)
    {
        m_seed = s;
    }

    void NoiseModule::setOctaves(int o)
    {
        m_octaves = o;
    }

    void NoiseModule::setScale(double s) 
    {
        m_scale = s;
    }

    void NoiseModule::setPersitence(double p)
    {
        m_persitence = p;
    }

    void NoiseModule::setBounds(double low, double high) 
    {
        m_lowBound = low;
        m_highBound = high;
    }

} // end namespace Noise