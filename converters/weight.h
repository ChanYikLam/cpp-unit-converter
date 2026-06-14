#ifndef CONVERTER_WEIGHT_H
#define CONVERTER_WEIGHT_H

#include "../factor_converter.h"

class WeightConverter : public FactorConverter {
public:
    WeightConverter() : FactorConverter("\xe9\x87\x8d\xe9\x87\x8f (Weight)") {
        addUnit("kg",          1.0);
        addUnit("g",           0.001);
        addUnit("mg",          0.000001);
        addUnit("t(metric)",   1000.0);
        addUnit("lb",          0.45359237);
        addUnit("oz",          0.028349523125);
        addUnit("jin",         0.5);
    }
};

#endif
