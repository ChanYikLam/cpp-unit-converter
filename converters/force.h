#ifndef CONVERTER_FORCE_H
#define CONVERTER_FORCE_H

#include "../factor_converter.h"

class ForceConverter : public FactorConverter {
public:
    ForceConverter() : FactorConverter("力") {
        addUnit("牛(N)",            1.0);
        addUnit("千牛(kN)",           1000.0);
        addUnit("达因(dyne)",         0.00001);
        addUnit("磅力(lbf)",          4.448221615);
        addUnit("千克力(kgf)",          9.80665);
    }
};

#endif
