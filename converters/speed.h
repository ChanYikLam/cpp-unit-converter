#ifndef CONVERTER_SPEED_H
#define CONVERTER_SPEED_H

#include "../factor_converter.h"

class SpeedConverter : public FactorConverter {
public:
    SpeedConverter() : FactorConverter("速度") {
        addUnit("米/秒",          1.0);
        addUnit("千米/时",         0.2777777778);
        addUnit("英里/时",          0.44704);
        addUnit("节",         0.5144444444);
        addUnit("马赫",         340.2933);
    }
};

#endif
