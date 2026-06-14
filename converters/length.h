#ifndef CONVERTER_LENGTH_H
#define CONVERTER_LENGTH_H

#include "../factor_converter.h"

class LengthConverter : public FactorConverter {
public:
    LengthConverter() : FactorConverter("长度") {
        addUnit("米",          1.0);
        addUnit("千米",         1000.0);
        addUnit("厘米",         0.01);
        addUnit("毫米",         0.001);
        addUnit("英里",       1609.344);
        addUnit("码",       0.9144);
        addUnit("英尺",       0.3048);
        addUnit("英寸",       0.0254);
        addUnit("里",         500.0);
    }
};

#endif
