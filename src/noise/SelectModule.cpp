#include "SelectModule.h"
#include "Utils.h"

namespace Noise
{

    SelectModule::SelectModule()
    {
        m_control = 0;
        m_lowSource = 0;
        m_highSource = 0;

        m_threshold = 0.0;
        m_falloff = 0.0;
    }

    SelectModule::SelectModule(Module *c, Module *low, Module *high, double t, double f)
    {
        m_control = c;
        m_lowSource = low;
        m_highSource = high;

        m_threshold = t;
        m_falloff = f;
    }

    SelectModule::~SelectModule()
    {
        delete m_control;
        delete m_lowSource;
        delete m_highSource;
    }

    void SelectModule::setControlSource(Module *c)
    {
        m_control = c;
    }

    void SelectModule::setLowSource(Module *low)
    {
        m_lowSource = low;
    }

    void SelectModule::setHighSource(Module *high)
    {
        m_highSource = high;
    }

    void SelectModule::setThreshold(double t)
    {
        m_threshold = t;
    }

    void SelectModule::setFalloff(double f)
    {
        m_falloff = f;
    }

    double SelectModule::getValue(double x, double y)
    {
        double n = m_control->getValue(x, y);
        if(n > m_threshold + m_falloff)
            return m_highSource->getValue(x, y);
        else if(n < m_threshold - m_falloff)
            return m_lowSource->getValue(x, y);
        else
            return Utils::lerp(m_highSource->getValue(x, y), 
                               m_lowSource->getValue(x, y),
                               0.5);
    }

    double SelectModule::getValue(double x, double y, double z)
    {
        // always use 2d noise for the control
        double n = m_control->getValue(x, z);
        if(n > m_threshold + m_falloff)
            return m_highSource->getValue(x, y, z);
        else if(n < m_threshold - m_falloff)
            return m_lowSource->getValue(x, y, z);
        else
        {
            double upper = m_threshold + m_falloff;
            double lower = m_threshold - m_falloff;
            double blend = Utils::blend_quintic((n-lower)/(upper-lower));
            return Utils::lerp(m_lowSource->getValue(x, y, z),
                               m_highSource->getValue(x, y, z),
                               blend);
        }
    }

} // end namespace Noise