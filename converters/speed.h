#ifndef CONVERTER_SPEED_H
#define CONVERTER_SPEED_H

#include "../factor_converter.h"

class SpeedConverter : public FactorConverter {
public:
    SpeedConverter() : FactorConverter("\xe9\x80\x9f\xe5\xba\xa6 (Speed)") {
        addUnit("m/s",          1.0);
        addUnit("km/h",         0.2777777778);
        addUnit("mph",          0.44704);
        addUnit("knot",         0.5144444444);
        addUnit("mach",         340.2933);
    }
};

#endif
