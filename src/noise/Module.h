#ifndef MODULE_H
#define MODULE_H

namespace Noise
{

    class Module
    {
        public:
            Module();
            ~Module();

            virtual double getValue(double x, double y) = 0;
            virtual double getValue(double x, double y, double z) = 0;
    };

} // end namespace Noise

#endif