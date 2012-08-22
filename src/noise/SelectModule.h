#ifndef SELECTMODULE_H
#define SELECTMODULE_H

#include "Module.h"

// a module that selects between two other modules based on the source module
// the threshold is the dividing line between the high and low sources
// the fall off is the area where the teo sources are blended together
// to create a smooth transition between them

namespace Noise
{

    class SelectModule : public Module
    {
        protected:
            Module *m_control;
            Module *m_lowSource;
            Module *m_highSource;

            double m_threshold;
            double m_falloff;
        public:
            SelectModule();
            SelectModule(Module *c, Module *low, Module *high, double t, double f);
            ~SelectModule();

            void setControlSource(Module *c);
            void setLowSource(Module *low);
            void setHighSource(Module *high);
            void setThreshold(double t);
            void setFalloff(double f);

            virtual double getValue(double x, double y);
            virtual double getValue(double x, double y, double z);
    };

} // end namespace Noise

#endif