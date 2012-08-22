#ifndef CACHEMODULE_H
#define CACHEMODULE_H

#include "Module.h"

namespace Noise
{
    class CacheModule : public Module
    {
        protected:
            Module *m_source;

            bool m_stored_2d;
            double m_storedX_2d;
            double m_storedY_2d;
            double m_storedValue_2d;

            bool m_stored_3d;
            double m_storedX_3d;
            double m_storedY_3d;
            double m_storedZ_3d;
            double m_storedValue_3d;

        public:
            CacheModule(Module *source);
            ~CacheModule();

            virtual double getValue(double x, double y);
            virtual double getValue(double x, double y, double z);
    };

} // end namespace Noise

#endif