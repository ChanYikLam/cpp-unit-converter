#ifndef CONVERTER_FORCE_H
#define CONVERTER_FORCE_H

#include "../factor_converter.h"

class ForceConverter : public FactorConverter {
public:
    ForceConverter() : FactorConverter("\xe5\x8a\x9b (Force)") {
        addUnit("N",            1.0);
        addUnit("kN",           1000.0);
        addUnit("dyne",         0.00001);
        addUnit("lbf",          4.448221615);
        addUnit("kgf",          9.80665);
    }
};

#endif
