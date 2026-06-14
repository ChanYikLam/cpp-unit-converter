#ifndef CONVERTER_WEIGHT_H
#define CONVERTER_WEIGHT_H

#include "../factor_converter.h"

class WeightConverter : public FactorConverter {
public:
    WeightConverter() : FactorConverter("重量") {
        addUnit("千克",          1.0);
        addUnit("克",           0.001);
        addUnit("毫克",          0.000001);
        addUnit("吨",   1000.0);
        addUnit("磅",          0.45359237);
        addUnit("盎司",          0.028349523125);
        addUnit("斤",         0.5);
    }
};

#endif
